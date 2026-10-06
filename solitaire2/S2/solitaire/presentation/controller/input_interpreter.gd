class_name InputInterpreter
extends RefCounted

## Presentation-only translation of raw pointer intent into an explicit Move
## (WP-08). It never decides legality: every returned candidate Move is still
## validated/applied by MoveExecutor through the GameSession, and anything the
## UI does not understand returns null (no move attempted). Tap/double-tap
## auto-targeting reuses Move factories + RulesEngine.validate (Core), so
## presentation never re-implements a rule. All helpers are read-only.

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


## Auto-targeting for a tap/double-click on a playable card: find the most
## suitable legal destination using the legacy reference order — foundation
## slots 0..3 (排基) first, then tableau columns 0..6 (可接龙的位置). A
## tableau source may be the column top (single card) or a face-up card inside
## a run (the whole legal suffix from that card is moved). Every candidate is
## built through the same Move factories as drag translation and validated by
## RulesEngine, so presentation never re-implements a rule; the function only
## decides destination priority. Returns null when the source has no legal
## destination (stock click is handled separately by stock_click_move).
static func auto_find_move(state: GameState, source: Dictionary) -> Move:
	if state == null or source.is_empty():
		return null
	var src_kind: String = source.get("kind", "")
	match src_kind:
		"tableau":
			return _auto_find_tableau(state, source)
		"waste":
			return _auto_find_waste(state, source)
	return null


## Keep the double-click entry point stable: it is the same auto-find search,
## so a single tap and a double tap behave identically.
static func double_click_move(state: GameState, source: Dictionary) -> Move:
	return auto_find_move(state, source)


## Waste auto-target: foundation slots 0..3 first, then tableau columns 0..6.
static func _auto_find_waste(state: GameState, source: Dictionary) -> Move:
	if state.waste.is_empty() or state.waste.top() == null or not state.waste.top().face_up:
		return null
	for slot in GameState.FOUNDATION_COUNT:
		var move := Move.waste_to_foundation(slot)
		if RulesEngine.validate(state, move).ok:
			return move
	for col in GameState.TABLEAU_COUNT:
		var move := Move.waste_to_tableau(col)
		if RulesEngine.validate(state, move).ok:
			return move
	return null


## Tableau auto-target: only the column top may seek a foundation slot;
## tableau (接龙) destinations are searched for the clicked card, moving the
## legal run suffix (count = pile.size() - card_index) exactly like a drag.
static func _auto_find_tableau(state: GameState, source: Dictionary) -> Move:
	var col := int(source.get("index", -1))
	if col < 0 or col >= GameState.TABLEAU_COUNT:
		return null
	var pile := state.tableau_pile(col)
	if pile == null or pile.is_empty():
		return null
	var card_index := int(source.get("card_index", -1))
	if card_index < 0 or card_index >= pile.size():
		return null
	var card := pile.card_at(card_index)
	if card == null or not card.face_up:
		return null
	if card_index == pile.size() - 1:
		for slot in GameState.FOUNDATION_COUNT:
			var move := Move.tableau_to_foundation(col, slot)
			if RulesEngine.validate(state, move).ok:
				return move
	var count := pile.size() - card_index
	for dst_col in GameState.TABLEAU_COUNT:
		if dst_col == col:
			continue
		var move := Move.tableau_to_tableau(col, dst_col, count)
		if RulesEngine.validate(state, move).ok:
			return move
	return null
