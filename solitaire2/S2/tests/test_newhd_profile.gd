extends McpTestSuite

func suite_name() -> String:
	return "newhd_profile"
var path := "user://newhd_profile_tests.cfg"
func fresh() -> NewHDProfile:
	DirAccess.remove_absolute(ProjectSettings.globalize_path(path))
	return NewHDProfile.new(path)

func test_source_defaults_and_independent_save() -> void:
	var profile := fresh()
	assert_eq(profile.coins, 100)
	assert_eq(profile.diamonds, 0)
	assert_eq(profile.magic, 5)
	assert_eq(profile.level, 1)
	assert_eq(profile.skin_owned.background, [0, 18])
	profile.settings.background = 18
	profile.save()
	assert_eq(NewHDProfile.new(path).settings.background, 18)

func test_magic_uses_newhd_diamonds() -> void:
	var profile := fresh()
	profile.coins = 9999
	assert_false(profile.buy_magic().ok)
	assert_eq(profile.magic, 5)
	profile.diamonds = 200
	assert_true(profile.buy_magic().ok)
	assert_eq(profile.diamonds, 0)
	assert_eq(profile.coins, 9999)
	assert_eq(profile.magic, 6)

func test_sign_rewards_and_idempotency() -> void:
	var profile := fresh()
	var gold := [100, 0, 0, 0, 150, 0, 0]
	var gems := [0, 50, 0, 0, 0, 100, 0]
	for day in range(1, 8):
		var before_gold := profile.coins
		var before_gems := profile.diamonds
		var date := "2026-10-%02d" % day
		assert_true(profile.claim_sign(date).ok)
		assert_eq(profile.coins - before_gold, gold[day - 1])
		assert_eq(profile.diamonds - before_gems, gems[day - 1])
		assert_false(profile.claim_sign(date).ok)
	assert_eq(profile.magic, 6)
	assert_eq(profile.sign_data.draws.size(), 6)
	for index in 6:
		var award := profile.open_sign_draw(index)
		assert_true(award > 0)
		assert_eq(profile.open_sign_draw(index), 0)
	assert_eq(NewHDProfile.new(path).coins, profile.coins)
	assert_eq(NewHDProfile.new(path).diamonds, profile.diamonds)

func test_store_payment_and_pending_rewards() -> void:
	var profile := fresh()
	profile.coins = 500
	assert_true(profile.buy_box("coins", 5).ok)
	assert_eq(profile.coins, 0)
	assert_eq(profile.reward_draws.size(), 5)
	assert_true(profile.buy_box("coins", 5).pending)
	assert_eq(profile.coins, 0)
	for i in 5:
		profile.open_box(i)
		var gold := profile.coins
		var gems := profile.diamonds
		profile.open_box(i)
		assert_eq(profile.coins, gold)
		assert_eq(profile.diamonds, gems)

func test_source_manifest() -> void:
	var manifest: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/manifest.json"))
	assert_eq(manifest.source_commit, "cc2a21868d726d4ddaaace762c441c887028edd2")
	assert_eq(manifest.scenes.size(), 187)
	assert_eq(manifest.design, [1080.0, 1920.0])

func test_sign_gap_and_year_boundary() -> void:
	var profile := fresh()
	assert_true(profile.claim_sign("2026-12-31").ok)
	assert_eq(profile.sign_day("2027-01-01"), 2)
	assert_true(profile.claim_sign("2027-01-01").ok)
	assert_eq(profile.sign_day("2027-01-03"), 1)
	assert_true(profile.claim_sign("2027-01-03").ok)

func test_active_tasks_claim_once_and_reset_daily_only() -> void:
	var profile := fresh()
	profile.advance_task(8)
	assert_eq(profile.task_data.counts.get("8", 0), 0)
	profile.advance_task(0)
	assert_true(profile.claim_task(0).ok)
	assert_eq(profile.coins, 125)
	assert_false(profile.claim_task(0).ok)
	assert_eq(profile.coins, 125)
	assert_true(3 in profile.task_data.active)
	var restored := NewHDProfile.new(path)
	assert_true(0 in restored.task_data.claimed)
	restored.task_data.counts["100"] = 1
	restored.refresh_tasks("2099-01-01")
	assert_true(0 in restored.task_data.claimed)
	assert_false(restored.task_data.counts.has("100"))

func test_newhd_first_box_guarantee_and_persistence() -> void:
	var profile := fresh()
	profile.coins = 300
	profile.diamonds = 200
	assert_true(profile.buy_box("coins", 1).ok)
	assert_eq(profile.reward_draws[0].kind, "back")
	assert_eq(profile.reward_draws[0].index, 3)
	profile.open_box(0)
	assert_true(3 in profile.skin_owned.back)
	profile.buy_box("coins", 1)
	profile.open_box(0)
	profile.buy_box("diamonds", 1)
	assert_eq(profile.reward_draws[0].kind, "music")
	assert_eq(profile.reward_draws[0].index, 0)
	profile.open_box(0)
	assert_true(0 in NewHDProfile.new(path).skin_owned.music)
