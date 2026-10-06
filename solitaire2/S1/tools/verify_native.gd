extends SceneTree

var game: MasterGame
var failures: Array[String] = []
const EVIDENCE := "res://docs/native-evidence"

func _initialize() -> void:
	call_deferred("_run")

func check(condition: bool, message: String) -> void:
	if not condition:
		failures.append(message)
		push_error(message)

func screenshot(name: String) -> void:
	await process_frame
	RenderingServer.force_draw(false)
	root.get_texture().get_image().save_png(EVIDENCE + "/" + name + ".png")

func click(point: Vector2) -> void:
	var press := InputEventMouseButton.new()
	press.button_index = MOUSE_BUTTON_LEFT
	press.position = point
	press.pressed = true
	root.push_input(press, true)
	await process_frame
	var release := InputEventMouseButton.new()
	release.button_index = MOUSE_BUTTON_LEFT
	release.position = point
	release.pressed = false
	root.push_input(release, true)
	await process_frame

func _run() -> void:
	DirAccess.make_dir_recursive_absolute(EVIDENCE)
	game = load("res://scenes/master_main.tscn").instantiate()
	game.profile = SolitaireProfile.new("user://native_acceptance_profile.cfg")
	game.profile.settings.draw = 1
	game.profile.coins = 1000
	game.profile.free_coin_time = 0
	game.profile.settings.left = false
	root.add_child(game)
	await create_timer(3).timeout
	check(not game.busy, "initial deal completes")
	check(game.board.cards.size() == 52, "52 persistent card nodes")
	var instances := {}
	for id in game.board.cards:
		instances[id] = game.board.cards[id].get_instance_id()
	await screenshot("01-board")
	var stock_size := game.session.state.stock.size()
	await click(Vector2(519, 144))
	await create_timer(.7).timeout
	check(game.session.state.stock.size() == stock_size - 1, "mouse stock click draws one")
	game._undo()
	await create_timer(.7).timeout
	check(game.session.state.stock.size() == stock_size, "undo restores draw")
	for id in instances:
		check(game.board.cards[id].get_instance_id() == instances[id], "card persists through draw/undo %d" % id)
	game._action("btn_set")
	await create_timer(.4).timeout
	await screenshot("02-settings")
	var current_mode := game.session.state.draw_count
	game._action("btn_three_on")
	check(game.profile.settings.draw == 3, "draw-three preference changes")
	check(game.session.state.draw_count == current_mode, "mode change does not reset current game")
	game._action("btn_left_on")
	check(game.board.left, "left mode mirrors current board")
	await screenshot("03-left-mode")
	game._action("panel_rule")
	await create_timer(.4).timeout
	await screenshot("04-rules")
	game._close_modal()
	await create_timer(.3).timeout
	game._action("panel_statistics")
	await create_timer(.4).timeout
	await screenshot("05-statistics")
	game._close_all()
	game.paused = false
	game._action("btn_shop")
	await create_timer(.6).timeout
	await screenshot("06-shop")
	game._open_scene("FreeCoinLayer")
	await create_timer(.4).timeout
	await screenshot("07-free-coins")
	var button: BaseButton = game._active_modal.find_child("btn_guankan", true, false)
	check(button.disabled, "disabled ad provider has no available rewarded video")
	game._close_all()
	game.paused = false
	game.new_game(true, false)
	await create_timer(3).timeout
	check(game.session.state.draw_count == 3, "next game applies new draw mode")
	await screenshot("08-draw-three")
	# Actual animation event drives the visible face, independently of state.
	var card: MasterCard = game.board.cards[game.session.state.tableau[0].top().id]
	card.show_face(false)
	card.show_face(true, true)
	card.spine.animation_player.seek(.15, true)
	check(not card.spine.shown_face, "face remains back before flop event")
	card.spine.animation_player.advance(.06)
	check(card.spine.shown_face, "flop event switches to front")
	await screenshot("09-flip-mesh")
	await create_timer(.5).timeout
	# Use a controlled final state, then exercise the real commit -> win flow.
	game.session.state = FixtureStates.near_win()
	for i in 12:
		game.session.state.foundation[3].add_top(game.session.state.tableau[0].pop_top())
	game.board.present(game.session.state, false)
	game._commit(Move.tableau_to_foundation(0, 3))
	await create_timer(2.4).timeout
	check(game.settled, "final move triggers win settlement")
	await screenshot("10-win")
	var result := {"failed": failures.size(), "failures": failures, "persistent_cards": 52, "evidence": EVIDENCE}
	FileAccess.open(EVIDENCE + "/runtime.json", FileAccess.WRITE).store_string(JSON.stringify(result, "\t"))
	print("NATIVE_RUNTIME_RESULT ", JSON.stringify(result))
	game.queue_free()
	game = null
	await process_frame
	quit(0 if failures.is_empty() else 1)
