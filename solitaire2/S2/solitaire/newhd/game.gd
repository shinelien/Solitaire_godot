class_name NewHDGame
extends Control
var profile := NewHDProfile.new()
var session := NewHDSession.new()
var board: NewHDBoard
var game_ui: NewHDScene
var lobby: NewHDScene
var background: NewHDBackground
var home: NewHDScene
var dialogs: Array[NewHDScene] = []
var ads: SolitaireAdService
var levels: Array[Dictionary] = []
var level_groups: Array[Dictionary] = []
var group_starts: Array[int] = []
var busy := false
var game_visible := true
var focus_paused := false
var finished := false
var auto_active := false
var generation := 0
var selected_level := 0
var mode := "classic"
var pressed: NewHDCard
var press_point := Vector2.ZERO
var dragging := false
var pointer_down := false
var toast: Label
var audio: AudioStreamPlayer
var dealing := false
var daily_date: Dictionary = {}
var daily_mode := 1
var idle_hint_clock := 0.0
var strings: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/strings_zh.json"))

func _ready() -> void:
	var level_data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/level.json"))
	for group in 6:
		group_starts.append(levels.size())
		level_groups.append(level_data["level%d" % group])
		for item: Dictionary in level_groups[group].data:
			levels.append(item)
	background = NewHDBackground.new()
	add_child(background)
	background.configure(profile)
	game_ui = scene("GameLayerHD")
	game_ui.z_index = 800
	add_child(game_ui)
	game_ui.play_clip("idle")
	for name in ["Button_2_0_0", "Button_teach", "FileNode_6", "Button_2_0", "FileNode_dailytips", "FileNode_teach", "Button_effff", "Button_effff_0", "Button_win", "Button_winceshi", "Panel_tips", "FileNode_task", "FileNode_relive", "Text_dailyContent", "Text_levelContent", "FileNode_getMagic", "FileNode_1", "FileNode_lunPan", "panel_gift", "Button_fanPai", "btn_challenge", "Button_Collect", "menu_fish_tips"]:
		hide_node(game_ui, name)
	var menu := game_ui.find_child("FileNode_2020Menu", true, false) as NewHDScene
	if menu != null:
		menu.play_clip("Start0")
	board = NewHDBoard.new()
	board.z_index = 900
	add_child(board)
	board.bind_scene(game_ui)
	bind_buttons(game_ui)
	lobby = scene("2020Dating_0")
	lobby.z_index = 800
	add_child(lobby)
	lobby.hide()
	for name in ["Node_tabLock1", "Node_tabLock2", "Node_tabLock3", "Button_share", "Button_teach", "Button_effCeShi", "Button_effCeShi_0", "Button_effCeShi_1", "FileNode_StarBox", "FileNode_StarBox2", "FileNode_CrownBox2", "Button_tab12"]:
		hide_node(lobby, name)
	bind_buttons(lobby)
	setup_home()
	var leaf := lobby.find_child("Node_leaf", true, false)
	if leaf != null:
		var actor := NewHDSpineActor.new()
		leaf.add_child(actor)
		actor.configure("scenes")
		actor.play("home", true)
	ads = SolitaireAdService.new()
	add_child(ads)
	var ad_session := str(Time.get_unix_time_from_system()) + ":" + str(randi())
	ads.reward_earned.connect(func(placement: String, receipt: int):
		if placement == "coins":
			profile.award_reward(placement, ad_session + ":" + str(receipt), 50))
	audio = AudioStreamPlayer.new()
	add_child(audio)
	play_music()
	toast = Label.new()
	toast.z_index = 4090
	toast.position = Vector2(140, 980)
	toast.size = Vector2(800, 100)
	toast.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	toast.add_theme_font_override("font", load("res://assets/newhd/chinese.tres"))
	toast.add_theme_font_size_override("font_size", 36)
	toast.add_theme_color_override("font_outline_color", Color.BLACK)
	toast.add_theme_constant_override("outline_size", 8)
	toast.mouse_filter = Control.MOUSE_FILTER_IGNORE
	add_child(toast)
	profile.changed.connect(update_hud)
	get_viewport().size_changed.connect(layout_screen)
	layout_screen()
	# Original branch resetOne() enters the card game on first launch.
	new_game()

func scene(name: String) -> NewHDScene:
	return load("res://scenes/newhd/ui/%s.tscn" % name).instantiate()

func text(parent: Node, name: String, value: String) -> void:
	var node := parent.find_child(name, true, false)
	if node is NewHDLabel:
		node.set_caption(value)
	elif node is Label:
		node.text = value

func hide_node(parent: Node, name: String) -> void:
	for node in parent.find_children(name, "CanvasItem", true, false):
		var scope := node.get_parent()
		while scope != null and not scope is NewHDScene:
			scope = scope.get_parent()
		if scope is NewHDScene:
			scope.suppress_node(node)
		else:
			node.hide()

func bind_buttons(parent: Node) -> void:
	for button: Node in parent.find_children("*", "TextureButton", true, false):
		if not button.has_meta("bound"):
			button.set_meta("bound", true)
			button.pressed.connect(action.bind(str(button.name), button))

