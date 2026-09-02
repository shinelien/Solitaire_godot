extends BaseTest

## Library integrity: counts, byte sizes, hashes tied to the fixed source
## commit, and full-library strict-decode validity for both Draw-1 and Draw-3.

func _sha256(path: String) -> String:
	var f := FileAccess.open(path, FileAccess.READ)
	if f == null:
		return ""
	var ctx := HashingContext.new()
	ctx.start(HashingContext.HASH_SHA256)
	var data := f.get_buffer(65536)
	while data.size() > 0:
		ctx.update(data)
		data = f.get_buffer(65536)
	f.close()
	return ctx.finish().hex_encode()

func _bytes(path: String) -> int:
	var f := FileAccess.open(path, FileAccess.READ)
	if f == null:
		return -1
	var n := f.get_length()
	f.close()
	return n

func test_draw1_library_integrity() -> void:
	var repo := LegacyDealRepository.new()
	check_eq(repo.count_for(GameConfig.DRAW1), GameConfig.EXPECTED_COUNT_1, "draw1 count")
	check_eq(_bytes(GameConfig.DEAL_PATH_1), GameConfig.EXPECTED_BYTES_1, "draw1 bytes")
	check_eq(_sha256(GameConfig.DEAL_PATH_1), GameConfig.SHA256_1, "draw1 sha256")

func test_draw3_library_integrity() -> void:
	var repo := LegacyDealRepository.new()
	check_eq(repo.count_for(GameConfig.DRAW3), GameConfig.EXPECTED_COUNT_3, "draw3 count")
	check_eq(_bytes(GameConfig.DEAL_PATH_3), GameConfig.EXPECTED_BYTES_3, "draw3 bytes")
	check_eq(_sha256(GameConfig.DEAL_PATH_3), GameConfig.SHA256_3, "draw3 sha256")

func test_all_draw1_records_decode() -> void:
	var repo := LegacyDealRepository.new()
	var recs := repo.all_records(GameConfig.DRAW1)
	for i in recs.size():
		if not LegacyDealDecoder.is_valid(recs[i]):
			check(false, "draw1 record %d invalid" % i)
			return

func test_all_draw3_records_decode() -> void:
	var repo := LegacyDealRepository.new()
	var recs := repo.all_records(GameConfig.DRAW3)
	for i in recs.size():
		if not LegacyDealDecoder.is_valid(recs[i]):
			check(false, "draw3 record %d invalid" % i)
			return

func test_out_of_range_returns_empty() -> void:
	var repo := LegacyDealRepository.new()
	check_eq(repo.get_record(GameConfig.DRAW1, -1), "", "negative index")
	check_eq(repo.get_record(GameConfig.DRAW1, 32084), "", "past end")
	check_eq(repo.get_record(GameConfig.DRAW3, 4999), "", "past end draw3")
	check_not_null(repo.get_record(GameConfig.DRAW1, 0), "first record present")
	check_eq(repo.get_record(GameConfig.DRAW1, 0).length(), 52, "record length")
