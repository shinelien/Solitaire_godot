extends SceneTree
var game: InvincibleGame
var failures: Array[String] = []
var render_view: SubViewport
func _initialize() -> void:
	call_deferred("run")
func check(value: bool, name: String) -> void:
	if not value:
		failures.append(name)
func snapshot(name: String) -> void:
	await RenderingServer.frame_post_draw
	var path := "res://docs/invincible-evidence/" + name + ".png"
	var image := render_view.get_texture().get_image()
	check(image.get_size() == Vector2i(1080, 1920), "1080p framebuffer: " + name)
	image.save_png(path)

func click(point: Vector2) -> void:
	for down in [true, false]:
		var event := InputEventMouseButton.new()
		event.position = point
		event.button_index = MOUSE_BUTTON_LEFT
		event.pressed = down
		render_view.push_input(event, true)
		await process_frame
func run() -> void:
	DirAccess.make_dir_recursive_absolute(ProjectSettings.globalize_path("res://docs/invincible-evidence"))
	game = load("res://scenes/invincible_main.tscn").instantiate()
	game.profile = InvincibleProfile.new("user://invincible_acceptance.cfg")
	var preview := SubViewportContainer.new()
	preview.size = Vector2(540, 960)
	preview.stretch = false
	preview.scale = Vector2.ONE * .5
	root.add_child(preview)
	render_view = SubViewport.new()
	render_view.size = Vector2i(1080, 1920)
	render_view.render_target_update_mode = SubViewport.UPDATE_ALWAYS
	preview.add_child(render_view)
	render_view.add_child(game)
	await create_timer(4).timeout
	check(game.get_viewport_rect().size == Vector2(1080, 1920), "design resolution")
	check(game.board.cards.size() == 52, "52 persistent cards")
	await snapshot("01-game")
	var before := game.session.state.stock.size()
	await click(game.board.stock_point)
	await create_timer(.8).timeout
	check(game.session.state.stock.size() == before - 1, "stock draw")
	await snapshot("02-draw")
	game.action("Button_pause", game)
	await create_timer(1).timeout
	await snapshot("03-pause")
	game.show_lobby()
	await create_timer(1).timeout
	await snapshot("04-lobby")
	game.fish_shop()
	await create_timer(1).timeout
	await snapshot("05-fish-shop")
	game.close_all()
	game.tank_shop()
	await create_timer(1).timeout
	await snapshot("06-tanks")
	game.close_all()
	game.level_selector()
	await create_timer(1).timeout
	await snapshot("07-levels")
	game.close_all()
	game.level_selector(0)
	await create_timer(1).timeout
	check(game.dialogs.back().find_child("ListView_bg1", true, false).is_visible_in_tree(), "level list visible")
	await snapshot("07b-level-group")
	game.close_all()
	game.new_game(false, 0)
	await create_timer(3.2).timeout
	check(game.session.level.subShow == 1, "configured level 1")
	await snapshot("08-level-game")
	game.show_lobby()
	game.daily_selector()
	await create_timer(1).timeout
	await snapshot("09-daily-calendar")
	game.daily_modes()
	await create_timer(1).timeout
	await snapshot("10-daily-modes")
	game.start_daily(4)
	await create_timer(3.2).timeout
	check(game.session.state.draw_count == 3, "daily mode 4 draws three")
	check(game.mode == "daily", "daily scene")
	await snapshot("11-daily-game")
	game.profile.settings.left = true
	game.board.set_skins(game.profile)
	game.board.present(game.session.state, false)
	await click(game.board._p(game.board.stock_point))
	await create_timer(.8).timeout
	await snapshot("12-left-draw-three")
	print(JSON.stringify({"failures": failures, "viewport": [1080, 1920], "cards": game.board.cards.size()}))
	game.queue_free()
	preview.queue_free()
	await process_frame
	await process_frame
	quit(0 if failures.is_empty() else 1)