func layout_screen() -> void:
	var height := get_viewport_rect().size.y
	for interface in [game_ui, lobby]:
		if interface == null:
			continue
		var bottom := interface.find_child("Panel_bottom", true, false) as Control
		if bottom != null:
			var baseline: float = bottom.get_meta("baseline_y", bottom.position.y)
			bottom.set_meta("baseline_y", baseline)
			bottom.position.y = baseline + height - 1920
	# Native scene coordinates stay at 1080 design width. Background covers tall displays.
	if background != null:
		background.scale.y = maxf(1, height / 1920)

func _process(delta: float) -> void:
	if game_visible and dialogs.is_empty() and not focus_paused and not finished and not dealing and session.state != null:
		session.elapsed += delta
		if profile.settings.hints and not busy and not dragging:
			idle_hint_clock += delta
			if idle_hint_clock > 12:
				idle_hint_clock = 0
				var options := session.hint_options()
				if not options.is_empty():
					board.hint(options[0], session.state)
		if not busy and session.objective().lost:
			finish(false)
	update_hud()

func _notification(what: int) -> void:
	if what == NOTIFICATION_APPLICATION_FOCUS_OUT:
		focus_paused = true
		cancel_pointer()
	elif what == NOTIFICATION_APPLICATION_FOCUS_IN:
		focus_paused = false
	elif what == NOTIFICATION_WM_CLOSE_REQUEST:
		profile.save()

func update_hud() -> void:
	if game_ui == null or lobby == null:
		return
	for interface in [game_ui, lobby]:
		text(interface, "BitmapFontLabel_gold", str(profile.coins))
		text(interface, "BitmapFontLabel_diamond", str(profile.diamonds))
		text(interface, "BitmapFontLabel_level", str(profile.level))
		text(interface, "Text_currentLv", "等级")
		text(interface, "Text_level", str(profile.level))
	for dialog in dialogs:
		if str(dialog.get_meta("dialog_scene", "")) == "UI_set":
			for pair in [["btn_three_on", profile.settings.draw == 3], ["btn_left_on", profile.settings.left], ["btn_MusicTips", profile.settings.music], ["btn_effTips", profile.settings.sound], ["btn_AutoTips", profile.settings.hints]]:
				var switch := dialog.find_child(pair[0], true, false) as TextureButton
				var texture: Texture2D = NewHDAtlas.texture("ui_switch%d.png" % (0 if pair[1] else 1))
				switch.texture_normal = texture
				switch.texture_pressed = texture
		text(dialog, "BitmapFontLabel_gold", str(profile.coins))
		text(dialog, "BitmapFontLabel_diamond", str(profile.diamonds))
		text(dialog, "BitmapFontLabel_level", str(profile.level))
		text(dialog, "Text_currentLv", "等级")
		if not str(dialog.get_meta("dialog_scene", "")).begins_with("WinLayer"):
			text(dialog, "Text_level", str(profile.level))
	text(game_ui, "Text_level", str(profile.level))
	text(game_ui, "Text_btnMagic2", "魔法")
	text(game_ui, "Text_btntips", "提示")
	text(game_ui, "Text_redution2", "撤销")
	text(game_ui, "Text_newgame2", "暂停")
	for label in lobby.find_children("Text_play", "Label", true, false):
		if label is NewHDLabel:
			label.set_caption("开始游戏")
		else:
			label.text = "开始游戏"
	text(lobby, "Text_LunPan", "轮盘")
	for name in ["Node_tabLock1", "Node_tabLock2", "Node_tabLock3"]:
		hide_node(lobby, name)
	if session.state == null:
		return
	text(game_ui, "BitmapFontLabel_score", str(session.state.score))
	text(game_ui, "Text_moveNum", str(session.state.move_count))
	text(game_ui, "Text_new_time", "%02d:%02d" % [int(session.elapsed) / 60, int(session.elapsed) % 60])
	text(game_ui, "text_mainscore", "得分")
	text(game_ui, "text_mainmove", "步数")
	text(game_ui, "text_maintime", "时间")
	text(game_ui, "Text_ShuffleNum", str(profile.magic))
	text(game_ui, "Text_ShuffleNum_0", str(profile.magic))
	text(game_ui, "Text_ShuffleNum_1", str(profile.magic))
	var level_bar := game_ui.find_child("LoadingBar_menu_level", true, false) as TextureProgressBar
	if level_bar != null:
		level_bar.value = 100.0 * profile.exp / maxi(1, int(profile.level_data.lv[profile.level].exp))
	var auto := game_ui.find_child("FileNode_auto", true, false) as CanvasItem
	if auto != null:
		auto.visible = session.can_auto() and not finished

