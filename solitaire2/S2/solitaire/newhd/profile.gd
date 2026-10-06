class_name NewHDProfile
extends RefCounted
signal changed
var path := "user://newhd_profile.cfg"
var settings := {"draw": 1, "left": false, "face": 0, "back": 0, "music": true, "music_track": -1, "sound": true, "animations": true, "hints": true, "background": 0, "random": false}
var coins := 100
var diamonds := 0
var magic := 5
var level := 1
var exp := 1
var stars: Dictionary = {}
var daily_completed: Dictionary = {}
var statistics: Dictionary = {}
var skin_owned := {"face": [0], "back": [0], "music": [], "background": [0, 18]}
var face_cards: Dictionary = {}
var face_choices: Dictionary = {}
var sign_data := {"day": 1, "last_date": "", "claimed": [], "draws": []}
var task_data := {"date": "", "counts": {}, "claimed": [], "active": [0, 1, 2], "rewards": 0}
var reward_draws: Array = []
var reward_receipts: Dictionary = {}
var last_time := 0
var level_data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/player.json"))

func _init(test_path := "") -> void:
	if not test_path.is_empty():
		path = test_path
	var file := ConfigFile.new()
	if file.load(path) == OK:
		for key in settings:
			settings[key] = file.get_value("settings", key, settings[key])
		for key in ["coins", "diamonds", "magic", "level", "exp", "stars", "daily_completed", "statistics", "skin_owned", "face_cards", "face_choices", "sign_data", "reward_draws", "reward_receipts", "last_time", "task_data"]:
			set(key, file.get_value("player", key, get(key)))
	if not skin_owned.has("music"):
		skin_owned.music = [0]


func save() -> void:
	var file := ConfigFile.new()
	for key in settings:
		file.set_value("settings", key, settings[key])
	for key in ["coins", "diamonds", "magic", "level", "exp", "stars", "daily_completed", "statistics", "skin_owned", "face_cards", "face_choices", "sign_data", "reward_draws", "reward_receipts", "last_time", "task_data"]:
		file.set_value("player", key, get(key))
	file.save(path)
	changed.emit()

func owns_face(style: int, card_id: int) -> bool:
	return style in skin_owned.face or card_id in face_cards.get(str(style), [])

func face_count(style: int) -> int:
	return 52 if style in skin_owned.face else face_cards.get(str(style), []).size()

func card_style(card_id: int) -> int:
	var style := int(face_choices.get(str(card_id), settings.face))
	return style if owns_face(style, card_id) else 0

func buy_skin(_kind: String, _index: int) -> Dictionary:
	return {"ok": false, "reason": "此道具从奖励宝箱获得"}

func buy_magic() -> Dictionary:
	if magic >= 50:
		return {"ok": false, "reason": "魔法棒已达到 50 根上限"}
	if diamonds < 200:
		return {"ok": false, "reason": "钻石不足"}
	diamonds -= 200
	magic += 1
	save()
	return {"ok": true}

func unlock_level(kind: String, index: int) -> int:
	var type := 1 if kind == "background" else 3 if kind == "back" else 4 if kind == "music" else 2
	var value := 0
	for item: Dictionary in level_data.unlocklv:
		if int(item.itemType) == type and int(item.itemId) == index:
			value = 0 if item.has("default") else int(item.get("unlocklv", 0))
	return value

func sign_day(today := "") -> int:
	if today.is_empty():
		today = Time.get_date_string_from_system()
	var day := int(sign_data.day)
	var previous := str(sign_data.last_date)
	if previous.is_empty():
		sign_data.last_date = today
	elif previous < today:
		var gap := (Time.get_unix_time_from_datetime_string(today + "T00:00:00") - Time.get_unix_time_from_datetime_string(previous + "T00:00:00")) / 86400
		day = day % 7 + 1 if gap == 1 else 1
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
	var gold: int = 100 if day == 1 else 150 if day == 5 else 0
	var gems: int = 50 if day == 2 else 100 if day == 6 else 0
	var wands: int = 1 if day == 3 else 0
	coins += gold
	diamonds += gems
	magic = mini(50, magic + wands)
	if day in [4, 7]:
		var values := [{"coins": 100 if day == 4 else 150, "diamonds": 0, "opened": false}, {"coins": randi_range(2, 20), "diamonds": 0, "opened": false}, {"coins": 0, "diamonds": randi_range(2, 20) if day == 4 else randi_range(100, 120), "opened": false}]
		values.shuffle()
		sign_data.draws.append_array(values)
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
	diamonds += int(item.get("diamonds", 0))
	save()
	return int(item.coins) + int(item.get("diamonds", 0))

