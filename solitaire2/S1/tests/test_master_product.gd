@tool
extends McpTestSuite

func suite_name() -> String:
	return "master_product"

func test_random_deal_replay_and_card_conservation() -> void:
	var session := MasterSession.new()
	for draw in [1, 3]:
		session.start(draw)
		var first := session.original_ids.duplicate()
		assert_eq(first.size(), 52)
		assert_eq(session.state.total_card_count(), 52)
		assert_eq(session.state.stock.size(), 24 - draw)
		assert_eq(session.state.waste.size(), draw)
		var unique := {}
		for id in first:
			unique[id] = true
		assert_eq(unique.size(), 52)
		session.start(draw, true)
		assert_eq(session.original_ids, first, "replay retains the exact random deal")
		session.start(draw)
		assert_true(session.original_ids != first, "new game changes the shuffled deck")

func test_master_scoring_recycle_and_undo_are_distinct_from_legacy() -> void:
	var session := MasterSession.new()
	session.start(1)
	session.state.score = 200
	while not session.state.stock.is_empty():
		assert_true(session.apply(Move.draw_stock()).ok)
	assert_true(session.apply(Move.recycle_stock()).ok)
	assert_eq(session.state.score, 180, "master draw-one recycling costs 20")
	assert_true(session.undo())
	assert_eq(session.state.score, 178, "master undo does not refund the recycle fee")
	assert_eq(session.state.total_card_count(), 52)
	session.start(3)
	session.state.score = 200
	while not session.state.stock.is_empty():
		assert_true(session.apply(Move.draw_stock()).ok)
	assert_true(session.apply(Move.recycle_stock()).ok)
	assert_eq(session.state.score, 100, "master draw-three recycling costs 100")

func test_foundation_rollback_cost_and_move_count_on_repeated_undo() -> void:
	var session := MasterSession.new()
	session.state = GameState.new()
	session.state.foundation[0].add_top(CardData.new(0, true))
	session.state.tableau[1].add_top(CardData.new(14, true))
	session.state.score = 50
	assert_true(session.apply(Move.foundation_to_tableau(0, 1)).ok)
	assert_eq(session.state.score, 35)
	assert_true(session.undo())
	assert_eq(session.state.score, 48)
	assert_eq(session.state.move_count, 2)
	assert_true(session.apply(Move.foundation_to_tableau(0, 1)).ok)
	assert_true(session.undo())
	assert_eq(session.state.move_count, 4, "undo advances current count instead of restoring old count")

func test_native_spine_source_clips_and_event_timestamps() -> void:
	var lib: AnimationLibrary = load("res://assets/master/spine/card_animations.tres")
	for clip in ["Flip0", "Flip1", "Flip2", "Flip3", "Flip_L1", "Flip_L2", "Magic", "flight0", "touch1"]:
		assert_true(lib.has_animation(clip), clip)
	for entry in [["Flip0", .2], ["Flip1", .0667], ["Flip2", .1], ["Flip3", .1], ["Flip_L1", .0667], ["Flip_L2", .1]]:
		var animation := lib.get_animation(entry[0])
		var found := false
		for track in animation.get_track_count():
			if animation.track_get_type(track) == Animation.TYPE_METHOD:
				assert_true(absf(animation.track_get_key_time(track, 0) - entry[1]) < .00001)
				found = true
		assert_true(found, "flip event is present: " + entry[0])

func test_all_source_scene_resources_load() -> void:
	for name in ["GameLayer", "ShopLayer", "ItemNode", "RuleLayer", "CountLayer", "WinLayer", "CoinLayer", "FreeCoinLayer", "TipsNode"]:
		var packed: PackedScene = load("res://scenes/native/%s.tscn" % name)
		assert_true(packed != null, name)
		var instance := packed.instantiate()
		assert_true(instance.get_child_count() > 0)
		instance.free()
