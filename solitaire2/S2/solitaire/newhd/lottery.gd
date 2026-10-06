class_name NewHDLottery
extends RefCounted
## The original BoxDataManager tables select the balance tier and two weighted levels.
var data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/boxData.json"))
var profile: NewHDProfile

func _init(owner_profile: NewHDProfile) -> void:
	profile = owner_profile

func weighted(rows: Array) -> Dictionary:
	var value := randi_range(0, 99)
	var total := 0
	for row: Dictionary in rows:
		total += int(row.rate)
		if value < total:
			return row
	return rows[0]

func generate(currency: String, count: int, balance: int) -> Array:
	var tiers: Dictionary = data["TGold" if currency == "coins" else "TGem"]["one" if count == 1 else "five"]
	for tier: Dictionary in tiers.values():
		var limits: Array = tier.money_range
		if balance >= int(limits[0]) and (int(limits[1]) < 0 or balance < int(limits[1])):
			var result: Array = []
			if count == 1:
				result.append(prize(weighted(tier.group)))
			else:
				for rows: Array in tier.group.values():
					result.append(prize(weighted(rows)))
			result.shuffle()
			return result
	return []

func prize(row: Dictionary) -> Dictionary:
	var type: String = row.type2
	if type != "Item":
		return {"kind": "coins" if type in ["Gold", "BigGold"] else "diamonds", "amount": randi_range(int(row.values[0]), int(row.values[1])), "opened": false}
	var item := weighted(row.items_rate)
	type = str(item.type2)
	if type == "Magic":
		return {"kind": "magic", "amount": 1, "opened": false}
	var kind: String = {"PBack": "back", "PFore": "face", "BG": "background", "Music": "music"}[type]
	var count := 35 if kind == "back" else 6 if kind == "face" else 26 if kind == "background" else 20
	var indices: Array[int] = []
	for i in count:
		indices.append(i)
	indices.shuffle()
	var repeat := not bool(profile.statistics.get("lottery_repeat", false)) and randi_range(0, 100) < int(item.sec_rate)
	profile.statistics.lottery_repeat = repeat
	var selected := 0
	for i in indices:
		var owned: bool = i in profile.skin_owned[kind]
		if owned == repeat:
			selected = i
			break
	var card_id := randi_range(0, 51)
	if kind == "face" and not repeat:
		var candidates: Array[int] = []
		for id in 52:
			if not profile.owns_face(selected, id):
				candidates.append(id)
		if not candidates.is_empty():
			card_id = candidates.pick_random()
	return {"kind": kind, "index": selected, "card_id": card_id, "amount": 1, "opened": false}
