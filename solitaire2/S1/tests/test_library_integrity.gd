@tool
extends McpTestSuite


func suite_name() -> String:
	return "library_integrity"


const KNOWN_SHA_BUREAU1 := "36414bfcd91c916caa77c8b908dc51000732bfc8ba2b8113798d6a2a48d2ccf5"
const KNOWN_SHA_BUREAU3 := "0bf9409ac5a5954a02460274fc50e8cd1ca79693be4dd90e70cc6ebcac81ca43"
const KNOWN_RECORD0_SHA_52B := "7a0e10fddf0759403b0b06788ae1dc256df74d7c9f8e52e39e8c00c25a34fce0"
const KNOWN_RECORD0_SHA_53B := "6c839523eed3cdb1a2f8212b81a4e561525f926f27395c923fd289ffa7e7111f"


func _sha256(bytes: PackedByteArray) -> String:
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	ctx.update(bytes)
	return ctx.finish().hex_encode()


func test_pool_counts_bytes_and_sha_match_fixed_object() -> void:
	assert_eq(LegacyDealRepository.record_count("bureau1"), 32084, "bureau1 record count")
	assert_eq(LegacyDealRepository.record_count("bureau3"), 4999, "bureau3 record count")
	assert_eq(LegacyDealRepository.pool_byte_count("bureau1"), 1700452, "bureau1 bytes")
	assert_eq(LegacyDealRepository.pool_byte_count("bureau3"), 264947, "bureau3 bytes")
	assert_eq(LegacyDealRepository.pool_sha256("bureau1"), KNOWN_SHA_BUREAU1, "bureau1 content sha256")
	assert_eq(LegacyDealRepository.pool_sha256("bureau3"), KNOWN_SHA_BUREAU3, "bureau3 content sha256")
	assert_eq(LegacyDealRepository.expected_records("bureau1"), 32084, "expected_records b1")
	assert_eq(LegacyDealRepository.expected_records("bureau3"), 4999, "expected_records b3")


func test_golden_meta_consistent_with_repository() -> void:
	for pool in ["bureau1", "bureau3"]:
		var meta := GoldenLoader.meta(pool)
		var pools: Dictionary = meta.get("pools", {})
		var info: Dictionary = pools.get(pool, {})
		assert_eq(
			LegacyDealRepository.pool_sha256(pool),
			String(info.get("sha256", "")),
			"%s sha matches generator meta" % pool
		)
		assert_eq(
			LegacyDealRepository.record_count(pool),
			int(info.get("records", -1)),
			"%s records match generator meta" % pool
		)


func test_full_library_validation_deterministic() -> void:
	for pool in ["bureau1", "bureau3"]:
		var first := LegacyDealRepository.validate_pool(pool)
		var second := LegacyDealRepository.validate_pool(pool)
		assert_true(first.ok, "%s whole-library layout decodes" % pool)
		assert_eq(first.record_count, LegacyDealRepository.record_count(pool), "%s count" % pool)
		assert_eq(first.first_error_index, -1, "%s no first error" % pool)
		assert_eq(second.ok, first.ok, "%s deterministic" % pool)


func test_record0_hashes_pin_fixed_object() -> void:
	var record := LegacyDealRepository.get_record("bureau1", 0)
	assert_true(record.ok, "record0 fetched")
	var record_text: String = record.record
	var bytes_52: PackedByteArray = record_text.to_ascii_buffer()
	var bytes_53 := PackedByteArray()
	bytes_53.append_array(bytes_52)
	bytes_53.append(10)
	assert_eq(_sha256(bytes_52), KNOWN_RECORD0_SHA_52B, "record0 52B sha")
	assert_eq(_sha256(bytes_53), KNOWN_RECORD0_SHA_53B, "record0 53B sha")
	var meta := GoldenLoader.meta("bureau1")
	var record0: Dictionary = meta.get("record0", {})
	assert_eq(_sha256(bytes_53), String(record0.get("sha256_53b_with_lf", "")), "53B matches meta")
	assert_eq(_sha256(bytes_52), String(record0.get("sha256_52b_no_lf", "")), "52B matches meta")


func test_index_bounds_explicit_no_fallback() -> void:
	var first := LegacyDealRepository.get_record("bureau1", 0)
	var last := LegacyDealRepository.get_record("bureau1", 32083)
	var last3 := LegacyDealRepository.get_record("bureau3", 4998)
	assert_true(first.ok, "first bureau1 record")
	assert_true(last.ok, "last bureau1 record")
	assert_true(last3.ok, "last bureau3 record")
	assert_eq(first.record.length(), 52, "record length 52")
	for bad in [[-1, "bureau1"], [32084, "bureau1"], [-5, "bureau3"], [4999, "bureau3"]]:
		var result := LegacyDealRepository.get_record(bad[1], bad[0])
		assert_false(result.ok, "reject %s#%d" % [bad[1], bad[0]])
		assert_eq(result.error_code, "index_out_of_range", "index code for %s#%d" % [bad[1], bad[0]])
	var unknown := LegacyDealRepository.get_record("bogus", 0)
	assert_false(unknown.ok, "unknown pool")
	assert_eq(unknown.error_code, "invalid_pool", "unknown pool code")


func test_fixture_records_equal_repository_records() -> void:
	for pool in ["bureau1", "bureau3"]:
		var fixtures := GoldenLoader.fixtures(pool)
		var problems: Array[String] = []
		for fixture in fixtures:
			var index := int(fixture.index)
			var fetch := LegacyDealRepository.get_record(pool, index)
			if not fetch.ok or fetch.record != String(fixture.raw_deal):
				problems.append("%s#%d raw mismatch" % [pool, index])
		assert_true(problems.is_empty(), "fixture raw == repository raw: " + str(problems))
