class_name AutoCompletePlanResult
extends RefCounted

## AutoCompletePlanner.plan 的类型化结果（WP-07）：携带资格判定、
## 确定性有序的普通合法移动列表、完成情况、类型化停止原因、
## 步数/访问度量以及模拟终局快照。
## 规划器绝不修改源 GameState；`moves` 是不可变计划数据，
## final_state_snapshot() 返回全新深克隆，调用方无法经由本对象改动结果。

const CODE_ELIGIBLE := "eligible"
const CODE_INVALID_STATE := "invalid_state"
const CODE_TABLEAU_NOT_FACE_UP := "hidden_tableau_cards"
const CODE_ALREADY_WON := "already_won"

const STOP_WON := "won"
const STOP_NO_LEGAL_MOVE := "no_legal_move"
const STOP_NO_PROGRESS := "no_progress"
const STOP_MAX_STEPS := "max_steps"

var eligible: bool = false
var eligibility_code: String = CODE_INVALID_STATE
var eligibility_message: String = ""
var completed: bool = false
var stop_reason: String = ""
var stop_message: String = ""
var moves: Array[Move] = []
var step_count: int = 0
var visited_count: int = 0

var _final_state: GameState = null


static func eligible_result(
	completed_flag: bool,
	stop: String,
	message: String,
	plan_moves: Array[Move],
	final_state: GameState,
	steps: int,
	visited: int
) -> AutoCompletePlanResult:
	var result := AutoCompletePlanResult.new()
	result.eligible = true
	result.eligibility_code = CODE_ELIGIBLE
	result.eligibility_message = "all tableau cards face-up"
	result.completed = completed_flag
	result.stop_reason = stop
	result.stop_message = message
	result.moves = plan_moves.duplicate()
	result.step_count = steps
	result.visited_count = visited
	result._final_state = final_state
	return result


static func not_eligible(code: String, message: String) -> AutoCompletePlanResult:
	var result := AutoCompletePlanResult.new()
	result.eligible = false
	result.eligibility_code = code
	result.eligibility_message = message
	result.completed = false
	result.stop_reason = code
	result.stop_message = message
	return result


## 返回模拟终局的深克隆；当规划器未模拟（不可执行）时返回 null。
## 返回的绝不是规划器的内部对象。
func final_state_snapshot() -> GameState:
	if _final_state == null:
		return null
	return _final_state.clone()


## 调试用字符串：不可执行时显示原因，可执行时显示完成度与统计。
func _to_string() -> String:
	if not eligible:
		return "AutoCompletePlanResult(not eligible: %s %s)" % [eligibility_code, eligibility_message]
	return "AutoCompletePlanResult(eligible, completed=%s, stop=%s, steps=%d, moves=%d)" % [
		str(completed), stop_reason, step_count, moves.size()
	]