func new_game(replay := false, level_index := -1, daily_record := "", daily_draw := 0) -> void:
	idle_hint_clock = 0
	generation += 1
	var token := generation
	busy = true
	dealing = true
	auto_active = false
	cancel_pointer()
	close_all()
	finished = false
	show_game()
	mode = "level" if level_index >= 0 else "daily" if not daily_record.is_empty() else "classic"
	var count := int(profile.settings.draw)
	if daily_draw > 0:
		count = daily_draw
	var record := daily_record
	session.level = {}
	if level_index >= 0:
		selected_level = level_index
		session.level = levels[level_index]
		count = 1 if session.level.pokerMode == "One" else 3
		record = session.level.bureau
	session.start(count, replay, record, bool(profile.settings.random))
	background.change_color()
	board.set_skins(profile)
	board.present(session.state, false)
	if not session.level.is_empty():
		text(game_ui, "Text_levelContent", "第 %d 关：%s" % [int(session.level.subShow), localize(str(session.level.name))])
		(game_ui.find_child("Text_levelContent", true, false) as CanvasItem).show()
	else:
		hide_node(game_ui, "Text_levelContent")
	var daily_label := game_ui.find_child("Text_dailyContent", true, false) as CanvasItem
	daily_label.visible = mode == "daily"
	if mode == "daily":
		text(game_ui, "Text_dailyContent", "%d 年 %d 月 %d 日 · 翻 %d 张" % [daily_date.year, daily_date.month, daily_date.day, count])
	await board.deal(session.state)
	if token != generation:
		return
	busy = false
	dealing = false
	ads.request_interstitial("new_game")

func show_game() -> void:
	game_visible = true
	game_ui.show()
	board.show()
	if lobby != null:
		lobby.hide()
	update_hud()

func show_lobby() -> void:
	cancel_pointer()
	close_all()
	game_visible = false
	game_ui.hide()
	board.hide()
	lobby.show()
	lobby.play_clip("idle")
	if home != null:
		home.play_clip("In")
	update_hud()

func open_dialog(name: String, clip := "") -> NewHDScene:
	cancel_pointer()
	if not dialogs.is_empty():
		dialogs.back().hide()
	var dialog := scene(name)
	dialog.set_meta("dialog_scene", name)
	dialog.z_index = 1600 + dialogs.size() * 20
	# Some Cocos modal roots have zero size. The shield belongs to the viewport,
	# so those roots cannot shrink it or move it away from the background UI.
	var blocker := Control.new()
	blocker.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	blocker.mouse_filter = Control.MOUSE_FILTER_STOP
	blocker.z_index = dialog.z_index
	add_child(blocker)
	dialog.set_meta("modal_blocker", blocker)
	add_child(dialog)
	dialogs.append(dialog)
	bind_buttons(dialog)
	if not clip.is_empty():
		dialog.play_clip(clip)
	if name == "2020Pause":
		for pair in [["Text_NewGame", "难度"], ["Text_Again", "重新开始"], ["Text_game_daily", "每日挑战"], ["Text_Lobby", "大厅"]]:
			text(dialog, pair[0], pair[1])
		text(dialog, "Text_pauseTitle1", "暂停")
		text(dialog, "Text_DailyBack", "难度")
		hide_node(dialog, "Button_DailyBack" if mode != "daily" else "Button_NewGame")
	update_hud()
	return dialog

func close_dialog() -> void:
	if dialogs.is_empty():
		return
	var dialog: NewHDScene = dialogs.pop_back()
	if str(dialog.get_meta("dialog_scene", "")) == "2020Store_0":
		(lobby.find_child("Panel_home", true, false) as CanvasItem).show()
	var blocker := dialog.get_meta("modal_blocker") as Control
	blocker.hide()
	blocker.mouse_filter = Control.MOUSE_FILTER_IGNORE
	blocker.queue_free()
	dialog.hide()
	dialog.queue_free()
	if not dialogs.is_empty():
		dialogs.back().show()

func close_all() -> void:
	while not dialogs.is_empty():
		close_dialog()

func message(value: String) -> void:
	toast.text = value
	toast.modulate.a = 1
	var token := value
	get_tree().create_timer(2).timeout.connect(func():
		if toast.text == token:
			toast.text = "")

