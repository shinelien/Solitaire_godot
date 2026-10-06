@tool
class_name MasterAtlasNumber
extends Control

@export var text := "0":
	set(value):
		text = value
		queue_redraw()
@export var glyph_size := Vector2(14, 18)
@export var first_character := "."
@export var atlas: Texture2D

func _draw() -> void:
	if atlas == null or first_character.is_empty():
		return
	var x := (size.x - glyph_size.x * text.length()) / 2.0
	for letter in text:
		var index := letter.unicode_at(0) - first_character.unicode_at(0)
		if index >= 0:
			draw_texture_rect_region(atlas, Rect2(Vector2(x, 0), glyph_size), Rect2(Vector2(index * glyph_size.x, 0), glyph_size))
		x += glyph_size.x
