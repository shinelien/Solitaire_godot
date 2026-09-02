class_name MoveExecutor
extends RefCounted

## Immutable executor (pure data, no Node deps). Every successful ongoing-state
## change is represented by an explicit Move/MoveBatch and is performed on a
## deep clone of the source state; the source GameState is never mutated and
## shares no CardData/CardPile with the result. On failure no changed state is
## exposed. Generated automatic tableau flips are explicit FLIP_TABLEAU moves
## listed in the batch. Undo is exposed as a typed action through
## execute_undo(), which pops SnapshotHistory and returns a cloned restored
## state without direct GameState mutation.

const CODE_OK := MoveExecutionResult.CODE_OK
const CODE_INTERNAL := MoveExecutionResult.CODE_INTERNAL


## Execute one requested user move on a clone of `state`.
## `history` (optional) records the pre-action deep snapshot on success only.
static func execute(state: GameState, move: Move, history: SnapshotHistory = null) -> MoveExecutionResult:
	if state == null:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_STATE,
			"cannot execute a move against a null state"
		)
	if move == null:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_STATE,
			"move is null"
		)

	var validation := RulesEngine.validate(state, move)
	if not validation.ok:
		return MoveExecutionResult.failure(
			validation.error_code,
			validation.error_message,
			validation
		)

	var working := state.clone()
	var generated: Array[Move] = []
	_apply(working, move)

	## A flip is generated only when the move leaves a newly exposed face-down
	## tableau top (never when the column is empty or still face-up).
	var flip_col := _flip_candidate_column(move)
	if flip_col >= 0:
		var pile := working.tableau_pile(flip_col)
		if pile != null and not pile.is_empty() and not pile.top().face_up:
			var flip := Move.flip_tableau(flip_col)
			var flip_validation := RulesEngine.validate(working, flip)
			if not flip_validation.ok:
				return MoveExecutionResult.failure(
					CODE_INTERNAL,
					"generated flip %s rejected: %s" % [flip.description(), flip_validation.error_message],
					flip_validation
				)
			_apply(working, flip)
			generated.append(flip)

	var batch := MoveBatch.from_moves(move, generated)
	working.score = LegacyScorePolicy.apply_batch(working.score, batch)
	working.move_count += 1
	WinEvaluator.update_status(working)

	if history != null:
		history.push(state)

	return MoveExecutionResult.success(working, batch)


## Undo the most recent successful user batch: pops the pre-action snapshot,
## returns a fresh clone with the exact pre-action board, then applies the
## explicit legacy undo policy (score -2 floored at zero, counted as one user
## action). Positions are never reconstructed. Empty history is a typed
## failure.
static func execute_undo(state: GameState, history: SnapshotHistory) -> MoveExecutionResult:
	if history == null or not history.can_undo():
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_NOTHING_TO_UNDO,
			"no snapshot to undo"
		)
	var snapshot := history.pop()
	if snapshot == null:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_NOTHING_TO_UNDO,
			"no snapshot to undo"
		)
	snapshot.score = LegacyScorePolicy.undo_score(snapshot.score)
	snapshot.move_count += 1
	var batch := MoveBatch.undo_batch()
	return MoveExecutionResult.success(snapshot, batch)


## Dedicated session-boundary entrypoint (WP-07): restores a freshly dealt ready
## `target` state as a deep clone and returns it together with an explicit
## REPLAY / NEW_DEAL boundary batch. It never calls RulesEngine gameplay
## validation (these identities are not gameplay moves) and it never mutates
## either input; SnapshotHistory is intentionally left untouched because the
## GameSession clears its history on every boundary transition. The current
## state is accepted for a uniform signature but is not read.
static func execute_boundary(current_state: GameState, target: GameState, boundary: Move) -> MoveExecutionResult:
	if current_state == null:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_STATE,
			"cannot apply a session boundary to a null current state"
		)
	if target == null:
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_STATE,
			"cannot apply a session boundary to a null target state"
		)
	if boundary == null or (boundary.kind != Move.MoveKind.REPLAY and boundary.kind != Move.MoveKind.NEW_DEAL):
		return MoveExecutionResult.failure(
			MoveExecutionResult.CODE_INVALID_KIND,
			"boundary move must be a REPLAY or NEW_DEAL identity, not %s" % (boundary.description() if boundary != null else "null")
		)
	var restored := target.clone()
	var batch := MoveBatch.from_moves(boundary)
	return MoveExecutionResult.success(restored, batch)


