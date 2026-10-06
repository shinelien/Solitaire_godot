class_name MoveExecutor
extends RefCounted

## 不可变执行器（纯数据，无 Node 依赖）。每次对局中状态的成功变更
## 都由显式 Move/MoveBatch 表示，并在源状态的深克隆上执行；
## 源 GameState 绝不被修改，与结果之间不共享任何 CardData/CardPile。
## 失败时不会暴露任何被改动状态。自动生成的 tableau 翻牌是列于批次中的
## 显式 FLIP_TABLEAU 移动。撤销通过 execute_undo() 作为类型化动作暴露：
## 弹出 SnapshotHistory 中的快照并返回克隆的还原状态，不做直接状态修改。

const CODE_OK := MoveExecutionResult.CODE_OK
const CODE_INTERNAL := MoveExecutionResult.CODE_INTERNAL


## 在 `state` 的克隆上执行一个用户请求的移动。
## `history`（可选）仅在成功时记录动作前的深快照。
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

	## 仅当移动使某列新暴露出一张盖牌顶时，才生成自动翻牌
	## （列已空或顶牌仍为翻开时不会生成）。
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


## 撤销最近一次成功的用户批次：弹出动作前快照并返回其全新克隆
## （牌面与动作前完全一致），随后应用显式旧版撤销策略
## （扣 2 分、下限为 0，并计作一次用户操作）。绝不重建牌位。
## 历史为空时返回类型化失败。
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


## 专用会话边界入口（WP-07）：把新发好、就绪的 `target` 状态深克隆后返回，
## 并附带显式 REPLAY / NEW_DEAL 边界批次。它从不调用规则引擎的游戏校验
## （这些身份不是游戏移动），也不修改任一入参；刻意不动 SnapshotHistory，
## 因为 GameSession 在每次边界转换时都会清空历史。
## `current_state` 仅为统一签名而接收，实际不会被读取。
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


# ----- 状态应用（可信路径：仅在 RulesEngine 校验通过后调用）-----

## 按移动种类把动作应用到（克隆后的）状态上。
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


## 应用 tableau 列间连牌移动：从源列顶部取 count 张依次加到目标列顶。
static func _apply_tableau_run(state: GameState, from_col: int, to_col: int, count: int) -> void:
	var moved := state.tableau_pile(from_col).pop_top_n(count)
	for card in moved:
		state.tableau_pile(to_col).add_top(card)


## 应用 tableau 顶牌 → foundation：取牌、确保翻开、放入目标槽。
static func _apply_tableau_to_foundation(state: GameState, from_col: int, slot: int) -> void:
	var card := state.tableau_pile(from_col).pop_top()
	if card != null:
		card.face_up = true
		state.foundation_pile(slot).add_top(card)


## 应用 waste 顶牌 → tableau 列。
static func _apply_waste_to_tableau(state: GameState, to_col: int) -> void:
	var card := state.waste.pop_top()
	if card != null:
		state.tableau_pile(to_col).add_top(card)


## 应用 waste 顶牌 → foundation（放入前确保翻开）。
static func _apply_waste_to_foundation(state: GameState, slot: int) -> void:
	var card := state.waste.pop_top()
	if card != null:
		card.face_up = true
		state.foundation_pile(slot).add_top(card)


## 应用 foundation 顶牌退回 tableau 列（顶牌在基础堆中恒为翻开）。
static func _apply_foundation_to_tableau(state: GameState, from_slot: int, to_col: int) -> void:
	var card := state.foundation_pile(from_slot).pop_top()
	if card != null:
		state.tableau_pile(to_col).add_top(card)


## 翻牌：从 stock 顶弹出 min(draw_count, 剩余数) 张翻开牌放入 waste
## （与发牌就绪态自动翻牌完全一致，保证执行器翻牌可精确复现夹具就绪 waste）。
static func _apply_draw(state: GameState) -> void:
	var n := mini(state.draw_count, state.stock.size())
	for i in n:
		var card := state.stock.pop_top()
		if card == null:
			break
		card.face_up = true
		state.waste.add_top(card)


## 整堆重翻：从 waste 顶逐张弹出并作为盖牌追加到 stock，直到 waste 清空，
## 然后 stock_passes 加 1。该过程还原了确定的 stock 顺序，
## 使下一次翻牌重现完全相同的 waste 分组，保证翻牌循环可无限稳定循环。
static func _apply_recycle(state: GameState) -> void:
	while not state.waste.is_empty():
		var card := state.waste.pop_top()
		card.face_up = false
		state.stock.add_top(card)
	state.stock_passes += 1


## 移动从 tableau 列取走牌后，若该列新暴露的顶牌为盖牌，则返回该列号
## 作为自动翻牌候选；其它移动种类返回 -1（不生成翻牌）。
static func _flip_candidate_column(move: Move) -> int:
	if move.kind == Move.MoveKind.TABLEAU_TO_TABLEAU or move.kind == Move.MoveKind.TABLEAU_TO_FOUNDATION:
		return move.source_index
	return -1
