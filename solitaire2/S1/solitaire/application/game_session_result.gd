class_name GameSessionResult
extends RefCounted

## Typed outcome of GameSession.create (WP-07): either a constructed session
## or an explicit failure (pool/index/draw mode/deal record errors). Session
## transitions themselves reuse MoveExecutionResult codes because they flow
## through MoveExecutor; only construction carries deal-layer codes.

const CODE_OK := "ok"
const CODE_INVALID_POOL := "invalid_pool"
const CODE_INDEX_OUT_OF_RANGE := "index_out_of_range"
const CODE_INVALID_DRAW_COUNT := "invalid_draw_count"
const CODE_INVALID_RECORD := "invalid_record"
const CODE_IO_ERROR := "io_error"

var ok: bool = false
var error_code: String = CODE_OK
var error_message: String = ""
var session: GameSession = null


static func success(session: GameSession) -> GameSessionResult:
	var result := GameSessionResult.new()
	result.ok = true
	result.session = session
	return result


static func failure(code: String, message: String) -> GameSessionResult:
	var result := GameSessionResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	return result


func _to_string() -> String:
	if not ok:
		return "GameSessionResult(fail: %s %s)" % [error_code, error_message]
	if session == null:
		return "GameSessionResult(ok)"
	return "GameSessionResult(ok, %s)" % session.deal_key()
