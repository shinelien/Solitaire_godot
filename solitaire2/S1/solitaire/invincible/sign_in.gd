class_name InvincibleSignIn
extends Node
var game: InvincibleGame
var dialog: InvincibleScene
var clock := 0.0

func configure(owner_game: InvincibleGame, view: InvincibleScene) -> void:
	game = owner_game
	dialog = view
	var get_button := dialog.find_child("Button_get", true, false) as TextureButton
	get_button.set_meta("local_action", claim)
	var video := dialog.find_child("Button_getAD", true, false) as TextureButton
	video.set_meta("local_action", func():
		game.ads.request_rewarded("sign_in")
		game.message("广告尚未接入，暂时无法重复领取"))
	game.text(dialog, "Text_10", "七日签到")
	game.text(dialog, "Text_getx2", "再领一次")
	update_view()
	for item: Dictionary in game.profile.sign_data.draws:
		if not item.opened:
			call_deferred("draw_rewards")
			break

func _process(delta: float) -> void:
	clock += delta
	if clock >= 1:
		clock = 0
		update_time()

func update_time() -> void:
	var now := Time.get_time_dict_from_system()
	game.text(dialog, "Text_time", "%d小时%d分钟" % [23 - now.hour, 59 - now.minute])

func update_view() -> void:
	var day := game.profile.sign_day()
	var claimed: bool = day in game.profile.sign_data.claimed
	game.text(dialog, "Text_get", "已领取" if claimed else "领取")
	(dialog.find_child("Button_get", true, false) as TextureButton).disabled = claimed
	for i in range(1, 8):
		var item := dialog.find_child("FileNode_%d" % i, true, false) as InvincibleScene
		for j in range(1, 8):
			var panel := item.find_child("Panel_reward%d" % j, true, false) as CanvasItem
			if j != i:
				item.suppress_node(panel)
			else:
				panel.show()
		var reward := item.find_child("Panel_reward%d" % i, true, false)
		game.text(reward, "Text_28", "天")
		var marker := reward.find_child("Ui_7day1_0", true, false) as CanvasItem
		if marker != null:
			marker.modulate.a = 1 if i in game.profile.sign_data.claimed else 0
		if i in [1, 2, 4, 5, 6]:
			game.text(reward, "BitmapFontLabel_1", "+%d" % [14, 20, 28, 1, 50, 70, 1][i - 1])
			game.text(reward, "BitmapFontLabel_magic", "x%d" % [0, 1, 1, 1, 1, 2, 2][i - 1])
		elif i in [3, 7]:
			var type := 0 if i == 3 else 1
			var fish_holder := reward.find_child("Node_fish", true, false)
			var icon := reward.find_child("Node_icon", true, false) as CanvasItem
			var fish_icon := reward.find_child("Node_icon_fish", true, false) as CanvasItem
			var first: bool = type not in game.profile.sign_data.fish_claimed
			icon.visible = not first
			fish_icon.visible = first
			game.text(reward, "BitmapFontLabel_1", "+%d" % (28 if i == 3 else 1))
			game.text(reward, "BitmapFontLabel_magic", "x%d" % (1 if i == 3 else 2))
			game.text(reward, "BitmapFontLabel_fish_1", "+%d" % (28 if i == 3 else 1))
			game.text(reward, "BitmapFontLabel_fish_magic", "x%d" % (1 if i == 3 else 2))
			if fish_holder.get_child_count() == 0:
				var fish := InvincibleSpineActor.new()
				fish_holder.add_child(fish)
				fish.configure("fish%d" % type)
				fish.play("Run", true)
		game.text(reward, "Text_28_0_0", "签到大奖")
	update_time()

func claim() -> void:
	var result := game.profile.claim_sign()
	if not result.ok:
		game.message(str(result.reason))
		return
	var item := dialog.find_child("FileNode_%d" % int(result.day), true, false) as InvincibleScene
	item.play_clip("Day1")
	update_view()
	game.aquarium.configure(game.profile)
	game.play_effect("Get_coin")
	game.message("签到奖励已领取")
	if int(result.day) in [4, 7]:
		draw_rewards()

func draw_rewards() -> void:
	var view := game.open_dialog("2020Draw", "Start1")
	game.hide_node(view, "Panel_Again")
	var draws: Array = game.profile.sign_data.draws
	var first := maxi(0, draws.size() - 3)
	var completed := view.find_child("Button_get", true, false) as TextureButton
	completed.set_meta("local_action", func():
		if draws.all(func(item: Dictionary): return bool(item.opened)):
			game.close_dialog())
	var open_all := view.find_child("Button_open", true, false) as TextureButton
	game.text(view, "Text_open", "全部翻开")
	game.text(view, "Text_13", "完成")
	for id in [2, 3]:
		game.hide_node(view, "FileNode_%d" % id)
	for offset in 3:
		var id: int = [4, 1, 5][offset]
		var item := view.find_child("FileNode_%d" % id, true, false) as InvincibleScene
		var panel := item.get_node("card_bg_0_1/Panel_69") as Control
		for child in panel.get_children():
			if child is CanvasItem:
				child.hide()
		game.hide_node(item, "Node_AD")
		var area := item.get_node("card_bg_0_1/Panel_get") as Control
		var hit := TextureButton.new()
		area.add_child(hit)
		hit.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
		var index := first + offset
		hit.pressed.connect(func(): reveal_draw(view, item, index))
		if bool(draws[index].opened):
			reveal_draw(view, item, index, false)
	open_all.set_meta("local_action", func():
		for offset in 3:
			var id: int = [4, 1, 5][offset]
			reveal_draw(view, view.find_child("FileNode_%d" % id, true, false), first + offset))
	completed.disabled = not draws.all(func(item: Dictionary): return bool(item.opened))

func reveal_draw(view: InvincibleScene, item: InvincibleScene, index: int, award := true) -> void:
	if award and bool(game.profile.sign_data.draws[index].opened):
		return
	if award:
		game.profile.open_sign_draw(index)
		game.play_effect("Get_coin")
	item.play_clip("Start1" if int(game.profile.sign_data.draws[index].coins) >= 30 else "Start")
	var panel := item.get_node("card_bg_0_1/Panel_69") as Control
	(panel.get_node("Gold0") as CanvasItem).show()
	(panel.get_node("BitmapFontLabel_num") as CanvasItem).show()
	game.text(panel, "BitmapFontLabel_num", "+%d" % int(game.profile.sign_data.draws[index].coins))
	(view.find_child("Button_get", true, false) as TextureButton).show()
	(view.find_child("Button_get", true, false) as TextureButton).disabled = not game.profile.sign_data.draws.all(func(reward: Dictionary): return bool(reward.opened))