# ----- application (trusted: only called after RulesEngine validated) -----

static func _apply(state: GameState, move: Move) -> void:
	match move.kind:
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			_apply_tableau_run(state, move.source_index, move.target_index, move.count)
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			_apply_tableau_to_foundation(state, move.source_index, move.target_index)
		Move.MoveKind.WASTE_TO_TABLEAU:
			_apply_waste_to_tableau(state, move.target_index)
		Move.MoveKind.WASTE_TO_FOUNDATION:
			_apply_waste_to_foundation(state, move.target_index)
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			_apply_foundation_to_tableau(state, move.source_index, move.target_index)
		Move.MoveKind.DRAW_STOCK:
			_apply_draw(state)
		Move.MoveKind.RECYCLE_STOCK:
			_apply_recycle(state)
		Move.MoveKind.FLIP_TABLEAU:
			state.tableau_pile(move.source_index).top().face_up = true
		_:
			push_warning("MoveExecutor._apply called with unhandled move kind %d" % move.kind)


static func _apply_tableau_run(state: GameState, from_col: int, to_col: int, count: int) -> void:
	var moved := state.tableau_pile(from_col).pop_top_n(count)
	for card in moved:
		state.tableau_pile(to_col).add_top(card)


static func _apply_tableau_to_foundation(state: GameState, from_col: int, slot: int) -> void:
	var card := state.tableau_pile(from_col).pop_top()
	if card != null:
		card.face_up = true
		state.foundation_pile(slot).add_top(card)


static func _apply_waste_to_tableau(state: GameState, to_col: int) -> void:
	var card := state.waste.pop_top()
	if card != null:
		state.tableau_pile(to_col).add_top(card)


static func _apply_waste_to_foundation(state: GameState, slot: int) -> void:
	var card := state.waste.pop_top()
	if card != null:
		card.face_up = true
		state.foundation_pile(slot).add_top(card)


static func _apply_foundation_to_tableau(state: GameState, from_slot: int, to_col: int) -> void:
	var card := state.foundation_pile(from_slot).pop_top()
	if card != null:
		state.tableau_pile(to_col).add_top(card)


## Stock draw: pop min(draw_count, remaining) face-up cards off the stock top
## into the waste (identical to the deal_ready auto-draw so executor draws
## reproduce the fixture-ready waste exactly).
static func _apply_draw(state: GameState) -> void:
	var n := mini(state.draw_count, state.stock.size())
	for i in n:
		var card := state.stock.pop_top()
		if card == null:
			break
		card.face_up = true
		state.waste.add_top(card)


## Recycle: pop the waste top and append face-down to the stock until the
## waste is empty, then count one stock pass. This restores the deterministic
## stock order so the next draw reproduces the exact same waste group, keeping
## the draw cycle stable across unlimited passes.
static func _apply_recycle(state: GameState) -> void:
	while not state.waste.is_empty():
		var card := state.waste.pop_top()
		card.face_up = false
		state.stock.add_top(card)
	state.stock_passes += 1


## After a move removes cards from a tableau column, a flip is generated when a
## face-down card is newly exposed as that column's top.
static func _flip_candidate_column(move: Move) -> int:
	if move.kind == Move.MoveKind.TABLEAU_TO_TABLEAU or move.kind == Move.MoveKind.TABLEAU_TO_FOUNDATION:
		return move.source_index
	return -1
