class_name HintResult
extends RefCounted

## HintEngine.hint 的类型化结果（WP-07）：要么是携带选定其的确定性
## 优先级层级（tier）的合法 Move，要么是显式的无提示类型化原因。
## HintResult 绝不修改状态，也绝不持有计算来源状态的引用。

const CODE_HINT := "hint"
const CODE_NO_LEGAL_MOVE := "no_legal_move"
const CODE_ALREADY_WON := "already_won"
const CODE_INVALID_STATE := "invalid_state"

## 优先级层级，数值越小越优先。完整全序契约见 HintEngine 类注释；
## TIER_NONE 表示“无提示”结果。
const TIER_NONE := -1
const TIER_EXPOSE := 0
const TIER_TO_FOUNDATION := 1
const TIER_WASTE_TO_TABLEAU := 2
const TIER_TABLEAU_RUN := 3
const TIER_STOCK := 4
const TIER_FOUNDATION_ROLLBACK := 5
const TIER_TRIVIAL := 6

## 是否成功给出提示。
var ok: bool = false
## 结果码（hint / no_legal_move / already_won / invalid_state）。
var code: String = CODE_NO_LEGAL_MOVE
## 供界面/日志使用的可读消息。
var message: String = ""
## 仅当 ok 时非空；对询问提示的状态而言，它始终已通过规则引擎校验。
var move: Move = null
## 选中该移动的优先级层级；无提示时为 TIER_NONE。
var tier: int = TIER_NONE


## 构造成功提示结果：合法移动 + 选定层级 + 消息。
static func success(move: Move, tier: int, message: String) -> HintResult:
	var result := HintResult.new()
	result.ok = true
	result.code = CODE_HINT
	result.move = move
	result.tier = tier
	result.message = message
	return result


## 构造失败结果：类型化原因码 + 消息。
static func failure(code: String, message: String) -> HintResult:
	var result := HintResult.new()
	result.ok = false
	result.code = code
	result.message = message
	return result


## 是否确实存在可用提示。
func has_hint() -> bool:
	return ok and move != null


## 调试用字符串：失败显示原因码，成功显示层级与移动描述。
func _to_string() -> String:
	if not ok:
		return "HintResult(fail: %s %s)" % [code, message]
	return "HintResult(ok tier=%d %s)" % [tier, move.description() if move != null else "null"]
