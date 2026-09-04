class_name HintEngine
extends RefCounted

## 确定性、不修改状态的经典 Klondike 提示提供器（纯服务，无 Node 依赖，
## WP-07）。绝不修改 GameState/历史，也绝不返回规则引擎会拒绝的移动：
## 每个候选在返回前都经过 RulesEngine.validate 校验。
##
## 总排序（已文档化并测试）：
##   TIER 0  TIER_EXPOSE              执行后会暴露一张盖牌的合法 tableau 移动
##                                    （自动翻牌）——唯一能翻开新牌的层级
##   TIER 1  TIER_TO_FOUNDATION       tableau/waste 顶牌 → foundation 的合法移动
##                                    （源扫描顺序：tableau 列 0..6 再 waste；
##                                    目标：foundation 槽 0..3 升序）
##   TIER 2  TIER_WASTE_TO_TABLEAU    waste 顶牌 → tableau 列（列升序）
##   TIER 3  TIER_TABLEAU_RUN         其它合法且不暴露盖牌的 tableau 连牌移动
##   TIER 4  TIER_STOCK               DRAW_STOCK，或合法时的 RECYCLE_STOCK
##   TIER 5  TIER_FOUNDATION_ROLLBACK foundation 顶牌 → tableau（最后兜底）
##   TIER 6  TIER_TRIVIAL             不暴露牌的 K/整串移入空列的琐碎移动
##                                    （仅当层级 0..5 均无移动时选用）
## 同一层级内按规范枚举顺序取第一个获胜。`all_legal_moves` 返回按层级
## （升序）分组的全部合法候选；相同状态下的结果确定。

## 花色 → 颜色组；与 RulesEngine 保持一致，使“是否暴露盖牌”检查留在 Core。
static func suit_is_red(suit: int) -> bool:
	return suit == 1 or suit == 3


## 返回层级的稳定可读名称（用于日志与消息）。
static func tier_name(tier: int) -> String:
	match tier:
		HintResult.TIER_EXPOSE:
			return "expose"
		HintResult.TIER_TO_FOUNDATION:
			return "to_foundation"
		HintResult.TIER_WASTE_TO_TABLEAU:
			return "waste_to_tableau"
		HintResult.TIER_TABLEAU_RUN:
			return "tableau_run"
		HintResult.TIER_STOCK:
			return "stock"
		HintResult.TIER_FOUNDATION_ROLLBACK:
			return "foundation_rollback"
		HintResult.TIER_TRIVIAL:
			return "trivial"
	return "none"


## 提示入口：对给定状态返回最高优先级（层级最小）的合法移动；
## null/已胜利/无合法移动时返回对应的类型化失败。
static func hint(state: GameState) -> HintResult:
	if state == null:
		return HintResult.failure(
			HintResult.CODE_INVALID_STATE,
			"cannot hint a null state"
		)
	if state.game_status == GameState.GameStatus.WON:
		return HintResult.failure(
			HintResult.CODE_ALREADY_WON,
			"game is already won; no further moves are legal"
		)
	var ranked := _ranked(state)
	if ranked.is_empty():
		return HintResult.failure(
			HintResult.CODE_NO_LEGAL_MOVE,
			"no legal hintable move exists in this state"
		)
	var best: Dictionary = ranked[0]
	return HintResult.success(best.move, int(best.tier), tier_name(int(best.tier)))


## 返回全部可提示的合法移动（确定性）：按层级升序分组，
## 同一层级内按规范枚举顺序排列。只读，不修改状态。
static func all_legal_moves(state: GameState) -> Array[Move]:
	if state == null or state.game_status == GameState.GameStatus.WON:
		return []
	var ranked := _ranked(state)
	var out: Array[Move] = []
	for entry in ranked:
		out.append(entry.move)
	return out


# ----- 分层排序 -----

## 把候选按层级升序整理：从 TIER_EXPOSE 到 TIER_TRIVIAL 逐层收集。
static func _ranked(state: GameState) -> Array:
	var candidates := _enumerate(state)
	if candidates.is_empty():
		return []
	var ranked: Array = []
	for tier in range(HintResult.TIER_EXPOSE, HintResult.TIER_TRIVIAL + 1):
		for entry in candidates:
			if int(entry.tier) == tier:
				ranked.append(entry)
	return ranked


