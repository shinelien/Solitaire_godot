class_name NewHDCard
extends Node2D
const CARD_SIZE := Vector2(148, 220)
var card_id := 0
var source: Dictionary = {}
var face_up := false
var shown_face := false
var face_skin := 0
var back_skin := 0
var spine: NewHDSpineActor
var motion: Tween

func _ready() -> void:
	spine = NewHDSpineActor.new()
	add_child(spine)
	spine.configure("card")
	spine.spine_event.connect(_face_event)
	spine.clip_finished.connect(func(clip: StringName):
		if clip == &"RESET":
			return
		shown_face = face_up
		_update_skin()
		spine.play("RESET"))

func configure(id: int, face: int, back: int) -> void:
	card_id = id
	face_skin = face
	back_skin = back
	_update_skin()

func _update_skin() -> void:
	var prefix := ""
	spine.overrides.card_bg_1 = NewHDAtlas.texture(prefix + ("card_fronts.png" if shown_face else "card_bg_%d.png" % back_skin))
	var suit := card_id / 13
	var rank := card_id % 13 + 1
	var style := 0 if face_skin == 0 else face_skin + 1
	if rank <= 10 and style == 3:
		style = 0
	var image := "card_%d_%s%s.png" % [style, char(65 + suit), str(rank) if rank > 10 else ""]
	spine.overrides.poker0 = NewHDAtlas.texture(prefix + image)
	spine.overrides.poker2 = NewHDAtlas.texture(prefix + "card_0%d.png" % rank)
	spine.overrides.poker3 = spine.overrides.poker2
	spine.hidden_slots.poker0 = not shown_face
	spine.hidden_slots.poker2 = not shown_face or suit % 2 != 0
	spine.hidden_slots.poker3 = not shown_face or suit % 2 == 0
	spine._sample(spine.sample_time)

func _face_event(event: String) -> void:
	if event in ["flop", "unflop"]:
		shown_face = face_up
		_update_skin()

func show_face(value: bool, animate := false, stock := false, left := false) -> float:
	face_up = value
	if animate and shown_face != value:
		var clip := "Flip0" if value else "Flip3"
		if stock:
			clip = ("Flip_L1" if left else "Flip1") if value else ("Flip_L2" if left else "Flip2")
		return spine.play(clip)
	shown_face = value
	_update_skin()
	spine.play("RESET")
	return 0

func travel(target: Vector2, duration := .1, delay := 0.0) -> void:
	if motion != null and motion.is_valid():
		motion.kill()
	if duration <= 0:
		position = target
		return
	motion = create_tween()
	if delay > 0:
		motion.tween_interval(delay)
	motion.tween_property(self, "position", target, duration)

func contains_point(point: Vector2) -> bool:
	return Rect2(position - CARD_SIZE / 2, CARD_SIZE).has_point(point)

func reject() -> void:
	var tween := create_tween()
	tween.tween_property(self, "rotation", deg_to_rad(10), .05)
	tween.tween_property(self, "rotation", deg_to_rad(-10), .1)
	tween.tween_property(self, "rotation", 0.0, .05)

func lift(value: bool) -> void:
	spine.play("touch1" if value else "RESET")
