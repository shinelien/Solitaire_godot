class_name LegacyDealResult
extends RefCounted

## 解码/发牌操作的类型化结果：要么是构建好的 GameState，
## 要么是显式失败码 + 消息。绝无静默降级。

const CODE_OK := "ok"
const CODE_INVALID_RECORD := "invalid_record"
const CODE_INVALID_POOL := "invalid_pool"
const CODE_INVALID_DRAW_COUNT := "invalid_draw_count"
const CODE_INDEX_OUT_OF_RANGE := "index_out_of_range"
const CODE_IO_ERROR := "io_error"

## 操作是否成功。
var ok: bool = false
## 失败时的稳定错误码；成功时为 CODE_OK。
var error_code: String = CODE_OK
## 失败时的可读原因。
var error_message: String = ""
## 成功时构建好的牌局状态（失败时为 null）。
var state: GameState = null


## 构造成功结果：携带构建好的牌局状态。
static func success(state: GameState) -> LegacyDealResult:
	var result := LegacyDealResult.new()
	result.ok = true
	result.state = state
	return result


## 构造失败结果：稳定错误码 + 可读消息。
static func failure(code: String, message: String) -> LegacyDealResult:
	var result := LegacyDealResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	return result


## 调试用字符串：失败显示错误码，成功显示牌局身份。
func _to_string() -> String:
	if not ok:
		return "LegacyDealResult(fail: %s %s)" % [error_code, error_message]
	if state == null:
		return "LegacyDealResult(ok)"
	return "LegacyDealResult(ok, %s)" % state.deal_key()
