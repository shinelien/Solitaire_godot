class_name LegacyDealResult
extends RefCounted

## Typed result of a decode/deal operation: either a built GameState or an
## explicit failure code+message. Never silently falls back.

const CODE_OK := "ok"
const CODE_INVALID_RECORD := "invalid_record"
const CODE_INVALID_POOL := "invalid_pool"
const CODE_INVALID_DRAW_COUNT := "invalid_draw_count"
const CODE_INDEX_OUT_OF_RANGE := "index_out_of_range"
const CODE_IO_ERROR := "io_error"

var ok: bool = false
var error_code: String = CODE_OK
var error_message: String = ""
var state: GameState = null


static func success(state: GameState) -> LegacyDealResult:
	var result := LegacyDealResult.new()
	result.ok = true
	result.state = state
	return result


static func failure(code: String, message: String) -> LegacyDealResult:
	var result := LegacyDealResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	return result


func _to_string() -> String:
	if not ok:
		return "LegacyDealResult(fail: %s %s)" % [error_code, error_message]
	if state == null:
		return "LegacyDealResult(ok)"
	return "LegacyDealResult(ok, %s)" % state.deal_key()
