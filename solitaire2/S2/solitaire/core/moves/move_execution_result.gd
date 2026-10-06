class_name MoveExecutionResult
extends RefCounted

## MoveExecutor.execute / execute_undo 的类型化结果。
## 成功时携带深克隆的 new_state 与显式 MoveBatch
## （requested/applied/generated）；失败时 new_state 为 null，
## 且源状态绝未被修改（执行器只在克隆上工作）。

const CODE_OK := "ok"
const CODE_INVALID_STATE := "invalid_state"
const CODE_INVALID_KIND := "invalid_kind"
const CODE_NOTHING_TO_UNDO := "nothing_to_undo"
const CODE_INTERNAL := "internal_error"

## 是否执行成功。
var ok: bool = false
## 失败时的稳定错误码；成功时为 CODE_OK。
var error_code: String = CODE_OK
## 失败时的可读原因。
var error_message: String = ""
## 成功后的新牌局状态（深克隆；失败时为 null）。
var new_state: GameState = null
## 实际执行的移动批次（成功后非空）。
var batch: MoveBatch = null
## 仅当请求的游戏移动被规则引擎拒绝时非空（携带具体校验结果）。
var validation: MoveValidationResult = null


## 构造成功结果：携带新状态与已执行批次。
static func success(state: GameState, batch: MoveBatch) -> MoveExecutionResult:
	var result := MoveExecutionResult.new()
	result.ok = true
	result.new_state = state
	result.batch = batch
	return result


## 构造失败结果：稳定错误码 + 原因，可选附带规则引擎校验结果。
static func failure(code: String, message: String, validation_result: MoveValidationResult = null) -> MoveExecutionResult:
	var result := MoveExecutionResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	result.validation = validation_result
	return result


## 返回用户请求的移动；无批次时返回 null。
func requested_move() -> Move:
	if batch == null:
		return null
	return batch.requested


## 返回按执行顺序排列的全部实际移动。
func applied_moves() -> Array[Move]:
	if batch == null:
		return []
	return batch.applied


## 返回执行器自动生成的移动列表。
func generated_moves() -> Array[Move]:
	if batch == null:
		return []
	return batch.generated


## 该结果是否对应一次撤销操作。
func undoes() -> bool:
	return batch != null and batch.is_undo_batch()


## 调试用字符串：失败显示错误码与消息，成功显示批次概要。
func _to_string() -> String:
	if not ok:
		return "MoveExecutionResult(fail: %s %s)" % [error_code, error_message]
	return "MoveExecutionResult(ok, %s)" % str(batch)
