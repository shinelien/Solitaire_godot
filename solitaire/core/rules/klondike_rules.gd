class_name KlondikeRules
extends RefCounted

## Pure Klondike legality. Static functions only; never mutates GameState.
## Legacy parity (SpriteManager.cpp / CardSprite.cpp):
##   - Tableau build: descending rank, alternating color (suit % 2).
##   - Empty tableau accepts only a King.
##   - Foundation: same suit, ascending A->K. Empty accepts only an Ace.

static func tableau_accepts(target_top: CardData, moved_top: CardData) -> bool:
	if moved_top == null:
		return false
	if target_top == null:
		return moved_top.rank == 13
	return moved_top.rank == target_top.rank - 1 \
		and moved_top.color_key() != target_top.color_key()

static func foundation_accepts(target_top: CardData, moved: CardData) -> bool:
	if moved == null:
		return false
	if target_top == null:
		return moved.rank == 1
	return moved.suit == target_top.suit and moved.rank == target_top.rank + 1

static func sequence_valid(seq: Array[CardData]) -> bool:
	for i in range(1, seq.size()):
		if not tableau_accepts(seq[i - 1], seq[i]):
			return false
	return true

static func draw_count_for(state: GameState) -> int:
	if state.stock.is_empty():
		return 0
	return mini(state.draw_mode, state.stock.size())

static func is_won(state: GameState) -> bool:
	for i in PileType.FOUNDATION_COUNT:
		if state.fnd(i).size() != 13:
			return false
	return true

static func matching_foundation(state: GameState, card: CardData) -> int:
	for f in PileType.FOUNDATION_COUNT:
		var top := state.top_card(Location.foundation(f))
		if foundation_accepts(top, card):
			return f
	return -1

static func is_legal_move(state: GameState, move: Move) -> bool:
	if move == null or move.type != Move.MoveType.MOVE_CARD:
		return false
	var src: Array[CardData] = state.get_pile(move.from_pile)
	var dst: Array[CardData] = state.get_pile(move.to_pile)
	if move.to_pile.type != PileType.TABLEAU \
			and move.to_pile.type != PileType.FOUNDATION:
		return false
	var moved: CardData = null
	var moved_cards: Array[CardData] = []
	if move.from_pile.type == PileType.WASTE \
			or move.from_pile.type == PileType.FOUNDATION:
		if src.is_empty():
			return false
		if move.from_index != -1 and move.from_index != src.size() - 1:
			return false
		if move.count != 1:
			return false
		moved = src[src.size() - 1]
		if not moved.face_up:
			return false
	elif move.from_pile.type == PileType.TABLEAU:
		var n := src.size()
		if move.from_index < 0 or move.from_index >= n:
			return false
		if move.count <= 0 or move.from_index + move.count > n:
			return false
		moved_cards = src.slice(move.from_index, move.from_index + move.count)
		for c in moved_cards:
			if not c.face_up:
				return false
		if not sequence_valid(moved_cards):
			return false
		moved = moved_cards[0]
	else:
		return false
	if move.to_pile.type == PileType.TABLEAU:
		var top: CardData = null
		if not dst.is_empty():
			top = dst[dst.size() - 1]
			if not top.face_up:
				return false
		return tableau_accepts(top, moved)
	return foundation_accepts(state.top_card(move.to_pile), moved)

## Deterministic first legal foundation move (used by Auto Complete and Hint).
static func find_foundation_move(state: GameState) -> Move:
	if not state.waste.is_empty():
		var card: CardData = state.waste[state.waste.size() - 1]
		var f := matching_foundation(state, card)
		if f != -1:
			return _move_was_top_to_foundation(state, f)
	for i in PileType.TABLEAU_COUNT:
		var cards := state.col(i)
		if cards.is_empty():
			continue
		var card: CardData = cards[cards.size() - 1]
		if not card.face_up:
			continue
		var f := matching_foundation(state, card)
		if f != -1:
			return _move_tab_top_to_foundation(state, i, f)
	return null

