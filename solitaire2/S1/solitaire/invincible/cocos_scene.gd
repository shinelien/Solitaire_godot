class_name InvincibleScene
extends Control
signal frame_event(target: NodePath, event_name: String)
var looping_clip: StringName = &""
var local_library := false

func suppress_node(target: CanvasItem) -> void:
	# Editor preview visibility must not be restored by a later timeline key.
	var player := get_node_or_null("AnimationPlayer") as AnimationPlayer
	if player != null:
		if not local_library:
			var library := player.get_animation_library("").duplicate(true) as AnimationLibrary
			player.remove_animation_library("")
			player.add_animation_library("", library)
			local_library = true
		var path := str(get_path_to(target)) + ":visible"
		for clip in player.get_animation_list():
			var animation := player.get_animation(clip)
			for track in animation.get_track_count():
				if str(animation.track_get_path(track)) == path:
					animation.track_set_enabled(track, false)
	target.hide()

func play_clip(clip: String, loop := false) -> float:
	var player := get_node_or_null("AnimationPlayer") as AnimationPlayer
	if player == null or not player.has_animation(clip):
		return 0.0
	# The resource is shared by scene instances; don't mutate loop_mode globally.
	looping_clip = StringName(clip) if loop else &""
	player.play(clip)
	player.advance(0)
	if loop and not player.animation_finished.is_connected(_loop_clip):
		player.animation_finished.connect(_loop_clip)
	return player.get_animation(clip).length

func _loop_clip(clip: StringName) -> void:
	if clip == looping_clip:
		get_node("AnimationPlayer").play(clip)

func timeline_event(target: String, property: String, payload: String) -> void:
	var data: Dictionary = JSON.parse_string(payload)
	var child := get_node_or_null(NodePath(target))
	if property == "ActionValue" and child is InvincibleScene:
		child.play_clip(str(data.get("CurrentAnimationName", "")), int(data.get("InnerActionType", 0)) == 1)
	elif property == "FrameEvent":
		frame_event.emit(NodePath(target), str(data.get("Value", "")))
