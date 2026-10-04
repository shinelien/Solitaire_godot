class_name MasterGame
extends Control

## Native product loop. Domain rules remain pure data; this scene coordinates
## persistent cards, AnimationPlayer clips, input, UI scenes and service ports.
@onready var board: MasterBoard = $Board
@onready var ui: Control = $Interface
@onready var overlays: Control = $Overlays
@onready var background: TextureRect = $Background
@onready var audio: AudioStreamPlayer = $Sfx
@onready var ads: SolitaireAdService = $Ads
var profile := SolitaireProfile.new()
var session := MasterSession.new()
var elapsed := 0.0
var busy := true
var paused := false
var auto_active := false
var settled := false
var focus_paused := false
var _pressed: MasterCard
var _press_point := Vector2.ZERO
var _dragging := false
var _touch_index := -1
var _active_modal: Control
var _modal_stack: Array[Control] = []
var _ui_nodes: Dictionary = {}
var _shop: Control
var _shop_items: Dictionary = {}
var _shop_prices: Dictionary = {}
var _generation := 0
var _banner_height := 0.0
var _rewards_seen: Dictionary = {}

func _ready() -> void:
	_collect(ui, _ui_nodes)
	_shop_prices = JSON.parse_string(FileAccess.get_file_as_string("res://assets/master/data/ShopData.json"))
	for name in ["panel_set", "panel_pause", "panel_reset"]:
		_ui_nodes[name].hide()
	for name in ["btn_set", "btn_pause", "btn_game", "btn_shop", "btn_tips", "btn_reduction", "btn_auto", "btn_gift_lingqu", "btn_set_close", "btn_pause_close", "btn_pause_continue", "btn_reset_close", "btn_reset_replay", "btn_reset_new", "btn_three_on", "btn_left_on", "btn_music_on", "panel_rule", "panel_statistics"]:
		_bind(_ui_nodes[name], _action.bind(name))
	if _ui_nodes.has("btn_moreApp"):
		_ui_nodes.btn_moreApp.hide()
	ads.banner_height_changed.connect(_banner_changed)
	ads.reward_earned.connect(_ad_reward)
	ads.availability_changed.connect(func(_placement, _available): _update_reward_buttons())
	get_viewport().size_changed.connect(_layout_ui)
	_update_settings()
	_layout_ui()
	new_game(false, false)
	ads.show_banner()

func _collect(root: Node, into: Dictionary) -> void:
	into[str(root.name)] = root
	for child in root.get_children():
		_collect(child, into)

func _bind(node: Control, callable: Callable) -> void:
	if node is BaseButton:
		node.pressed.connect(callable)
	else:
		node.mouse_filter = Control.MOUSE_FILTER_STOP
		node.gui_input.connect(func(event):
			if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and not event.pressed:
				callable.call()
		)

func _text(node: Node, value: String) -> void:
	if node is Label or node is MasterAtlasNumber:
		node.text = value

func _process(delta: float) -> void:
	if not paused and not focus_paused and not settled and not busy:
		elapsed += delta
	_update_hud()

func _notification(what: int) -> void:
	if what == NOTIFICATION_APPLICATION_FOCUS_OUT:
		focus_paused = true
		if board != null and _pressed != null:
			_cancel_pointer()
	elif what == NOTIFICATION_APPLICATION_FOCUS_IN:
		focus_paused = false
	elif what == NOTIFICATION_WM_CLOSE_REQUEST:
		profile.save()

func _layout_ui() -> void:
	var content := get_viewport_rect().size
	background.size = content
	# Preserve master 576x1024 geometry; extra height extends only the background
	# and positions the bottom toolbar. Safe insets are mapped to canvas units.
	var inset_top := 0.0
	var inset_bottom := 0.0
	if OS.has_feature("mobile"):
		var safe := DisplayServer.get_display_safe_area()
		var window_size := DisplayServer.window_get_size()
		var factor := content.x / maxf(1, window_size.x)
		inset_top = safe.position.y * factor
		inset_bottom = maxf(0, window_size.y - safe.end.y) * factor
	board.position.y = inset_top
	ui.position.y = inset_top
	var bottom: Control = _ui_nodes.get("panel_bottom")
	if bottom != null:
		bottom.position.y = content.y - inset_top - inset_bottom - _banner_height - bottom.size.y
	overlays.position.y = inset_top

