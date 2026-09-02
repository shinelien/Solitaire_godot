class_name LegacyDealRepository
extends RefCounted

## Read-only access to the legacy deal pools exported under res://data/legacy/
## from fixed Git object InvincibleWarrior@74f51802... (pure data, no Node).
## Index bounds are enforced; out-of-range requests return an explicit error,
## never a random fallback.

const POOL_BUREAU1 := "bureau1"
const POOL_BUREAU3 := "bureau3"

const FILE_BUREAU1 := "res://data/legacy/bureau1.d"
const FILE_BUREAU3 := "res://data/legacy/bureau3.d"

## Paths inside the fixed legacy source object (deal identity / provenance).
const SOURCE_BUREAU1 := "Resources/data/bureau1.d"
const SOURCE_BUREAU3 := "Resources/data/bureau3.d"

const EXPECTED_RECORDS_BUREAU1 := 32084
const EXPECTED_RECORDS_BUREAU3 := 4999
const EXPECTED_BYTES_BUREAU1 := 1700452
const EXPECTED_BYTES_BUREAU3 := 264947

static var _cache: Dictionary = {}


static func file_path(pool: String) -> String:
	if pool == POOL_BUREAU1:
		return FILE_BUREAU1
	if pool == POOL_BUREAU3:
		return FILE_BUREAU3
	return ""


static func source_path(pool: String) -> String:
	if pool == POOL_BUREAU1:
		return SOURCE_BUREAU1
	if pool == POOL_BUREAU3:
		return SOURCE_BUREAU3
	return ""


static func expected_records(pool: String) -> int:
	if pool == POOL_BUREAU1:
		return EXPECTED_RECORDS_BUREAU1
	if pool == POOL_BUREAU3:
		return EXPECTED_RECORDS_BUREAU3
	return -1


static func is_known_pool(pool: String) -> bool:
	return pool == POOL_BUREAU1 or pool == POOL_BUREAU3


static func load_bytes(pool: String) -> PackedByteArray:
	if _cache.has(pool):
		return _cache[pool]
	var result := _read_file(file_path(pool))
	if not result.is_empty():
		_cache[pool] = result
	return result


static func _read_file(path: String) -> PackedByteArray:
	var file := FileAccess.open(path, FileAccess.READ)
	if file == null:
		return PackedByteArray()
	var bytes := file.get_buffer(file.get_length())
	file.close()
	return bytes


static func pool_sha256(pool: String) -> String:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return ""
	return _sha256(bytes)


static func pool_byte_count(pool: String) -> int:
	return load_bytes(pool).size()


static func record_count(pool: String) -> int:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return -1
	return bytes.size() / LegacyDealDecoder.RECORD_BYTES_WITH_LF


## Fetch one record (52 ASCII chars) by zero-based index.
static func get_record(pool: String, index: int) -> Dictionary:
	if not is_known_pool(pool):
		return {"ok": false, "error_code": "invalid_pool", "error_message": "unknown pool '%s'" % pool}
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return {"ok": false, "error_code": "io_error", "error_message": "cannot read pool '%s'" % pool}
	var count := bytes.size() / LegacyDealDecoder.RECORD_BYTES_WITH_LF
	if index < 0 or index >= count:
		return {
			"ok": false,
			"error_code": "index_out_of_range",
			"error_message": "index %d outside [0,%d)" % [index, count],
		}
	var offset := index * LegacyDealDecoder.RECORD_BYTES_WITH_LF
	var rec := bytes.slice(offset, offset + LegacyDealDecoder.RECORD_LENGTH)
	var text := rec.get_string_from_ascii()
	return {"ok": true, "record": text}


## Strict full-library validation via LegacyDealDecoder (all records decode,
## layout is 53-byte records). Returns the decoder result dictionary.
static func validate_pool(pool: String) -> Dictionary:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return {
			"ok": false,
			"error_code": "io_error",
			"error_message": "cannot read pool '%s'" % pool,
		}
	return LegacyDealDecoder.validate_pool_bytes(bytes)


static func _sha256(bytes: PackedByteArray) -> String:
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	ctx.update(bytes)
	return ctx.finish().hex_encode()
