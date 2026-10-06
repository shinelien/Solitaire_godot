class_name MasterAtlas
extends RefCounted
static var frames: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/master/atlas_frames.json"))
static var textures: Dictionary = {}
static func has_frame(name: String) -> bool:
	return frames.has(name)
static func texture(name: String) -> AtlasTexture:
	if textures.has(name):
		return textures[name]
	if not frames.has(name):
		push_error("Missing atlas frame: " + name)
		return null
	var item: Dictionary = frames[name]
	var result := AtlasTexture.new()
	result.atlas = load(item.page)
	result.region = Rect2(item.region[0], item.region[1], item.region[2], item.region[3])
	result.margin = Rect2(item.margin[0], item.margin[1], item.margin[2], item.margin[3])
	result.filter_clip = true
	textures[name] = result
	return result
