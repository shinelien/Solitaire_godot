class_name HintResult
extends RefCounted

## Typed outcome of HintEngine.hint (WP-07). Either a legal Move with the
## deterministic priority tier that selected it, or an explicit typed no-hint
## reason. A HintResult never mutates state and never carries a reference to
## the state it was computed from.

const CODE_HINT := "hint"
const CODE_NO_LEGAL_MOVE := "no_legal_move"
const CODE_ALREADY_WON := "already_won"
const CODE_INVALID_STATE := "invalid_state"

## Priority tiers, lower = preferred. See HintEngine docstring for the exact
## total ordering contract. TIER_NONE marks a no-hint result.
const TIER_NONE := -1
const TIER_EXPOSE := 0
const TIER_TO_FOUNDATION := 1
const TIER_WASTE_TO_TABLEAU := 2
const TIER_TABLEAU_RUN := 3
const TIER_STOCK := 4
const TIER_FOUNDATION_ROLLBACK := 5
const TIER_TRIVIAL := 6

var ok: bool = false
var code: String = CODE_NO_LEGAL_MOVE
var message: String = ""
## Non-null iff ok; always RulesEngine-legal for the state the hint was asked.
var move: Move = null
var tier: int = TIER_NONE


static func success(move: Move, tier: int, message: String) -> HintResult:
	var result := HintResult.new()
	result.ok = true
	result.code = CODE_HINT
	result.move = move
	result.tier = tier
	result.message = message
	return result


static func failure(code: String, message: String) -> HintResult:
	var result := HintResult.new()
	result.ok = false
	result.code = code
	result.message = message
	return result


func has_hint() -> bool:
	return ok and move != null


func _to_string() -> String:
	if not ok:
		return "HintResult(fail: %s %s)" % [code, message]
	return "HintResult(ok tier=%d %s)" % [tier, move.description() if move != null else "null"]
