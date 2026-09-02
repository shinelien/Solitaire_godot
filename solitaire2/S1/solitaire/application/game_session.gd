class_name GameSession
extends RefCounted

## RefCounted application-layer session over one live deal (WP-07). It owns the
## private current GameState, the current deal identity (pool/index/draw mode)
## and its SnapshotHistory. It is never a Node and never enters the SceneTree.
##
## Every state transition is an explicit Move/MoveBatch executed through
## MoveExecutor: apply_move uses execute, undo uses execute_undo, and replay /
## new deal use the dedicated execute_boundary entrypoint (there is no hidden
## direct GameState assignment from application code). hint() and
## plan_auto_complete() are read-only: they delegate to the non-mutating
## HintEngine / AutoCompletePlanner and never touch _state or _history.
##
## External state access is clone-only: state_snapshot() and every returned
## MoveExecutionResult.new_state is a fresh deep clone, so no caller can mutate
## the session's owned state through a getter.

func _init() -> void:
	_state = GameState.new()
	_history = SnapshotHistory.new()


static func create(pool: String, index: int, draw_count: int) -> GameSessionResult:
	if not LegacyDealRepository.is_known_pool(pool):
		return GameSessionResult.failure(
			GameSessionResult.CODE_INVALID_POOL,
			"unknown pool '%s'" % pool
		)
	var ready := LegacyDealer.deal_ready(pool, index, draw_count)
	if not ready.ok:
		return GameSessionResult.failure(ready.error_code, ready.error_message)
	var session := GameSession.new()
	session._pool = pool
	session._index = index
	session._draw_count = draw_count
	session._state = ready.state
	session._history.clear()
	return GameSessionResult.success(session)


# ----- read-only identity / state getters (all clone-safe) -----

func deal_pool() -> String:
	return _pool


func deal_index() -> int:
	return _index


func draw_count() -> int:
	return _draw_count


func deal_key() -> String:
	return "%s#%d" % [_pool, _index]


## Fresh deep clone of the owned current state.
func state_snapshot() -> GameState:
	return _state.clone()


func history_size() -> int:
	return _history.size()


func can_undo() -> bool:
	return _history.can_undo()


# ----- transitions (all explicit Move/MoveBatch via MoveExecutor) -----

## Apply one ordinary gameplay move through MoveExecutor.execute. Boundary
## identities (UNDO/REPLAY/NEW_DEAL) are rejected by the executor with a typed
## invalid_kind — use undo()/replay()/new_deal() instead.
func apply_move(move: Move) -> MoveExecutionResult:
	var result := MoveExecutor.execute(_state, move, _history)
	if not result.ok:
		return result
	_state = result.new_state
	return _adopt(result.batch)


## Undo the previous action through MoveExecutor.execute_undo.
func undo() -> MoveExecutionResult:
	if not _history.can_undo():
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_NOTHING_TO_UNDO,
			"no snapshot to undo in this session"
		)
	var result := MoveExecutor.execute_undo(_state, _history)
	if not result.ok:
		return result
	_state = result.new_state
	return _adopt(result.batch)


## Replay: deterministically re-deal the exact same pool/index/draw_count ready
## state through the REPLAY boundary, resetting counters (a fresh ready deal
## has move_count/score/stock_passes at zero) and clearing history.
func replay() -> MoveExecutionResult:
	var ready := LegacyDealer.deal_ready(_pool, _index, _draw_count)
	if not ready.ok:
		return MoveExecutionResult.failure(ready.error_code, ready.error_message)
	var result := MoveExecutor.execute_boundary(_state, ready.state, Move.replay())
	if not result.ok:
		return result
	_state = result.new_state
	_history.clear()
	return _adopt(result.batch)


## New deal: deterministically select (current_index + 1) mod pool_count,
## re-deal that ready state through the NEW_DEAL boundary and clear history.
## Same pool and draw mode are preserved; wrap around is explicit.
func new_deal() -> MoveExecutionResult:
	var count := LegacyDealRepository.record_count(_pool)
	if count < 0:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_STATE,
			"cannot read pool '%s' record count" % _pool
		)
	var selection := DeterministicDealSelector.next_index(_index, count)
	if not selection.get("ok", false):
		return MoveExecutionResult.failure(
			selection.get("error_code", MoveExecutionResult.CODE_INVALID_STATE),
			selection.get("error_message", "cannot select the next deal index")
		)
	var next_index := int(selection.get("next_index", -1))
	var ready := LegacyDealer.deal_ready(_pool, next_index, _draw_count)
	if not ready.ok:
		return MoveExecutionResult.failure(ready.error_code, ready.error_message)
	var result := MoveExecutor.execute_boundary(_state, ready.state, Move.new_deal())
	if not result.ok:
		return result
	_state = result.new_state
	_index = next_index
	_history.clear()
	return _adopt(result.batch)


# ----- read-only hints / plans (delegate to non-mutating services) -----

func hint() -> HintResult:
	return HintEngine.hint(_state)


func plan_auto_complete() -> AutoCompletePlanResult:
	return AutoCompletePlanner.plan(_state)


# ----- internals -----

var _pool: String = ""
var _index: int = -1
var _draw_count: int = GameState.DRAW1
var _state: GameState = null
var _history: SnapshotHistory = null


## Build the caller-visible success result from the executor batch: new_state
## is a fresh deep clone of the adopted internal state, never the internal one.
func _adopt(batch: MoveBatch) -> MoveExecutionResult:
	return MoveExecutionResult.success(_state.clone(), batch)