func _banner_changed(height: float) -> void:
	_banner_height = maxf(0, height)
	_layout_ui()

func _sound(name: String) -> void:
	if not profile.settings.sound:
		return
	var path := "res://assets/master/music/%s.mp3" % name
	if ResourceLoader.exists(path):
		audio.stream = load(path)
		audio.play()

func new_game(replay: bool, count_previous := true) -> void:
	_generation += 1
	var generation := _generation
	auto_active = false
	busy = true
	_cancel_pointer()
	board.clear_hint()
	if count_previous and not settled and session.state != null:
		profile.settle(session.state.draw_count, false, session.state.score, int(elapsed), session.state.move_count, session.used_undo)
	_close_all()
	settled = false
	paused = false
	elapsed = 0
	# In master the draw setting explicitly applies to the next game.
	session.start(int(profile.settings.draw), replay)
	board.set_skins(profile)
	_update_background()
	_sound("shuffle")
	_update_hud()
	await board.deal(session.state)
	if generation != _generation:
		return
	busy = false
	ads.request_interstitial("new_game")

func _update_background() -> void:
	var skin := int(profile.settings.background)
	background.texture = load("res://assets/master/game/background-%d.png" % (0 if skin <= 2 else skin))
	background.modulate = [Color8(29, 121, 62), Color8(147, 41, 41), Color8(0, 101, 151)][skin] if skin <= 2 else Color.WHITE

func _update_hud() -> void:
	if session.state == null or _ui_nodes.is_empty():
		return
	_text(_ui_nodes.atlasLabel_score, str(session.state.score))
	_text(_ui_nodes.atlasLabel_moveNum, str(session.state.move_count))
	_text(_ui_nodes.atlasLabel_time, _clock(int(elapsed)))
	_text(_ui_nodes.atlasLabel_waitnum, str(session.state.stock.size()))
	_ui_nodes.img_waitnum.visible = not session.state.stock.is_empty()
	_ui_nodes.img_waitnum.position.x = (57 if profile.settings.left else 519) - _ui_nodes.img_waitnum.pivot_offset.x
	_ui_nodes.btn_auto.visible = session.can_auto() and not auto_active and not settled
	_ui_nodes.panel_gift.visible = profile.free_coins_remaining() == 0 and not settled

func _clock(seconds: int) -> String:
	return "%02d/%02d" % [seconds / 60, seconds % 60]

func _update_settings() -> void:
	for pair in [["btn_three_on", profile.settings.draw == 3], ["btn_left_on", profile.settings.left], ["btn_music_on", profile.settings.sound]]:
		var button: TextureButton = _ui_nodes[pair[0]]
		button.texture_normal = load("res://assets/master/img/img_music_%s.png" % ("on" if pair[1] else "off"))
		button.texture_pressed = button.texture_normal
	# Original left-hand mode also mirrors toolbar controls, including captions.
	for name in ["btn_set", "btn_shop", "btn_game", "btn_tips", "btn_reduction"]:
		var button: Control = _ui_nodes[name]
		if not button.has_meta("master_x"):
			button.set_meta("master_x", button.position.x)
		button.position.x = 576 - float(button.get_meta("master_x")) - button.size.x if profile.settings.left else float(button.get_meta("master_x"))

