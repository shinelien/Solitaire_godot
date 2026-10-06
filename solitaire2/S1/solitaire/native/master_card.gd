class_name MasterCard
extends Node2D

const CARD_SIZE := Vector2(71.4, 106.4)
var card_id := 0
var source: Dictionary = {}
var face_up := false
var spine: NativeSpineCard
var motion: Tween
var _shadow: Sprite2D

func _ready() -> void:
	_shadow = Sprite2D.new()
	_shadow.texture = preload("res://assets/master/game/img_card_shader.png")
	_shadow.position.y = 6.3
	_shadow.scale = Vector2.ONE * 1.435
	add_child(_shadow)
	spine = NativeSpineCard.new()
	spine.scale = CARD_SIZE / Vector2(148, 220)
	add_child(spine)

func configure(id: int, face_skin: int, back_skin: int) -> void:
	card_id = id
	spine.set_textures(MasterAtlas.texture("card_%d_%d_%d.png" % [face_skin, id % 13 + 1, id / 13]), MasterAtlas.texture("card_bg_%d.png" % back_skin))

func show_face(value: bool, animate := false, stock := false, left := false) -> float:
	face_up = value
	if animate and spine.shown_face != value:
		return spine.flip(value, stock, left)
	spine.shown_face = value
	spine.desired_face = value
	spine.reset_pose()
	return 0.0

func travel(target: Vector2, duration := 0.1, delay := 0.0) -> void:
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
	return Rect2(position - CARD_SIZE / 2.0, CARD_SIZE).has_point(point)

func reject() -> void:
	var tween := create_tween()
	tween.tween_property(self, "rotation", deg_to_rad(20), .05)
	tween.tween_property(self, "rotation", deg_to_rad(-20), .1)
	tween.tween_property(self, "rotation", 0.0, .05)

func lift(value: bool) -> void:
	if value:
		spine.desired_face = face_up
		spine.animation_player.play("touch1")
	else:
		spine.reset_pose()
