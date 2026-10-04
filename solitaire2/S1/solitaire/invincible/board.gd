class_name InvincibleBoard
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

var foundation_points: Array[Vector2] = []
var tableau_points: Array[Vector2] = []
var stock_point := Vector2(991, 383)
var waste_point := Vector2(706, 383)
var waste_left_point := Vector2(267, 383)
var source_scene: Control

func _ready() -> void:
	for i in 4:
		foundation_points.append(Vector2(80 + 150.33 * i, 383))
	for i in 7:
		tableau_points.append(Vector2(80 + 150.33 * i, 610))
	for id in 52:
		var card := InvincibleCard.new()
		card.name = "Card%d" % id
		add_child(card)
		card.configure(id, face_skin, back_skin)
		cards[id] = card

func bind_scene(scene: Control) -> void:
	source_scene = scene
	for i in 4:
		var node := scene.find_child("Sprite_aPoker%d" % i, true, false) as Control
		foundation_points[i] = node.global_position + node.pivot_offset
	for i in 7:
		var node := scene.find_child("Sprite_pokerStack%d" % i, true, false) as Control
		tableau_points[i] = node.global_position + node.pivot_offset
	var stock := scene.find_child("Sprite_wait", true, false) as Control
	stock_point = stock.global_position + stock.pivot_offset
	var waste := scene.find_child("Node_waitOpen", true, false) as Control
	waste_point = waste.global_position
	var waste_three := scene.find_child("Node_waitOpenThree", true, false) as Control
	waste_left_point = Vector2(1080 - waste_three.global_position.x, waste_three.global_position.y)

func _mirror(x: float) -> float:
	return 1080 - x if left else x

func _p(point: Vector2) -> Vector2:
	return Vector2(_mirror(point.x), point.y)

func _update_slots() -> void:
	if source_scene == null:
		return
	var container := source_scene.find_child("Node_bg", true, false)
	for node in container.get_children():
		if node is Control:
			var original: Vector2 = node.get_meta("original_position", node.position)
			node.set_meta("original_position", original)
			node.position.x = -original.x - 2 * node.pivot_offset.x if left else original.x

func set_skins(profile: InvincibleProfile) -> void:
	left = profile.settings.left
	face_skin = profile.settings.face
	back_skin = profile.settings.back
	for card in cards.values():
		card.configure(card.card_id, profile.card_style(card.card_id), back_skin)
	_update_slots()

func build_layout(state: GameState) -> Dictionary:
	var out := {}
	for i in state.stock.size():
		var card := state.stock.card_at(i)
		var depth := mini(i, 7)
		var offset_x: float = [0, .5, 1, 2, 3, 4, 5, 6][depth]
		out[card.id] = {"pos": _p(stock_point) + Vector2(offset_x, -depth * 3), "face": false, "z": i, "source": {"kind": "stock", "index": -1, "card_index": i}}
	var visible := mini(3, state.waste.size())
	for i in state.waste.size():
		var fan := maxi(0, i - state.waste.size() + visible)
		var card := state.waste.card_at(i)
		out[card.id] = {"pos": (waste_left_point if left else waste_point) + Vector2(fan * 57, 0), "face": true, "z": 60 + i, "source": {"kind": "waste", "index": -1, "card_index": i}}
	for col in 4:
		for i in state.foundation[col].size():
			var card := state.foundation[col].card_at(i)
			out[card.id] = {"pos": _p(foundation_points[col]), "face": true, "z": 100 + i, "source": {"kind": "foundation", "index": col, "card_index": i}}
	for col in 7:
		var y := tableau_points[col].y
		for i in state.tableau[col].size():
			var card := state.tableau[col].card_at(i)
			out[card.id] = {"pos": Vector2(_mirror(tableau_points[col].x), y), "face": card.face_up, "z": 160 + i, "source": {"kind": "tableau", "index": col, "card_index": i}}
			y += 66.0 if card.face_up else 30.0
	return out

func present(state: GameState, animate := true) -> float:
	clear_hint()
	var next := build_layout(state)
	var duration := .15 if animate else 0.0
	var latest := duration
	var draw_offset := 0
	for id in next:
		var card: InvincibleCard = cards[id]
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
			var card: InvincibleCard = cards[state.tableau[col].card_at(i).id]
			card.show_face(false)
			card.position = Vector2(540, 2040)
			card.z_index = layout[card.card_id].z
			card.source = layout[card.card_id].source
			number += 1
			card.travel(layout[card.card_id].pos, .2, number * .05)
	for pile in [state.stock, state.waste]:
		for item in pile.cards_snapshot():
			var card: InvincibleCard = cards[item.id]
			card.show_face(false)
			card.source = layout[item.id].source
			card.position = Vector2(-148 if left else 1228, stock_point.y)
			card.z_index = layout[item.id].z
			card.travel(_p(stock_point), .3, 1.9)
	await get_tree().create_timer(2.2).timeout
	for col in 7:
		var card: InvincibleCard = cards[state.tableau[col].top().id]
		card.show_face(true, true, false, left)
	for i in state.waste.size():
		var item := state.waste.card_at(i)
		var card: InvincibleCard = cards[item.id]
		card.travel(layout[item.id].pos, .2, i * .06)
		get_tree().create_timer(i * .06).timeout.connect(card.show_face.bind(true, true, true, left))
	await get_tree().create_timer(.55).timeout
	settle_layers()

func hit(point: Vector2, state: GameState) -> InvincibleCard:
	var chosen: InvincibleCard = null
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
	return Rect2(_p(stock_point) - InvincibleCard.CARD_SIZE / 2, InvincibleCard.CARD_SIZE).has_point(point)

func drop_target(point: Vector2, moving_card: InvincibleCard) -> Dictionary:
	# Original tests overlap of the dragged card against the destination card.
	var moving := Rect2(point - InvincibleCard.CARD_SIZE / 2, InvincibleCard.CARD_SIZE)
	for col in 4:
		var box := Rect2(_p(foundation_points[col]) - InvincibleCard.CARD_SIZE / 2, InvincibleCard.CARD_SIZE)
		if moving.intersects(box):
			return {"kind": "foundation", "index": col}
	var candidates := []
	for col in 7:
		var target := _p(tableau_points[col])
		for id in layout:
			var entry: Dictionary = layout[id]
			if entry.source.kind == "tableau" and entry.source.index == col:
				target = entry.pos
		var box := Rect2(target - InvincibleCard.CARD_SIZE / 2 - Vector2(0, 15), InvincibleCard.CARD_SIZE + Vector2(0, 15))
		if moving.intersects(box) and not (moving_card.source.kind == "tableau" and moving_card.source.index == col):
			candidates.append({"kind": "tableau", "index": col, "distance": target.distance_to(point)})
	if not candidates.is_empty():
		candidates.sort_custom(func(a, b): return a.distance < b.distance)
		return candidates[0]
	return {}

func begin_drag(card: InvincibleCard, point: Vector2) -> void:
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
	var card: InvincibleCard = cards[source_id]
	var target: Vector2
	if move.kind in [Move.MoveKind.TABLEAU_TO_FOUNDATION, Move.MoveKind.WASTE_TO_FOUNDATION]:
		target = _p(foundation_points[move.target_index])
	elif move.kind == Move.MoveKind.DRAW_STOCK:
		target = _p(waste_point)
	else:
		target = _p(tableau_points[move.target_index])
		var pile := state.tableau[move.target_index]
		if not pile.is_empty():
			target = layout[pile.top().id].pos + Vector2(0, 66)
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
