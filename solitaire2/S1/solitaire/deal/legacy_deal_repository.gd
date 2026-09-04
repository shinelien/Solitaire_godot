class_name LegacyDealRepository
extends RefCounted

## 对导出到 res://data/legacy/ 的旧版牌池的只读访问
## （源为固定 Git 对象 InvincibleWarrior@74f51802...；纯数据，无 Node）。
## 强制校验索引边界；越界请求返回显式错误，绝不随机回退。

const POOL_BUREAU1 := "bureau1"
const POOL_BUREAU3 := "bureau3"

const FILE_BUREAU1 := "res://data/legacy/bureau1.d"
const FILE_BUREAU3 := "res://data/legacy/bureau3.d"

## 固定旧版源对象内的路径（牌局身份/出处记录）。
const SOURCE_BUREAU1 := "Resources/data/bureau1.d"
const SOURCE_BUREAU3 := "Resources/data/bureau3.d"

## 各牌池的期望记录数与字节数（用于完整性校验）。
const EXPECTED_RECORDS_BUREAU1 := 32084
const EXPECTED_RECORDS_BUREAU3 := 4999
const EXPECTED_BYTES_BUREAU1 := 1700452
const EXPECTED_BYTES_BUREAU3 := 264947

## 已加载牌池内容的进程内缓存（pool -> PackedByteArray）。
static var _cache: Dictionary = {}


## 返回指定牌池的导出文件路径；未知牌池返回空串。
static func file_path(pool: String) -> String:
	if pool == POOL_BUREAU1:
		return FILE_BUREAU1
	if pool == POOL_BUREAU3:
		return FILE_BUREAU3
	return ""


## 返回指定牌池在旧版源对象内的出处路径；未知牌池返回空串。
static func source_path(pool: String) -> String:
	if pool == POOL_BUREAU1:
		return SOURCE_BUREAU1
	if pool == POOL_BUREAU3:
		return SOURCE_BUREAU3
	return ""


## 返回指定牌池的期望记录数；未知牌池返回 -1。
static func expected_records(pool: String) -> int:
	if pool == POOL_BUREAU1:
		return EXPECTED_RECORDS_BUREAU1
	if pool == POOL_BUREAU3:
		return EXPECTED_RECORDS_BUREAU3
	return -1


## 是否为受支持的牌池名（bureau1/bureau3）。
static func is_known_pool(pool: String) -> bool:
	return pool == POOL_BUREAU1 or pool == POOL_BUREAU3


## 读取指定牌池的完整字节内容（带进程内缓存）。
static func load_bytes(pool: String) -> PackedByteArray:
	if _cache.has(pool):
		return _cache[pool]
	var result := _read_file(file_path(pool))
	if not result.is_empty():
		_cache[pool] = result
	return result


## 直接以只读方式读取一个文件的全部字节；失败返回空数组。
static func _read_file(path: String) -> PackedByteArray:
	var file := FileAccess.open(path, FileAccess.READ)
	if file == null:
		return PackedByteArray()
	var bytes := file.get_buffer(file.get_length())
	file.close()
	return bytes


## 计算整个牌池文件的 SHA-256（十六进制）；读取失败返回空串。
static func pool_sha256(pool: String) -> String:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return ""
	return _sha256(bytes)


## 牌池文件字节数；读取失败返回 0。
static func pool_byte_count(pool: String) -> int:
	return load_bytes(pool).size()


## 牌池记录数（按 53 字节/条计算）；读取失败返回 -1。
static func record_count(pool: String) -> int:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return -1
	return bytes.size() / LegacyDealDecoder.RECORD_BYTES_WITH_LF


## 按从 0 开始的索引取一条记录（52 个 ASCII 字符）。
## 返回 {"ok", "record"} 或带错误码/消息的失败字典。
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


## 经 LegacyDealDecoder 对整个牌池做严格全量校验
## （每条记录可解码、布局为 53 字节记录）。返回解码器的结果字典。
static func validate_pool(pool: String) -> Dictionary:
	var bytes := load_bytes(pool)
	if bytes.is_empty():
		return {
			"ok": false,
			"error_code": "io_error",
			"error_message": "cannot read pool '%s'" % pool,
		}
	return LegacyDealDecoder.validate_pool_bytes(bytes)


## 计算字节内容的 SHA-256（十六进制）。
static func _sha256(bytes: PackedByteArray) -> String:
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	ctx.update(bytes)
	return ctx.finish().hex_encode()
