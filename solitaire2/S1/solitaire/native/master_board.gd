class_name MasterBoard
extends Node2D

var cards: Dictionary = {}
var layout: Dictionary = {}
var left := false
var face_skin := 0
var back_skin := 0
var _slots: Array[Sprite2D] = []
var drag_ids: Array[int] = []
var drag_origin: Dictionary = {}
var drag_start := Vector2.ZERO
var _hint_tween: Tween

func _ready() -> void:
	for i in 11:
		var slot := Sprite2D.new()
		slot.texture = load("res://assets/master/game/img_card_a.png" if i < 4 else "res://assets/master/game/img_card_k.png")
		slot.scale = Vector2.ONE * .9
		_slots.append(slot)
		add_child(slot)
	var refresh := Sprite2D.new()
	refresh.name = "Recycle"
	refresh.texture = preload("res://assets/master/game/img_card_refush.png")
	refresh.scale = Vector2.ONE * .9
	add_child(refresh)
	for id in 52:
		var card := MasterCard.new()
		card.name = "Card%d" % id
		add_child(card)
		card.configure(id, face_skin, back_skin)
		cards[id] = card
	_update_slots()

func _mirror(x: float) -> float:
	return 576.0 - x if left else x

func _update_slots() -> void:
	for i in 11:
		_slots[i].position = Vector2(_mirror(57 + 77 * (i if i < 4 else i - 4)), 144 if i < 4 else 304)
	$Recycle.position = Vector2(_mirror(519), 144)

func set_skins(profile: SolitaireProfile) -> void:
	left = profile.settings.left
	face_skin = profile.settings.face
	back_skin = profile.settings.back
	for card in cards.values():
		card.configure(card.card_id, face_skin, back_skin)
	_update_slots()

func build_layout(state: GameState) -> Dictionary:
	var out := {}
	for i in state.stock.size():
		var card := state.stock.card_at(i)
		out[card.id] = {"pos": Vector2(_mirror(519), 144), "face": false, "z": i, "source": {"kind": "stock", "index": -1, "card_index": i}}
	var visible := mini(3, state.waste.size())
	for i in state.waste.size():
		var fan := maxi(0, i - state.waste.size() + visible)
		var card := state.waste.card_at(i)
		out[card.id] = {"pos": Vector2(_mirror(375 + fan * 25), 144 + fan * 15), "face": true, "z": 60 + i, "source": {"kind": "waste", "index": -1, "card_index": i}}
	for col in 4:
		for i in state.foundation[col].size():
			var card := state.foundation[col].card_at(i)
			out[card.id] = {"pos": Vector2(_mirror(57 + col * 77), 144), "face": true, "z": 100 + i, "source": {"kind": "foundation", "index": col, "card_index": i}}
	for col in 7:
		var y := 304.0
		for i in state.tableau[col].size():
			var card := state.tableau[col].card_at(i)
			out[card.id] = {"pos": Vector2(_mirror(57 + col * 77), y), "face": card.face_up, "z": 160 + i, "source": {"kind": "tableau", "index": col, "card_index": i}}
			y += 35.0 if card.face_up else 10.0
	return out

func present(state: GameState, animate := true) -> float:
	clear_hint()
	var next := build_layout(state)
	var duration := .1 if animate else 0.0
	var latest := duration
	var draw_offset := 0
	for id in next:
		var card: MasterCard = cards[id]
		var entry: Dictionary = next[id]
		var old: Dictionary = layout.get(id, {})
		card.source = entry.source
		var stock_flip: bool = (old.get("source", {}).get("kind") in ["stock", "waste"] and entry.source.kind in ["stock", "waste"])
		var delay := 0.0
		if animate and stock_flip and old.get("face", entry.face) != entry.face:
			delay = draw_offset * .06
			draw_offset += 1
		card.z_index = entry.z
		if animate and card.position.distance_to(entry.pos) > .1:
			card.z_index = 400 + entry.z
		card.travel(entry.pos, duration, delay)
		if delay > 0:
			get_tree().create_timer(delay).timeout.connect(card.show_face.bind(entry.face, animate, stock_flip, left))
		else:
			var clip_time := card.show_face(entry.face, animate, stock_flip, left)
			latest = maxf(latest, clip_time)
		latest = maxf(latest, delay + .5 if animate else 0.0)
	layout = next
	return latest

func settle_layers() -> void:
	for id in layout:
		cards[id].z_index = layout[id].z

func deal(state: GameState) -> void:
	layout = build_layout(state)
	var number := 0
	for col in 7:
		for i in state.tableau[col].size():
			var card: MasterCard = cards[state.tableau[col].card_at(i).id]
			card.show_face(false)
			card.position = Vector2(288, 1044)
			card.z_index = layout[card.card_id].z
			card.source = layout[card.card_id].source
			number += 1
			card.travel(layout[card.card_id].pos, .2, number * .05)
	for pile in [state.stock, state.waste]:
		for item in pile.cards_snapshot():
			var card: MasterCard = cards[item.id]
			card.show_face(false)
			card.source = layout[item.id].source
			card.position = Vector2(-64 if left else 640, 144)
			card.z_index = layout[item.id].z
			card.travel(Vector2(_mirror(519), 144), .3, 1.9)
	await get_tree().create_timer(2.2).timeout
	for col in 7:
		var card: MasterCard = cards[state.tableau[col].top().id]
		card.show_face(true, true, false, left)
	for i in state.waste.size():
		var item := state.waste.card_at(i)
		var card: MasterCard = cards[item.id]
		card.travel(layout[item.id].pos, .2, i * .06)
		get_tree().create_timer(i * .06).timeout.connect(card.show_face.bind(true, true, true, left))
	await get_tree().create_timer(.55).timeout
	settle_layers()

