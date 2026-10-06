extends SceneTree

func _initialize() -> void:
	call_deferred("_run")

func _run() -> void:
	var suites: Array = []
	for file in DirAccess.get_files_at("res://tests"):
		if file.begins_with("test_") and file.ends_with(".gd"):
			var script: Script = load("res://tests/" + file)
			if script == null or not script.can_instantiate():
				push_error("Test suite could not load: " + file)
				quit(1)
				return
			suites.append(script.new())
	var runner := McpTestRunner.new()
	var result := runner.run_suites(suites)
	print("SOLITAIRE_TEST_RESULT ", JSON.stringify(result))
	suites.clear()
	runner = null
	quit(0 if result.failed == 0 else 1)
