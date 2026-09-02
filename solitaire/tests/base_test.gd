class_name BaseTest
extends RefCounted

## Shared assertion helpers. Suites extend this; the runner calls every
## method whose name starts with "test_".

var _failures: Array[String] = []

func clear_failures() -> void:
	_failures.clear()

func failures() -> Array[String]:
	return _failures

func check(cond: bool, msg: String) -> void:
	if not cond:
		_failures.push_back(msg)

func check_true(cond: bool, msg: String) -> void:
	check(cond, msg)

func check_false(cond: bool, msg: String) -> void:
	check(not cond, msg)

func check_eq(actual, expected, msg: String) -> void:
	if actual != expected:
		_failures.push_back("%s: expected=%s actual=%s" % [msg, str(expected), str(actual)])

func check_not_null(v, msg: String) -> void:
	if v == null:
		_failures.push_back(msg + " (was null)")

func check_null(v, msg: String) -> void:
	if v != null:
		_failures.push_back(msg + " (was not null: %s)" % str(v))

func check_empty(arr: Array, msg: String) -> void:
	if not arr.is_empty():
		_failures.push_back(msg + " (expected empty, got %d)" % arr.size())

## Builds a typed Array[CardData] from an untyped literal so tests never
## replace pile arrays with untyped arrays (which the strict analyzer rejects
## when read back through GameState.col/fnd).
func typed_col(cards: Array) -> Array[CardData]:
	var out: Array[CardData] = []
	for c in cards:
		out.push_back(c)
	return out
