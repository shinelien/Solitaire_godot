class_name NativeSpineCard
extends Node2D

signal face_event(event_name: String)
signal clip_finished
const LIBRARY = preload("res://assets/master/spine/card_animations.tres")
static var _bindings: Dictionary = {}
var animation_player: AnimationPlayer
var rig: Node2D
var _mesh: Polygon2D
var front: Texture2D
var back: Texture2D
var shown_face := false
var desired_face := false

func _ready() -> void:
	if _bindings.is_empty():
		_bindings = JSON.parse_string(FileAccess.get_file_as_string("res://assets/master/spine/bindings.json"))
	rig = Node2D.new()
	rig.name = "Rig"
	add_child(rig)
	for slot_name in _bindings:
		var variants: Dictionary = _bindings[slot_name]
		var attachment: Dictionary = variants.values()[0]
		var poly := Polygon2D.new()
		poly.name = slot_name
		poly.texture = load(attachment.texture)
		var uv := PackedVector2Array()
		for i in range(0, attachment.uv.size(), 2):
			uv.append(Vector2(attachment.uv[i], attachment.uv[i + 1]))
		poly.uv = uv
		var triangles: Array[PackedInt32Array] = []
		for i in range(0, attachment.triangles.size(), 3):
			triangles.append(PackedInt32Array(attachment.triangles.slice(i, i + 3)))
		poly.polygons = triangles
		if attachment.screen:
			var material := CanvasItemMaterial.new()
			material.blend_mode = CanvasItemMaterial.BLEND_MODE_ADD
			poly.material = material
		rig.add_child(poly)
		if slot_name == "card_bg_1":
			_mesh = poly
	animation_player = AnimationPlayer.new()
	animation_player.name = "AnimationPlayer"
	animation_player.root_node = NodePath("../Rig")
	animation_player.callback_mode_method = AnimationMixer.ANIMATION_CALLBACK_MODE_METHOD_IMMEDIATE
	animation_player.add_animation_library("", LIBRARY)
	add_child(animation_player)
	animation_player.animation_finished.connect(_finished)
	reset_pose()

func set_textures(p_front: Texture2D, p_back: Texture2D) -> void:
	front = p_front
	back = p_back
	_apply_texture()

func _apply_texture() -> void:
	if _mesh == null:
		return
	var selected := (front if shown_face else back) as AtlasTexture
	if selected == null:
		return
	_mesh.texture = selected.atlas
	var source: Array = _bindings.card_bg_1.card_bg_5.uv
	var original: Texture2D = load(_bindings.card_bg_1.card_bg_5.texture)
	var uv := PackedVector2Array()
	for i in range(0, source.size(), 2):
		uv.append(Vector2(source[i], source[i + 1]) / original.get_size() * selected.get_size() - selected.margin.position + selected.region.position)
	_mesh.uv = uv
	if not selected.has_meta("clip_material"):
		var material := ShaderMaterial.new()
		material.shader = preload("res://solitaire/invincible/atlas_clip.gdshader")
		var size := selected.atlas.get_size()
		material.set_shader_parameter("atlas_bounds", Vector4(selected.region.position.x / size.x, selected.region.position.y / size.y, selected.region.size.x / size.x, selected.region.size.y / size.y))
		selected.set_meta("clip_material", material)
	_mesh.material = selected.get_meta("clip_material")

func flip(to_face: bool, from_stock: bool, left: bool) -> float:
	desired_face = to_face
	var clip := "Flip0" if to_face else "Flip3"
	if from_stock:
		clip = ("Flip_L1" if left else "Flip1") if to_face else ("Flip_L2" if left else "Flip2")
	animation_player.play(clip)
	return animation_player.get_animation(clip).length

func _spine_event(event_name: String) -> void:
	if event_name in ["flop", "unflop"]:
		shown_face = desired_face
		_apply_texture()
	face_event.emit(event_name)

func reset_pose() -> void:
	animation_player.play("RESET")
	animation_player.advance(0)
	animation_player.stop()
	_apply_texture()

func _finished(_clip: StringName) -> void:
	shown_face = desired_face
	reset_pose()
	clip_finished.emit()
