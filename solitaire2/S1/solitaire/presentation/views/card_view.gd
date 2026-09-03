class_name CardView
extends Control

## One playable card in the pure-2D board (WP-08). It is a render/input-only
## Control: it shows whatever textures BoardView configured (never reads a
## GameState and knows no solitaire rule) and forwards raw press/release/tap
## intents to the controller callables configured by BoardView. All gameplay
## decision making lives in the controller / application / core layers.

## Conventional double-click / double-tap window (review: 350–500ms; 450ms
## preferred). A second press within this window after the previous release is
## a double action; ordinary separate clicks fall outside it.
const DOUBLE_TAP_MS := 450

## Legacy face composition (WP-08 correction 1): the rank glyph is its own
## 56x56 atlas region and is rendered at its native size in the card top-left
## corner (legacy CardFace `Sprite_num` 56x56, anchor center x = 28), never
## stretched to the full 148x220 card.
const RANK_CELL := 56
const RANK_CELL_CENTER_X := 28

## Placement descriptor set by BoardView: {kind, index, card_index}.
var source: Dictionary = {}
var card_id := -1
var face_up := false

var press_handler: Callable = Callable()
var release_handler: Callable = Callable()
var double_handler: Callable = Callable()

var _layer_base: TextureRect = null
var _layer_suit: TextureRect = null
var _layer_rank: TextureRect = null
var _layer_back: TextureRect = null
var _fallback: ColorRect = null

var _last_release_msec := -1


func _init() -> void:
	mouse_filter = Control.MOUSE_FILTER_STOP
	_fallback = ColorRect.new()
	_fallback.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_fallback.color = Color(0.28, 0.44, 0.6)
	add_child(_fallback)

	_layer_base = _make_layer()
	_layer_suit = _make_layer()
	_layer_rank = _make_layer()
	_layer_back = _make_layer()
	_layer_base.visible = false
	_layer_suit.visible = false
	_layer_rank.visible = false
	_layer_back.visible = false
	_fallback.visible = true


func _make_layer() -> TextureRect:
	var rect := TextureRect.new()
	rect.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	rect.mouse_filter = Control.MOUSE_FILTER_IGNORE
	rect.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	rect.stretch_mode = TextureRect.STRETCH_SCALE
	add_child(rect)
	return rect


## face textures from LegacyAtlas.face_textures(): {base,suit,rank,back,red}.
func configure(p_id: int, is_face_up: bool, textures: Dictionary, p_source: Dictionary) -> void:
	card_id = p_id
	face_up = is_face_up
	source = p_source
	var base: Texture2D = textures.get("base")
	var suit: Texture2D = textures.get("suit")
	var rank: Texture2D = textures.get("rank")
	var back: Texture2D = textures.get("back")
	_layer_base.texture = base
	_layer_suit.texture = suit
	_layer_rank.texture = rank
	_layer_back.texture = back
	var red := bool(textures.get("red", false))
	_layer_rank.modulate = Color(0.72, 0.08, 0.08) if red else Color(0.12, 0.12, 0.15)
	_layer_base.visible = is_face_up and base != null
	_layer_suit.visible = is_face_up and suit != null
	_layer_rank.visible = is_face_up and rank != null
	_layer_back.visible = (not is_face_up) and back != null
	_fallback.visible = (not _layer_base.visible and not _layer_back.visible)
	if _layer_rank.visible:
		_layout_rank_native()


## Keep the rank glyph at its native 56x56 region size anchored in the card
## top-left corner (center x = RANK_CELL_CENTER_X), matching the legacy
## CardFace layout. The card node must already have its final size when a
## rank texture is configured so the anchors resolve to the real card bounds.
func _layout_rank_native() -> void:
	if _layer_rank == null:
		return
	_layer_rank.set_anchors_and_offsets_preset(Control.PRESET_TOP_LEFT)
	_layer_rank.position = Vector2.ZERO
	_layer_rank.size = Vector2(RANK_CELL, RANK_CELL)
	_layer_rank.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	_layer_rank.stretch_mode = TextureRect.STRETCH_SCALE


## Local (card-space) rect of the rank overlay; used by layout assertions.
## Empty when the card is face-down (no rank layer shown).
func rank_rect() -> Rect2:
	if _layer_rank == null or not _layer_rank.visible:
		return Rect2()
	return _layer_rank.get_rect()


## Displayed size of the rank overlay layer (asserted to equal the native
## 56x56 region size so the glyph is never stretched).
func rank_display_size() -> Vector2:
	if _layer_rank == null or not _layer_rank.visible:
		return Vector2.ZERO
	return _layer_rank.size


func set_selected(selected: bool) -> void:
	if selected:
		modulate = Color(1.0, 1.0, 0.55)
	else:
		modulate = Color.WHITE


func _gui_input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		var button: InputEventMouseButton = event as InputEventMouseButton
		if button.button_index != MOUSE_BUTTON_LEFT:
			return
		var global: Vector2 = get_global_transform() * button.position
		if button.pressed:
			_handle_press(global)
		else:
			_handle_release(global)
	elif event is InputEventScreenTouch:
		var touch: InputEventScreenTouch = event as InputEventScreenTouch
		if touch.pressed:
			_handle_press(touch.position)
		else:
			_handle_release(touch.position)


func _handle_press(global_pos: Vector2) -> void:
	var now := Time.get_ticks_msec()
	if _last_release_msec >= 0 and (now - _last_release_msec) < DOUBLE_TAP_MS:
		_last_release_msec = -1
		if double_handler.is_valid():
			double_handler.call(self, global_pos)
		return
	if press_handler.is_valid():
		press_handler.call(self, global_pos)


func _handle_release(global_pos: Vector2) -> void:
	_last_release_msec = Time.get_ticks_msec()
	if release_handler.is_valid():
		release_handler.call(self, global_pos)
