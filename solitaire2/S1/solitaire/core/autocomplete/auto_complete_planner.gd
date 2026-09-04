class_name AutoCompletePlanner
extends RefCounted

## 确定性、必然终止的自动完成“规划器”（纯服务，无 Node 依赖，WP-07）。
## 它刻意不是第二套规则引擎/执行器：模拟时只把选出的普通移动经
## MoveExecutor 在深克隆上执行，因此源 GameState 与 SnapshotHistory
## 永不被触碰。
##
## 允许产出的移动（仅限普通游戏种类）：
##   TABLEAU_TO_FOUNDATION、WASTE_TO_FOUNDATION、DRAW_STOCK、RECYCLE_STOCK。
## 它绝不产出 tableau 重排、foundation 回退、直接 FLIP_TABLEAU、
## 牌身份变更或任何仅自动模式专用修改。
##
## 终止性：模拟受文档化的最大步数（>=512）与规范牌局签名约束
## （签名含各容器牌身份 + 翻面状态 + 翻牌模式；刻意排除计数器，
## 以便捕获 重翻/翻牌 的循环）。签名重复 → 类型化 no_progress；
## 步数用尽 → max_steps；无可用移动 → no_legal_move。
## 所有结果均为类型化 AutoCompletePlanResult，规划器绝不卡死。

const MAX_STEPS := 2048


## 自动完成规划入口：返回可达的确定性收牌计划。
## 前置条件：所有 tableau 牌均已翻开（否则不可执行）。
static func plan(state: GameState) -> AutoCompletePlanResult:
	if state == null:
		return AutoCompletePlanResult.not_eligible(
			AutoCompletePlanResult.CODE_INVALID_STATE,
			"cannot auto-complete a null state"
		)
	if state.game_status == GameState.GameStatus.WON:
		return AutoCompletePlanResult.eligible_result(
			true,
			AutoCompletePlanResult.STOP_WON,
			"game already won",
			[],
			state,
			0,
			1
		)
	if not _all_tableau_face_up(state):
		return AutoCompletePlanResult.not_eligible(
			AutoCompletePlanResult.CODE_TABLEAU_NOT_FACE_UP,
			"auto-complete requires every tableau card face-up"
		)

	var working := state.clone()
	var plan_moves: Array[Move] = []
	var visited := {}
	var steps := 0
	while true:
		var sig := _signature(working)
		if visited.has(sig):
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_PROGRESS,
				"state signature repeated; no foundation progress possible within a deterministic cycle",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		visited[sig] = true
		if working.game_status == GameState.GameStatus.WON:
			return AutoCompletePlanResult.eligible_result(
				true,
				AutoCompletePlanResult.STOP_WON,
				"all four foundations are complete",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		if steps >= MAX_STEPS:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_MAX_STEPS,
				"step budget of %d exhausted without reaching WON" % MAX_STEPS,
				plan_moves,
				working,
				steps,
				visited.size()
			)
		var move := _select_move(working)
		if move == null:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
				"no permitted auto-complete move is legal in this state",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		var result := MoveExecutor.execute(working, move, null)
		if not result.ok:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
				"permitted move %s was rejected by the executor: %s" % [move.description(), result.error_message],
				plan_moves,
				working,
				steps,
				visited.size()
			)
		plan_moves.append(move)
		working = result.new_state
		steps += 1
	return AutoCompletePlanResult.eligible_result(
		false,
		AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
		"unreachable",
		plan_moves,
		working,
		steps,
		visited.size()
	)


## 按优先级确定性地选出下一步普通移动：
##   1. tableau 顶牌 → foundation（列升序；目标槽按动态规则扫描）
##   2. waste 顶牌 → foundation
##   3. DRAW_STOCK（stock 非空）
##   4. RECYCLE_STOCK（stock 已空、waste 非空）
## 无合法移动时返回 null。每个返回的移动都已预先通过 RulesEngine 校验，
## 因此经 MoveExecutor 回放时必然保持合法。
static func _select_move(state: GameState) -> Move:
	for col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(col)
		if pile == null or pile.is_empty() or not pile.top().face_up:
			continue
		var slot := _foundation_slot_for_card(state, pile.top())
		if slot >= 0:
			return Move.tableau_to_foundation(col, slot)
	if not state.waste.is_empty() and state.waste.top().face_up:
		var waste_slot := _foundation_slot_for_card(state, state.waste.top())
		if waste_slot >= 0:
			return Move.waste_to_foundation(waste_slot)
	if not state.stock.is_empty():
		return Move.draw_stock()
	if not state.waste.is_empty():
		return Move.recycle_stock()
	return null


## 确定性的动态 foundation 目标槽查找（结果同样由规则引擎校验）：
## A 使用第一个空槽（不限花色）；其余牌使用槽位升序中顶牌同花色且
## 点数恰好小 1 的第一个槽。无法放置时返回 -1。
static func _foundation_slot_for_card(state: GameState, card: CardData) -> int:
	if card == null:
		return -1
	for slot in GameState.FOUNDATION_COUNT:
		var pile := state.foundation_pile(slot)
		if pile == null:
			continue
		if pile.is_empty():
			if card.rank == 1:
				return slot
			continue
		var top := pile.top()
		if top == null or not top.face_up:
			continue
		if top.suit == card.suit and top.rank == card.rank - 1:
			return slot
	return -1


## 校验全部 tableau 牌（7 列、每个位置）都已翻开。
static func _all_tableau_face_up(state: GameState) -> bool:
	for col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(col)
		if pile == null:
			return false
		for card in pile.cards_snapshot():
			if not card.face_up:
				return false
	return true


## 规范牌局签名：按固定顺序取每个容器的“牌身份 + 翻面状态”，
## 再叠加翻牌模式。刻意排除移动/分数/重翻计数与牌局身份，
## 使“整堆重翻→翻牌”回到同一布局的循环被识别为无进展，而非无限运行。
static func _signature(state: GameState) -> String:
	var parts: Array[String] = []
	parts.append(_pile_sig(state.stock))
	parts.append(_pile_sig(state.waste))
	for col in GameState.TABLEAU_COUNT:
		parts.append(_pile_sig(state.tableau_pile(col)))
	for slot in GameState.FOUNDATION_COUNT:
		parts.append(_pile_sig(state.foundation_pile(slot)))
	parts.append("draw=%d" % state.draw_count)
	return "|".join(parts)


## 单个牌堆的签名片段：逐张牌编码为 "id+u/d"，空堆为 "-"。
static func _pile_sig(pile: CardPile) -> String:
	if pile == null:
		return "-"
	var parts: Array[String] = []
	for card in pile.cards_snapshot():
		parts.append("%d%s" % [card.id, "u" if card.face_up else "d"])
	return "[%s]" % ",".join(parts)
