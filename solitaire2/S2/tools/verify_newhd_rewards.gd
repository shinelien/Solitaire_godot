extends "res://tools/verify_newhd_runtime.gd"

func run() -> void:
	create_timer(60).timeout.connect(func(): print("TIMEOUT"); quit(1))
	var test_path := "user://newhd_rewards_gui_test.cfg"
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
	game.show_lobby()
	game.profile.sign_data.day = 4
	game.profile.sign_data.last_date = Time.get_date_string_from_system()
	game.profile.sign_data.claimed = [1, 2, 3]
	game.profile.save()
	game.sign_in()
	await create_timer(.8).timeout
	await click(button(game.dialogs.back(), "Button_get"))
	check(game.profile.sign_data.draws.size() == 3, "NewHD fourth day chest persisted")
	await create_timer(2.5).timeout
	await click(button(game.dialogs.back(), "Button_open"))
	await create_timer(3.5).timeout
	check(game.profile.sign_data.draws.all(func(item: Dictionary): return bool(item.opened)), "NewHD sign chest opened")
	check(game.profile.diamonds >= 2 and game.profile.diamonds <= 20, "NewHD sign diamond range")
	await snapshot("19-sign-chest")
	await click(button(game.dialogs.back(), "Button_get"))
	await click(button(game.dialogs.back(), "Button_close"))
	var before_gold := game.profile.coins
	var before_gems := game.profile.diamonds
	var before_magic := game.profile.magic
	await click(button(game.lobby, "Button_LunPan"))
	await create_timer(.8).timeout
	await snapshot("20-roulette")
	await click(button(game.dialogs.back(), "Button_adget"))
	check(game.profile.coins == before_gold and game.profile.diamonds == before_gems and game.profile.magic == before_magic, "disabled roulette SDK never awards")
	await snapshot("21-roulette-unavailable")
	await click(button(game.dialogs.back(), "btn_close"))
	await click(button(game.lobby, "Button_Set"))
	await create_timer(.8).timeout
	await snapshot("22-settings")
	var previous := bool(game.profile.settings.left)
	await click(button(game.dialogs.back(), "btn_left_on"))
	check(game.profile.settings.left != previous, "left setting native input")
	await click(button(game.dialogs.back(), "btn_set_close"))
	await click(button(game.home, "Button_modeRight"))
	check(game.profile.settings.draw == 3, "draw three setting native input")
	game.close_all()
	game.new_game()
	await create_timer(3.3).timeout
	var click_target := Control.new()
	click_target.mouse_filter = Control.MOUSE_FILTER_IGNORE
	click_target.position = game.board._p(game.board.stock_point) - Vector2(10, 10)
	click_target.size = Vector2(20, 20)
	game.add_child(click_target)
	var initial_waste := game.session.state.waste.size()
	var initial_stock := game.session.state.stock.size()
	await click(click_target)
	await create_timer(.6).timeout
	check(game.session.state.waste.size() == initial_waste + 3 and game.session.state.stock.size() == initial_stock - 3, "left draw three through viewport pointer")
	check(game.session.state.total_card_count() == 52, "left draw three 52 cards")
	await snapshot("23-left-draw-three")
	print(JSON.stringify({"checks": checks, "failures": failures}))
	preview.queue_free()
	await process_frame
	await process_frame
	quit(0 if failures.is_empty() else 1)
