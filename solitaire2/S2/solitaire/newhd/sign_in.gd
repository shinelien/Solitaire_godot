class_name NewHDSignIn
extends Node
var game: NewHDGame
var dialog: NewHDScene
var clock := 0.0

func configure(owner_game: NewHDGame, view: NewHDScene) -> void:
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
	(dialog.find_child("Button_get", true, false) as TextureButton).visible = not claimed
	(dialog.find_child("Button_getAD", true, false) as TextureButton).visible = claimed
	for i in range(1, 8):
		var item := dialog.find_child("FileNode_%d" % i, true, false) as NewHDScene
		for j in range(1, 8):
			var panel := item.find_child("Panel_reward%d" % j, true, false) as CanvasItem
			if j != i:
				item.suppress_node(panel)
			else:
				panel.show()
		var reward := item.find_child("Panel_reward%d" % i, true, false)
		game.text(reward, "Text_28", "天")
		var marker := reward.find_child("Image_reward1", true, false) as CanvasItem
		if marker != null:
			marker.modulate.a = 1 if i in game.profile.sign_data.claimed else 0
		game.text(reward, "BitmapFontLabel_1", ("x" if i in [3, 4, 7] else "+") + str([100, 50, 1, 1, 150, 100, 1][i - 1]))
		game.text(reward, "Text_28_0_0", "签到大奖")
	var box := dialog.find_child("FileNode_7", true, false).find_child("FileNode_box", true, false) as NewHDScene
	if box != null and box.get_node("AnimationPlayer").current_animation != "Loop":
		box.play_clip("Loop", true)
	update_time()

func claim() -> void:
	var result := game.profile.claim_sign()
	if not result.ok:
		game.message(str(result.reason))
		return
	var item := dialog.find_child("FileNode_%d" % int(result.day), true, false) as NewHDScene
	item.play_clip("Day1")
	update_view()
	game.play_effect("Get_coin")
	game.message("签到奖励已领取")
	if int(result.day) in [4, 7]:
		draw_rewards()

func draw_rewards() -> void:
	var draws: Array = game.profile.sign_data.draws
	var first := -1
	for index in draws.size():
		if not bool(draws[index].opened):
			first = index / 3 * 3
			break
	if first < 0:
		return
	var indices := [first, first + 1, first + 2]
	var view := game.open_dialog("2020Draw", "Start1")
	view.set_meta("draw_indices", indices)
	view.set_meta("ready_at", Time.get_ticks_msec() + 2400)
	view.set_meta("revealing", 0)
	game.hide_node(view, "Panel_Again")
	var completed := view.find_child("Button_get", true, false) as TextureButton
	completed.set_meta("local_action", func():
		if draws_finished(view):
			game.close_dialog()
			if draws.any(func(item: Dictionary): return not bool(item.opened)):
				call_deferred("draw_rewards"))
	var open_all := view.find_child("Button_open", true, false) as TextureButton
	game.text(view, "Text_open", "全部翻开")
	game.text(view, "Text_13", "完成")
	for id in [2, 3]:
		game.hide_node(view, "FileNode_%d" % id)
	for offset in 3:
		var id: int = [4, 1, 5][offset]
		var item := view.find_child("FileNode_%d" % id, true, false) as NewHDScene
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
	update_draw_buttons(view)

func draws_finished(view: NewHDScene) -> bool:
	var indices: Array = view.get_meta("draw_indices")
	return int(view.get_meta("revealing")) == 0 and indices.all(func(index: int): return bool(game.profile.sign_data.draws[index].opened))

func update_draw_buttons(view: NewHDScene) -> void:
	var completed := view.find_child("Button_get", true, false) as TextureButton
	completed.disabled = not draws_finished(view)
	var indices: Array = view.get_meta("draw_indices")
	if indices.all(func(index: int): return bool(game.profile.sign_data.draws[index].opened)):
		game.hide_node(view, "Button_open")
		completed.show()

func reveal_draw(view: NewHDScene, item: NewHDScene, index: int, award := true) -> void:
	if award and Time.get_ticks_msec() < int(view.get_meta("ready_at", 0)):
		return
	if award and bool(game.profile.sign_data.draws[index].opened):
		return
	if award:
		game.profile.open_sign_draw(index)
		game.play_effect("Get_coin")
	var prize: Dictionary = game.profile.sign_data.draws[index]
	var gems := int(prize.get("diamonds", 0)) > 0
	var amount := int(prize.get("diamonds", 0)) if gems else int(prize.coins)
	var large := amount >= 100
	var duration := item.play_clip("Start1" if large else "Start")
	var panel := item.get_node("card_bg_0_1/Panel_69") as Control
	(panel.get_node(("Baoshi1" if large else "Baoshi0") if gems else ("Gold1" if large else "Gold0")) as CanvasItem).show()
	(panel.get_node("BitmapFontLabel_num") as CanvasItem).show()
	game.text(panel, "BitmapFontLabel_num", "+%d" % amount)
	var player := item.get_node("AnimationPlayer") as AnimationPlayer
	if award and duration > 0:
		view.set_meta("revealing", int(view.get_meta("revealing")) + 1)
		player.animation_finished.connect(func(_clip):
			if is_instance_valid(view):
				view.set_meta("revealing", int(view.get_meta("revealing")) - 1)
				update_draw_buttons(view), CONNECT_ONE_SHOT)
	else:
		player.seek(duration, true)
		player.stop(true)
	update_draw_buttons(view)