func action(name: String, button: Node) -> void:
	idle_hint_clock = 0
	if busy and game_visible and dialogs.is_empty():
		return
	play_effect("button_start")
	if button.has_meta("local_action"):
		(button.get_meta("local_action") as Callable).call()
		return
	match name:
		"Button_pause":
			open_dialog("2020Pause", "Start0")
		"Button_Lobby", "btn_lobby":
			show_lobby()
		"Button_start":
			if button.has_meta("daily_calendar"):
				daily_modes()
			else:
				new_game()
		"Button_start1", "Button_start2", "Button_start3", "Button_start4":
			start_daily(int(name.right(1)))
		"Button_game":
			reset_menu()
		"Button_NewGame", "btn_new":
			new_game(false, selected_level if mode == "level" else -1)
		"Button_Again", "Button_again":
			new_game(true, selected_level if mode == "level" else -1)
		"Button_reduction":
			if session.undo():
				play_effect("undo")
				refresh_board()
		"Button_tips":
			var hints := session.hint_options()
			if not hints.is_empty():
				board.hint(hints[0], session.state)
			else:
				message("暂无可移动的牌")
		"Button_Shuffle", "Button_Shuffle111":
			use_magic()
		"Button_setting", "Button_Set":
			var settings := open_dialog("UI_set", "Start")
			hide_node(settings, "Node_update")
			for key in ["Node_1", "Node_dyy", "Node_startAni", "Node_endAni"]:
				var node := settings.find_child(key, true, false) as CanvasItem
				if node != null:
					node.visible = key == "Node_1"
		"Button_rule":
			var rules := open_dialog("RuleLayer", "loop")
			for i in 9:
				text(rules, "text_rule%d" % i, localize(str(100140 + i)))
		"Button_privacy":
			OS.shell_open("https://sites.google.com/view/space-cat-studio/%E9%A6%96%E9%A1%B5")
		"btn_three_on", "btn_three_on_0", "Button_1_0_0_1_0", "Button_three":
			profile.settings.draw = 3 if profile.settings.draw == 1 else 1
			profile.save()
			message("翻 %d 张，将在下一局生效" % int(profile.settings.draw))
		"btn_left_on", "Button_left":
			profile.settings.left = not profile.settings.left
			profile.save()
			board.set_skins(profile)
			board.present(session.state, false)
		"btn_MusicTips", "Button_music":
			profile.settings.music = not profile.settings.music
			profile.save()
			play_music()
		"btn_effTips", "Button_eff":
			profile.settings.sound = not profile.settings.sound
			profile.save()
		"btn_AutoTips", "Button_Auto":
			profile.settings.hints = not profile.settings.hints
			profile.save()
		"Button_close", "btn_set_close", "btn_level_close", "Button_back":
			var group: int = button.get_meta("level_group", -1)
			close_dialog()
			if group >= 0:
				level_selector()
		"Button_Mybag", "Button_beibao":
			wardrobe()
		"Button_Sign":
			sign_in()
		"Button_tab3", "Button_shop":
			store()
		"Button_Dailytasks":
			daily_tasks()
		"Button_LunPan":
			var view := open_dialog("RewardRoulette", "Start")
			var controller := NewHDRoulette.new()
			view.add_child(controller)
			controller.configure(self, view)
		"Button_fanPai":
			ads.request_rewarded("draw")
			message("广告尚未接入，暂时无法领取")
		"Button_Level", "Button_level", "Button_tab1":
			level_selector()
		"Button_daily", "Button_game_daily", "Button_tab2", "Button_DailyBack":
			daily_selector()
		"Button_tab0":
			show_lobby()
		"Button_modeRight", "Button_modeLeft1":
			if button.has_meta("daily_calendar"):
				daily_date.month += 1 if name == "Button_modeRight" else -1
				var today := Time.get_date_dict_from_system()
				daily_date.day = today.day if daily_date.month == today.month else days_in_month(daily_date.year, daily_date.month)
				populate_calendar(dialogs.back())
			else:
				profile.settings.draw = 3 if name == "Button_modeRight" else 1
				profile.save()
				if not dialogs.is_empty():
					text(dialogs.back(), "Text_mode", "翻 %d 张" % int(profile.settings.draw))
		"Button_getGold", "Button_Sign_AD", "btn_gift_lingqu":
			ads.request_rewarded("coins")
			message("奖励暂不可用")
		"Button_auto", "btn_auto", "Button_Complete":
			auto_complete()
		_:
			if "close" in name:
				close_dialog()

func refresh_board() -> void:
	busy = true
	var time := board.present(session.state)
	await get_tree().create_timer(time).timeout
	board.settle_layers()
	busy = false
	var result := session.objective()
	if result.won:
		finish(true)
	elif result.lost:
		finish(false)

func use_magic() -> void:
	if busy or finished or not game_visible or not dialogs.is_empty() or session.state == null:
		return
	if profile.magic <= 0:
		magic_shop()
		return
	var plan := session.magic_plan()
	if plan.is_empty():
		message("当前没有适合魔法棒移动的牌")
		return
	cancel_pointer()
	board.clear_hint()
	busy = true
	var token := generation
	var effect := load("res://scenes/newhd/ui/Animation/Magic.tscn").instantiate() as NewHDScene
	effect.name = "MagicEffect"
	effect.position = board.cards[plan.card_id].position + Vector2(-148, -110)
	effect.z_index = 2200
	add_child(effect)
	effect.frame_event.connect(func(_target: NodePath, event: String):
		if event == "magic" and token == generation and not effect.has_meta("applied"):
			effect.set_meta("applied", true)
			apply_magic_event(plan, token))
	(effect.get_node("AnimationPlayer") as AnimationPlayer).animation_finished.connect(func(_clip): effect.queue_free(), CONNECT_ONE_SHOT)
	effect.play_clip("Start0")
	play_effect("Magic0")

func apply_magic_event(plan: Dictionary, token: int) -> void:
	if profile.magic <= 0 or not session.apply_magic(plan):
		busy = false
		message("当前没有适合魔法棒移动的牌")
		return
	profile.advance_task(4)
	profile.magic -= 1
	profile.statistics.magic_used = int(profile.statistics.get("magic_used", 0)) + 1
	profile.save()
	var duration := board.magic_transfer(session.state, int(plan.card_id))
	await get_tree().create_timer(duration).timeout
	if token != generation:
		return
	board.settle_layers()
	busy = false
	var result := session.objective()
	if result.won:
		finish(true)
	elif result.lost:
		finish(false)

