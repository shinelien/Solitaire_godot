class_name InvincibleProfile
extends RefCounted
signal changed
var path := "user://invincible_profile.cfg"
var settings := {"draw": 1, "left": false, "face": 0, "back": 0, "music": true, "music_track": -1, "sound": true, "animations": true, "hints": true}
var coins := 0
var diamonds := 0
var magic := 3
var level := 0
var exp := 1
var current_tank := 0
var tanks: Array = [[{"type": 0, "hp": 60, "death_at": 0}], [], [], []]
var decorations: Array = [[], [], [], []]
var stars: Dictionary = {}
var daily_completed: Dictionary = {}
var statistics: Dictionary = {}
var skin_owned := {"face": [0], "back": [0], "music": [0]}
var face_cards: Dictionary = {}
var face_choices: Dictionary = {}
var sign_data := {"day": 1, "last_date": "", "claimed": [], "fish_claimed": [], "draws": []}
var reward_receipts: Dictionary = {}
var last_time := 0
var level_data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/invincible/data/player.json"))
var fish_data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/invincible/data/fish.json"))

func _init(test_path := "") -> void:
	if not test_path.is_empty():
		path = test_path
	var file := ConfigFile.new()
	if file.load(path) == OK:
		for key in settings:
			settings[key] = file.get_value("settings", key, settings[key])
		for key in ["coins", "diamonds", "magic", "level", "exp", "current_tank", "tanks", "decorations", "stars", "daily_completed", "statistics", "skin_owned", "face_cards", "face_choices", "sign_data", "reward_receipts", "last_time"]:
			set(key, file.get_value("player", key, get(key)))
	if not skin_owned.has("music"):
		skin_owned.music = [0]
	update_hunger(int(Time.get_unix_time_from_system()))

func save() -> void:
	var file := ConfigFile.new()
	for key in settings:
		file.set_value("settings", key, settings[key])
	for key in ["coins", "diamonds", "magic", "level", "exp", "current_tank", "tanks", "decorations", "stars", "daily_completed", "statistics", "skin_owned", "face_cards", "face_choices", "sign_data", "reward_receipts", "last_time"]:
		file.set_value("player", key, get(key))
	file.save(path)
	changed.emit()

func update_hunger(now: int) -> void:
	if last_time == 0:
		last_time = now
	var minutes := maxi(0, (now - last_time) / 60)
	if minutes == 0:
		return
	for fish_tank: Array in tanks:
		for fish: Dictionary in fish_tank:
			fish.hp = maxi(0, int(fish.hp) - minutes)
			if fish.hp == 0 and int(fish.death_at) == 0:
				fish.death_at = now + 86400
	last_time += minutes * 60
	save()

func feed() -> void:
	for fish: Dictionary in tanks[current_tank]:
		fish.hp = mini(60, int(fish.hp) + 30)
		fish.death_at = 0
	save()

func owns_face(style: int, card_id: int) -> bool:
	return style in skin_owned.face or card_id in face_cards.get(str(style), [])

func face_count(style: int) -> int:
	return 52 if style in skin_owned.face else face_cards.get(str(style), []).size()

func card_style(card_id: int) -> int:
	var style := int(face_choices.get(str(card_id), settings.face))
	return style if owns_face(style, card_id) else 0

func buy_skin(kind: String, index: int) -> Dictionary:
	var shop: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/invincible/data/shop2021.json"))
	var item: Dictionary = shop["CardBg" if kind == "back" else "Music"][index]
	if index in skin_owned[kind]:
		return {"ok": true}
	if level < int(item.unlock):
		return {"ok": false, "reason": "%d 级解锁" % int(item.unlock)}
	if coins < int(item.price):
		return {"ok": false, "reason": "金币不足"}
	coins -= int(item.price)
	skin_owned[kind].append(index)
	save()
	return {"ok": true}

func sign_day(today := "") -> int:
	if today.is_empty():
		today = Time.get_date_string_from_system()
	var day := int(sign_data.day)
	if not str(sign_data.last_date).is_empty() and str(sign_data.last_date) < today and day in sign_data.claimed:
		day = day % 7 + 1
		if day == 1:
			sign_data.claimed.clear()
		sign_data.day = day
		sign_data.last_date = today
		save()
	return day

func claim_sign(today := "") -> Dictionary:
	if today.is_empty():
		today = Time.get_date_string_from_system()
	var day := sign_day(today)
	if day in sign_data.claimed:
		return {"ok": false, "reason": "今天的奖励已经领取"}
	var fish_type := 0 if day == 3 else 1
	if day in [3, 7] and fish_type not in sign_data.fish_claimed and tanks[current_tank].size() >= 25:
		return {"ok": false, "reason": "鱼缸已满，请先腾出空间"}
	var gold: int = [14, 20, 28, 0, 50, 70, 0][day - 1]
	var wands: int = [0, 1, 1, 1, 1, 2, 2][day - 1]
	coins += gold
	magic += wands
	if day in [3, 7] and fish_type not in sign_data.fish_claimed:
		tanks[current_tank].append({"type": fish_type, "hp": 60, "death_at": 0})
		sign_data.fish_claimed.append(fish_type)
	if day in [4, 7]:
		# The original SevenGold/SevenDiamond draw shuffles one large and
		# two small coin rewards (diamond rewards were converted to coins).
		var values := [30 if day == 4 else 100, randi_range(1, 5), randi_range(5, 9 if day == 4 else 10)]
		values.shuffle()
		for value: int in values:
			sign_data.draws.append({"coins": value, "opened": false})
	sign_data.claimed.append(day)
	sign_data.last_date = today
	save()
	return {"ok": true, "coins": gold, "magic": wands, "day": day}

func open_sign_draw(index: int) -> int:
	var item: Dictionary = sign_data.draws[index]
	if item.opened:
		return 0
	item.opened = true
	coins += int(item.coins)
	save()
	return int(item.coins)

func buy_fish(type: int) -> Dictionary:
	var item: Dictionary = fish_data.totalCNT[type]
	if level < int(item.unlock):
		return {"ok": false, "reason": "%d 级解锁" % int(item.unlock)}
	if tanks[current_tank].size() >= 25:
		return {"ok": false, "reason": "鱼缸已满"}
	if coins < int(item.price):
		return {"ok": false, "reason": "金币不足"}
	coins -= int(item.price)
	tanks[current_tank].append({"type": type, "hp": 60, "death_at": 0})
	save()
	return {"ok": true}

func add_exp(amount: int) -> void:
	exp += amount
	while level < level_data.lv.size() - 1 and exp >= int(level_data.lv[level].exp):
		exp -= int(level_data.lv[level].exp)
		level += 1
	if level == level_data.lv.size() - 1:
		exp = mini(exp, int(level_data.lv[level].exp))
	save()

func tank_unlocked(index: int) -> bool:
	return level >= [0, 18, 39, 60][index]

func award_reward(placement: String, receipt: String, amount := 25) -> bool:
	if receipt.is_empty() or reward_receipts.has(receipt):
		return false
	reward_receipts[receipt] = placement
	coins += amount
	save()
	return true
