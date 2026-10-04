extends SceneTree
var game: InvincibleGame
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
	return parent.find_child(name, true, false) as Control

func snapshot(name: String) -> void:
	await RenderingServer.frame_post_draw
	var image := render_view.get_texture().get_image()
	check(image.get_size() == Vector2i(1080, 1920), "1080p: " + name)
	image.save_png("res://docs/invincible-evidence/" + name + ".png")

func overlap_pixels(reference: Image, current: Image, center: Vector2i) -> int:
	var changed := 0
	for x in range(center.x - 60, center.x + 60):
		for y in range(center.y - 85, center.y + 85):
			var a := reference.get_pixel(x, y)
			var b := current.get_pixel(x, y)
			# Original card-front pixels have alpha 253..255 in this region.
			if maxf(absf(a.r - b.r), maxf(absf(a.g - b.g), absf(a.b - b.b))) > 4.0 / 255:
				changed += 1
	return changed

func verify_overlap() -> void:
	game.board.hide()
	var proof := Node2D.new()
	proof.z_index = 950
	game.add_child(proof)
	var cards: Array[InvincibleCard] = []
	for i in 3:
		var card := InvincibleCard.new()
		proof.add_child(card)
		card.z_index = i
		card.position = Vector2(586 + i * 57, 383)
		card.configure([27, 10, 45][i], 0, 0)
		card.show_face(true, false)
		cards.append(card)
	cards[0].hide()
	cards[1].hide()
	await RenderingServer.frame_post_draw
	var reference := render_view.get_texture().get_image()
	cards[0].show()
	cards[1].show()
	await RenderingServer.frame_post_draw
	var fixed := overlap_pixels(reference, render_view.get_texture().get_image(), Vector2i(700, 383))
	check(fixed == 0, "overlapped artwork cannot change the front card's opaque pixels")
	# Positive control: restoring the old slot layers must reproduce the fault.
	for card in cards:
		for slot: Polygon2D in card.spine.slots.values():
			slot.z_index = slot.get_index()
	await RenderingServer.frame_post_draw
	var faulty := overlap_pixels(reference, render_view.get_texture().get_image(), Vector2i(700, 383))
	check(faulty > 100, "pixel check detects the reported layering regression")
	for card in cards:
		for slot: Polygon2D in card.spine.slots.values():
			slot.z_index = 0
	for i in 2:
		var card := InvincibleCard.new()
		proof.add_child(card)
		card.z_index = 10 + i
		card.position = Vector2(80, 639 + i * 66)
		card.configure(11 if i == 0 else 49, 0, 0)
		card.show_face(true, false)
	await snapshot("20-fixed-card-overlap")
	proof.queue_free()
	game.board.show()
	await process_frame

func verify_magic() -> void:
	print("VERIFY in-game magic")
	var previous := game.session.state.clone()
	var wand := button(game.game_ui, "Button_Shuffle")
	await click(wand)
	check(game.busy and game.get_node_or_null("MagicEffect") != null, "wand click starts original magic effect")
	check(game.profile.magic == 3 and game.session.state.content_equals(previous), "inventory and card state wait for native magic event")
	await snapshot("22-magic-windup")
	await click(wand)
	check(game.profile.magic == 2 and game.session.magic_used == 1, "repeated click consumes only one wand")
	check(game.session.state.move_count == previous.move_count + 1, "magic records one move")
	check(game.session.history.is_empty(), "magic clears undo history")
	await create_timer(.5).timeout
	await snapshot("23-magic-transfer")
	await create_timer(2).timeout
	check(not game.busy and game.get_node_or_null("MagicEffect") == null, "native magic effect and transfer finish")
	check(game.session.state.total_card_count() == 52, "magic preserves all cards")
	for id in game.board.layout:
		check(game.board.cards[id].position.distance_to(game.board.layout[id].pos) < 1, "magic settles every card position")
	check((button(game.game_ui, "Text_ShuffleNum_0") as Label).text == "2", "wand count updates in game HUD")
	var restored := InvincibleProfile.new("user://invincible_reported_bugs.cfg")
	check(restored.magic == 2 and restored.statistics.magic_used == 1, "wand consumption survives restart")
	await snapshot("24-magic-result")
	game.profile.magic = 0
	game.profile.coins = 70
	game.profile.save()
	previous = game.session.state.clone()
	await click(wand)
	check(game.dialogs.size() == 1, "empty inventory opens original magic shop from the game")
	var shop: InvincibleScene = game.dialogs.back()
	await click(button(shop, "btn_guankan0"))
	check(game.profile.magic == 0 and game.profile.coins == 70, "unavailable ad cannot award a wand")
	await click(button(shop, "btn_1000gold"))
	check(game.profile.magic == 1 and game.profile.coins == 0 and game.dialogs.is_empty(), "game shop charges 70 and returns to game")
	check(game.session.state.content_equals(previous), "buying a wand does not change the current deal")

