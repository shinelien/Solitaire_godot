class_name LegacyDealDecoder
extends RefCounted

## 确定性旧版牌库（bureau）解码器（纯数据，无 Node 依赖）。
## 一条记录为 52 个 ASCII 字节，值域 48..99；id = 字节 - 48，范围 [0,51]。
## cardIds = reverse(record)；游戏按 FIFO 消费 cardIds，
## 因此解码出的 `ids` 已经是消费顺序。畸形输入以类型化错误码拒绝，
## 绝不回退到随机发牌（旧版会随机化，我们不允许）。

const CARD_COUNT := 52
const RECORD_LENGTH := 52
const RECORD_BYTES_WITH_LF := 53
const MIN_BYTE := 48
const MAX_BYTE := 99
const NEWLINE_BYTE := 10

const CODE_OK := "ok"
const CODE_INVALID_LENGTH := "invalid_length"
const CODE_INVALID_BYTE := "invalid_byte"
const CODE_DUPLICATE_ID := "duplicate_id"
const CODE_INVALID_ID_RANGE := "invalid_id_range"
const CODE_FILE_LAYOUT := "file_layout"


## 解码一条 52 字节记录。成功返回 {"ok": true, "ids": Array[int]}；
## 失败返回 {"ok": false, "error_code": String, "error_message": String}。
static func decode_bytes(record: PackedByteArray) -> Dictionary:
	if record.size() != RECORD_LENGTH:
		return _error(CODE_INVALID_LENGTH, "record length %d != 52" % record.size())
	var seen := PackedByteArray()
	seen.resize(CARD_COUNT)
	var ids: Array[int] = []
	for i in CARD_COUNT:
		var byte := record[CARD_COUNT - 1 - i]
		if byte < MIN_BYTE or byte > MAX_BYTE:
			return _error(
				CODE_INVALID_BYTE,
				"byte %d at source index %d not in [48,99]" % [byte, CARD_COUNT - 1 - i]
			)
		var card_id := byte - MIN_BYTE
		if seen[card_id] == 1:
			return _error(CODE_DUPLICATE_ID, "duplicate id %d at source index %d" % [card_id, CARD_COUNT - 1 - i])
		seen[card_id] = 1
		ids.append(card_id)
	## 52 个互异且都在 0..51 的 id，按抽屉原理即为完整排列，无需再校验。
	return {"ok": true, "ids": ids}


## 以 ASCII 文本（52 字符）形式解码一条记录。decode_bytes 的便捷封装；
## 不修改文本本身。
static func decode_record(text: String) -> Dictionary:
	return decode_bytes(text.to_ascii_buffer())


## 判断一条记录文本是否为合法记录（可用于批量预检）。
static func is_valid_record(text: String) -> bool:
	var result := decode_record(text)
	return result.get("ok", false)


## 校验整个牌池文件缓冲：布局须为固定 53 字节记录（52 字符 + LF），
## 且每条记录都能解码。返回 ok / record_count / 可选首个错误
## {first_error_index, error_code}。绝不随机化。
static func validate_pool_bytes(bytes: PackedByteArray) -> Dictionary:
	if bytes.is_empty():
		return _error(CODE_FILE_LAYOUT, "empty pool file")
	if bytes.size() % RECORD_BYTES_WITH_LF != 0:
		return _error(
			CODE_FILE_LAYOUT,
			"file size %d is not a multiple of 53" % bytes.size()
		)
	var record_count := bytes.size() / RECORD_BYTES_WITH_LF
	for r in record_count:
		var offset := r * RECORD_BYTES_WITH_LF
		if bytes[offset + RECORD_LENGTH] != NEWLINE_BYTE:
			return {
				"ok": false,
				"error_code": CODE_FILE_LAYOUT,
				"error_message": "record %d not terminated by LF" % r,
				"record_count": record_count,
				"first_error_index": r,
			}
		var result := decode_bytes(bytes.slice(offset, offset + RECORD_LENGTH))
		if not result.get("ok", false):
			result["record_count"] = record_count
			result["first_error_index"] = r
			return result
	return {"ok": true, "record_count": record_count, "first_error_index": -1}


## 统一构造解码错误结果。
static func _error(code: String, message: String) -> Dictionary:
	return {"ok": false, "error_code": code, "error_message": message}
