class_name InputHandler
extends Control

## Translates pointer events into controller intents (draw/recycle on stock,
## drag to a pile, double-click to foundation). Presentation -> Application
## only; it never mutates GameState directly.

var controller: GameController = null
var board: BoardView = null
var _drag_source: Dictionary = {}
var _dragging := false

func _ready() -> void:
	mouse_filter = Control.MOUSE_FILTER_STOP

func set_controller(c: GameController) -> void:
	controller = c

func set_board(b: BoardView) -> void:
	board = b

func _gui_input(event: InputEvent) -> void:
	if controller == null or board == null:
		return
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.double_click and event.pressed:
			_handle_double_click(event.position)
			return
		if event.pressed:
			var hit := board.hit_test(event.position)
			if not hit.is_empty():
				_drag_source = hit
				_dragging = true
		else:
			_handle_release(event.position)
			_drag_source = {}
			_dragging = false

func _handle_double_click(pos: Vector2) -> void:
	var hit := board.hit_test(pos)
	if hit.is_empty():
		return
	var t: int = hit["type"]
	if t == PileType.WASTE or t == PileType.TABLEAU or t == PileType.FOUNDATION:
		var top := _top_card(hit)
		if top != null and top.face_up:
			var loc := _location_from_hit(hit)
			controller.request_auto_foundation(loc)

func _handle_release(pos: Vector2) -> void:
	if _drag_source.is_empty():
		return
	var st: int = _drag_source["type"]
	if st == PileType.STOCK:
		controller.request_stock_action()
		return
	var target := board.hit_test(pos)
	if target.is_empty():
		return
	var tt: int = target["type"]
	if tt != PileType.TABLEAU and tt != PileType.FOUNDATION:
		return
	if st == tt and _drag_source["index"] == target["index"]:
		return
	if tt == PileType.FOUNDATION and _drag_source["count"] != 1:
		return
	var from_loc := _location_from_hit(_drag_source)
	var to_loc := _location_from_hit(target)
	controller.request_move(from_loc, _drag_source["from_index"], _drag_source["count"], to_loc)

func _top_card(hit: Dictionary) -> CardData:
	if controller == null or controller.state == null:
		return null
	var t: int = hit["type"]
	match t:
		PileType.WASTE:
			if controller.state.waste.is_empty():
				return null
			return controller.state.waste[controller.state.waste.size() - 1]
		PileType.TABLEAU:
			var cards := controller.state.col(hit["index"])
			if cards.is_empty():
				return null
			return cards[cards.size() - 1]
		PileType.FOUNDATION:
			var f := controller.state.fnd(hit["index"])
			if f.is_empty():
				return null
			return f[f.size() - 1]
	return null

func _location_from_hit(hit: Dictionary) -> Location:
	var loc := Location.new()
	loc.type = hit["type"]
	loc.index = hit["index"]
	return loc
