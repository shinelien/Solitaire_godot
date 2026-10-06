class_name NewHDSpineActor
extends Node2D
## Original weighted geometry and constraints are evaluated at asset-build time.
## Runtime animation, rendering and face events use Godot's native nodes.
signal spine_event(event_name: String)
signal clip_finished(clip: StringName)
static var cache: Dictionary = {}
var data: Dictionary = {}
var player: AnimationPlayer
var slots: Dictionary = {}
var attachments: Array = []
var clip := "RESET"
var sample_time := 0.0:
	set(value):
		sample_time = value
		_sample(value)
var overrides: Dictionary = {}
var hidden_slots: Dictionary = {}

func configure(rig_name: String) -> void:
	if not cache.has(rig_name):
		var bytes := FileAccess.get_file_as_bytes("res://assets/newhd/baked/%s.json.gz" % rig_name)
		cache[rig_name] = JSON.parse_string(bytes.decompress_dynamic(100_000_000, FileAccess.COMPRESSION_GZIP).get_string_from_utf8())
	data = cache[rig_name]
	for child in get_children():
		child.queue_free()
	slots.clear()
	attachments.clear()
	for item: Dictionary in data.attachments:
		var a := item.duplicate()
		a.texture = load(str(data.atlas_dir) + "/" + str(item.page))
		var uv := PackedVector2Array()
		for i in range(0, item.uv.size(), 2):
			uv.append(Vector2(item.uv[i], item.uv[i + 1]) * a.texture.get_size())
		a.uv_packed = uv
		var triangles: Array[PackedInt32Array] = []
		for i in range(0, item.triangles.size(), 3):
			triangles.append(PackedInt32Array(item.triangles.slice(i, i + 3)))
		a.triangles_packed = triangles
		attachments.append(a)
		if not slots.has(item.slot):
			var poly := Polygon2D.new()
			poly.name = item.slot
			if int(item.blend) != 0:
				var mat := CanvasItemMaterial.new()
				mat.blend_mode = CanvasItemMaterial.BLEND_MODE_ADD if int(item.blend) == 1 else CanvasItemMaterial.BLEND_MODE_MUL if int(item.blend) == 2 else CanvasItemMaterial.BLEND_MODE_MIX
				poly.material = mat
			poly.set_meta("base_material", poly.material)
			add_child(poly)
			slots[item.slot] = poly
	player = AnimationPlayer.new()
	player.name = "AnimationPlayer"
	player.root_node = NodePath("..")
	player.callback_mode_method = AnimationMixer.ANIMATION_CALLBACK_MODE_METHOD_IMMEDIATE
	var library := AnimationLibrary.new()
	for name: String in data.clips:
		var anim := Animation.new()
		anim.length = maxf(.001, data.clips[name].duration)
		var track := anim.add_track(Animation.TYPE_VALUE)
		anim.track_set_path(track, NodePath(".:sample_time"))
		anim.value_track_set_update_mode(track, Animation.UPDATE_CONTINUOUS)
		anim.track_insert_key(track, 0, 0.0)
		anim.track_insert_key(track, anim.length, anim.length)
		var events: Array = data.events.get(name, [])
		if not events.is_empty():
			track = anim.add_track(Animation.TYPE_METHOD)
			anim.track_set_path(track, NodePath("."))
			for event: Dictionary in events:
				anim.track_insert_key(track, event.get("time", 0), {"method": "_event", "args": [event.name]})
		library.add_animation(name, anim)
	player.add_animation_library("", library)
	add_child(player)
	player.animation_finished.connect(func(name: StringName): clip_finished.emit(name))
	play("RESET")

func play(name: String, loop := false) -> float:
	if not data.clips.has(name):
		return 0.0
	clip = name
	var anim := player.get_animation(name)
	anim.loop_mode = Animation.LOOP_LINEAR if loop else Animation.LOOP_NONE
	player.play(name)
	player.advance(0)
	return anim.length

func _event(name: String) -> void:
	spine_event.emit(name)

func _sample(time: float) -> void:
	if data.is_empty() or not data.clips.has(clip):
		return
	var frames: Array = data.clips[clip].frames
	var index := mini(frames.size() - 1, int(time * int(data.fps)))
	var next := mini(index + 1, frames.size() - 1)
	var fraction := clampf(time * int(data.fps) - index, 0, 1)
	for slot: Polygon2D in slots.values():
		slot.visible = false
	var row: Array = frames[index]
	var next_row: Array = frames[next]
	for i in row.size():
		var entry: Array = row[i]
		var a: Dictionary = attachments[int(entry[0])]
		var poly: Polygon2D = slots[a.slot]
		poly.visible = not hidden_slots.get(a.slot, false)
		# A slot must not escape its actor's z layer. Godot adds child z_index
		# to the card's z_index, which interleaves the artwork of adjacent cards.
		poly.z_index = 0
		if poly.get_index() != i:
			move_child(poly, i)
		var vertices := PackedVector2Array()
		var target: Array = next_row[i][1] if i < next_row.size() and int(next_row[i][0]) == int(entry[0]) else entry[1]
		for j in range(0, entry[1].size(), 2):
			vertices.append(Vector2(lerpf(entry[1][j], target[j], fraction), lerpf(entry[1][j + 1], target[j + 1], fraction)))
		poly.polygon = vertices
		poly.polygons = a.triangles_packed
		poly.texture = a.texture
		poly.material = poly.get_meta("base_material", null)
		poly.uv = a.uv_packed
		if overrides.has(a.slot):
			var replacement := overrides[a.slot] as AtlasTexture
			poly.texture = replacement.atlas
			var uv := PackedVector2Array()
			var source: Array = a.override_uv
			for j in range(0, source.size(), 2):
				uv.append(Vector2(source[j], source[j + 1]) * replacement.get_size() - replacement.margin.position + replacement.region.position)
			poly.uv = uv
			if not replacement.has_meta("clip_material"):
				var material := ShaderMaterial.new()
				material.shader = preload("res://solitaire/newhd/atlas_clip.gdshader")
				var atlas_size := replacement.atlas.get_size()
				material.set_shader_parameter("atlas_bounds", Vector4(replacement.region.position.x / atlas_size.x, replacement.region.position.y / atlas_size.y, replacement.region.size.x / atlas_size.x, replacement.region.size.y / atlas_size.y))
				replacement.set_meta("clip_material", material)
			poly.material = replacement.get_meta("clip_material")
		var color: Array = entry[2]
		poly.modulate = Color(color[0], color[1], color[2], color[3])
