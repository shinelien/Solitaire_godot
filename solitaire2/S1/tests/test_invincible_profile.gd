@tool
extends McpTestSuite

func suite_name() -> String:
	return "invincible_profile"

func fresh(name: String) -> InvincibleProfile:
	var path := "user://invincible_regression_%s.cfg" % name
	DirAccess.remove_absolute(ProjectSettings.globalize_path(path))
	return InvincibleProfile.new(path)

func test_skin_purchase_enforces_unlock_coins_and_persistence() -> void:
	var player := fresh("skins")
	player.coins = 200
	assert_false(player.buy_skin("back", 1).ok, "locked skin cannot consume coins")
	assert_eq(player.coins, 200)
	player.level = 5
	assert_true(player.buy_skin("back", 1).ok)
	assert_eq(player.coins, 50)
	assert_true(player.buy_skin("back", 1).ok)
	assert_eq(player.coins, 50, "already owned skin cannot charge twice")
	assert_false(player.buy_skin("back", 2).ok)
	player.settings.back = 1
	player.save()
	var restored := InvincibleProfile.new(player.path)
	assert_true(1 in restored.skin_owned.back)
	assert_eq(restored.settings.back, 1)
	assert_eq(restored.coins, 50)

func test_sign_in_seven_days_and_claimed_draws_survive_restart() -> void:
	var player := fresh("sign")
	for day in range(1, 8):
		var date := "2026-10-%02d" % day
		assert_eq(player.sign_day(date), day)
		assert_true(player.claim_sign(date).ok)
		var before := player.coins
		assert_false(player.claim_sign(date).ok)
		assert_eq(player.coins, before, "same-day claim is idempotent")
	assert_eq(player.magic, 11, "source magic rewards sum to 8")
	assert_eq(player.coins, 182, "source regular coin rewards")
	assert_eq(player.tanks[0].size(), 3, "day 3 and day 7 award fish once")
	assert_eq(player.sign_data.draws.size(), 6)
	var total := 182
	for i in player.sign_data.draws.size():
		total += int(player.sign_data.draws[i].coins)
		assert_true(player.open_sign_draw(i) > 0)
		assert_eq(player.open_sign_draw(i), 0, "flipped reward is awarded once")
	assert_eq(player.coins, total)
	var restored := InvincibleProfile.new(player.path)
	assert_eq(restored.coins, total)
	assert_eq(restored.open_sign_draw(0), 0)
	assert_eq(restored.sign_day("2026-10-08"), 1, "seven-day cycle resets on next eligible day")
	assert_true(restored.claim_sign("2026-10-08").ok)
	assert_eq(restored.sign_data.fish_claimed, [0, 1])

func test_full_tank_does_not_consume_fish_sign_reward() -> void:
	var player := fresh("full_tank")
	player.claim_sign("2026-10-01")
	player.claim_sign("2026-10-02")
	while player.tanks[0].size() < 25:
		player.tanks[0].append({"type": 0, "hp": 60, "death_at": 0})
	var before := player.coins
	assert_false(player.claim_sign("2026-10-03").ok)
	assert_eq(player.coins, before)
	assert_false(3 in player.sign_data.claimed)
	player.tanks[0].pop_back()
	assert_true(player.claim_sign("2026-10-03").ok)
	assert_eq(player.tanks[0].size(), 25)

func test_unowned_face_is_not_applied_to_individual_cards() -> void:
	var player := fresh("faces")
	player.settings.face = 2
	assert_eq(player.card_style(10), 0)
	player.face_cards["2"] = [10]
	assert_eq(player.card_style(10), 2)
	assert_eq(player.card_style(11), 0)
	assert_eq(player.face_count(2), 1)
	player.face_choices["10"] = 0
	assert_eq(player.card_style(10), 0)
