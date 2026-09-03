class_name InputInterpreter
extends RefCounted

## Presentation-only translation of raw pointer intent into an explicit Move
## (WP-08). It never decides legality: every returned candidate Move is still
## validated/applied by MoveExecutor through the GameSession, and anything the
## UI does not understand returns null (no move attempted). Foundation
## auto-targeting for double-click reuses HintEngine.all_legal_moves (Core),
## so presentation never re-implements a rule. All helpers are read-only.

## Source descriptor keys: kind in {"tableau","waste","foundation","stock"},
## index (column/slot), card_index (0-based in the pile; -1/ignored for single
## piles). Target descriptor keys: kind/index.
static func build_drag_move(state: GameState, source: Dictionary, target: Dictionary) -> Move:
	if state == null or source.is_empty() or target.is_empty():
		return null
	var src_kind: String = source.get("kind", "")
	var dst_kind: String = target.get("kind", "")
	if src_kind == "stock":
		return null
	if dst_kind == "stock" or dst_kind == "waste":
		return null
	match src_kind:
		"tableau":
			return _tableau_drag(state, source, target, dst_kind)
		"waste":
			return _waste_drag(state, target, dst_kind)
		"foundation":
			return _foundation_drag(state, source, target, dst_kind)
	return null


static func _tableau_drag(state: GameState, source: Dictionary, target: Dictionary, dst_kind: String) -> Move:
	var col := int(source.get("index", -1))
	var pile := state.tableau_pile(col)
	if pile == null or pile.is_empty():
		return null
	var card_index := int(source.get("card_index", -1))
	if card_index < 0 or card_index >= pile.size():
		return null
	var card := pile.card_at(card_index)
	if card == null or not card.face_up:
		return null
	if dst_kind == "tableau":
		var d := int(target.get("index", -1))
		if d == col:
			return null
		return Move.tableau_to_tableau(col, d, pile.size() - card_index)
	if dst_kind == "foundation":
		if card_index != pile.size() - 1:
			return null
		var slot := int(target.get("index", -1))
		if slot < 0 or slot >= GameState.FOUNDATION_COUNT:
			return null
		return Move.tableau_to_foundation(col, slot)
	return null


static func _waste_drag(state: GameState, target: Dictionary, dst_kind: String) -> Move:
	if state.waste.is_empty() or state.waste.top() == null or not state.waste.top().face_up:
		return null
	if dst_kind == "tableau":
		var d := int(target.get("index", -1))
		if d < 0 or d >= GameState.TABLEAU_COUNT:
			return null
		return Move.waste_to_tableau(d)
	if dst_kind == "foundation":
		var slot := int(target.get("index", -1))
		if slot < 0 or slot >= GameState.FOUNDATION_COUNT:
			return null
		return Move.waste_to_foundation(slot)
	return null


static func _foundation_drag(state: GameState, source: Dictionary, target: Dictionary, dst_kind: String) -> Move:
	var slot := int(source.get("index", -1))
	var pile := state.foundation_pile(slot)
	if pile == null or pile.is_empty() or pile.top() == null or not pile.top().face_up:
		return null
	if dst_kind == "tableau":
		var d := int(target.get("index", -1))
		if d < 0 or d >= GameState.TABLEAU_COUNT:
			return null
		return Move.foundation_to_tableau(slot, d)
	return null


## Stock area interaction: draw while stock is non-empty, otherwise recycle the
## waste (a single click; nothing else to do on an empty stock+waste).
static func stock_click_move(state: GameState) -> Move:
	if state == null:
		return null
	if not state.stock.is_empty():
		return Move.draw_stock()
	if not state.waste.is_empty():
		return Move.recycle_stock()
	return null


## Double-click/tap on a tableau or waste top: send that exact top card to its
## deterministic foundation slot. The slot resolution delegates to Core
## (HintEngine.all_legal_moves enumerates legal foundation moves with the
## canonical slot order); returns null when no foundation move exists for this
## source.
static func double_click_move(state: GameState, source: Dictionary) -> Move:
	if state == null or source.is_empty():
		return null
	var src_kind: String = source.get("kind", "")
	var index := int(source.get("index", -1))
	var legal := HintEngine.all_legal_moves(state)
	for move in legal:
		if move == null:
			continue
		if src_kind == "waste":
			if move.kind == Move.MoveKind.WASTE_TO_FOUNDATION:
				if _is_source_top(state, source):
					return move
		elif src_kind == "tableau":
			if not _is_tableau_top(state, source):
				return null
			if move.kind == Move.MoveKind.TABLEAU_TO_FOUNDATION and move.source_index == index:
				return move
	return null


static func _is_tableau_top(state: GameState, source: Dictionary) -> bool:
	var pile := state.tableau_pile(int(source.get("index", -1)))
	if pile == null or pile.is_empty():
		return false
	var card_index := int(source.get("card_index", -1))
	return card_index == pile.size() - 1 and pile.top() != null and pile.top().face_up


static func _is_source_top(state: GameState, source: Dictionary) -> bool:
	var pile: CardPile = null
	var src_kind: String = source.get("kind", "")
	if src_kind == "waste":
		pile = state.waste
	elif src_kind == "tableau":
		pile = state.tableau_pile(int(source.get("index", -1)))
	else:
		return false
	if pile == null or pile.is_empty():
		return false
	return pile.top() != null and pile.top().face_up
