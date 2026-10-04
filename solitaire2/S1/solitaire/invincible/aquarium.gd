class_name InvincibleAquarium
extends Node2D
var profile: InvincibleProfile
var background: InvincibleScene
var fish_nodes: Array[InvincibleSpineActor] = []
var targets: Array[Vector2] = []
var speeds: Array[float] = []
var feeding := false
var hunger_clock := 0.0

func configure(player: InvincibleProfile) -> void:
	profile = player
	if background != null:
		background.queue_free()
	background = load("res://scenes/invincible/ui/desktop/scene%d.tscn" % profile.current_tank).instantiate()
	add_child(background)
	move_child(background, 0)
	background.play_clip("loop", true)
	var top := background.find_child("Panel_top", true, false) as CanvasItem
	if top != null:
		top.hide()
	for i in range(1, 20):
		for name in [str(i), "FileNode_%d" % i]:
			var decoration := background.find_child(name, true, false) as CanvasItem
			if decoration != null:
				decoration.visible = i - 1 in profile.decorations[profile.current_tank]
	for fish in fish_nodes:
		fish.queue_free()
	fish_nodes.clear()
	targets.clear()
	speeds.clear()
	for data: Dictionary in profile.tanks[profile.current_tank]:
		var actor := InvincibleSpineActor.new()
		add_child(actor)
		actor.configure("fish%d" % int(data.type))
		actor.play("Run", true)
		actor.position = Vector2(randf_range(180, 900), randf_range(500, 1430))
		actor.scale = Vector2.ONE * .8
		fish_nodes.append(actor)
		targets.append(Vector2(randf_range(150, 930), randf_range(500, 1460)))
		speeds.append(randf_range(40, 80))

func _process(delta: float) -> void:
	if profile == null:
		return
	hunger_clock += delta
	if hunger_clock >= 60:
		hunger_clock = 0
		profile.update_hunger(int(Time.get_unix_time_from_system()))
	for i in fish_nodes.size():
		var fish := fish_nodes[i]
		var data: Dictionary = profile.tanks[profile.current_tank][i]
		if int(data.hp) == 0:
			fish.modulate = Color(.6, .7, .75, .8)
		var direction := targets[i] - fish.position
		if direction.length() < 10:
			targets[i] = Vector2(randf_range(150, 930), randf_range(500, 1460))
			fish.play("Run", true)
		fish.position += direction.normalized() * delta * speeds[i] * (.3 if int(data.hp) == 0 else 1)
		fish.scale.x = absf(fish.scale.x) * (1 if direction.x < 0 else -1)

func feed() -> bool:
	var hungry := false
	for fish: Dictionary in profile.tanks[profile.current_tank]:
		hungry = hungry or int(fish.hp) < 60
	if not hungry or feeding:
		return false
	feeding = true
	var point := Vector2(540 + randf_range(-200, 200), 960 + randf_range(-200, 200))
	var food := load("res://scenes/invincible/ui/Animation/Node_siliao.tscn").instantiate() as InvincibleScene
	add_child(food)
	food.position = point
	var duration := food.play_clip("start")
	get_tree().create_timer(maxf(1, duration)).timeout.connect(func():
		food.queue_free()
		feeding = false)
	profile.feed()
	for i in fish_nodes.size():
		fish_nodes[i].modulate = Color.WHITE
		fish_nodes[i].play("happy", false)
		targets[i] = point
		speeds[i] = 100
	return true
