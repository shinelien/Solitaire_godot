extends SceneTree

## Dependency-free test entry point. Run with:
##   Godot --headless --path . --script res://tests/run_all.gd
## Discovers res://tests/test_*.gd, runs every test_* method, prints a
## summary and exits non-zero on any failure.

var _passed := 0
var _failed := 0
var _failures: Array[String] = []

func _initialize() -> void:
	_passed = 0
	_failed = 0
	_failures.clear()
	var dir := DirAccess.open("res://tests")
	if dir == null:
		print("TESTS: cannot open res://tests")
		quit(1)
		return
	var files := dir.get_files()
	files.sort()
	var suites: Array[String] = []
	for f in files:
		if f.begins_with("test_") and f.ends_with(".gd"):
			suites.push_back("res://tests/" + f)
	if suites.is_empty():
		print("TESTS: no suites found")
		quit(1)
		return
	for path in suites:
		_run_suite(path)
	print("")
	print("=== TEST SUMMARY ===")
	print("suites: %d, tests passed: %d, tests failed: %d" % [suites.size(), _passed, _failed])
	if not _failures.is_empty():
		print("failures:")
		for msg in _failures:
			print("  - " + msg)
	quit(1 if _failed > 0 else 0)

func _run_suite(path: String) -> void:
	var script: GDScript = load(path)
	if script == null:
		_failed += 1
		_failures.push_back(path + ": script failed to load (parse error)")
		print("SUITE %s: LOAD FAILED" % path.get_file())
		return
	var suite: Object = script.new()
	if not (suite is BaseTest):
		_failed += 1
		_failures.push_back(path + ": not a BaseTest subclass")
		print("SUITE %s: NOT BASETEST" % path.get_file())
		return
	var methods: Array[Dictionary] = suite.get_method_list()
	var test_methods: Array[String] = []
	for m in methods:
		var name: String = m["name"]
		if name.begins_with("test_"):
			test_methods.push_back(name)
	test_methods.sort()
	var suite_failed := 0
	for method in test_methods:
		suite.clear_failures()
		suite.call(method)
		if suite.failures().is_empty():
			_passed += 1
		else:
			_failed += 1
			suite_failed += 1
			_failures.push_back("%s.%s: %s" % [path.get_file(), method, " | ".join(suite.failures())])
	print("SUITE %s: %d tests (%d failed)" % [path.get_file(), test_methods.size(), suite_failed])