func _action(name: String) -> void:
	if busy and name not in ["btn_pause_close", "btn_pause_continue"]:
		return
	_sound("click")
	match name:
		"btn_set": _open_builtin("panel_set", "img_set")
		"btn_pause":
			paused = true
			_open_builtin("panel_pause", "img_pause")
		"btn_game": _open_builtin("panel_reset", "img_reset")
		"btn_set_close", "btn_pause_close", "btn_pause_continue", "btn_reset_close": _close_modal()
		"btn_reset_replay": new_game(true)
		"btn_reset_new": new_game(false)
		"btn_three_on":
			profile.settings.draw = 3 if profile.settings.draw == 1 else 1
			profile.save()
			_update_settings()
		"btn_music_on":
			profile.settings.sound = not profile.settings.sound
			if not profile.settings.sound:
				audio.stop()
			profile.save()
			_update_settings()
		"btn_left_on":
			profile.settings.left = not profile.settings.left
			profile.save()
			_update_settings()
			board.set_skins(profile)
			board.present(session.state, false)
		"panel_rule": _open_scene("RuleLayer")
		"panel_statistics": _open_scene("CountLayer")
		"btn_shop": _open_shop()
		"btn_gift_lingqu": _open_scene("FreeCoinLayer")
		"btn_reduction": _undo()
		"btn_tips": _hint()
		"btn_auto": _auto()

func _open_builtin(panel: String, content: String) -> void:
	_push_modal(_ui_nodes[panel])
	_animate_dialog(_active_modal, _ui_nodes[content])

func _push_modal(modal: Control) -> void:
	_cancel_pointer()
	board.clear_hint()
	if _active_modal != null:
		_modal_stack.append(_active_modal)
	_active_modal = modal
	modal.show()
	modal.mouse_filter = Control.MOUSE_FILTER_STOP
	# A dialog blocks the board even if its imported children ignore mouse input.
	paused = true

func _animate_dialog(modal: Control, body: Control, slide := false) -> void:
	var target := body.position
	modal.modulate.a = 0.0
	if slide:
		body.position.y += 1024
	else:
		body.scale = Vector2.ONE * 1.2
	var tween := create_tween().set_parallel(true)
	tween.tween_property(modal, "modulate:a", 1.0, .2)
	if slide:
		tween.tween_property(body, "position", target, .4)
	else:
		tween.tween_property(body, "scale", Vector2.ONE, .2).set_trans(Tween.TRANS_BACK).set_ease(Tween.EASE_OUT)

func _close_modal() -> void:
	if _active_modal == null:
		return
	var modal := _active_modal
	_active_modal = _modal_stack.pop_back() if not _modal_stack.is_empty() else null
	var tween := create_tween()
	tween.tween_property(modal, "modulate:a", 0.0, .2)
	tween.tween_callback(func():
		modal.hide()
		modal.modulate.a = 1.0
		if modal.get_parent() == overlays and modal != _shop:
			modal.queue_free()
	)
	paused = _active_modal != null
	if not paused:
		ads.hide_banner()
		ads.show_banner()

func _close_all() -> void:
	for name in ["panel_set", "panel_pause", "panel_reset"]:
		_ui_nodes[name].hide()
	for child in overlays.get_children():
		if child == _shop:
			child.hide()
		else:
			child.queue_free()
	_active_modal = null
	_modal_stack.clear()

func _open_scene(scene_name: String) -> Control:
	var modal: Control = load("res://scenes/native/%s.tscn" % scene_name).instantiate()
	overlays.add_child(modal)
	var nodes := {}
	_collect(modal, nodes)
	for child in modal.get_children():
		if child is Control:
			child.show()
	for close in ["btn_close", "btn_coin_close"]:
		if nodes.has(close):
			_bind(nodes[close], _close_modal)
	_push_modal(modal)
	var body: Control = nodes.get({"RuleLayer": "panel_rule", "CountLayer": "panel_count", "FreeCoinLayer": "img_freecoin", "CoinLayer": "img_coin", "WinLayer": "panel_win"}.get(scene_name, ""), modal)
	_animate_dialog(modal, body)
	match scene_name:
		"RuleLayer", "CountLayer":
			if nodes.has("btn_close"):
				_button_caption(nodes.btn_close, "返回")
			if scene_name == "CountLayer":
				_populate_statistics(nodes)
		"FreeCoinLayer":
			_bind(nodes.btn_lingqu, _claim_free)
			_bind(nodes.btn_guankan, _request_reward.bind("double_free_coins"))
			nodes.btn_lingqu.disabled = profile.free_coins_remaining() > 0
			nodes.btn_guankan.disabled = not ads.is_available("double_free_coins") or profile.free_coins_remaining() > 0
			if not ads.is_available("double_free_coins"):
				_text(nodes.text_guankan, "暂无视频")
		"CoinLayer":
			_bind(nodes.btn_freecoin, _open_scene.bind("FreeCoinLayer"))
			_bind(nodes.btn_ads, _request_reward.bind("coin_shop"))
			nodes.btn_ads.disabled = not ads.is_available("coin_shop")
			nodes.btn_freecoin.disabled = profile.free_coins_remaining() > 0
			_text(nodes.atlasLabel_time, _clock(profile.free_coins_remaining()))
		"WinLayer":
			_bind(nodes.btn_new, new_game.bind(false))
	return modal

