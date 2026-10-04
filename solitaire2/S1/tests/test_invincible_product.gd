@tool
extends McpTestSuite

func suite_name() -> String:
	return "invincible_product"

func test_latest_branch_deals_replay_and_recycle_scoring() -> void:
	var session := InvincibleSession.new()
	for draw in [1, 3]:
		session.start(draw)
		var record := session.replay_record
		assert_eq(session.state.total_card_count(), 52)
		assert_eq(session.state.waste.size(), draw)
		session.start(draw, true)
		assert_eq(session.replay_record, record)
		session.state.score = 200
		while not session.state.stock.is_empty():
			assert_true(session.apply(Move.draw_stock()).ok)
		assert_true(session.apply(Move.recycle_stock()).ok)
		assert_eq(session.state.score, 200, "latest branch disables recycle penalty")
		assert_true(session.undo())
		assert_eq(session.state.score, 198)
		assert_eq(session.state.total_card_count(), 52)

func test_level_time_limit_uses_source_multiplier_and_rounding() -> void:
	var session := InvincibleSession.new()
	session.start(1)
	session.level = {"type": "LimitTime", "times": 123}
	session.elapsed = 299.9
	assert_false(session.objective().lost)
	session.elapsed = 300
	assert_true(session.objective().lost, "123 * 2.5 is rounded down to 300 seconds")

func test_all_daily_decks_are_valid_in_both_draw_modes() -> void:
	var data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/invincible/data/daily.json"))
	assert_eq(data.config.size(), 366)
	for day in data.config.size():
		for mode in range(1, 5):
			var record: String = data.config[day][str(mode)].decks
			var result := LegacyDealer.deal_ready_from_record(record, "daily", day, 3 if mode in [2, 4] else 1, "InvincibleWarrior")
			assert_true(result.ok, "%d:%d" % [day, mode])
			if result.ok:
				assert_eq(result.state.total_card_count(), 52)

func test_source_flip_events_and_dynamic_region_orientation() -> void:
	var bytes := FileAccess.get_file_as_bytes("res://assets/invincible/baked/card.json.gz")
	var rig: Dictionary = JSON.parse_string(bytes.decompress_dynamic(100_000_000, FileAccess.COMPRESSION_GZIP).get_string_from_utf8())
	for entry in [["Flip0", .2], ["Flip1", .0667], ["Flip2", .1], ["Flip3", .1], ["Flip_L1", .0667], ["Flip_L2", .1]]:
		assert_true(rig.clips.has(entry[0]))
		assert_true(absf(float(rig.events[entry[0]][0].time) - entry[1]) < .00001)
	for attachment: Dictionary in rig.attachments:
		if attachment.slot in ["poker0", "poker2", "poker3"]:
			assert_eq(attachment.override_uv, [1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0], "BR BL UL UR quad order")
