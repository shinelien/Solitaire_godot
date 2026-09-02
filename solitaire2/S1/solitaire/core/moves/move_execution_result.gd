class_name MoveExecutionResult
extends RefCounted

## Typed outcome of MoveExecutor.execute / execute_undo. On success it carries
## a deep-cloned new_state plus the explicit MoveBatch (requested/applied/
## generated). On failure new_state is null and the source state was never
## mutated (the executor works on clones only).

const CODE_OK := "ok"
const CODE_INVALID_STATE := "invalid_state"
const CODE_INVALID_KIND := "invalid_kind"
const CODE_NOTHING_TO_UNDO := "nothing_to_undo"
const CODE_INTERNAL := "internal_error"

var ok: bool = false
var error_code: String = CODE_OK
var error_message: String = ""
var new_state: GameState = null
var batch: MoveBatch = null
## Non-null only when a requested gameplay move was rejected by RulesEngine.
var validation: MoveValidationResult = null


static func success(state: GameState, batch: MoveBatch) -> MoveExecutionResult:
	var result := MoveExecutionResult.new()
	result.ok = true
	result.new_state = state
	result.batch = batch
	return result


static func failure(code: String, message: String, validation_result: MoveValidationResult = null) -> MoveExecutionResult:
	var result := MoveExecutionResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	result.validation = validation_result
	return result


func requested_move() -> Move:
	if batch == null:
		return null
	return batch.requested


func applied_moves() -> Array[Move]:
	if batch == null:
		return []
	return batch.applied


func generated_moves() -> Array[Move]:
	if batch == null:
		return []
	return batch.generated


func undoes() -> bool:
	return batch != null and batch.is_undo_batch()


func _to_string() -> String:
	if not ok:
		return "MoveExecutionResult(fail: %s %s)" % [error_code, error_message]
	return "MoveExecutionResult(ok, %s)" % str(batch)