func _button_caption(button: Control, caption: String) -> void:
	var label := Label.new()
	label.text = caption
	label.mouse_filter = Control.MOUSE_FILTER_IGNORE
	label.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
	label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
	label.add_theme_font_override("font", preload("res://assets/master/chinese.tres"))
	label.add_theme_font_size_override("font_size", 24)
	button.add_child(label)

func _populate_statistics(nodes: Dictionary) -> void:
	for mode in [1, 3]:
		var panel: Node = nodes["panel_num_%d" % (1 if mode == 1 else 2)]
		var values: Array = profile.statistics[str(mode)]
		for i in 12:
			var label := panel.find_child("atlasLabel_%d" % (i + 1), true, false)
			_text(label, _clock(values[i]) if i in [3, 4, 11] else ("%.1f" % values[i] if i == 2 else str(values[i])))

func _open_shop() -> void:
	if _shop == null:
		_shop = load("res://scenes/native/ShopLayer.tscn").instantiate()
		overlays.add_child(_shop)
		var nodes := {}
		_collect(_shop, nodes)
		_bind(nodes.btn_shop_close, _close_modal)
		_bind(nodes.btn_add, _open_scene.bind("CoinLayer"))
		for category in ["background", "face", "back"]:
			var scroll: ScrollContainer = nodes[{"background": "scrollView_bg", "face": "scrollView_face", "back": "scrollView_cardbg"}[category]]
			var content: Control = scroll.get_node("Content")
			var prices: Array = _shop_prices[{"background": "gamebgprice", "face": "cardfaceprice", "back": "cardbgprice"}[category]]
			content.custom_minimum_size = Vector2(prices.size() * 145, 180)
			_shop_items[category] = []
			for i in prices.size():
				var item: Control = load("res://scenes/native/ItemNode.tscn").instantiate()
				content.add_child(item)
				item.position = Vector2(70 + i * 145, 90)
				var parts := {}
				_collect(item, parts)
				var filename: String = {"background": "game_bg_%d.png", "face": "card_%d_13_0.png", "back": "card_bg_%d.png"}[category] % i
				parts.img_card.texture = load("res://assets/master/frames/" + filename)
				_bind(parts.img_card, _shop_select.bind(category, i))
				parts.img_new.hide()
				parts.img_light_1.hide()
				parts.img_light_2.hide()
				_shop_items[category].append(parts)
	var nodes := {}
	_collect(_shop, nodes)
	nodes.panel_shop.show()
	_push_modal(_shop)
	_animate_dialog(_shop, nodes.img_shop, true)
	_refresh_shop()

func _refresh_shop() -> void:
	if _shop == null:
		return
	_text(_shop.find_child("atlasLabel_coin", true, false), str(profile.coins))
	for category in _shop_items:
		var prices: Array = _shop_prices[{"background": "gamebgprice", "face": "cardfaceprice", "back": "cardbgprice"}[category]]
		for i in _shop_items[category].size():
			var parts: Dictionary = _shop_items[category][i]
			var owned: bool = i in profile.unlocked[category]
			var selected: bool = i == int(profile.settings[category])
			parts.img_coin.visible = not owned
			parts.atlasLabel_num.visible = not owned
			_text(parts.atlasLabel_num, str(prices[i]))
			parts.atlasLabel_num.modulate = Color.RED if profile.coins < int(prices[i]) else Color.WHITE
			parts.text_item.visible = owned
			_text(parts.text_item, "使用中" if selected else "已获得")
			parts.img_light_1.visible = selected
			parts.img_light_2.visible = selected
			if selected and not parts.img_light_1.has_meta("spinning"):
				parts.img_light_1.set_meta("spinning", true)
				var tween: Tween = parts.img_light_1.create_tween().set_loops()
				tween.tween_property(parts.img_light_1, "rotation", TAU, 10).as_relative()

