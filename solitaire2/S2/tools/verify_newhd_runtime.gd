extends SceneTree
var game: NewHDGame
var render_view: SubViewport
var failures: Array[String] = []
var checks := 0

func _initialize() -> void:
	call_deferred("run")

func check(value: bool, description: String) -> void:
	checks += 1
	if not value:
		failures.append(description)
		push_error(description)

func click(control: Control) -> void:
	print("GUI click ", control.name if control != null else "missing")
	check(control != null, "click target exists")
	if control == null:
		return
	var point := control.get_global_transform_with_canvas() * (control.size / 2)
	var motion := InputEventMouseMotion.new()
	motion.position = point
	motion.global_position = point
	render_view.push_input(motion, true)
	for down in [true, false]:
		var event := InputEventMouseButton.new()
		event.position = point
		event.global_position = point
		event.button_index = MOUSE_BUTTON_LEFT
		event.pressed = down
		event.button_mask = MOUSE_BUTTON_MASK_LEFT if down else 0
		render_view.push_input(event, true)
	await create_timer(.6).timeout

func button(parent: Node, name: String) -> Control:
	for candidate in parent.find_children(name, "Control", true, false):
		if candidate.is_visible_in_tree():
			return candidate
	return null

func snapshot(name: String) -> void:
	print("GUI snapshot ", name)
	await RenderingServer.frame_post_draw
	var image := render_view.get_texture().get_image()
	check(image.get_size() == Vector2i(1080, 1920), "1080p: " + name)
	image.save_png("res://docs/newhd-evidence/" + name + ".png")

func run() -> void:
	create_timer(120).timeout.connect(func(): print("TIMEOUT"); quit(1))
	var test_path := "user://newhd_gui_test.cfg"
	DirAccess.remove_absolute(ProjectSettings.globalize_path(test_path))
	game = load("res://scenes/newhd_main.tscn").instantiate()
	game.profile = NewHDProfile.new(test_path)
	var preview := TextureRect.new()
	preview.expand_mode = TextureRect.EXPAND_IGNORE_SIZE
	preview.size = Vector2(1080, 1920)
	root.add_child(preview)
	render_view = SubViewport.new()
	render_view.size = Vector2i(1080, 1920)
	render_view.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	preview.add_child(render_view)
	preview.texture = render_view.get_texture()
	render_view.notify_mouse_entered()
	render_view.add_child(game)
	await create_timer(3.3).timeout
	check(game.board.cards.size() == 52, "all cards constructed")
	await snapshot("01-game")
	await click(button(game.game_ui, "Button_pause"))
	check(game.dialogs.size() == 1, "pause via mouse")
	await snapshot("02-pause")
	await click(button(game.dialogs.back(), "Button_Lobby"))
	check(not game.game_visible, "home via mouse")
	await create_timer(1).timeout
	await snapshot("04-lobby")
	await click(button(game.lobby, "Button_tab2"))
	check(game.dialogs.size() == 1, "calendar via mouse")
	await snapshot("03-calendar")
	await click(button(game.dialogs.back(), "Button_close"))
	await click(button(game.lobby, "Button_Mybag"))
	check(game.dialogs.size() == 1, "wardrobe via mouse")
	await snapshot("05-backs")
	await click(button(game.dialogs.back(), "Button_tab1"))
	await snapshot("06-backgrounds")
	await click(button(game.dialogs.back(), "Button_close"))
	await click(button(game.lobby, "Button_Sign"))
	await snapshot("07-sign")
	await click(button(game.dialogs.back(), "Button_get"))
	check(game.profile.coins == 200, "NewHD day one 100 coins")
	await click(button(game.dialogs.back(), "Button_close"))
	await click(button(game.lobby, "Button_tab3"))
	await snapshot("08-store")
	var money := game.profile.coins
	await click(button(game.dialogs.back(), "Button_gold"))
	check(game.dialogs.size() == 2, "store draw via mouse")
	check(game.profile.coins == money - 100, "store charges original price")
	await create_timer(2.5).timeout
	await click(button(game.dialogs.back(), "Button_open"))
	await create_timer(3.5).timeout
	check(game.profile.reward_draws.all(func(item: Dictionary): return bool(item.opened)), "store prizes opened")
	await snapshot("11-store-reward")
	await click(button(game.dialogs.back(), "Button_get"))
	await click(button(game.dialogs.back(), "Button_close"))
	check(game.home.is_visible_in_tree(), "home restored after store")
	await click(button(game.lobby, "Button_Mybag"))
	await click(button(game.dialogs.back(), "Button_tab2_0"))
	await snapshot("12-card-faces")
	await click(button(game.dialogs.back(), "Button_zhengmian"))
	check(game.dialogs.back().find_children("*", "NewHDCard", true, false).size() == 52, "52 original face cards")
	await snapshot("13-face-details")
	game.close_dialog()
	await process_frame
	await click(button(game.dialogs.back(), "Button_tab1"))
	var scroll := game.dialogs.back().find_child("ListView_bg", true, false) as ScrollContainer
	scroll.scroll_vertical = 2600
	await create_timer(.2).timeout
	await click(button(scroll.get_node("Content").get_child(18), "Button_gameBg"))
	check(game.profile.settings.background == 18, "source animated background selected")
	game.close_all()
	await create_timer(.6).timeout
	await snapshot("14-live-background")
	game.daily_tasks()
	await create_timer(.6).timeout
	var reward_before := game.profile.coins
	await click(button(game.dialogs.back(), "Button_Task1"))
	await create_timer(1.2).timeout
	check(game.profile.coins == reward_before + 25, "NewHD background task reward")
	await snapshot("15-tasks")
	game.close_all()
	await click(button(game.home, "Button_start"))
	await create_timer(3.3).timeout
	var before := game.profile.magic
	var wand := button(game.game_ui, "Button_Shuffle")
	await click(wand)
	check(game.busy, "magic via mouse")
	await snapshot("09-magic")
	await create_timer(3).timeout
	check(game.profile.magic == before - 1, "magic consumed once")
	await snapshot("10-result")
	await click(button(game.game_ui, "Button_pause"))
	await click(button(game.dialogs.back(), "Button_Lobby"))
	game.level_selector()
	await create_timer(.6).timeout
	await snapshot("16-level-groups")
	await click(button(game.dialogs.back(), "Button_go"))
	await create_timer(.6).timeout
	await click(button(game.dialogs.back(), "Button_go"))
	await create_timer(3.3).timeout
	check(game.mode == "level" and game.selected_level == 0, "level 1 pointer flow")
	game.finish(true)
	await create_timer(3.5).timeout
	await snapshot("17-level-win")
	check(game.profile.stars.has("0"), "level result saved")
	await click(button(game.dialogs.back(), "btn_next"))
	await create_timer(3.3).timeout
	check(game.selected_level == 1, "next level native pointer flow")
	game.show_lobby()
	game.daily_selector()
	await create_timer(.6).timeout
	await click(button(game.dialogs.back(), "Button_start"))
	await snapshot("18-daily-modes")
	await click(button(game.dialogs.back(), "Button_start1"))
	await create_timer(3.3).timeout
	check(game.mode == "daily", "daily native pointer flow")
	check(game.session.state.total_card_count() == 52, "daily deck 52 cards")
	print(JSON.stringify({"checks": checks, "failures": failures}))
	preview.queue_free()
	await process_frame
	await process_frame
	quit(0 if failures.is_empty() else 1)
