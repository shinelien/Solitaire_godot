class_name GameSessionResult
extends RefCounted

## GameSession.create 的类型化结果（WP-07）：要么是构造好的会话，
## 要么是显式失败（牌池/序号/翻牌模式/牌局记录错误）。
## 会话内状态转换因为都经 MoveExecutor 执行，复用 MoveExecutionResult 的错误码；
## 只有“构造会话”路径携带 deal 层错误码。

const CODE_OK := "ok"
const CODE_INVALID_POOL := "invalid_pool"
const CODE_INDEX_OUT_OF_RANGE := "index_out_of_range"
const CODE_INVALID_DRAW_COUNT := "invalid_draw_count"
const CODE_INVALID_RECORD := "invalid_record"
const CODE_IO_ERROR := "io_error"
## 共享的结构性失败码（例如调试夹具不是合法的 52 张全排列）；
## 与 MoveExecutionResult 使用同一错误码字符串。
const CODE_INVALID_STATE := "invalid_state"

## 会话构造是否成功。
var ok: bool = false
## 失败时的稳定错误码；成功时为 CODE_OK。
var error_code: String = CODE_OK
## 失败时的可读原因。
var error_message: String = ""
## 成功时构造好的会话（失败时为 null）。
var session: GameSession = null


## 构造成功结果：携带新会话。
static func success(session: GameSession) -> GameSessionResult:
	var result := GameSessionResult.new()
	result.ok = true
	result.session = session
	return result


## 构造失败结果：稳定错误码 + 可读消息。
static func failure(code: String, message: String) -> GameSessionResult:
	var result := GameSessionResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	return result


## 调试用字符串：失败显示错误码，成功显示牌局身份。
func _to_string() -> String:
	if not ok:
		return "GameSessionResult(fail: %s %s)" % [error_code, error_message]
	if session == null:
		return "GameSessionResult(ok)"
	return "GameSessionResult(ok, %s)" % session.deal_key()