func _shop_select(category: String, index: int) -> void:
	var prices: Array = _shop_prices[{"background": "gamebgprice", "face": "cardfaceprice", "back": "cardbgprice"}[category]]
	if not index in profile.unlocked[category]:
		var price := int(prices[index])
		if profile.coins < price:
			_toast("金币不足")
			return
		profile.coins -= price
		profile.unlocked[category].append(index)
		_toast("购买成功")
	else:
		profile.settings[category] = index
		board.set_skins(profile)
		_update_background()
	profile.save()
	_refresh_shop()

func _claim_free() -> void:
	if profile.claim_free_coins():
		_sound("coin")
		_close_modal()
		_refresh_shop()
		_toast("获得金币500")

func _request_reward(placement: String) -> void:
	ads.request_rewarded(placement)

func _ad_reward(placement: String, request_id: int) -> void:
	var key := "%s:%d" % [placement, request_id]
	if _rewards_seen.has(key):
		return
	if placement == "double_free_coins":
		if not profile.claim_free_coins():
			return
		profile.coins += 500
	elif placement == "coin_shop":
		profile.coins += 500
	else:
		return
	_rewards_seen[key] = true
	profile.save()
	_refresh_shop()
	_update_reward_buttons()

func _update_reward_buttons() -> void:
	if _active_modal == null:
		return
	var nodes := {}
	_collect(_active_modal, nodes)
	if nodes.has("btn_guankan"):
		nodes.btn_guankan.disabled = not ads.is_available("double_free_coins") or profile.free_coins_remaining() > 0
	if nodes.has("btn_ads"):
		nodes.btn_ads.disabled = not ads.is_available("coin_shop")

func _toast(message: String) -> void:
	var toast: Control = load("res://scenes/native/TipsNode.tscn").instantiate()
	add_child(toast)
	toast.position = Vector2(288, 512)
	toast.z_index = 2000
	_text(toast.find_child("text_tips", true, false), message)
	toast.modulate.a = 0
	var tween := toast.create_tween()
	tween.tween_property(toast, "modulate:a", 1.0, .1)
	tween.tween_interval(.2)
	tween.set_parallel(true)
	tween.tween_property(toast, "modulate:a", 0.0, .8)
	tween.tween_property(toast, "position:y", 554.0, .8)
	tween.chain().tween_callback(toast.queue_free)

func _input(event: InputEvent) -> void:
	# Capture a held pointer's motion/release even when it crosses GUI controls.
	if _pressed == null:
		return
	if event is InputEventMouseMotion and _touch_index == -1:
		_pointer_move(event.position)
		get_viewport().set_input_as_handled()
	elif event is InputEventScreenDrag and event.index == _touch_index:
		_pointer_move(event.position)
		get_viewport().set_input_as_handled()
	elif event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and not event.pressed and _touch_index == -1:
		_pointer_release(event.position)
		get_viewport().set_input_as_handled()
	elif event is InputEventScreenTouch and not event.pressed and event.index == _touch_index:
		_pointer_release(event.position)
		get_viewport().set_input_as_handled()

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed and event.keycode == KEY_ESCAPE:
		if _active_modal != null:
			_close_modal()
		elif not busy:
			_action("btn_pause")
		return
	if busy or paused or focus_paused or settled or _pressed != null:
		return
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
		_touch_index = -1
		_pointer_press(event.position)
	elif event is InputEventScreenTouch and event.pressed:
		_touch_index = event.index
		_pointer_press(event.position)

