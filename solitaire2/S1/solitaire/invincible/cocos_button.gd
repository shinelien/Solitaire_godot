class_name InvincibleButton
extends TextureButton
## Cocos Scale9 buttons preserve their border widths when the widget grows.
@export var scale9_margins := Vector4.ZERO
var surface: NinePatchRect

func _ready() -> void:
	surface = NinePatchRect.new()
	surface.name = "Scale9Surface"
	surface.mouse_filter = Control.MOUSE_FILTER_IGNORE
	surface.self_modulate = self_modulate
	self_modulate.a = 0
	add_child(surface)
	move_child(surface, 0)
	surface.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	queue_redraw()

func _draw() -> void:
	if surface == null:
		return
	var texture := texture_normal
	if get_draw_mode() == BaseButton.DRAW_DISABLED and texture_disabled != null:
		texture = texture_disabled
	elif get_draw_mode() in [BaseButton.DRAW_PRESSED, BaseButton.DRAW_HOVER_PRESSED] and texture_pressed != null:
		texture = texture_pressed
	if texture == null:
		return
	surface.texture = texture
	surface.patch_margin_left = clampi(int(scale9_margins.x), 0, int(texture.get_width() / 2))
	surface.patch_margin_right = clampi(int(scale9_margins.y), 0, int(texture.get_width() / 2))
	surface.patch_margin_top = clampi(int(scale9_margins.z), 0, int(texture.get_height() / 2))
	surface.patch_margin_bottom = clampi(int(scale9_margins.w), 0, int(texture.get_height() / 2))
