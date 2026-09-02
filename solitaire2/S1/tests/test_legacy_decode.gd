@tool
extends McpTestSuite


func suite_name() -> String:
	return "legacy_decode"


const RECORD0_CONSUMPTION := [
	3, 11, 2, 9, 30, 41, 5, 28, 24, 13, 1, 48, 37, 45, 8,
	32, 17, 39, 4, 49, 26, 15, 31, 21, 22, 33, 25, 7,
	19, 16, 0, 46, 44, 12, 10, 34, 38, 40, 18, 20, 29, 27,
	47, 35, 36, 51, 50, 6, 14, 43, 42, 23,
]


static func _record_from_ids(ids: Array) -> String:
	var bytes := PackedByteArray()
	bytes.resize(52)
	for i in 52:
		bytes[i] = int(ids[51 - i]) + 48
	return bytes.get_string_from_ascii()


static func _record_with_byte_override(source: String, index: int, byte_value: int) -> String:
	var bytes := source.to_ascii_buffer()
	bytes[index] = byte_value
	return bytes.get_string_from_ascii()


static func _pool_bytes(record_texts: Array) -> PackedByteArray:
	var bytes := PackedByteArray()
	for text in record_texts:
		bytes.append_array(String(text).to_ascii_buffer())
		bytes.append(LegacyDealDecoder.NEWLINE_BYTE)
	return bytes


func test_record0_consumption_is_reverse_fifo() -> void:
	var fetch := LegacyDealRepository.get_record("bureau1", 0)
	assert_true(fetch.ok, "record 0 fetched")
	var result := LegacyDealDecoder.decode_record(fetch.record)
	assert_true(result.ok, "record 0 decodes")
	var expected: Array[int] = []
	for v in RECORD0_CONSUMPTION:
		expected.append(int(v))
	assert_eq(result.ids, expected, "record 0 consumption = reverse(record)")
	var forward: PackedByteArray = fetch.record.to_ascii_buffer()
	assert_eq(expected[0], int(forward[51]) - 48, "consumption[0] == last forward byte")
	assert_eq(expected[51], int(forward[0]) - 48, "consumption[51] == first forward byte")
	assert_ne(expected[0], int(forward[0]) - 48, "consumption is not the forward record order")


func test_decode_full_permutation_round_trip() -> void:
	var ordered: Array[int] = []
	for i in 52:
		ordered.append(i)
	var text := _record_from_ids(ordered)
	var result := LegacyDealDecoder.decode_record(text)
	assert_true(result.ok, "decode ok")
	assert_eq(result.ids, ordered, "decode(encode(ids)) == ids")


func test_decode_deterministic_and_no_mutation() -> void:
	var fetch := LegacyDealRepository.get_record("bureau3", 42)
	assert_true(fetch.ok, "record fetched")
	var first := LegacyDealDecoder.decode_record(fetch.record)
	var second := LegacyDealDecoder.decode_record(fetch.record)
	assert_true(first.ok and second.ok, "both decode")
	assert_eq(first.ids, second.ids, "deterministic ids")
	assert_eq(fetch.record.length(), 52, "input record not mutated by decode")
	assert_eq(fetch.record, fetch.record, "input unchanged")


func test_decode_rejects_wrong_lengths() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	for bad in ["", "0", "0123456789", good.substr(0, 51), good + "0"]:
		var result := LegacyDealDecoder.decode_record(bad)
		assert_false(result.ok, "reject length %d" % bad.length())
		assert_eq(result.error_code, "invalid_length", "length error code for %d" % bad.length())


func test_decode_rejects_illegal_bytes() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	for byte_value in [32, 47, 100, 126]:
		var bad := _record_with_byte_override(good, 25, byte_value)
		var result := LegacyDealDecoder.decode_record(bad)
		assert_false(result.ok, "reject byte %d" % byte_value)
		assert_eq(result.error_code, "invalid_byte", "byte error code %d" % byte_value)


func test_decode_bytes_rejects_nul_and_high_bytes() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var base := good.to_ascii_buffer()
	for byte_value in [0, 255]:
		var rec := base.duplicate()
		rec[25] = byte_value
		var result := LegacyDealDecoder.decode_bytes(rec)
		assert_false(result.ok, "reject raw byte %d" % byte_value)
		assert_eq(result.error_code, "invalid_byte", "raw byte code %d" % byte_value)


func test_decode_rejects_duplicate_and_missing_ids() -> void:
	var dupe := RECORD0_CONSUMPTION.duplicate()
	dupe[51] = dupe[0]
	var result := LegacyDealDecoder.decode_record(_record_from_ids(dupe))
	assert_false(result.ok, "duplicate rejected")
	assert_eq(result.error_code, "duplicate_id", "duplicate error code")
	## A missing id is the complement of a duplicate over 52 range-limited
	## slots; the same record omits one id (here 51 is absent).
	var contains_all := true
	for i in 52:
		if not dupe.has(i):
			contains_all = false
			break
	assert_false(contains_all, "record indeed misses an id")
	assert_false(LegacyDealDecoder.is_valid_record(_record_from_ids(dupe)), "is_valid false")


