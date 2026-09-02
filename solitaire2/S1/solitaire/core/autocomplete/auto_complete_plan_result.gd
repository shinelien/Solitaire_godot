class_name AutoCompletePlanResult
extends RefCounted

## Typed outcome of AutoCompletePlanner.plan (WP-07). Carries eligibility, the
## deterministic ordered list of ordinary legal moves to apply, completion,
## a typed stop reason, step/visited metrics and a snapshot of the simulated
## final state. The planner never mutates the source GameState; `moves` are
## immutable plan data and `final_state_snapshot()` hands back a fresh deep
## clone so no caller can mutate the planner's result through this object.

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


## Fresh deep clone of the simulated final state, or null when the planner did
## not simulate (not eligible). Never the planner's internal object.
func final_state_snapshot() -> GameState:
	if _final_state == null:
		return null
	return _final_state.clone()


func _to_string() -> String:
	if not eligible:
		return "AutoCompletePlanResult(not eligible: %s %s)" % [eligibility_code, eligibility_message]
	return "AutoCompletePlanResult(eligible, completed=%s, stop=%s, steps=%d, moves=%d)" % [
		str(completed), stop_reason, step_count, moves.size()
	]
