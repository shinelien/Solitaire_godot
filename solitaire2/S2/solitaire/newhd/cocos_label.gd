class_name NewHDLabel
extends Label
## Keep the authored center when Godot's font metrics differ from Cocos.
@export var design_size := Vector2.ZERO
@export var design_center := Vector2.ZERO
@export var design_font_size := 32
@export var bitmap_font := false
@export var fit_box := false

func _ready() -> void:
	fit_caption()

func set_caption(value: String) -> void:
	if text == value:
		return
	text = value
	fit_caption()

func fit_caption() -> void:
	if design_size.x <= 0 or design_size.y <= 0:
		return
	var font := get_theme_font("font")
	var font_size := design_font_size
	var limit := design_size if fit_box else Vector2(10000, 10000)
	if get_parent() is TextureButton:
		limit = (get_parent() as TextureButton).size * Vector2(.88, .8)
	var measured := Vector2.ZERO
	if not bitmap_font:
		while font_size > 8:
			var width := 0.0
			var lines := text.split("\n")
			for line in lines:
				width = maxf(width, font.get_string_size(line, HORIZONTAL_ALIGNMENT_LEFT, -1, font_size).x)
			measured = Vector2(width, font.get_height(font_size) * lines.size())
			if measured.x <= limit.x and measured.y <= limit.y:
				break
			font_size -= 1
	add_theme_font_size_override("font_size", font_size)
	if bitmap_font:
		measured = get_minimum_size()
	size = design_size.max(measured.ceil())
	position = design_center - size / 2