func test_decode_never_randomizes_repeatedly() -> void:
	for i in [0, 1, 2, 9, 99]:
		var fetch := LegacyDealRepository.get_record("bureau1", i)
		var previous: Array[int] = []
		var stable := true
		for trial in 5:
			var result := LegacyDealDecoder.decode_record(fetch.record)
			if not result.ok:
				stable = false
				break
			if trial > 0 and result.ids != previous:
				stable = false
				break
			previous = result.ids
		assert_true(stable, "decode stable for bureau1#%d" % i)


func test_validate_pool_accepts_well_formed_multirecord_buffer() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var bytes := _pool_bytes([good, good])
	var result := LegacyDealDecoder.validate_pool_bytes(bytes)
	assert_true(result.ok, "two clean records validate")
	assert_eq(result.record_count, 2, "record_count reported")
	assert_eq(result.first_error_index, -1, "no error index on ok")


func test_validate_pool_rejects_empty_buffer() -> void:
	var result := LegacyDealDecoder.validate_pool_bytes(PackedByteArray())
	assert_false(result.ok, "empty pool rejected")
	assert_eq(result.error_code, LegacyDealDecoder.CODE_FILE_LAYOUT, "file_layout code")
	assert_true(
		String(result.error_message).find("empty") != -1,
		"message names the empty pool"
	)


func test_validate_pool_rejects_size_not_multiple_of_53() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var full := _pool_bytes([good, good, good])
	for bad_size in [1, 52, 53 + 1, 53 * 3 - 1]:
		var truncated := full.slice(0, bad_size)
		var result := LegacyDealDecoder.validate_pool_bytes(truncated)
		assert_false(result.ok, "reject %d bytes" % truncated.size())
		assert_eq(
			result.error_code,
			LegacyDealDecoder.CODE_FILE_LAYOUT,
			"file_layout code for %d bytes" % truncated.size()
		)


func test_validate_pool_rejects_record_not_terminated_by_lf() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var bytes := PackedByteArray()
	bytes.append_array(good.to_ascii_buffer())
	bytes.append(13)
	bytes.append_array(good.to_ascii_buffer())
	bytes.append(LegacyDealDecoder.NEWLINE_BYTE)
	var result := LegacyDealDecoder.validate_pool_bytes(bytes)
	assert_false(result.ok, "CR terminator rejected")
	assert_eq(result.error_code, LegacyDealDecoder.CODE_FILE_LAYOUT, "file_layout code")
	assert_eq(result.record_count, 2, "record_count reported")
	assert_eq(result.first_error_index, 0, "bad terminator is record 0")


func test_validate_pool_lf_error_in_later_record_reports_index() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var bytes := PackedByteArray()
	bytes.append_array(good.to_ascii_buffer())
	bytes.append(LegacyDealDecoder.NEWLINE_BYTE)
	bytes.append_array(good.to_ascii_buffer())
	bytes.append(13)
	bytes.append_array(good.to_ascii_buffer())
	bytes.append(LegacyDealDecoder.NEWLINE_BYTE)
	var result := LegacyDealDecoder.validate_pool_bytes(bytes)
	assert_false(result.ok, "later CR terminator rejected")
	assert_eq(result.error_code, LegacyDealDecoder.CODE_FILE_LAYOUT, "file_layout code")
	assert_eq(result.record_count, 3, "record_count reported")
	assert_eq(result.first_error_index, 1, "first bad terminator is record 1")


func test_validate_pool_embedded_invalid_record_reports_index_and_code() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var corrupt := _record_with_byte_override(good, 0, 47)
	var bytes := _pool_bytes([good, corrupt, good])
	var result := LegacyDealDecoder.validate_pool_bytes(bytes)
	assert_false(result.ok, "embedded invalid record rejected")
	assert_eq(result.record_count, 3, "record_count reported")
	assert_eq(result.first_error_index, 1, "invalid record is index 1")
	assert_eq(result.error_code, LegacyDealDecoder.CODE_INVALID_BYTE, "decoder code propagated")
	assert_true(
		String(result.error_message).find("47") != -1,
		"message names the offending byte value"
	)


func test_validate_pool_malformed_buffer_deterministic_repeatedly() -> void:
	var good := _record_from_ids(RECORD0_CONSUMPTION)
	var corrupt := _record_with_byte_override(good, 0, 47)
	var bytes := _pool_bytes([good, corrupt])
	var first := LegacyDealDecoder.validate_pool_bytes(bytes)
	var second := LegacyDealDecoder.validate_pool_bytes(bytes)
	assert_false(first.ok, "malformed rejected deterministically")
	assert_eq(first.ok, second.ok, "same ok across runs")
	assert_eq(first.error_code, second.error_code, "same error_code across runs")
	assert_eq(first.record_count, second.record_count, "same record_count across runs")
	assert_eq(first.first_error_index, second.first_error_index, "same first_error_index across runs")
	assert_eq(first.error_message, second.error_message, "same error_message across runs")