func magic_shop(after_purchase: Callable = Callable()) -> void:
	var view := open_dialog("AD_magic", "loop")
	text(view, "Text_title", "获得魔法棒")
	text(view, "Text_miaoshu", "获得 1 根魔法棒")
	text(view, "text_1000", "200")
	text(view, "text_guankan", "领取")
	text(view, "text_guankan0", "免费领取")
	text(view, "Text_xianZhi", "%d/50" % profile.magic)
	# The source shows one video entry alongside the coin purchase.
	hide_node(view, "btn_guankan")
	var buy := view.find_child("btn_1000gold", true, false) as TextureButton
	buy.disabled = profile.diamonds < 200 or profile.magic >= 50
	buy.set_meta("local_action", func():
		var result := profile.buy_magic()
		if not result.ok:
			message(str(result.reason))
			return
		close_dialog()
		if after_purchase.is_valid():
			after_purchase.call()
		message("已获得 1 根魔法棒"))
	for name in ["btn_guankan", "btn_guankan0"]:
		var button := view.find_child(name, true, false) as TextureButton
		button.set_meta("local_action", func():
			ads.request_rewarded("magic")
			message("广告尚未接入，暂时无法领取"))

func commit(move: Move) -> void:
	if move == null:
		return
	var result := session.apply(move)
	if result.ok:
		play_effect("Cover0" if move.kind == Move.MoveKind.DRAW_STOCK else "movecard")
		refresh_board()
	elif pressed != null:
		play_effect("nomove")
		pressed.reject()

func play_effect(name: String) -> void:
	if not profile.settings.sound:
		return
	var path := "res://assets/newhd/music/%s.mp3" % name
	if not ResourceLoader.exists(path):
		return
	var effect := AudioStreamPlayer.new()
	effect.stream = load(path)
	add_child(effect)
	effect.finished.connect(effect.queue_free)
	effect.play()

func play_music() -> void:
	audio.stop()
	var track := int(profile.settings.music_track)
	if profile.settings.music and track >= 0:
		audio.stream = load("res://assets/newhd/music/bgm%d.mp3" % track).duplicate()
		(audio.stream as AudioStreamMP3).loop = true
		audio.play()

func _unhandled_input(event: InputEvent) -> void:
	if not game_visible or busy or not dialogs.is_empty() or finished:
		return
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.pressed:
			press(event.position)
		else:
			release(event.position)
	elif event is InputEventMouseMotion and pointer_down:
		motion(event.position)

func _input(event: InputEvent) -> void:
	# Releases must also be handled when the pointer leaves the board into UI.
	if pointer_down and event is InputEventMouseButton and not event.pressed:
		release(event.position)
		get_viewport().set_input_as_handled()

func press(point: Vector2) -> void:
	idle_hint_clock = 0
	if board.stock_contains(point):
		commit(InputInterpreter.stock_click_move(session.state))
		return
	pressed = board.hit(point, session.state)
	if pressed == null:
		return
	pointer_down = true
	press_point = point
	dragging = false

func motion(point: Vector2) -> void:
	if pressed == null:
		return
	if not dragging and point.distance_to(press_point) >= 2:
		dragging = true
		board.begin_drag(pressed, press_point)
	if dragging:
		board.drag_to(point)

func release(point: Vector2) -> void:
	if not pointer_down or pressed == null:
		return
	pointer_down = false
	if dragging:
		var target := board.drop_target(pressed.position, pressed)
		var move := InputInterpreter.build_drag_move(session.state, pressed.source, target)
		board.end_drag()
		if move != null and RulesEngine.validate(session.state, move).ok:
			commit(move)
		else:
			board.present(session.state)
	else:
		var move := InputInterpreter.auto_find_move(session.state, pressed.source)
		if move != null:
			commit(move)
		else:
			pressed.reject()
	pressed = null
	dragging = false

func cancel_pointer() -> void:
	if board != null and pointer_down:
		board.end_drag()
		if session.state != null:
			board.present(session.state, false)
	pointer_down = false
	pressed = null
	dragging = false

func auto_complete() -> void:
	if auto_active or not session.can_auto():
		return
	var plan := session.auto_plan()
	if not plan.ok:
		return
	auto_active = true
	for move in plan.moves:
		if not auto_active:
			break
		session.apply(move)
		await refresh_board()
	auto_active = false

