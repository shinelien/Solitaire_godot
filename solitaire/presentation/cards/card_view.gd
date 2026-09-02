class_name CardView
extends Control

## Renders one card (or an empty drop-zone placeholder) from CardData.
## Purely a view: never mutates GameState.

const CARD_W := 90.0
const CARD_H := 126.0

var card: CardData = null
var highlighted := false
var placeholder := false

func _ready() -> void:
	custom_minimum_size = Vector2(CARD_W, CARD_H)

func set_card(c: CardData, hl: bool = false) -> void:
	card = c
	highlighted = hl
	placeholder = false
	visible = true
	queue_redraw()

func set_placeholder() -> void:
	card = null
	highlighted = false
	placeholder = true
	visible = true
	queue_redraw()

func set_highlighted(hl: bool) -> void:
	if highlighted == hl:
		return
	highlighted = hl
	queue_redraw()

func hide_card() -> void:
	visible = false

func _draw() -> void:
	var rect := Rect2(Vector2.ZERO, Vector2(CARD_W, CARD_H))
	if placeholder or card == null:
		draw_rect(rect, Color(0.16, 0.22, 0.3, 0.35), true)
		draw_rect(rect, Color(1, 1, 1, 0.22), false, 1.5)
		return
	if not card.face_up:
		var back := Color(0.16, 0.28, 0.46)
		draw_rect(rect, back, true)
		draw_rect(rect, Color(0.03, 0.05, 0.1), false, 2.0)
		var line_color := Color(0.8, 0.9, 1.0, 0.30)
		for i in range(9):
			draw_line(Vector2(14.0 + i * 9.0, 4.0), Vector2(4.0, CARD_H - 8.0 - i * 5.0), line_color, 1.0)
		if highlighted:
			draw_rect(rect, Color(1.0, 0.84, 0.2, 0.95), false, 3.0)
		return
	draw_rect(rect, Color(0.97, 0.97, 0.97), true)
	draw_rect(rect, Color(0.04, 0.06, 0.1), false, 2.0)
	var ink := Color(0.82, 0.12, 0.12) if card.is_red() else Color(0.09, 0.09, 0.12)
	var font := ThemeDB.fallback_font
	var rank_label: String = CardData.RANK_LABELS[card.rank - 1]
	draw_string(font, Vector2(9, 28), rank_label, HORIZONTAL_ALIGNMENT_LEFT, -1, 20, ink)
	draw_string(font, Vector2(9, 48), CardData.SUIT_SYMBOLS[card.suit], HORIZONTAL_ALIGNMENT_LEFT, -1, 20, ink)
	draw_string(font, Vector2(CARD_W * 0.5 - 18, CARD_H * 0.5 + 22), \
		CardData.SUIT_SYMBOLS[card.suit], HORIZONTAL_ALIGNMENT_LEFT, -1, 44, ink)
	if highlighted:
		draw_rect(rect, Color(1.0, 0.84, 0.2, 0.95), false, 3.0)
