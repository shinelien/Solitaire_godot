extends BaseTest

## Decoder negative paths: wrong length, invalid byte, duplicate id, missing
## id must all fail closed — never a random fallback.

const ID_BASE := 0x30

func _enc_from_ids(ids: Array[int]) -> String:
	# Builds the stored record from the *unreversed* id order so a duplicate
	# at the end also lands in the reversed decode.
	var chars := PackedByteArray()
	for id in ids:
		chars.append(ID_BASE + id)
	return chars.get_string_from_ascii()

func test_wrong_length() -> void:
	check_false(LegacyDealDecoder.is_valid(""), "empty")
	check_false(LegacyDealDecoder.is_valid("ABC"), "short")
	var long := ""
	for i in 53:
		long += "A"
	check_false(LegacyDealDecoder.is_valid(long), "too long")

func test_valid_permutation_accepted() -> void:
	var ids: Array[int] = []
	for i in 52:
		ids.push_back(i)
	var enc := _enc_from_ids(ids)
	check_true(LegacyDealDecoder.is_valid(enc), "identity permutation accepted")
	var dec := LegacyDealDecoder.decode(enc)
	check_eq(dec.size(), 52, "decoded size")
	check_eq(dec[0], 51, "reversed order (draw order) start")
	check_eq(dec[51], 0, "reversed order end")

func test_invalid_byte_rejected() -> void:
	var ids: Array[int] = []
	for i in 52:
		ids.push_back(i)
	ids[0] = 52
	var enc := _enc_from_ids(ids)
	check_false(LegacyDealDecoder.is_valid(enc), "id 52 out of range")
	# byte below '0'
	var base := _enc_from_ids(ids)
	var b := base.to_utf8_buffer()
	b[0] = 0x2F
	check_false(LegacyDealDecoder.is_valid(b.get_string_from_ascii()), "byte below ascii 0")

func test_duplicate_rejected() -> void:
	var ids: Array[int] = []
	for i in 52:
		ids.push_back(i)
	ids[51] = 1  # duplicate of ids[1]
	var enc := _enc_from_ids(ids)
	check_false(LegacyDealDecoder.is_valid(enc), "duplicate id")
	check_eq(LegacyDealDecoder.decode(enc).size(), 0, "decode empty on duplicate")

func test_missing_rejected() -> void:
	var ids: Array[int] = []
	for i in 52:
		ids.push_back(i)
	ids[50] = 2  # duplicate 2, missing 50
	var enc := _enc_from_ids(ids)
	check_false(LegacyDealDecoder.is_valid(enc), "missing id -> duplicate triggers rejection")

func test_validate_reason_describes_problem() -> void:
	check(LegacyDealDecoder.validate_reason("") != "", "reason for empty")
