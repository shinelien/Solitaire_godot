class_name BoardView
extends Control

## Renders all piles from GameState and provides layout geometry + hit
## testing for the input layer. Read-only with respect to GameState.

const CARD_W := 90.0
const CARD_H := 126.0

const STOCK_POS := Vector2(20, 20)
const WASTE_POS := Vector2(130, 20)
const FOUNDATION_X := 860.0
const FOUNDATION_Y := 20.0
const FOUNDATION_GAP := 95.0
const TABLEAU_X0 := 20.0
const TABLEAU_Y := 180.0
const TABLEAU_GAP := 100.0
const FACE_UP_OFFSET := 28.0
const FACE_DOWN_OFFSET := 13.0

var controller: GameController = null
var _views: Dictionary = {}
var _highlight_keys: Dictionary = {}

func _ready() -> void:
	mouse_filter = Control.MOUSE_FILTER_IGNORE

func attach(c: GameController) -> void:
	controller = c

func clear_highlights() -> void:
	_highlight_keys.clear()
	for key in _views:
		_views[key].set_highlighted(false)

func set_hint_key(key: String) -> void:
	_highlight_keys[key] = true

func refresh(state: GameState) -> void:
	if state == null:
		return
	var needed := {}
	# Stock: one representative face-down back (or placeholder when empty).
	if state.stock.is_empty():
		_place_placeholder("stock", STOCK_POS, needed)
	else:
		_place_card("stock", STOCK_POS, state.stock[state.stock.size() - 1], false, needed)
	# Waste: only the top card is visible.
	if state.waste.is_empty():
		_place_placeholder("waste", WASTE_POS, needed)
	else:
		var wtop: CardData = state.waste[state.waste.size() - 1]
		_place_card("waste", WASTE_POS, wtop, _highlight_keys.has("waste"), needed)
	# Foundations: top card each.
	for i in PileType.FOUNDATION_COUNT:
		var pos := Vector2(FOUNDATION_X + i * FOUNDATION_GAP, FOUNDATION_Y)
		var key := "fnd%d" % i
		if state.fnd(i).is_empty():
			_place_placeholder(key, pos, needed)
		else:
			_place_card(key, pos, state.fnd(i)[state.fnd(i).size() - 1], _highlight_keys.has(key), needed)
	# Tableau: full columns bottom-up.
	for c in PileType.TABLEAU_COUNT:
		var cards := state.col(c)
		var x := TABLEAU_X0 + c * TABLEAU_GAP
		if cards.is_empty():
			_place_placeholder("tab%d" % c, Vector2(x, TABLEAU_Y), needed)
			continue
		var y := TABLEAU_Y
		for j in cards.size():
			var key := "tab%d_%d" % [c, j]
			var hl := _highlight_keys.has(key)
			_place_card(key, Vector2(x, y), cards[j], hl, needed)
			y += FACE_UP_OFFSET if cards[j].face_up else FACE_DOWN_OFFSET
	# Hide stale views.
	for key in _views:
		if not needed.has(key):
			_views[key].hide_card()

func _place_card(key: String, pos: Vector2, card: CardData, hl: bool, needed: Dictionary) -> void:
	var v := _view(key)
	v.set_card(card, hl)
	v.position = pos
	v.z_index = _z_for(key)
	needed[key] = true

func _place_placeholder(key: String, pos: Vector2, needed: Dictionary) -> void:
	var v := _view(key)
	v.set_placeholder()
	v.position = pos
	v.z_index = 0
	needed[key] = true

func _view(key: String) -> CardView:
	if not _views.has(key):
		var v := CardView.new()
		v.name = "Card_%s" % key
		add_child(v)
		_views[key] = v
	return _views[key]

func _z_for(key: String) -> int:
	if key.begins_with("tab"):
		var j := int(key.split("_")[1])
		return 100 + j
	return 10

# ---------------------------------------------------------------- geometry

func stock_rect() -> Rect2:
	return Rect2(STOCK_POS, Vector2(CARD_W, CARD_H))

func waste_rect() -> Rect2:
	return Rect2(WASTE_POS, Vector2(CARD_W, CARD_H))

func foundation_rect(i: int) -> Rect2:
	return Rect2(Vector2(FOUNDATION_X + i * FOUNDATION_GAP, FOUNDATION_Y), Vector2(CARD_W, CARD_H))

func tableau_rect(c: int) -> Rect2:
	return Rect2(Vector2(TABLEAU_X0 + c * TABLEAU_GAP, TABLEAU_Y), Vector2(CARD_W, CARD_H))

func tableau_card_y(c: int, j: int, cards: Array[CardData]) -> float:
	var y := TABLEAU_Y
	for k in range(j):
		y += FACE_UP_OFFSET if cards[k].face_up else FACE_DOWN_OFFSET
	return y

## Returns {type, index, from_index, count} or {} for an empty hit.
func hit_test(pos: Vector2) -> Dictionary:
	if stock_rect().has_point(pos):
		return {"type": PileType.STOCK, "index": 0, "from_index": -1, "count": 0}
	if waste_rect().has_point(pos):
		if controller != null and controller.state != null \
				and not controller.state.waste.is_empty():
			return {"type": PileType.WASTE, "index": 0, "from_index": -1, "count": 1}
		return {}
	for i in PileType.FOUNDATION_COUNT:
		if foundation_rect(i).has_point(pos):
			if controller != null and controller.state != null \
					and not controller.state.fnd(i).is_empty():
				return {"type": PileType.FOUNDATION, "index": i, "from_index": -1, "count": 1}
			return {}
	for c in PileType.TABLEAU_COUNT:
		var cards := _tableau(c)
		var rect := tableau_rect(c)
		if not rect.has_point(pos):
			continue
		if cards.is_empty():
			return {"type": PileType.TABLEAU, "index": c, "from_index": -1, "count": 0}
		for j in range(cards.size() - 1, -1, -1):
			var y := tableau_card_y(c, j, cards)
			if pos.y >= y and pos.y <= y + CARD_H:
				return {"type": PileType.TABLEAU, "index": c, "from_index": j, "count": cards.size() - j}
		return {"type": PileType.TABLEAU, "index": c, "from_index": -1, "count": 0}
	return {}

func _tableau(c: int) -> Array[CardData]:
	if controller != null and controller.state != null:
		return controller.state.col(c)
	return []
