class_name MoveValidationResult
extends RefCounted

## Typed, stable outcome of a RulesEngine legality check. RulesEngine never
## mutates state; it only answers "is this move legal and why/why not" so the
## MoveExecutor can make decisions without ever using score to decide legality.

const CODE_OK := "ok"
const CODE_INVALID_STATE := "invalid_state"
const CODE_INVALID_KIND := "invalid_kind"
const CODE_INVALID_INDEX := "invalid_index"
const CODE_INVALID_LOCATION := "invalid_location"
const CODE_SELF_MOVE := "self_move"
const CODE_EMPTY_SOURCE := "empty_source"
const CODE_FACE_DOWN_CARD := "face_down_card"
const CODE_INVALID_COUNT := "invalid_count"
const CODE_RUN_RANK := "run_rank"
const CODE_RUN_COLOR := "run_color"
const CODE_DEST_RANK := "dest_rank"
const CODE_DEST_COLOR := "dest_color"
const CODE_DEST_REQUIRES_KING := "dest_requires_king"
const CODE_FOUNDATION_REQUIRES_ACE := "foundation_requires_ace"
const CODE_FOUNDATION_RANK := "foundation_rank"
const CODE_FOUNDATION_SUIT := "foundation_suit"
const CODE_STOCK_EMPTY := "stock_empty"
const CODE_STOCK_NOT_EMPTY := "stock_not_empty"
const CODE_WASTE_EMPTY := "waste_empty"
const CODE_NOT_FACE_DOWN := "not_face_down"
const CODE_ALREADY_WON := "already_won"
const CODE_INVALID_DRAW_COUNT := "invalid_draw_count"

var ok: bool = false
var error_code: String = CODE_OK
var error_message: String = ""


static func success() -> MoveValidationResult:
	var result := MoveValidationResult.new()
	result.ok = true
	result.error_code = CODE_OK
	return result


static func failure(code: String, message: String) -> MoveValidationResult:
	var result := MoveValidationResult.new()
	result.ok = false
	result.error_code = code
	result.error_message = message
	return result


func _to_string() -> String:
	if ok:
		return "MoveValidationResult(ok)"
	return "MoveValidationResult(fail: %s %s)" % [error_code, error_message]
