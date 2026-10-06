class_name NewHDBackground
extends Node2D
var profile: NewHDProfile
var theme: NewHDScene
var colors: Array = []
var color_index := -1
var themes: Array = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/ShopData.json")).gametheme

func configure(value: NewHDProfile) -> void:
	profile = value
	for child in get_children():
		remove_child(child)
		child.queue_free()
	colors.clear()
	color_index = -1
	theme = null
	var index := int(profile.settings.background)
	if index <= 13:
		var image := Sprite2D.new()
		image.texture = load("res://assets/newhd/game/background-%d.jpg" % index)
		image.centered = false
		image.scale = Vector2(1080, 1920) / image.texture.get_size()
		add_child(image)
		return
	var config: Dictionary = themes[index - 12]
	theme = load("res://scenes/newhd/ui/" + str(config.csb) + ".tscn").instantiate()
	add_child(theme)
	theme.play_clip(str(config.csbAni), true)
	var foreground := theme.find_child("Panel_top", true, false) as CanvasItem
	if foreground != null:
		foreground.z_as_relative = false
		foreground.z_index = 1500
	colors = config.get("color", [])
	change_color()
	if config.has("spine"):
		if config.spine is Array:
			for i in config.spine.size():
				var holder := theme.find_child(str(config.spineNode[i]), true, false)
				if holder != null:
					add_spine(holder, str(config.spineAni[i]), Vector2.ZERO)
		else:
			var padding: Array = config.get("spinePos", [0, 0])
			add_spine(theme, str(config.spineAni), Vector2(float(padding[0]), float(padding[1])))

func add_spine(holder: Node, animation: String, point: Vector2) -> void:
	var actor := NewHDSpineActor.new()
	holder.add_child(actor)
	actor.position = point
	actor.configure("scenes")
	actor.play(animation, true)

func change_color() -> void:
	if colors.is_empty() or theme == null:
		return
	color_index = (color_index + 1) % colors.size()
	var parts: PackedStringArray = str(colors[color_index]).split("/")
	var tint := Color(float(parts[0]) / 255, float(parts[1]) / 255, float(parts[2]) / 255)
	for target in theme.find_children("Basic1", "CanvasItem", true, false):
		create_tween().tween_property(target, "self_modulate", tint, 1)
