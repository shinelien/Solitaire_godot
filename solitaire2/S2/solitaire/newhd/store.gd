class_name NewHDStore
extends Node
var game: NewHDGame
var dialog: NewHDScene
var count := {"coins": 1, "diamonds": 1}

func configure(owner_game: NewHDGame, view: NewHDScene) -> void:
	game = owner_game
	dialog = view
	for pair in [["Button_gold", "coins"], ["Button_diamond", "diamonds"]]:
		dialog.find_child(pair[0], true, false).set_meta("local_action", purchase.bind(pair[1]))
	for pair in [["Button_Gold_btn", "coins"], ["Button_Diamond_btn", "diamonds"]]:
		dialog.find_child(pair[0], true, false).set_meta("local_action", toggle.bind(pair[1]))
	for pair in [["FileNode_Gold_btn", "Loop_L0"], ["FileNode_Diamond_btn", "Loop_L0"], ["FileNode_bag_A", "KingLoop"]]:
		var child := dialog.find_child(pair[0], true, false) as NewHDScene
		if child != null:
			child.play_clip(pair[1], true)
	for name in ["Button_GoldMiaoShu", "Button_DiamondMiaoShu"]:
		var button := dialog.find_child(name, true, false) as TextureButton
		button.set_meta("local_action", func(): game.message("金币宝箱：牌面、牌背、魔法棒；钻石宝箱另含场景和音乐。"))
	var close := TextureButton.new()
	close.name = "Button_close"
	close.texture_normal = NewHDAtlas.texture("ui_btn_close0.png")
	close.texture_pressed = NewHDAtlas.texture("ui_btn_close1.png")
	close.position = Vector2(970, 165)
	close.size = Vector2(90, 90)
	close.ignore_texture_size = true
	dialog.add_child(close)
	game.bind_buttons(dialog)
	refresh()
	if game.profile.reward_draws.any(func(item: Dictionary): return not bool(item.opened)):
		call_deferred("draw_rewards")

func toggle(currency: String) -> void:
	count[currency] = 5 if count[currency] == 1 else 1
	var child := dialog.find_child("FileNode_Gold_btn" if currency == "coins" else "FileNode_Diamond_btn", true, false) as NewHDScene
	child.play_clip("Loop_L0" if count[currency] == 1 else "Loop_R0", true)
	refresh()

func refresh() -> void:
	game.text(dialog, "BitmapFontLabel_Gold_store", str(100 * int(count.coins)))
	game.text(dialog, "BitmapFontLabel_Diamond_store", str(100 * int(count.diamonds)))

func purchase(currency: String) -> void:
	var result := game.profile.buy_box(currency, int(count[currency]))
	if not result.ok:
		game.message(str(result.reason))
		return
	draw_rewards()

func draw_rewards() -> void:
	var view := game.open_dialog("2020Draw", "Start0")
	var prizes: Array = game.profile.reward_draws
	var ids: Array = [1] if prizes.size() == 1 else [1, 2, 3, 4, 5]
	view.set_meta("revealing", 0)
	view.set_meta("ready_at", Time.get_ticks_msec() + 2400)
	game.hide_node(view, "Panel_Again")
	game.hide_node(view, "Button_close")
	var complete := view.find_child("Button_get", true, false) as TextureButton
	complete.set_meta("local_action", func():
		if prizes.all(func(item: Dictionary): return bool(item.opened)):
			game.close_dialog()
			refresh())
	game.text(view, "Text_13", "完成")
	game.text(view, "Text_open", "全部翻开")
	for id in 5:
		if id + 1 not in ids:
			game.hide_node(view, "FileNode_%d" % (id + 1))
	for i in ids.size():
		var item := view.find_child("FileNode_%d" % ids[i], true, false) as NewHDScene
		if prizes.size() == 1:
			item.position.x = 540
		var panel := item.get_node("card_bg_0_1/Panel_69") as Control
		for child in panel.get_children():
			if child is CanvasItem:
				child.hide()
		game.hide_node(item, "Node_AD")
		var area := item.get_node("card_bg_0_1/Panel_get") as Control
		var hit := TextureButton.new()
		area.add_child(hit)
		hit.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
		hit.pressed.connect(reveal.bind(view, item, i, true))
		if bool(prizes[i].opened):
			reveal(view, item, i, false)
	(view.find_child("Button_open", true, false) as TextureButton).set_meta("local_action", func():
		for i in ids.size():
			reveal(view, view.find_child("FileNode_%d" % ids[i], true, false), i, true))
	update_buttons(view)

func update_buttons(view: NewHDScene) -> void:
	var all_open := game.profile.reward_draws.all(func(item: Dictionary): return bool(item.opened))
	var complete := view.find_child("Button_get", true, false) as TextureButton
	complete.visible = all_open
	complete.disabled = not all_open or int(view.get_meta("revealing")) > 0
	if all_open:
		game.hide_node(view, "Button_open")

func reveal(view: NewHDScene, item: NewHDScene, index: int, award: bool) -> void:
	var prize: Dictionary = game.profile.reward_draws[index]
	if award and Time.get_ticks_msec() < int(view.get_meta("ready_at", 0)):
		return
	if award and bool(prize.opened):
		return
	if award:
		game.profile.open_box(index)
	var duration := item.play_clip("Start1" if int(prize.amount) >= 50 else "Start")
	var panel := item.get_node("card_bg_0_1/Panel_69") as Control
	if prize.kind in ["coins", "diamonds"]:
		var icon := panel.get_node(("Gold" if prize.kind == "coins" else "Baoshi") + ("1" if int(prize.amount) >= 50 else "0")) as CanvasItem
		icon.show()
	else:
		var image := panel.get_node("card_item") as TextureRect
		var filename := "game_magic0" if prize.kind == "magic" else "card_bg_%d" % int(prize.index) if prize.kind == "back" else "game_bg_%d" % int(prize.index) if prize.kind == "background" else "Musicicon" if prize.kind == "music" else "card_fronts"
		var path := "" + filename + ".png"
		if NewHDAtlas.has_frame(path):
			image.texture = NewHDAtlas.texture(path)
		image.show()
	(panel.get_node("BitmapFontLabel_num") as CanvasItem).show()
	game.text(panel, "BitmapFontLabel_num", ("+" if prize.kind in ["coins", "diamonds"] else "x") + str(prize.amount))
	if award:
		view.set_meta("revealing", int(view.get_meta("revealing")) + 1)
		game.get_tree().create_timer(duration).timeout.connect(func():
			if is_instance_valid(view):
				view.set_meta("revealing", int(view.get_meta("revealing")) - 1)
				update_buttons(view))
	update_buttons(view)
