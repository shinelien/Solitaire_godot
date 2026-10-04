class_name SolitaireProfile
extends RefCounted

const SAVE_PATH := "user://master_profile.cfg"
var storage_path := SAVE_PATH
var settings := {"draw": 1, "left": false, "sound": true, "background": 0, "face": 0, "back": 0}
var coins := 1000
var free_coin_time := 0
var unlocked := {"background": [0], "face": [0], "back": [0]}
var statistics := {"1": [], "3": []}

func _init(path: String = SAVE_PATH) -> void:
	storage_path = path
	for key in statistics:
		statistics[key].resize(12)
		statistics[key].fill(0)
	var config := ConfigFile.new()
	if config.load(storage_path) == OK:
		for key in settings:
			settings[key] = config.get_value("settings", key, settings[key])
		coins = int(config.get_value("player", "coins", coins))
		free_coin_time = int(config.get_value("player", "free_coin_time", 0))
		for key in unlocked:
			unlocked[key] = config.get_value("unlocked", key, unlocked[key])
		for key in statistics:
			var saved: Array = config.get_value("statistics", key, statistics[key])
			if saved.size() == 12:
				statistics[key] = saved

func save() -> void:
	var config := ConfigFile.new()
	for key in settings:
		config.set_value("settings", key, settings[key])
	config.set_value("player", "coins", coins)
	config.set_value("player", "free_coin_time", free_coin_time)
	for key in unlocked:
		config.set_value("unlocked", key, unlocked[key])
	for key in statistics:
		config.set_value("statistics", key, statistics[key])
	var error := config.save(storage_path)
	if error != OK:
		push_error("Could not save Solitaire profile: %s" % error)

func settle(draw: int, won: bool, score: int, seconds: int, moves: int, undo_used: bool) -> int:
	var s: Array = statistics[str(draw)]
	if won:
		s[0] += 1
		s[3] = seconds if s[3] == 0 else mini(s[3], seconds)
		s[4] = maxi(s[4], seconds)
		s[5] = moves if s[5] == 0 else mini(s[5], moves)
		s[6] = maxi(s[6], moves)
		if not undo_used:
			s[7] += 1
		s[8] = maxi(s[8], score)
		s[9] += 1
		s[10] = maxi(s[10], s[9])
	else:
		s[1] += 1
		s[9] = 0
	s[2] = float(s[0]) * 100.0 / maxi(1, s[0] + s[1])
	s[11] += seconds
	# Avoid the original zero-time division while keeping its reward formula.
	var reward := int(200000.0 / maxf(1.0, seconds)) if won else 0
	coins += reward
	save()
	return reward

func free_coins_remaining() -> int:
	return maxi(0, free_coin_time + 3599 - int(Time.get_unix_time_from_system()))

func claim_free_coins() -> bool:
	if free_coins_remaining() > 0:
		return false
	free_coin_time = int(Time.get_unix_time_from_system())
	coins += 500
	save()
	return true
