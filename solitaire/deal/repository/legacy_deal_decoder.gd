class_name LegacyDealDecoder
extends RefCounted

## Strict 52-byte legacy decoder (ADR-004).
##
## Each stored record is 52 ASCII bytes + '\n'. Each byte encodes a Card ID
## as byte - ASCII '0' (in [0, 51]). Decode returns the REVERSED id sequence
## (draw order), exactly matching legacy SpriteManager::initCardIds:
##   for i in 0..51: cardIds.push_back(byte[51-i] - '0')
##
## Malformed input is rejected with an empty result. NEVER falls back to a
## random deal: a malformed requested deal is a hard failure.

const RECORD_LENGTH := 52
const ID_BASE := 0x30
const ID_MIN := 0
const ID_MAX := CardData.DECK_SIZE - 1

static func is_valid(encoded: String) -> bool:
	return not decode(encoded).is_empty()

## Returns the 52 ids in reversed (draw) order, or [] if malformed.
static func decode(encoded: String) -> Array[int]:
	if encoded.length() != RECORD_LENGTH:
		return []
	var ids: Array[int] = []
	var seen := {}
	for i in range(RECORD_LENGTH - 1, -1, -1):
		var code := encoded.unicode_at(i)
		if code < ID_BASE or code > ID_BASE + ID_MAX:
			return []
		var id := code - ID_BASE
		if seen.has(id):
			return []
		seen[id] = true
		ids.push_back(id)
	if ids.size() != CardData.DECK_SIZE:
		return []
	return ids

## Diagnostic summary of why a record is invalid (for tests/evidence).
static func validate_reason(encoded: String) -> String:
	if encoded.length() != RECORD_LENGTH:
		return "length %d != 52" % encoded.length()
	var seen := {}
	for i in range(RECORD_LENGTH - 1, -1, -1):
		var code := encoded.unicode_at(i)
		var id := code - ID_BASE
		if code < ID_BASE or code > ID_BASE + ID_MAX:
			return "byte %d out of range" % i
		if seen.has(id):
			return "duplicate id %d" % id
		seen[id] = true
	return ""