func finish(won: bool) -> void:
	if finished:
		return
	finished = true
	var coins := 0
	var gems := 0
	var key := daily_key(daily_date, daily_mode) if mode == "daily" else str(selected_level)
	var repeated := profile.daily_completed.has(key) if mode == "daily" else profile.stars.has(key) if mode == "level" else false
	var stars := 3 if profile.settings.random or session.state.draw_count == 3 or session.elapsed <= 360 else 2 if session.elapsed <= 450 else 1
	if won:
		if mode == "daily":
			for id in [2, 9, 102, 103]:
				profile.advance_task(id)
			if daily_mode == 2:
				profile.advance_task(106)
			elif daily_mode == 4:
				profile.advance_task(107)
		elif mode == "level":
			profile.advance_task(8)
		elif profile.settings.random:
			profile.advance_task(108)
			if session.state.draw_count == 3:
				profile.advance_task(110)
		else:
			for id in [1, 100, 101]:
				profile.advance_task(id)
			if session.state.draw_count == 3:
				profile.advance_task(109)
		coins = 2 if repeated else 25
		gems = 1 if repeated else 15
		profile.coins += coins
		profile.diamonds += gems
		profile.statistics.wins = int(profile.statistics.get("wins", 0)) + 1
		profile.statistics.star_total = int(profile.statistics.get("star_total", 0)) + stars
		profile.statistics.best_score = maxi(int(profile.statistics.get("best_score", 0)), session.state.score + int(700000 / maxf(1, session.elapsed)))
		profile.add_exp(5 if repeated else 100)
		if mode == "daily":
			profile.daily_completed[key] = true
		elif mode == "level":
			profile.stars[key] = maxi(int(profile.stars.get(key, 0)), stars)
		profile.save()
	var view_name := "WinLayer_level" if mode == "level" else "WinLayer_Challenge" if mode == "daily" else "WinLayer"
	var win := open_dialog(view_name, "Start")
	var win_player := win.get_node("AnimationPlayer") as AnimationPlayer
	win_player.animation_finished.connect(func(clip_name):
		if clip_name == &"Start":
			win.play_clip("Btn"))
	for pair in [["Node_gold", "Animation/Node_gold", "Gold"], ["Node_zuanShi", "Animation/Node_currency", "Baoshi"]]:
		var holder := win.find_child(pair[0], true, false)
		if holder != null:
			var currency := scene(pair[1])
			holder.add_child(currency)
			currency.play_clip(pair[2], true)
	text(win, "Text_congratulations", "恭喜你！" if won else "本局结束")
	text(win, "Text_level", "第 %d 关" % (selected_level + 1))
	text(win, "text_you_TotalScore", str(session.state.score))
	text(win, "atlasLabel_you_time", "%02d:%02d" % [int(session.elapsed) / 60, int(session.elapsed) % 60])
	text(win, "atlasLabel_you_movetime", str(session.state.move_count))
	text(win, "atlasLabel_coinnum", str(coins))
	text(win, "atlasLabel_zuanShiNum", str(gems))
	for i in range(1, 4):
		var star := win.find_child("FileNode_star%d" % i, true, false) as CanvasItem
		if star != null:
			star.visible = won and i <= stars
	for name in ["Button_rank", "Button_PingJia", "Button_share", "text_rank", "atlasLabel_rank"]:
		hide_node(win, name)
	var double := win.find_child("Button_doubleWin", true, false) as TextureButton
	if double != null:
		double.set_meta("local_action", func():
			ads.request_rewarded("double_win")
			message("广告尚未接入，暂时无法领取"))
	var next := win.find_child("btn_next", true, false) as TextureButton
	if next != null:
		next.set_meta("local_action", func():
			if won and selected_level + 1 < levels.size():
				new_game(false, selected_level + 1)
			else:
				close_all()
				level_selector())

func localize(key: String) -> String:
	return str(strings.get(key, key))

func wardrobe() -> void:
	var dialog := open_dialog("2020Bag", "Start0")
	var controller := NewHDWardrobe.new()
	controller.name = "Wardrobe"
	dialog.add_child(controller)
	controller.configure(self, dialog)

func sign_in() -> void:
	var dialog := open_dialog("20207DaySgin", "Start0")
	var controller := NewHDSignIn.new()
	controller.name = "SignIn"
	dialog.add_child(controller)
	controller.configure(self, dialog)

func level_selector(group := -1) -> void:
	var dialog := open_dialog("Level0", "Start0")
	var scroller := dialog.find_child("ListView_bg%d" % (0 if group < 0 else 1), true, false) as ScrollContainer
	if scroller == null:
		return
	scroller.show()
	var other := dialog.find_child("ListView_bg%d" % (1 if group < 0 else 0), true, false) as CanvasItem
	other.hide()
	dialog.find_child("btn_level_close", true, false).set_meta("level_group", group)
	var content := scroller.get_node("Content") as Control
	for child in content.get_children():
		child.queue_free()
	if group < 0:
		content.custom_minimum_size = Vector2(scroller.size.x, level_groups.size() * 500)
		for i in level_groups.size():
			var info: Dictionary = level_groups[i]
			var item := scene("level_icon0")
			content.add_child(item)
			item.position = Vector2((scroller.size.x - item.size.x) / 2, i * 500)
			text(item, "Text_level", str(i + 1))
			text(item, "Text_mode", localize(info.hard))
			var stars := 0
			for level_index in range(group_starts[i], group_starts[i] + info.data.size()):
				stars += int(profile.stars.get(str(level_index), 0))
			text(item, "Text_winStar", "%d/%d" % [stars, int(info.total)])
			hide_node(item, "Node_lock")
			for placeholder in ["level_card0_1", "level_bg0_2"]:
				hide_node(item, placeholder)
			var button := item.find_child("Button_go", true, false) as TextureButton
			button.texture_normal = load("res://assets/newhd/level/" + str(info.icon))
			button.texture_pressed = button.texture_normal
			button.pressed.connect(func():
				close_dialog()
				level_selector(i))
		return
	var count: int = level_groups[group].data.size()
	content.custom_minimum_size = Vector2(scroller.size.x, ceilf(count / 4.0) * 380)
	for offset in count:
		var i: int = group_starts[group] + offset
		var item := scene("level_icon1")
		content.add_child(item)
		item.position = Vector2(offset % 4 * scroller.size.x / 4, offset / 4 * 380)
		text(item, "Text_level", str(int(levels[i].subShow)))
		text(item, "Text_title", localize(levels[i].name))
		(item.find_child("Level_icon1", true, false) as TextureRect).texture = load("res://assets/newhd/HD1/" + str(levels[i].icon))
		var button := item.find_child("Button_go", true, false) as TextureButton
		button.disabled = i > 0 and not profile.stars.has(str(i - 1))
		(item.find_child("Level_icon0", true, false) as CanvasItem).visible = button.disabled
		(item.find_child("Level_complete", true, false) as CanvasItem).visible = profile.stars.has(str(i))
		(item.find_child("Node_star", true, false) as CanvasItem).visible = profile.stars.has(str(i))
		hide_node(item, "Node_select")
		button.pressed.connect(new_game.bind(false, i))

