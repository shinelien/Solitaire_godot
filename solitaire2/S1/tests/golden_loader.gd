@tool
class_name GoldenLoader
extends RefCounted

## Read-only loader for the WP-05 golden fixture JSON files. Test-only support
## (never used by production core/deal code).

const FILE_BUREAU1 := "res://data/legacy/golden/golden_bureau1.json"
const FILE_BUREAU3 := "res://data/legacy/golden/golden_bureau3.json"

static var _cache: Dictionary = {}


static func load_doc(pool: String) -> Dictionary:
	if _cache.has(pool):
		return _cache[pool]
	var path := FILE_BUREAU1 if pool == "bureau1" else FILE_BUREAU3
	var text := FileAccess.get_file_as_string(path)
	if text.is_empty():
		return {}
	var parsed = JSON.parse_string(text)
	if parsed is Dictionary:
		_cache[pool] = parsed
		return parsed
	return {}


static func fixtures(pool: String) -> Array:
	var doc := load_doc(pool)
	if doc.is_empty() or not doc.has("fixtures"):
		return []
	return doc.fixtures


static func meta(pool: String) -> Dictionary:
	var doc := load_doc(pool)
	if doc.is_empty() or not doc.has("meta"):
		return {}
	return doc.meta


static func ints_from(arr: Array) -> Array[int]:
	var out: Array[int] = []
	for v in arr:
		out.append(int(v))
	return out


static func tableau_ids_from(fixture_tableau: Array) -> Array:
	## Returns Array[Array[int]] of per-column ids (bottom..top).
	var columns: Array = []
	for column in fixture_tableau:
		var ids: Array[int] = []
		for entry in column:
			ids.append(int(entry.id))
		columns.append(ids)
	return columns


static func tableau_face_up_from(fixture_tableau: Array) -> Array:
	## Returns Array[Array[bool]] of per-column face-up flags.
	var columns: Array = []
	for column in fixture_tableau:
		var flags: Array = []
		for entry in column:
			flags.append(bool(entry.face_up))
		columns.append(flags)
	return columns
