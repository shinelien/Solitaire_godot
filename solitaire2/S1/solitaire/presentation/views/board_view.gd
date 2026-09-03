class_name BoardView
extends Control

## Pure-2D board renderer (WP-08). BoardView is a dumb projection of a
## SnapshotProjector dictionary: it owns no GameState/CardData and knows no
## rules. It computes a responsive card layout (legacy sizes/offsets, with
## vertical compression when a column would overflow the available band) and
## creates/updates plain Control/TextureRect CardViews. Pointer press/release
## intents on cards are forwarded verbatim to controller callables.

const SIDE := 20
const ROW_Y := 26
const WASTE_GAP := 18
const COL_GAP := 6
const TOP_ROW_CARD_GAP := 14
const FOUNDATION_FAN := 4
const STOCK_FAN := 2
const TAB_TOP := 286
const BOTTOM_UI := 260

## Hint overlay colours: source zone green, target zone amber — deliberately
## distinguishable so the suggested move reads as source -> target.
const HINT_SOURCE_COLOR := Color(0.2, 1.0, 0.55, 0.32)
const HINT_TARGET_COLOR := Color(1.0, 0.72, 0.15, 0.38)

var controller_press: Callable = Callable()
var controller_release: Callable = Callable()
var controller_double: Callable = Callable()

var _zones: Dictionary = {}
var _stock_zone: Control = null
var _stock_callback: Callable = Callable()
var _drag_layer: Control = null
var _ghost: CardView = null
var _ghost_badge: Label = null
var _ghost_size := Vector2(BoardGeometry.CARD_W, BoardGeometry.CARD_H)
var _hint_layer: Control = null

var _face_texture_cache: Dictionary = {}


func _init() -> void:
	mouse_filter = Control.MOUSE_FILTER_IGNORE


func clear_board() -> void:
	for child in get_children():
		remove_child(child)
		child.queue_free()
	_zones.clear()
	_stock_zone = null
	_hint_layer = null


func _card_w() -> int:
	return BoardGeometry.CARD_W


func _card_h() -> int:
	return BoardGeometry.CARD_H


func _tableau_x(col: int) -> int:
	var total := 7 * _card_w() + 6 * COL_GAP
	var start := int((size.x - total) / 2.0)
	return start + col * (_card_w() + COL_GAP)


func _tab_bottom() -> int:
	return int(size.y) - BOTTOM_UI


func _tab_avail() -> int:
	return _tab_bottom() - TAB_TOP


func render(data: Dictionary) -> void:
	clear_board()
	_face_texture_cache.clear()
	_build_foundation(data)
	_build_waste(data)
	_build_stock(data)
	_build_tableau(data)
	_build_drag_layer()


# ----- pile builders (pure view construction) -----

func _build_foundation(data: Dictionary) -> void:
	var foundation: Array = data.get("foundation", [])
	var total := 4 * _card_w() + 3 * TOP_ROW_CARD_GAP
	var start := int(size.x) - SIDE - total
	for slot in 4:
		var cards: Array = foundation[slot] if slot < foundation.size() else []
		var x := start + slot * (_card_w() + TOP_ROW_CARD_GAP)
		if cards.is_empty():
			_draw_slot_placeholder(x, ROW_Y, Color(1, 1, 1, 0.06), _slot_label("F%d" % (slot + 1)))
		else:
			_draw_stack(x, ROW_Y, cards, FOUNDATION_FAN, "foundation", slot, 6)
		_zones[_zone_key("foundation", slot)] = Rect2(x, ROW_Y, _card_w(), _card_h())


func _build_waste(data: Dictionary) -> void:
	var waste: Array = data.get("waste", [])
	var stock_x := SIDE
	var x := stock_x + _card_w() + WASTE_GAP
	if waste.is_empty():
		_draw_slot_placeholder(x, ROW_Y, Color(1, 1, 1, 0.05), "")
	else:
		_draw_stack(x, ROW_Y, waste, 3, "waste", -1, 36)
	_zones[_zone_key("waste", -1)] = Rect2(x, ROW_Y, _card_w(), _card_h())