func hit(point: Vector2, state: GameState) -> MasterCard:
	var chosen: MasterCard = null
	for card in cards.values():
		if not card.contains_point(point):
			continue
		var src: Dictionary = card.source
		if src.is_empty():
			continue
		var kind: String = src.kind
		var valid := false
		match kind:
			"stock": valid = src.card_index == state.stock.size() - 1
			"waste": valid = src.card_index == state.waste.size() - 1
			"foundation": valid = src.card_index == state.foundation[src.index].size() - 1
			"tableau": valid = card.face_up
		if valid and (chosen == null or card.z_index > chosen.z_index):
			chosen = card
	return chosen

func stock_contains(point: Vector2) -> bool:
	return Rect2(Vector2(_mirror(519), 144) - MasterCard.CARD_SIZE / 2, MasterCard.CARD_SIZE).has_point(point)

func drop_target(point: Vector2, moving_card: MasterCard) -> Dictionary:
	# Original tests overlap of the dragged card against the destination card.
	var moving := Rect2(point - MasterCard.CARD_SIZE / 2, MasterCard.CARD_SIZE)
	for col in 4:
		var box := Rect2(Vector2(_mirror(57 + col * 77), 144) - MasterCard.CARD_SIZE / 2, MasterCard.CARD_SIZE)
		if moving.intersects(box):
			return {"kind": "foundation", "index": col}
	var candidates := []
	for col in 7:
		var target := Vector2(_mirror(57 + col * 77), 304)
		for id in layout:
			var entry: Dictionary = layout[id]
			if entry.source.kind == "tableau" and entry.source.index == col:
				target = entry.pos
		var box := Rect2(target - MasterCard.CARD_SIZE / 2 - Vector2(0, 15), MasterCard.CARD_SIZE + Vector2(0, 15))
		if moving.intersects(box) and not (moving_card.source.kind == "tableau" and moving_card.source.index == col):
			candidates.append({"kind": "tableau", "index": col, "distance": target.distance_to(point)})
	if not candidates.is_empty():
		candidates.sort_custom(func(a, b): return a.distance < b.distance)
		return candidates[0]
	return {}

func begin_drag(card: MasterCard, point: Vector2) -> void:
	clear_hint()
	drag_ids.clear()
	drag_origin.clear()
	drag_start = point
	var source: Dictionary = card.source
	for id in layout:
		var entry: Dictionary = layout[id]
		if id == card.card_id or (source.kind == "tableau" and entry.source.kind == source.kind and entry.source.index == source.index and entry.source.card_index >= source.card_index):
			drag_ids.append(id)
			drag_origin[id] = cards[id].position
			cards[id].z_index = 1000 + entry.source.card_index
			cards[id].lift(true)

func drag_to(point: Vector2) -> void:
	for id in drag_ids:
		cards[id].position = drag_origin[id] + point - drag_start

func end_drag() -> void:
	for id in drag_ids:
		cards[id].lift(false)
	drag_ids.clear()
	drag_origin.clear()

func hint(move: Move, state: GameState) -> void:
	clear_hint()
	var source_id := -1
	match move.kind:
		Move.MoveKind.TABLEAU_TO_FOUNDATION, Move.MoveKind.TABLEAU_TO_TABLEAU:
			var pile := state.tableau[move.source_index]
			source_id = pile.card_at(pile.size() - move.count).id
		Move.MoveKind.WASTE_TO_FOUNDATION, Move.MoveKind.WASTE_TO_TABLEAU:
			source_id = state.waste.top().id
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			source_id = state.foundation[move.source_index].top().id
		Move.MoveKind.DRAW_STOCK:
			source_id = state.stock.top().id
	if source_id < 0:
		return
	var card: MasterCard = cards[source_id]
	var target: Vector2
	if move.kind in [Move.MoveKind.TABLEAU_TO_FOUNDATION, Move.MoveKind.WASTE_TO_FOUNDATION]:
		target = Vector2(_mirror(57 + move.target_index * 77), 144)
	elif move.kind == Move.MoveKind.DRAW_STOCK:
		target = Vector2(_mirror(375), 144)
	else:
		target = Vector2(_mirror(57 + move.target_index * 77), 304)
		var pile := state.tableau[move.target_index]
		if not pile.is_empty():
			target = layout[pile.top().id].pos + Vector2(0, 35)
	card.z_index = 900
	_hint_tween = create_tween()
	_hint_tween.tween_property(card, "position", target, .5).set_trans(Tween.TRANS_SINE).set_ease(Tween.EASE_IN_OUT)
	_hint_tween.tween_interval(.3)
	_hint_tween.tween_property(card, "position", layout[source_id].pos, .5)
	_hint_tween.tween_interval(.7)

func clear_hint() -> void:
	if _hint_tween != null and _hint_tween.is_valid():
		_hint_tween.kill()
		for id in layout:
			cards[id].position = layout[id].pos
			cards[id].z_index = layout[id].z
	_hint_tween = null