## 规范、确定的候选枚举。每个元素是 Dictionary
## {"tier": int, "move": Move}，且每个移动都已通过 RulesEngine 校验。
static func _enumerate(state: GameState) -> Array:
	var out: Array = []
	for src_col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(src_col)
		if pile == null or pile.is_empty():
			continue
		_append_run_moves(out, state, src_col)
		for slot in GameState.FOUNDATION_COUNT:
			var tf := Move.tableau_to_foundation(src_col, slot)
			if RulesEngine.validate(state, tf).ok:
				out.append({"tier": _classify(state, tf), "move": tf})
	if not state.waste.is_empty():
		for to_col in GameState.TABLEAU_COUNT:
			var wt := Move.waste_to_tableau(to_col)
			if RulesEngine.validate(state, wt).ok:
				out.append({"tier": _classify(state, wt), "move": wt})
		for slot in GameState.FOUNDATION_COUNT:
			var wf := Move.waste_to_foundation(slot)
			if RulesEngine.validate(state, wf).ok:
				out.append({"tier": _classify(state, wf), "move": wf})
	var draw := Move.draw_stock()
	if RulesEngine.validate(state, draw).ok:
		out.append({"tier": _classify(state, draw), "move": draw})
	var recycle := Move.recycle_stock()
	if RulesEngine.validate(state, recycle).ok:
		out.append({"tier": _classify(state, recycle), "move": recycle})
	for slot in GameState.FOUNDATION_COUNT:
		var slot_pile := state.foundation_pile(slot)
		if slot_pile == null or slot_pile.is_empty():
			continue
		for to_col in GameState.TABLEAU_COUNT:
			var ft := Move.foundation_to_tableau(slot, to_col)
			if RulesEngine.validate(state, ft).ok:
				out.append({"tier": _classify(state, ft), "move": ft})
	return out


## 枚举单个源列的全部合法 tableau 连牌移动（T2T）：
## 对每个目标列，至多会找到一个连牌数量使其底牌符合收牌规则，
## 从而覆盖翻开连牌的每个可移动后缀。
static func _append_run_moves(out: Array, state: GameState, src_col: int) -> void:
	var pile := state.tableau_pile(src_col)
	var max_run := _face_up_valid_run_length(pile)
	if max_run <= 0:
		return
	for dst_col in GameState.TABLEAU_COUNT:
		if dst_col == src_col:
			continue
		for count in range(1, max_run + 1):
			var move := Move.tableau_to_tableau(src_col, dst_col, count)
			if RulesEngine.validate(state, move).ok:
				out.append({"tier": _classify(state, move), "move": move})


## 从堆顶向下计算最长、翻开、降序交替的合法连牌后缀长度。
## 自顶牌向下逐张检查：下一张（更靠底）牌必须比当前牌大 1 点
## 且颜色相反。
static func _face_up_valid_run_length(pile: CardPile) -> int:
	if pile == null or pile.is_empty():
		return 0
	if not pile.top().face_up:
		return 0
	var length := 1
	var prev := pile.top()
	var i := pile.size() - 2
	while i >= 0:
		var card := pile.card_at(i)
		if card == null or not card.face_up:
			break
		if card.rank != prev.rank + 1:
			break
		if suit_is_red(card.suit) == suit_is_red(prev.suit):
			break
		length += 1
		prev = card
		i -= 1
	return length


## 给一个（已通过合法性校验的）移动分配优先级层级，供排序使用。
static func _classify(state: GameState, move: Move) -> int:
	match move.kind:
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			var source := state.tableau_pile(move.source_index)
			var exposed_face_down := (
				move.count < source.size()
				and source.card_at(source.size() - move.count - 1) != null
				and not source.card_at(source.size() - move.count - 1).face_up
			)
			if exposed_face_down:
				return HintResult.TIER_EXPOSE
			if state.tableau_pile(move.target_index).is_empty() and move.count == source.size():
				return HintResult.TIER_TRIVIAL
			return HintResult.TIER_TABLEAU_RUN
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			var t_source := state.tableau_pile(move.source_index)
			if (
				t_source.size() > 1
				and t_source.card_at(t_source.size() - 2) != null
				and not t_source.card_at(t_source.size() - 2).face_up
			):
				return HintResult.TIER_EXPOSE
			return HintResult.TIER_TO_FOUNDATION
		Move.MoveKind.WASTE_TO_FOUNDATION:
			return HintResult.TIER_TO_FOUNDATION
		Move.MoveKind.WASTE_TO_TABLEAU:
			return HintResult.TIER_WASTE_TO_TABLEAU
		Move.MoveKind.DRAW_STOCK, Move.MoveKind.RECYCLE_STOCK:
			return HintResult.TIER_STOCK
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			return HintResult.TIER_FOUNDATION_ROLLBACK
	return HintResult.TIER_NONE