static func _move_was_top_to_foundation(state: GameState, f: int) -> Move:
	var card: CardData = state.waste[state.waste.size() - 1]
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.waste()
	m.from_index = state.waste.size() - 1
	m.count = 1
	m.to_pile = Location.foundation(f)
	m.card_id = card.id
	return m

static func _move_tab_top_to_foundation(state: GameState, col: int, f: int) -> Move:
	var cards := state.col(col)
	var card: CardData = cards[cards.size() - 1]
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.tableau(col)
	m.from_index = cards.size() - 1
	m.count = 1
	m.to_pile = Location.foundation(f)
	m.card_id = card.id
	return m

## Read-only hint: first legal move, or null. Never mutates state.
static func find_hint_move(state: GameState) -> Move:
	var foundation_move := find_foundation_move(state)
	if foundation_move != null:
		return foundation_move
	if not state.waste.is_empty():
		var card: CardData = state.waste[state.waste.size() - 1]
		for t in PileType.TABLEAU_COUNT:
			var dst := state.col(t)
			var top: CardData = null
			if not dst.is_empty():
				top = dst[dst.size() - 1]
				if not top.face_up:
					continue
			if tableau_accepts(top, card):
				return _move_waste_top_to_tableau(t, card.id)
	for src_col in PileType.TABLEAU_COUNT:
		var cards := state.col(src_col)
		for from_index in range(cards.size()):
			var card: CardData = cards[from_index]
			if not card.face_up:
				break
			var count := cards.size() - from_index
			var seq: Array[CardData] = cards.slice(from_index, cards.size())
			if not sequence_valid(seq):
				break
			for t in PileType.TABLEAU_COUNT:
				if t == src_col:
					continue
				var dst := state.col(t)
				var top: CardData = null
				if not dst.is_empty():
					top = dst[dst.size() - 1]
					if not top.face_up:
						continue
				if tableau_accepts(top, card):
					return _move_tab_seq_to_tableau(src_col, from_index, count, t, card.id)
	for f in PileType.FOUNDATION_COUNT:
		var cards := state.fnd(f)
		if cards.is_empty():
			continue
		var card: CardData = cards[cards.size() - 1]
		for t in PileType.TABLEAU_COUNT:
			var dst := state.col(t)
			var top: CardData = null
			if not dst.is_empty():
				top = dst[dst.size() - 1]
				if not top.face_up:
					continue
			if tableau_accepts(top, card):
				return _move_fnd_top_to_tableau(f, t, card.id)
	return null

static func _move_waste_top_to_tableau(t: int, card_id: int) -> Move:
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.waste()
	m.from_index = -1
	m.count = 1
	m.to_pile = Location.tableau(t)
	m.card_id = card_id
	return m

static func _move_tab_seq_to_tableau(src: int, from_index: int, count: int, t: int, card_id: int) -> Move:
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.tableau(src)
	m.from_index = from_index
	m.count = count
	m.to_pile = Location.tableau(t)
	m.card_id = card_id
	return m

static func _move_fnd_top_to_tableau(f: int, t: int, card_id: int) -> Move:
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.foundation(f)
	m.from_index = -1
	m.count = 1
	m.to_pile = Location.tableau(t)
	m.card_id = card_id
	return m

static func describe_move(state: GameState, move: Move) -> String:
	if move == null:
		return "No legal move available"
	match move.type:
		Move.MoveType.MOVE_CARD:
			var src: Array[CardData] = state.get_pile(move.from_pile)
			var card: CardData = null
			if move.from_index >= 0 and move.from_index < src.size():
				card = src[move.from_index]
			elif not src.is_empty():
				card = src[src.size() - 1]
			var card_name: String = "?" if card == null else str(card)
			var dest_name := PileType.label(move.to_pile.type)
			if move.to_pile.type == PileType.TABLEAU:
				dest_name += " %d" % (move.to_pile.index + 1)
			else:
				dest_name += " %d" % (move.to_pile.index + 1)
			return "Hint: %s -> %s" % [card_name, dest_name]
		Move.MoveType.DRAW:
			return "Draw"
		Move.MoveType.RECYCLE:
			return "Recycle"
	return ""
