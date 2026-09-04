class_name GameSession
extends RefCounted

## 单局进行中牌局的 RefCounted 应用层会话（WP-07）。持有私有的当前
## GameState、当前牌局身份（牌池/序号/翻牌模式）与 SnapshotHistory。
## 它永远不是 Node，也绝不进入场景树。
##
## 每个状态转换都是经 MoveExecutor 执行的显式 Move/MoveBatch：
## apply_move 走 execute，undo 走 execute_undo，
## 重开/新牌局走专用 execute_boundary 入口
## （应用代码不存在隐藏的直接 GameState 赋值）。
## hint() 与 plan_auto_complete() 为只读：委托给不修改状态的
## HintEngine / AutoCompletePlanner，绝不触碰 _state 或 _history。
##
## 外部状态访问只走克隆：state_snapshot() 与每个返回的
## MoveExecutionResult.new_state 都是全新深克隆，
## 因此调用方无法通过 getter 修改会话持有的状态。

## 构造空会话：初始化空白状态与历史栈。
func _init() -> void:
	_state = GameState.new()
	_history = SnapshotHistory.new()


## 会话工厂：从命名牌池 + 序号 + 翻牌模式发牌并构造就绪会话。
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


# ----- 只读身份/状态访问器（全部克隆安全）-----

## 当前牌池名。
func deal_pool() -> String:
	return _pool


## 当前牌局在牌池中的序号。
func deal_index() -> int:
	return _index


## 当前翻牌模式（1 或 3）。
func draw_count() -> int:
	return _draw_count


## 当前牌局的稳定标识，如 "bureau1#0"。
func deal_key() -> String:
	return "%s#%d" % [_pool, _index]


## 返回所持当前状态的深克隆。
func state_snapshot() -> GameState:
	return _state.clone()


## 历史中已记录的快照数量（可用于撤销计数）。
func history_size() -> int:
	return _history.size()


## 当前是否可撤销。
func can_undo() -> bool:
	return _history.can_undo()


# ----- 状态转换（全部经 MoveExecutor 执行显式 Move/MoveBatch）-----

## 通过 MoveExecutor.execute 应用一个普通游戏移动。
## 边界身份（UNDO/REPLAY/NEW_DEAL）会被执行器以类型化 invalid_kind 拒绝，
## 请改用 undo()/replay()/new_deal()。
func apply_move(move: Move) -> MoveExecutionResult:
	var result := MoveExecutor.execute(_state, move, _history)
	if not result.ok:
		return result
	_state = result.new_state
	return _adopt(result.batch)


## 通过 MoveExecutor.execute_undo 撤销上一次用户操作。
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


## 重开当前牌局：以 REPLAY 边界确定性重新发同一
## pool/index/draw_count 的就绪状态，重置计数器
## （新就绪牌局的 move_count/score/stock_passes 均为 0）并清空历史。
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


## 新牌局：确定性选择 (current_index + 1) mod pool_count，
## 以 NEW_DEAL 边界重新发该就绪状态并清空历史。
## 保留原牌池与翻牌模式；绕回（wrap around）行为是显式的。
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


## 显式、文档化的非产品接缝（WP-08）：构建一个当前状态为调用方提供的
## 完整 52 张 GameState 深克隆的会话（仅供 MCP 运行时验收矩阵经应用层
## 装载受控的近胜/混合牌面使用）。此后的每次转换仍与真实牌局一样
## 流经 MoveExecutor。玩家主循环绝不会调用它；
## 身份被标记为合成调试牌局。
## 发布边界：以 “editor” 特性硬性门控——编辑器之外一律返回
## 类型化失败，绝不构造调试会话。
static func debug_create_state(state: GameState, draw_mode: int) -> GameSessionResult:
	if not OS.has_feature("editor"):
		return GameSessionResult.failure(
			GameSessionResult.CODE_INVALID_STATE,
			"debug_create_state is editor-only and refused in a release build"
		)
	if state == null:
		return GameSessionResult.failure(
			GameSessionResult.CODE_INVALID_STATE,
			"cannot build a debug session from a null state"
		)
	if draw_mode != GameState.DRAW1 and draw_mode != GameState.DRAW3:
		return GameSessionResult.failure(
			GameSessionResult.CODE_INVALID_DRAW_COUNT,
			"draw_count must be 1 or 3"
		)
	if state.total_card_count() != 52:
		return GameSessionResult.failure(
			GameSessionResult.CODE_INVALID_STATE,
			"debug state must hold all 52 cards (found %d)" % state.total_card_count()
		)
	var seen := PackedByteArray()
	seen.resize(52)
	for id in state.all_card_ids():
		if id < 0 or id > 51 or seen[id] == 1:
			return GameSessionResult.failure(
				GameSessionResult.CODE_INVALID_STATE,
				"debug state must be a full permutation of ids 0..51"
			)
		seen[id] = 1
	var session := GameSession.new()
	session._pool = "debug"
	session._index = -1
	session._draw_count = draw_mode
	session._state = state.clone()
	session._history.clear()
	return GameSessionResult.success(session)


# ----- 只读提示/自动完成（委托给非修改型服务）-----

## 对当前状态求一个合法提示移动（只读）。
func hint() -> HintResult:
	return HintEngine.hint(_state)


## 对当前状态规划自动完成步骤（只读）。
func plan_auto_complete() -> AutoCompletePlanResult:
	return AutoCompletePlanner.plan(_state)


# ----- 内部状态 -----

## 当前牌池名。
var _pool: String = ""
## 当前牌局在牌池中的序号。
var _index: int = -1
## 当前翻牌模式（1/3）。
var _draw_count: int = GameState.DRAW1
## 会话私有的当前牌局状态（绝不出现在 getter 返回值中）。
var _state: GameState = null
## 撤销历史栈。
var _history: SnapshotHistory = null


## 由执行器批次构建返回给调用方的成功结果：
## new_state 是已采纳内部状态的全新深克隆，绝非内部对象本身。
func _adopt(batch: MoveBatch) -> MoveExecutionResult:
	return MoveExecutionResult.success(_state.clone(), batch)