func _build_stock(data: Dictionary) -> void:
	var stock: Array = data.get("stock", [])
	var x := SIDE
	_stock_zone = Control.new()
	_stock_zone.set_position(Vector2(x, ROW_Y))
	_stock_zone.set_size(Vector2(_card_w(), _card_h()))
	_stock_zone.mouse_filter = Control.MOUSE_FILTER_STOP
	_stock_zone.gui_input.connect(_on_stock_input)
	add_child(_stock_zone)
	if stock.is_empty():
		_draw_slot_placeholder(x, ROW_Y, Color(1, 1, 1, 0.05), "")
	else:
		_draw_stack(x, ROW_Y, stock, STOCK_FAN, "stock", -1, 6)
		var count := Label.new()
		count.text = str(stock.size())
		count.add_theme_font_size_override("font_size", 30)
		count.position = Vector2(x + _card_w() - 60, ROW_Y + _card_h() - 46)
		count.modulate = Color(1, 1, 1, 0.95)
		add_child(count)
	_zones[_zone_key("stock", -1)] = Rect2(x, ROW_Y, _card_w(), _card_h())


func _build_tableau(data: Dictionary) -> void:
	var tableau: Array = data.get("tableau", [])
	for col in 7:
		var cards: Array = tableau[col] if col < tableau.size() else []
		var x := _tableau_x(col)
		if cards.is_empty():
			_draw_slot_placeholder(x, TAB_TOP, Color(1, 1, 1, 0.05), "")
		else:
			var flags: Array = []
			for card in cards:
				flags.append(card.get("face_up", false))
			var geom := BoardGeometry.tableau_offsets(flags, _tab_avail())
			if not geom.valid:
				continue
			var positions := BoardGeometry.positions(TAB_TOP, geom.offsets)
			for i in cards.size():
				var card: Dictionary = cards[i]
				var view := _make_card(card, positions[i], x, "tableau", col, i)
				add_child(view)
		_zones[_zone_key("tableau", col)] = Rect2(x, TAB_TOP, _card_w(), maxi(_card_h(), _tab_bottom() - TAB_TOP))


func _make_card(card: Dictionary, y: int, x: int, kind: String, index: int, card_index: int) -> CardView:
	var id := int(card.get("id", -1))
	var face_up := bool(card.get("face_up", false))
	var view := CardView.new()
	view.set_position(Vector2(x, y))
	view.set_size(Vector2(_card_w(), _card_h()))
	var source := {"kind": kind, "index": index, "card_index": card_index}
	view.configure(id, face_up, _textures_for(id), source)
	view.press_handler = controller_press
	view.release_handler = controller_release
	view.double_handler = controller_double
	return view


func _textures_for(id: int) -> Dictionary:
	if _face_texture_cache.has(id):
		return _face_texture_cache[id]
	var textures := LegacyAtlas.face_textures(id)
	_face_texture_cache[id] = textures
	return textures


## Horizontal fan with the top (newest) card aligned at the slot origin:
## older visible cards are offset to the right by `step` px each, so the
## playable top card always sits at the base slot position.
func _draw_stack(x: int, y: int, cards: Array, fan: int, kind: String, index: int, step: int = 36) -> void:
	var shown := mini(cards.size(), fan)
	var start := cards.size() - shown
	for i in range(start, cards.size()):
		var card: Dictionary = cards[i]
		var x_offset := (cards.size() - 1 - i) * step
		var view := _make_card(card, y, x + x_offset, kind, index, i)
		add_child(view)


func _draw_slot_placeholder(x: int, y: int, _color: Color, label_text: String) -> void:
	var style := StyleBoxFlat.new()
	style.bg_color = Color(1, 1, 1, 0.04)
	style.border_color = Color(1, 1, 1, 0.18)
	style.set_border_width_all(2)
	style.set_corner_radius_all(10)
	var styled := Panel.new()
	styled.set_position(Vector2(x, y))
	styled.set_size(Vector2(_card_w(), _card_h()))
	styled.add_theme_stylebox_override("panel", style)
	styled.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(styled)
	if not label_text.is_empty():
		var label := Label.new()
		label.text = label_text
		label.add_theme_font_size_override("font_size", 22)
		label.position = Vector2(x + 6, y + 4)
		label.modulate = Color(1, 1, 1, 0.35)
		label.mouse_filter = Control.MOUSE_FILTER_IGNORE
		add_child(label)


func _slot_label(text: String) -> String:
	return text


func _zone_key(kind: String, index: int) -> String:
	return "%s:%d" % [kind, index]


func _on_stock_input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index != MOUSE_BUTTON_LEFT:
			return
		if not event.pressed:
			return
		if _stock_callback.is_valid():
			_stock_callback.call()
	elif event is InputEventScreenTouch:
		if event.pressed and _stock_callback.is_valid():
			_stock_callback.call()


