class_name NewHDRoulette
extends Node
const AMOUNTS := [150, 2, 75, 500, 125, 75, 1, 300]
const KINDS := ["coins", "magic", "diamonds", "coins", "diamonds", "coins", "magic", "diamonds"]
const LIMITS := [30, 33, 49, 51, 71, 83, 98, 100]
var game: NewHDGame
var dialog: NewHDScene
var wheel: Control
var spinning := false
var elapsed := 0.0
var initial := 0.0
var delta_rotation := 0.0
var pending: Dictionary = {}

func configure(owner_game: NewHDGame, view: NewHDScene) -> void:
	game = owner_game
	dialog = view
	wheel = dialog.find_child("Node_zhuan", true, false)
	for name in ["Panel_Get", "panel_SDKGift", "Text_time"]:
		game.hide_node(dialog, name)
	for i in 8:
		game.text(dialog, "Text_reward%d" % i, "+%d" % AMOUNTS[i])
	dialog.find_child("Button_get", true, false).set_meta("local_action", spin)
	dialog.find_child("Button_adget", true, false).set_meta("local_action", func():
		game.ads.request_rewarded("roulette")
		game.message("广告尚未接入，暂时无法额外抽奖"))
	dialog.find_child("Button_getreward", true, false).set_meta("local_action", game.close_dialog)
	pending = game.profile.statistics.get("roulette_pending", {})
	if not pending.is_empty():
		settle()

func _process(delta: float) -> void:
	if spinning:
		elapsed += delta
		var ratio := minf(elapsed / 10, 1)
		var eased := 1.0 if ratio == 1 else 1.0008 - pow(2, -10 * ratio)
		wheel.rotation_degrees = initial + eased * delta_rotation
		if elapsed >= 10.5:
			spinning = false
			settle()
	else:
		wheel.rotation_degrees -= 72 * delta

func spin() -> void:
	if spinning or not pending.is_empty():
		return
	var now := int(Time.get_unix_time_from_system())
	var next := int(game.profile.statistics.get("roulette_free_at", 0))
	if next > now:
		game.message("免费抽奖还需 %d 分钟" % ceili((next - now) / 60.0))
		return
	var number := randi_range(1, 100)
	var index := 0
	while number > LIMITS[index]:
		index += 1
	pending = {"kind": KINDS[index], "amount": AMOUNTS[index]}
	game.profile.statistics.roulette_pending = pending
	game.profile.statistics.roulette_free_at = now + 1204
	game.profile.save()
	initial = wheel.rotation_degrees
	delta_rotation = -(7200 + index * 45 + randf_range(10, 35) + fmod(initial, 360))
	elapsed = 0
	spinning = true
	(dialog.find_child("Node_bottom", true, false) as CanvasItem).hide()
	(dialog.find_child("btn_close", true, false) as CanvasItem).hide()

func settle() -> void:
	var kind := str(pending.kind)
	var amount := int(pending.amount)
	game.profile.set(kind, int(game.profile.get(kind)) + amount)
	game.profile.statistics.erase("roulette_pending")
	game.profile.save()
	var gift := dialog.find_child("panel_SDKGift", true, false) as CanvasItem
	gift.show()
	(dialog.find_child("btn_close", true, false) as CanvasItem).show()
	game.text(gift, "Text_addNum", "+%d" % amount)
	var image := gift.find_child("Sprite_reward", true, false) as TextureRect
	image.texture = NewHDAtlas.texture("" + ("Money/Gold_0.png" if kind == "coins" else "Money/Baoshi_10.png" if kind == "diamonds" else "game_magic0.png"))
	game.text(gift, "Text_acquire", "获得奖励")
	game.text(gift, "Text_getReward", "领取")