func daily_selector() -> void:
	daily_date = Time.get_date_dict_from_system()
	var dialog := open_dialog("2020Daily_riqi", "Start0")
	for name in ["Button_start", "Button_modeRight", "Button_modeLeft1"]:
		dialog.find_child(name, true, false).set_meta("daily_calendar", true)
	populate_calendar(dialog)

func days_in_month(year: int, month: int) -> int:
	if month == 2:
		return 29 if year % 400 == 0 or year % 4 == 0 and year % 100 != 0 else 28
	return 30 if month in [4, 6, 9, 11] else 31

func daily_key(date: Dictionary, challenge: int) -> String:
	return "%04d-%02d-%02d:%d" % [date.year, date.month, date.day, challenge]

func populate_calendar(dialog: NewHDScene) -> void:
	var container := dialog.find_child("Panel_container", true, false) as Control
	for child in container.get_children():
		child.free()
	var today := Time.get_date_dict_from_system()
	var first := Time.get_unix_time_from_datetime_dict({"year": daily_date.year, "month": daily_date.month, "day": 1, "hour": 0, "minute": 0, "second": 0})
	var weekday := int(Time.get_datetime_dict_from_unix_time(first).weekday)
	var completed := 0
	for day in days_in_month(daily_date.year, daily_date.month):
		var date := {"year": daily_date.year, "month": daily_date.month, "day": day + 1}
		var count := 0
		for challenge in range(1, 5):
			if profile.daily_completed.has(daily_key(date, challenge)):
				count += 1
		completed += count
		var closed: bool = date.month > today.month or date.month == today.month and date.day > today.day
		var item := scene("2020Daily_Node_0")
		container.add_child(item)
		var index := day + weekday
		item.position = Vector2((index % 7 + .5) * 138, container.size.y - (5 - index / 7 + .5) * 124)
		var image := item.get_node("Image_root") as TextureRect
		image.position = Vector2(-55, -55)
		image.size = Vector2(110, 110)
		image.pivot_offset = Vector2(55, 55)
		image.texture = NewHDAtlas.texture("daily/Daily_Daily%d.png" % (3 if closed else 2 if count > 0 else 1))
		var label := item.find_child("Text_day_0", true, false) as Label
		label.text = str(day + 1)
		label.position = Vector2(52.8, 51.7) - label.size / 2
		label.visible = count == 0
		label.self_modulate = Color.GRAY if closed else Color(0, 1, .494)
		hide_node(item, "Text_day")
		hide_node(item, "Text_seven")
		var crown := item.find_child("Node_cown", true, false) as Control
		crown.position = Vector2(55, 55)
		crown.scale = Vector2.ONE * .91
		crown.visible = count > 0
		(item.find_child("Sprite_cown", true, false) as TextureRect).texture = NewHDAtlas.texture("daily/Challenge_WG%d.png" % mini(3, count))
		for name in ["Daily_Daily4_1", "Daily_Daily4_1_0"]:
			var halo := item.find_child(name, true, false) as Control
			halo.position = Vector2(55, 53.9) - halo.size / 2
			halo.visible = date.day == daily_date.day
		if date.day == daily_date.day:
			item.play_clip("loop", true)
			label.self_modulate = Color.WHITE
		if not closed:
			image.mouse_filter = Control.MOUSE_FILTER_STOP
			image.gui_input.connect(func(event: InputEvent):
				if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and not event.pressed:
					daily_date.day = date.day
					populate_calendar.call_deferred(dialog))
	text(dialog, "Text_title2", "%d 年 %d 月" % [daily_date.year, daily_date.month])
	text(dialog, "Text_start11", "开始挑战")
	text(dialog, "Text_Star_miaoshu", "收集皇冠\n获取稀有鱼")
	text(dialog, "Text_getFish", "领取")
	text(dialog, "Text_rare", "稀有")
	text(dialog, "BitmapFontLabel_StarNum", str(completed))
	text(dialog, "BitmapFontLabel_StarNumMax", str(days_in_month(daily_date.year, daily_date.month) * 4))
	for i in range(1, 8):
		text(dialog, "Text_week%d" % i, ["日", "一", "二", "三", "四", "五", "六"][i % 7])
	(dialog.find_child("Button_modeLeft1", true, false) as TextureButton).disabled = daily_date.month == 1
	(dialog.find_child("Button_modeRight", true, false) as TextureButton).disabled = daily_date.month >= today.month