func set_stock_callback(cb: Callable) -> void:
	_stock_callback = cb


# ----- interaction queries for the controller (read-only geometry) -----

## Which container lies at a board-local position: {kind,index} or {} when the
## position is not over any drop target. Waste is only a valid drop target when
## empty (there is no move onto a non-empty waste), but the controller already
## rejects those; the geometry still reports the container for feedback.
func slot_at(local_pos: Vector2) -> Dictionary:
	for key in _zones:
		if _zones[key].has_point(local_pos):
			var parts: PackedStringArray = String(key).split(":")
			return {"kind": parts[0], "index": int(parts[1])}
	return {}


func zone_rect(kind: String, index: int) -> Rect2:
	return _zones.get(_zone_key(kind, index), Rect2())


func local_from_global(global_pos: Vector2) -> Vector2:
	return global_pos - get_global_transform().origin


# ----- drag ghost (visual only) -----

func _build_drag_layer() -> void:
	_drag_layer = Control.new()
	_drag_layer.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_drag_layer.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	add_child(_drag_layer)


func begin_ghost(card_id: int, run_count: int, local_pos: Vector2) -> void:
	end_ghost()
	_ghost = CardView.new()
	_ghost.set_size(_ghost_size)
	_ghost.configure(card_id, true, _textures_for(card_id), {})
	_ghost.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_drag_layer.add_child(_ghost)
	if run_count > 1:
		_ghost_badge = Label.new()
		_ghost_badge.text = "x%d" % run_count
		_ghost_badge.add_theme_font_size_override("font_size", 26)
		_ghost_badge.modulate = Color(1, 1, 1, 0.9)
		_drag_layer.add_child(_ghost_badge)
	move_ghost(local_pos)


func move_ghost(local_pos: Vector2) -> void:
	if _ghost == null:
		return
	_ghost.set_position(local_pos + Vector2(18, 18) - _ghost_size / 2)
	if _ghost_badge != null:
		_ghost_badge.set_position(local_pos + Vector2(18, 18) + Vector2(_ghost_size.x / 2, -8))


func end_ghost() -> void:
	if _ghost != null:
		_ghost.queue_free()
		_ghost = null
	if _ghost_badge != null:
		_ghost_badge.queue_free()
		_ghost_badge = null


# ----- hint highlight overlays (read-only feedback) -----

func show_hint(source: Dictionary, target: Dictionary) -> void:
	clear_hint()
	if _hint_layer == null:
		_hint_layer = Control.new()
		_hint_layer.mouse_filter = Control.MOUSE_FILTER_IGNORE
		_hint_layer.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
		add_child(_hint_layer)
	var s_rect := _rect_for_move_source(source)
	var t_rect := _rect_for_move_target(target)
	var added := 0
	if s_rect.has_area():
		_hint_layer.add_child(_make_overlay(s_rect, HINT_SOURCE_COLOR))
		added += 1
	if t_rect.has_area():
		_hint_layer.add_child(_make_overlay(t_rect, HINT_TARGET_COLOR))
		added += 1
	if added == 0:
		clear_hint()


func clear_hint() -> void:
	if _hint_layer == null:
		return
	remove_child(_hint_layer)
	_hint_layer.queue_free()
	_hint_layer = null


## Read-only introspection used by tests / MCP runtime checks.
func hint_active() -> bool:
	return _hint_layer != null


func hint_overlay_count() -> int:
	return _hint_layer.get_child_count() if _hint_layer != null else 0


func hint_overlay_rects() -> Array:
	var out: Array = []
	if _hint_layer == null:
		return out
	for child in _hint_layer.get_children():
		if child is ColorRect:
			out.append((child as ColorRect).get_rect())
	return out


func hint_overlay_colors() -> Array:
	var out: Array = []
	if _hint_layer == null:
		return out
	for child in _hint_layer.get_children():
		if child is ColorRect:
			out.append((child as ColorRect).color)
	return out


func _rect_for_move_source(source: Dictionary) -> Rect2:
	return _zones.get(_zone_key(source.get("kind", ""), int(source.get("index", -1))), Rect2())


func _rect_for_move_target(target: Dictionary) -> Rect2:
	return _zones.get(_zone_key(target.get("kind", ""), int(target.get("index", -1))), Rect2())


func _make_overlay(rect: Rect2, color: Color) -> ColorRect:
	var overlay := ColorRect.new()
	overlay.position = rect.position
	overlay.size = rect.size
	overlay.color = color
	overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	return overlay
