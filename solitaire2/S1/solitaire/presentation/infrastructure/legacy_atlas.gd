class_name LegacyAtlas
extends RefCounted

## Isolated presentation adapter for the fixed legacy texture atlas sheets
## (WP-08). It parses the Spine text .atlas files exported under
## assets/legacy and hands back AtlasTexture regions. It is the only place
## that understands the legacy texture format; core/deal/application never
## reference it and CardData/CardPile stay texture-free.
##
## Region rectangles in the Spine atlas are top-left based (xy grows down),
## which matches Godot AtlasTexture/TextureRect directly; none of the exported
## regions are rotated.

const REGION_UNKNOWN := 0
const REGION_MISSING := 1

static var _sheets: Dictionary = {}


## Parse one sheet pair (png + .atlas) once and cache region metadata.
static func _sheet(image_path: String, atlas_path: String) -> Dictionary:
	var key := "%s|%s" % [image_path, atlas_path]
	if _sheets.has(key):
		return _sheets[key]
	var texture := load(image_path)
	var regions := _parse_atlas(atlas_path)
	var sheet := {"texture": texture, "regions": regions}
	_sheets[key] = sheet
	return sheet


static func _parse_atlas(atlas_path: String) -> Dictionary:
	var out: Dictionary = {}
	var file := FileAccess.open(atlas_path, FileAccess.READ)
	if file == null:
		return out
	var lines := file.get_as_text().split("\n")
	var name := ""
	var xy := Vector2i.ZERO
	var size := Vector2i.ZERO
	var rotated := false
	for line in lines:
		var trimmed := line.strip_edges()
		if trimmed.is_empty():
			continue
		if not line.begins_with(" ") and not line.begins_with("\t"):
			if name != "":
				out[name] = {"xy": xy, "size": size, "rotated": rotated}
			name = trimmed
			xy = Vector2i.ZERO
			size = Vector2i.ZERO
			rotated = false
			if name.contains(":"):
				name = ""
			continue
		if name == "":
			continue
		var parts := trimmed.split(":", false, 1)
		if parts.size() != 2:
			continue
		var value := parts[1].strip_edges()
		match parts[0].strip_edges():
			"xy":
				xy = _parse_vec2i(value)
			"size":
				size = _parse_vec2i(value)
			"rotate":
				rotated = value == "true"
	if name != "":
		out[name] = {"xy": xy, "size": size, "rotated": rotated}
	return out


static func _parse_vec2i(value: String) -> Vector2i:
	var parts := value.split(",", false)
	if parts.size() != 2:
		return Vector2i.ZERO
	return Vector2i(int(parts[0].strip_edges()), int(parts[1].strip_edges()))

## Non-mutating probe: whether a named region exists in a sheet.
static func known_region(image_path: String, atlas_path: String, region_name: String) -> bool:
	return bool(region(image_path, atlas_path, region_name).get("ok", false))


## Texture region lookup result: {ok:bool, texture:AtlasTexture, code:int}.
static func region(image_path: String, atlas_path: String, region_name: String) -> Dictionary:
	var sheet := _sheet(image_path, atlas_path)
	if sheet.get("texture") == null:
		return {"ok": false, "code": REGION_MISSING, "texture": null}
	var regions: Dictionary = sheet.get("regions", {})
	if not regions.has(region_name):
		return {"ok": false, "code": REGION_MISSING, "texture": null}
	var meta: Dictionary = regions[region_name]
	if bool(meta.get("rotated", false)):
		return {"ok": false, "code": REGION_UNKNOWN, "texture": null}
	var atlas := AtlasTexture.new()
	atlas.atlas = sheet.get("texture")
	var r: Vector2i = meta.get("xy", Vector2i.ZERO)
	var s: Vector2i = meta.get("size", Vector2i.ZERO)
	atlas.region = Rect2(r.x, r.y, s.x, s.y)
	return {"ok": true, "code": REGION_UNKNOWN, "texture": atlas}


## All 52 card faces composed from the face sheet (base + rank + suit layer)
## plus the shared back, keyed by card id 0..51. Keys: base/suit/rank/back.
static func face_textures(card_id: int) -> Dictionary:
	var out := {"base": null, "suit": null, "rank": null, "back": null, "red": false}
	var card := CardData.new(card_id, true)
	var parts := LegacyFaceMapper.face_parts(card.rank, card.suit)
	out["red"] = parts.red
	var face := _sheet(LegacyFaceMapper.ATLAS_FACES_IMAGE, LegacyFaceMapper.ATLAS_FACES_FILE)
	if face.get("texture") != null:
		var regions: Dictionary = face.get("regions", {})
		out["base"] = _region_texture(face, regions, parts.base)
		out["suit"] = _region_texture(face, regions, parts.suit)
		out["rank"] = _region_texture(face, regions, parts.rank)
	var back := _sheet(LegacyFaceMapper.ATLAS_BACK_IMAGE, LegacyFaceMapper.ATLAS_BACK_FILE)
	if back.get("texture") != null:
		var back_regions: Dictionary = back.get("regions", {})
		out["back"] = _region_texture(back, back_regions, LegacyFaceMapper.back_region())
	return out


static func _region_texture(sheet: Dictionary, regions: Dictionary, region_name: String) -> AtlasTexture:
	if not regions.has(region_name):
		return null
	var atlas := AtlasTexture.new()
	atlas.atlas = sheet.get("texture")
	var r: Vector2i = regions[region_name].get("xy", Vector2i.ZERO)
	var s: Vector2i = regions[region_name].get("size", Vector2i.ZERO)
	atlas.region = Rect2(r.x, r.y, s.x, s.y)
	return atlas