func add_exp(amount: int) -> void:
	exp += amount
	while level < level_data.lv.size() - 1 and exp >= int(level_data.lv[level].exp):
		exp -= int(level_data.lv[level].exp)
		level += 1
	if level == level_data.lv.size() - 1:
		exp = mini(exp, int(level_data.lv[level].exp))
	save()

func award_reward(placement: String, receipt: String, amount := 25) -> bool:
	if receipt.is_empty() or reward_receipts.has(receipt):
		return false
	reward_receipts[receipt] = placement
	coins += amount
	save()
	return true

func buy_box(currency: String, count: int) -> Dictionary:
	if currency not in ["coins", "diamonds"] or count not in [1, 5]:
		return {"ok": false, "reason": "无效的购买"}
	if reward_draws.any(func(item: Dictionary): return not bool(item.opened)):
		return {"ok": true, "pending": true}
	var balance: int = get(currency)
	if balance < count * 100:
		return {"ok": false, "reason": "金币不足" if currency == "coins" else "钻石不足"}
	var lottery := NewHDLottery.new(self)
	set(currency, balance - count * 100)
	reward_draws = lottery.generate(currency, count, balance - count * 100)
	var purchases := int(statistics.get("box_purchases", 0)) + 1
	statistics.box_purchases = purchases
	var forced := "back" if purchases == 1 else "music" if currency == "diamonds" and purchases >= 3 and not bool(statistics.get("music_guarantee", false)) else ""
	if not forced.is_empty():
		var position := randi_range(0, reward_draws.size() - 1)
		reward_draws[position] = {"kind": forced, "index": 3 if forced == "back" else 0, "amount": 1, "opened": false}
		if forced == "music":
			statistics.music_guarantee = true
	advance_task(3 if currency == "coins" else 10)
	advance_task(104 if currency == "coins" else 105)
	save()
	return {"ok": true, "pending": false}

func open_box(index: int) -> Dictionary:
	if index < 0 or index >= reward_draws.size():
		return {}
	var prize: Dictionary = reward_draws[index]
	if bool(prize.opened):
		return prize
	prize.opened = true
	var kind: String = prize.kind
	if kind in ["coins", "diamonds", "magic"]:
		set(kind, int(get(kind)) + int(prize.amount))
	elif kind == "face":
		var style := str(prize.index)
		if not face_cards.has(style):
			face_cards[style] = []
		if int(prize.card_id) not in face_cards[style]:
			face_cards[style].append(int(prize.card_id))
		if face_cards[style].size() == 52 and int(prize.index) not in skin_owned.face:
			skin_owned.face.append(int(prize.index))
	elif int(prize.index) not in skin_owned[kind]:
		skin_owned[kind].append(int(prize.index))
	save()
	return prize

# Source: Classes/manager/TaskManager.cpp. Only the three active tasks advance.
const NEW_TASK_MAX := [1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
const DAY_TASK_MAX := [1, 3, 1, 3, 1, 1, 1, 1, 5, 1, 3]

func refresh_tasks(today := "") -> void:
	if today.is_empty():
		today = Time.get_date_string_from_system()
	if task_data.date != today:
		task_data.date = today
		for id in range(100, 111):
			task_data.counts.erase(str(id))
		task_data.claimed = task_data.claimed.filter(func(id): return int(id) < 100)
		task_data.active = []
		assign_tasks()
		save()

func assign_tasks() -> void:
	var candidates: Array = range(15) + range(100, 111)
	task_data.active = task_data.active.filter(func(id): return id not in task_data.claimed)
	for id in candidates:
		if task_data.active.size() >= 3:
			break
		if id in task_data.claimed or id in task_data.active:
			continue
		if id in range(11, 15) and task_data.active.any(func(other): return int(other) in range(11, 15)):
			continue
		task_data.active.append(id)

func task_max(id: int) -> int:
	return int(DAY_TASK_MAX[id - 100] if id >= 100 else NEW_TASK_MAX[id])

func advance_task(id: int) -> void:
	refresh_tasks()
	if id in task_data.active or id in range(11, 15):
		task_data.counts[str(id)] = mini(task_max(id), int(task_data.counts.get(str(id), 0)) + 1)
		save()

func claim_task(id: int) -> Dictionary:
	refresh_tasks()
	if id not in task_data.active or id in task_data.claimed or int(task_data.counts.get(str(id), 0)) < task_max(id):
		return {"ok": false}
	var stage := int(task_data.rewards) % 3
	var gold := 25 if stage == 0 else 100 if stage == 2 else 0
	var gems := 0 if stage == 0 else 50
	coins += gold
	diamonds += gems
	task_data.rewards += 1
	task_data.claimed.append(id)
	assign_tasks()
	save()
	return {"ok": true, "coins": gold, "diamonds": gems}