func run() -> void:
	create_timer(90).timeout.connect(func():
		check(false, "graphical verification timed out")
		print(JSON.stringify({"checks": checks, "failures": failures}))
		quit(1))
	var test_path := "user://invincible_reported_bugs.cfg"
	DirAccess.remove_absolute(ProjectSettings.globalize_path(test_path))
	game = load("res://scenes/invincible_main.tscn").instantiate()
	game.profile = InvincibleProfile.new(test_path)
	# Standalone viewport keeps synthesized pointer hover local; a
	# SubViewportContainer delegates hover to the operating-system cursor.
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
	await verify_magic()
	print("VERIFY card overlap")
	await verify_overlap()
	for card: InvincibleCard in game.board.cards.values():
		for slot: Polygon2D in card.spine.slots.values():
			check(slot.z_index == 0, "Spine slot remains in card layer")
	await click(button(game.game_ui, "Button_pause"))
	print("VERIFY pause and calendar")
	check(game.dialogs.size() == 1, "pause opens by pointer")
	if game.dialogs.is_empty():
		finish(preview)
		return
	var pause: InvincibleScene = game.dialogs.back()
	for name in ["Text_NewGame", "Text_Again", "Text_game_daily", "Text_Lobby"]:
		var label := pause.find_child(name, true, false) as InvincibleLabel
		check((label.position + label.size / 2).distance_to(label.design_center) < 1, "caption center: " + name)
	await snapshot("13-fixed-pause")
	await click(button(pause, "Button_game_daily"))
	check(game.dialogs.size() == 2, "daily opens from pause by pointer")
	check(not pause.is_visible_in_tree(), "pause hidden under daily calendar")
	var daily: InvincibleScene = game.dialogs.back()
	check(daily.get_node_or_null("Panel_more/Node_2/Node_1/Image_1") is NinePatchRect, "original daily background survived duplicate names")
	check(daily.get_node_or_null("Panel_more/Node_2/Node_1__2/Panel_container") != null, "calendar content preserved separately")
	await snapshot("14-fixed-calendar")
	var stock_count := game.session.state.stock.size()
	await click(button(game.game_ui, "Button_setting"))
	check(game.dialogs.size() == 2 and game.session.state.stock.size() == stock_count, "modal blocks background input")
	await click(button(daily, "Button_close"))
	check(game.dialogs.size() == 1 and pause.is_visible_in_tree(), "daily close restores pause")
	await click(button(pause, "Button_Lobby"))
	check(not game.game_visible and game.dialogs.is_empty(), "aquarium lobby opens by pointer")
	game.profile.coins = 300
	game.profile.level = 5
	game.profile.save()
	await click(button(game.lobby, "Button_Mybag"))
	print("VERIFY wardrobe")
	check(game.dialogs.size() == 1, "palette opens original wardrobe")
	var bag: InvincibleScene = game.dialogs.back()
	await snapshot("15-wardrobe-backs")
	var content: Node = bag.find_child("ListView_bg", true, false).get_node("Content")
	check(content.get_child_count() == 35, "35 original card backs")
	await click(button(content.get_child(1), "Button_buy"))
	check(game.profile.coins == 150 and 1 in game.profile.skin_owned.back, "back purchase deducts once and persists ownership")
	await click(button(content.get_child(1), "Button_card_bg"))
	check(game.profile.settings.back == 1, "back selection applies to live cards")
	await click(button(bag, "Button_tab2"))
	check(content.get_child_count() == 6, "six face collections")
	await snapshot("16-wardrobe-faces")
	await click(button(content.get_child(0), "Button_zhengmian"))
	check(game.dialogs.size() == 2, "face collection detail opens")
	var detail: InvincibleScene = game.dialogs.back()
	check(detail.find_child("ListView_card", true, false).get_node("Content").get_child_count() == 52, "52 individual face cards")
	await snapshot("17-face-detail")
	await click(button(detail, "Button_card_item1_close"))
	await click(button(bag, "Button_tab5"))
	check(content.get_child_count() == 20, "twenty original music choices")
	await click(button(content.get_child(0), "Button_music_on"))
	check((bag.get_node("Wardrobe") as InvincibleWardrobe).preview.playing, "music preview plays original audio")
	await click(button(bag, "Button_tab4"))
	await click(button(content.get_child(0), "Button_magic"))
	check(game.dialogs.size() == 2, "magic purchase opens")
	var magic_before := game.profile.magic
	await click(button(game.dialogs.back(), "btn_1000gold"))
	check(game.profile.magic == magic_before + 1 and game.profile.coins == 80, "magic purchase costs original 70 coins")
	await click(button(bag, "Button_close"))
	await click(button(game.lobby, "Button_Sign"))
	print("VERIFY sign-in")
	check(game.dialogs.size() == 1, "gift opens original seven-day sign-in")
	var sign: InvincibleScene = game.dialogs.back()
	await snapshot("18-sign-in")
	var before := game.profile.coins
	await click(button(sign, "Button_get"))
	check(game.profile.coins == before + 14, "first-day sign-in gives original 14 coins")
	await click(button(sign, "Button_get"))
	check(game.profile.coins == before + 14, "sign-in cannot award twice")
	var saved := InvincibleProfile.new(test_path)
	check(saved.sign_data.claimed.has(1) and saved.settings.back == 1 and saved.coins == game.profile.coins, "restart preserves claim and skin selection")
	await click(button(sign, "Button_close"))
	game.profile.sign_data.day = 4
	game.profile.sign_data.claimed = [1, 2, 3]
	game.profile.sign_data.last_date = Time.get_date_string_from_system()
	await click(button(game.lobby, "Button_Sign"))
	sign = game.dialogs.back()
	await click(button(sign, "Button_get"))
	check(game.dialogs.size() == 2 and game.profile.sign_data.draws.size() == 3, "day four opens original three-card treasure reward")
	var draw: InvincibleScene = game.dialogs.back()
	print("VERIFY treasure entrance")
	var draw_animation := draw.get_node("AnimationPlayer") as AnimationPlayer
	if draw_animation.is_playing():
		await draw_animation.animation_finished
	await click(button(draw, "Button_open"))
	print("VERIFY treasure opened")
	await create_timer(.8).timeout
	check(game.profile.sign_data.draws.all(func(item: Dictionary): return bool(item.opened)), "treasure reveals every reward through pointer input")
	check((button(draw, "Button_get") as TextureButton).disabled, "treasure completion waits for the original reveal animation")
	await create_timer(3).timeout
	await snapshot("21-sign-treasure")
	check(not (button(draw, "Button_get") as TextureButton).disabled, "treasure completion enables after the reveal animations")
	await click(button(draw, "Button_get"))
	await click(button(sign, "Button_close"))
	# Resume the oldest unfinished batch before a later day's rewards.
	game.profile.sign_data.draws = [{"coins": 30, "opened": true}, {"coins": 2, "opened": false}, {"coins": 6, "opened": true}, {"coins": 100, "opened": false}, {"coins": 3, "opened": false}, {"coins": 7, "opened": false}]
	game.profile.save()
	game.profile.sign_data = InvincibleProfile.new(test_path).sign_data
	before = game.profile.coins
	await click(button(game.lobby, "Button_Sign"))
	sign = game.dialogs.front()
	for batch in 2:
		draw = game.dialogs.back()
		check(draw.get_meta("draw_indices") == [batch * 3, batch * 3 + 1, batch * 3 + 2], "pending treasure resumes oldest unfinished batch")
		draw_animation = draw.get_node("AnimationPlayer")
		if draw_animation.is_playing():
			await draw_animation.animation_finished
		await click(button(draw, "Button_open"))
		await create_timer(3.5).timeout
		await click(button(draw, "Button_get"))
	check(game.profile.coins == before + 112, "resumed treasures award only unopened rewards once")
	check(game.dialogs.size() == 1, "every pending treasure can finish and return to sign-in")
	await click(button(sign, "Button_close"))
	game.profile.tanks[0][0].hp = 20
	await click(button(game.lobby, "Button_weishi"))
	check(game.profile.tanks[0][0].hp == 50 and game.aquarium.feeding, "feeding restores 30 and runs native food animation")
	await snapshot("19-feeding")
	await create_timer(3).timeout
	check(not game.aquarium.feeding, "feeding animation finishes")
	finish(preview)

func finish(preview: Node) -> void:
	print(JSON.stringify({"checks": checks, "failures": failures, "viewport": [1080, 1920]}))
	preview.queue_free()
	await process_frame
	await process_frame
	quit(0 if failures.is_empty() else 1)
