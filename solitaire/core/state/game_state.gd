class_name GameState
extends RefCounted

## Sole source of truth for one solitaire deal. Pure logic, no Node, no UI.
## The Presentation layer only ever reads this state and emits intents;
## it never mutates piles directly.

var status: int = GameStatus.Status.PLAYING
var draw_mode: int = GameConfig.DRAW1
var encoded: String = ""
var deal_index: int = -1
var stock: Array[CardData] = []
var waste: Array[CardData] = []
var tableau: Array = []          # 7 x Array[CardData], index 0 = bottom card
var foundations: Array = []      # 4 x Array[CardData], index 0 = Ace
var move_count: int = 0
var draw_count: int = 0
var history: Array[MoveCommand] = []
var session: Array = []          # Array[Dictionary] of deals played this session

func _init() -> void:
	tableau.resize(PileType.TABLEAU_COUNT)
	for i in PileType.TABLEAU_COUNT:
		var col_arr: Array[CardData] = []
		tableau[i] = col_arr
	foundations.resize(PileType.FOUNDATION_COUNT)
	for i in PileType.FOUNDATION_COUNT:
		var fnd_arr: Array[CardData] = []
		foundations[i] = fnd_arr

func col(i: int) -> Array[CardData]:
	var c: Array[CardData] = tableau[i]
	return c

func fnd(i: int) -> Array[CardData]:
	var f: Array[CardData] = foundations[i]
	return f

func get_pile(loc: Location) -> Array[CardData]:
	var p: Array[CardData] = stock
	match loc.type:
		PileType.STOCK:
			p = stock
		PileType.WASTE:
			p = waste
		PileType.TABLEAU:
			p = col(loc.index)
		PileType.FOUNDATION:
			p = fnd(loc.index)
	return p

func top_card(loc: Location) -> CardData:
	var p := get_pile(loc)
	if p.is_empty():
		return null
	return p[p.size() - 1]

func deep_copy() -> GameState:
	var s := GameState.new()
	s.status = status
	s.draw_mode = draw_mode
	s.encoded = encoded
	s.deal_index = deal_index
	s.move_count = move_count
	s.draw_count = draw_count
	s.stock = _copy_cards(stock)
	s.waste = _copy_cards(waste)
	for i in PileType.TABLEAU_COUNT:
		s.tableau[i] = _copy_cards(col(i))
	for i in PileType.FOUNDATION_COUNT:
		s.foundations[i] = _copy_cards(fnd(i))
	s.history.clear()
	for h in history:
		s.history.push_back(h.clone())
	s.session.clear()
	for d in session:
		s.session.push_back(d.duplicate(true))
	return s

func _copy_cards(src: Array[CardData]) -> Array[CardData]:
	var out: Array[CardData] = []
	for c in src:
		out.push_back(c.copy())
	return out

func equals(other: GameState) -> bool:
	if other == null:
		return false
	if status != other.status or draw_mode != other.draw_mode \
			or encoded != other.encoded or deal_index != other.deal_index \
			or move_count != other.move_count or draw_count != other.draw_count:
		return false
	if not _cards_equal(stock, other.stock) or not _cards_equal(waste, other.waste):
		return false
	for i in PileType.TABLEAU_COUNT:
		if not _cards_equal(col(i), other.col(i)):
			return false
	for i in PileType.FOUNDATION_COUNT:
		if not _cards_equal(fnd(i), other.fnd(i)):
			return false
	if history.size() != other.history.size():
		return false
	for i in history.size():
		if history[i].label != other.history[i].label:
			return false
	if session.size() != other.session.size():
		return false
	return true

func _cards_equal(a: Array[CardData], b: Array[CardData]) -> bool:
	if a.size() != b.size():
		return false
	for i in a.size():
		if not a[i].same_as(b[i]):
			return false
	return true

func invariant_errors() -> Array[String]:
	var errs: Array[String] = []
	var seen := {}
	var total := 0
	for c in stock:
		total += 1
		if c.face_up:
			errs.push_back("stock card face-up: %s" % c)
		if seen.has(c.id):
			errs.push_back("duplicate card id %d" % c.id)
		else:
			seen[c.id] = true
	for c in waste:
		total += 1
		if not c.face_up:
			errs.push_back("waste card face-down: %s" % c)
		if seen.has(c.id):
			errs.push_back("duplicate card id %d" % c.id)
		else:
			seen[c.id] = true
	for i in PileType.TABLEAU_COUNT:
		var cards := col(i)
		var saw_face_up := false
		for c in cards:
			total += 1
			if seen.has(c.id):
				errs.push_back("duplicate card id %d" % c.id)
			else:
				seen[c.id] = true
			if c.face_up:
				saw_face_up = true
			elif saw_face_up:
				errs.push_back("tableau %d has face-down card above face-up" % i)
		for j in range(1, cards.size()):
			var lo := cards[j - 1]
			var hi := cards[j]
			if lo.face_up and hi.face_up:
				if not _tableau_accepts(lo, hi):
					errs.push_back("tableau %d build violation at %d: %s on %s" \
						% [i, j, hi, lo])
	for i in PileType.FOUNDATION_COUNT:
		var cards := fnd(i)
		for j in cards.size():
			total += 1
			var c := cards[j]
			if seen.has(c.id):
				errs.push_back("duplicate card id %d" % c.id)
			else:
				seen[c.id] = true
			if not c.face_up:
				errs.push_back("foundation %d card face-down" % i)
		if not cards.is_empty() and cards[0].rank != 1:
			errs.push_back("foundation %d does not start at Ace" % i)
		for j in range(1, cards.size()):
			if not _foundation_accepts(cards[j - 1], cards[j]):
				errs.push_back("foundation %d build violation at %d" % [i, j])
	if total != CardData.DECK_SIZE:
		errs.push_back("total cards %d != 52" % total)
	if seen.size() != CardData.DECK_SIZE:
		errs.push_back("unique ids %d != 52" % seen.size())
	if status == GameStatus.Status.WON:
		for i in PileType.FOUNDATION_COUNT:
			if fnd(i).size() != 13:
				errs.push_back("WON status but foundation %d not full" % i)
	return errs

## Local copies of the Klondike build rules so GameState stays acyclic with
## respect to KlondikeRules (avoids a class_name dependency cycle that fails
## under headless analysis). These mirror KlondikeRules exactly.
func _tableau_accepts(target_top: CardData, moved_top: CardData) -> bool:
	if moved_top == null:
		return false
	if target_top == null:
		return moved_top.rank == 13
	return moved_top.rank == target_top.rank - 1 \
		and moved_top.color_key() != target_top.color_key()

func _foundation_accepts(target_top: CardData, moved: CardData) -> bool:
	if moved == null:
		return false
	if target_top == null:
		return moved.rank == 1
	return moved.suit == target_top.suit and moved.rank == target_top.rank + 1