func daily_modes() -> void:
	var dialog := open_dialog("2020Daily_gameNode", "start")
	dialog.position = Vector2(540, 960)
	hide_node(dialog, "panel_dailyget")
	text(dialog, "Text_dailyDialogTitle", "%d 月 %d 日挑战" % [daily_date.month, daily_date.day])
	for challenge in range(1, 5):
		var button := dialog.find_child("Button_start%d" % challenge, true, false)
		text(button, "Text_Name", "再次挑战" if profile.daily_completed.has(daily_key(daily_date, challenge)) else "开始挑战")
		text(dialog, "text_modeContext%d" % challenge, "翻三张" if challenge in [2, 4] else "翻一张")
		var crown := dialog.find_child("Level_win%d" % challenge, true, false) as CanvasItem
		if crown != null:
			crown.visible = profile.daily_completed.has(daily_key(daily_date, challenge))

func start_daily(challenge: int) -> void:
	daily_mode = challenge
	var day_of_year := int(daily_date.day)
	for month in range(1, int(daily_date.month)):
		day_of_year += days_in_month(daily_date.year, month)
	var data: Dictionary = JSON.parse_string(FileAccess.get_file_as_string("res://assets/newhd/data/daily.json"))
	# Source uses 1-based day indexes but ships 366 rows. Reserve row zero for
	# leap-year December 31 instead of inheriting its out-of-bounds access.
	var record: String = data.config[day_of_year % data.config.size()][str(challenge)].decks
	new_game(false, -1, record, 3 if challenge in [2, 4] else 1)


func setup_home() -> void:
	home = scene("2020HomeView_Classic")
	lobby.find_child("Panel_home", true, false).add_child(home)
	bind_buttons(home)
	for name in ["Text_hard", "Text_mode"]:
		var label := home.find_child(name, true, false) as NewHDLabel
		label.design_center.y = (label.get_parent() as Control).size.y / 2
		label.fit_caption()
	text(home, "Text_start", "开始游戏")
	text(home, "Text_hard", "随机" if profile.settings.random else "活局")
	text(home, "Text_mode", "翻 %d 张" % int(profile.settings.draw))
	for pair in [["Button_hardRight", true], ["Button_hardLeft1", false]]:
		home.find_child(pair[0], true, false).set_meta("local_action", func():
			profile.settings.random = pair[1]
			profile.save()
			text(home, "Text_hard", "随机" if profile.settings.random else "活局"))
	for pair in [["Button_modeRight", 3], ["Button_modeLeft1", 1]]:
		home.find_child(pair[0], true, false).set_meta("local_action", func():
			profile.settings.draw = pair[1]
			profile.save()
			text(home, "Text_mode", "翻 %d 张" % pair[1]))
	var holder := home.find_child("Node_sprite", true, false)
	if holder != null:
		var card := NewHDCard.new()
		holder.add_child(card)
		card.configure(0, 0, 0)
		card.show_face(true, false)
		var display := home.find_child("FileNode_theme", true, false) as NewHDScene
		display.frame_event.connect(func(_target, event_name):
			if event_name in ["event_front", "event_back"]:
				card.configure(0, profile.card_style(0), int(profile.settings.back))
				card.show_face(event_name == "event_front", false))
		display.play_clip("loop", true)

func store() -> void:
	(lobby.find_child("Panel_home", true, false) as CanvasItem).hide()
	var view := open_dialog("2020Store_0")
	var controller := NewHDStore.new()
	controller.name = "Store"
	view.add_child(controller)
	controller.configure(self, view)

func daily_tasks() -> void:
	var view := open_dialog("2020Dailytask", "Start0")
	var controller := NewHDTasks.new()
	view.add_child(controller)
	controller.configure(self, view)

func reset_menu() -> void:
	var view := open_dialog("UI_reset", "Start")
	for pair in [["btn_random_new", true], ["btn_huo_new", false]]:
		view.find_child(pair[0], true, false).set_meta("local_action", func():
			profile.settings.random = pair[1]
			profile.save()
			new_game())
	view.find_child("btn_reset_replay", true, false).set_meta("local_action", func(): new_game(true))
	view.find_child("btn_level", true, false).set_meta("local_action", level_selector)
	view.find_child("btn_daily", true, false).set_meta("local_action", daily_selector)
	view.find_child("btn_reset_out", true, false).set_meta("local_action", show_lobby)
	view.find_child("Button_statistic", true, false).set_meta("local_action", func():
		message("胜利 %d 局 · 最高分 %d · 魔法棒使用 %d 次" % [int(profile.statistics.get("wins", 0)), int(profile.statistics.get("best_score", 0)), int(profile.statistics.get("magic_used", 0))]))