func _pointer_press(point: Vector2) -> void:
	var local := point - board.position
	if board.stock_contains(local):
		var move := InputInterpreter.stock_click_move(session.state)
		if move != null:
			_commit(move)
		return
	_pressed = board.hit(local, session.state)
	_press_point = local
	_dragging = false

func _pointer_move(point: Vector2) -> void:
	if _pressed == null:
		return
	var local := point - board.position
	if not _dragging and local.distance_to(_press_point) > 1:
		board.begin_drag(_pressed, _press_point)
		_dragging = true
	if _dragging:
		board.drag_to(local)

func _pointer_release(_point: Vector2) -> void:
	if _pressed == null:
		return
	var card := _pressed
	_pressed = null
	var move: Move
	if _dragging:
		var target := board.drop_target(card.position, card)
		move = InputInterpreter.build_drag_move(session.state, card.source, target)
		board.end_drag()
	else:
		move = InputInterpreter.auto_find_move(session.state, card.source)
	_dragging = false
	_touch_index = -1
	if move != null and RulesEngine.validate(session.state, move).ok:
		_commit(move)
	else:
		board.present(session.state)
		card.reject()
		_sound("nomove")

func _cancel_pointer() -> void:
	if board == null:
		return
	board.end_drag()
	_pressed = null
	_dragging = false
	_touch_index = -1
	if session.state != null:
		board.present(session.state, false)

func _commit(move: Move) -> void:
	if busy or settled:
		return
	var result := session.apply(move)
	if not result.ok:
		_sound("nomove")
		return
	busy = true
	_sound("movecard")
	var duration := board.present(session.state)
	_update_hud()
	await get_tree().create_timer(duration).timeout
	board.settle_layers()
	busy = false
	if session.state.game_status == GameState.GameStatus.WON:
		_win()

func _undo() -> void:
	if not session.undo():
		_sound("nomove")
		return
	busy = true
	_sound("undo")
	var duration := board.present(session.state)
	await get_tree().create_timer(duration).timeout
	board.settle_layers()
	busy = false

func _hint() -> void:
	var hints := session.hint_options()
	if hints.is_empty():
		_toast("没有有效移动")
		return
	busy = true
	var shade := ColorRect.new()
	shade.color = Color(0, 0, 0, .5)
	shade.mouse_filter = Control.MOUSE_FILTER_IGNORE
	shade.size = get_viewport_rect().size
	shade.z_index = 800
	add_child(shade)
	for move in hints:
		board.hint(move, session.state)
		await get_tree().create_timer(2).timeout
	board.clear_hint()
	shade.queue_free()
	busy = false

func _auto() -> void:
	var plan := session.auto_plan()
	if not plan.eligible or plan.moves.is_empty():
		return
	auto_active = true
	_sound("autoplay")
	for move in plan.moves:
		if not auto_active or settled:
			break
		_commit(move)
		while busy:
			await get_tree().process_frame
	auto_active = false

func _win() -> void:
	if settled:
		return
	settled = true
	auto_active = false
	_sound("victory")
	var reward := profile.settle(session.state.draw_count, true, session.state.score, int(elapsed), session.state.move_count, session.used_undo)
	await get_tree().create_timer(.2).timeout
	var modal := _open_scene("WinLayer")
	var nodes := {}
	_collect(modal, nodes)
	var best: Array = profile.statistics[str(session.state.draw_count)]
	for pair in [["atlasLabel_you_score", str(session.state.score)], ["atlasLabel_you_time", _clock(int(elapsed))], ["atlasLabel_you_movetime", str(session.state.move_count)], ["atlasLabel_best_score", str(best[8])], ["atlasLabel_best_time", _clock(best[3])], ["atlasLabel_best_movetime", str(best[5])], ["atlasLabel_coinnum", str(reward)]]:
		_text(nodes[pair[0]], pair[1])
	for i in 7:
		var panel: Control = nodes["panel_%d" % i]
		panel.show()
		panel.modulate.a = 0
		var tween := panel.create_tween()
		tween.tween_interval(i * .2)
		tween.tween_property(panel, "modulate:a", 1.0, .2)
	ads.request_interstitial("victory")
