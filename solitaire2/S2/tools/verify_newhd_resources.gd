extends SceneTree
func _initialize() -> void:
	var failures: Array[String] = []
	var manifest: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/manifest.json"))
	for source: String in manifest.scenes:
		var path := "res://scenes/newhd/" + source.replace(".csd", ".tscn")
		var scene: PackedScene = load(path)
		if scene == null:
			failures.append(path)
		else:
			var node := scene.instantiate()
			if node == null:
				failures.append(path)
			else:
				node.free()
	print(JSON.stringify({"scenes": manifest.scenes.size(), "failures": failures}))
	quit(0 if failures.is_empty() else 1)
