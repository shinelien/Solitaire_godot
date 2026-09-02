class_name LegacyDealDecoder
extends RefCounted

## Deterministic legacy bureau decoder (pure data, no Node deps).
## A record is 52 ASCII bytes in 48..99; id = byte - 48 in [0,51].
## cardIds = reverse(record); gameplay consumes cardIds FIFO, so the decoded
## `ids` below are already the consumption order. Malformed input is rejected
## with a typed code and NEVER falls back to randomization (legacy did; we
## must not).

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


## Decode one 52-byte record. Returns {"ok": true, "ids": Array[int]} or
## {"ok": false, "error_code": String, "error_message": String}.
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
	## 52 unique ids each in 0..51 is a complete permutation by pigeonhole.
	return {"ok": true, "ids": ids}


## Decode one record given as ASCII text (52 chars). Convenience over
## decode_bytes; the text is not mutated.
static func decode_record(text: String) -> Dictionary:
	return decode_bytes(text.to_ascii_buffer())


static func is_valid_record(text: String) -> bool:
	var result := decode_record(text)
	return result.get("ok", false)


## Validate a whole pool buffer: layout is fixed 53-byte records (52 chars +
## LF), every record decodes. Returns ok / record_count / optional first error
## {at_record, error_code}. Never randomizes.
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


static func _error(code: String, message: String) -> Dictionary:
	return {"ok": false, "error_code": code, "error_message": message}
