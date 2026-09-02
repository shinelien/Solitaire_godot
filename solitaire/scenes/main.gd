extends Control

## Main scene root. Wires Application (GameController) to the Presentation
## (BoardView, InputHandler) and the minimal HUD. View layer only renders
## GameState and forwards intents; it never mutates state.

const BOARD_VIEW := preload("res://presentation/board/board_view.gd")
const INPUT_HANDLER := preload("res://presentation/input/input_handler.gd")

var controller: GameController
var board: Control
var input: Control
var status_label: Label
var draw1_button: Button
var draw3_button: Button
var hint_source_key := ""

func _ready() -> void:
	controller = GameController.new()
	controller.state_changed.connect(_on_state_changed)
	controller.message.connect(_on_message)

	board = BOARD_VIEW.new()
	board.name = "Board"
	add_child(board)
	_set_full_rect(board)
	board.attach(controller)

	input = INPUT_HANDLER.new()
	input.name = "Input"
	add_child(input)
	_set_full_rect(input)
	input.set_controller(controller)
	input.set_board(board)

	_build_hud()

	var smoke := OS.get_environment("SOLITAIRE_SMOKE")
	if smoke != "":
		_smoke_script.call_deferred(smoke)
	else:
		controller.new_deal(GameConfig.DRAW1, -1, "")

func _set_full_rect(node: Control) -> void:
	node.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)

func _build_hud() -> void:
	var bar := VBoxContainer.new()
	bar.name = "HUD"
	bar.add_theme_constant_override("separation", 4)
	var btn_row := HBoxContainer.new()
	btn_row.add_theme_constant_override("separation", 6)
	bar.add_child(btn_row)

	var new_deal := Button.new()
	new_deal.text = "New Deal"
	new_deal.pressed.connect(controller.request_new_deal)
	btn_row.add_child(new_deal)

	var undo := Button.new()
	undo.text = "Undo"
	undo.pressed.connect(controller.request_undo)
	btn_row.add_child(undo)

	var hint := Button.new()
	hint.text = "Hint"
	hint.pressed.connect(_on_hint_pressed)
	btn_row.add_child(hint)

	var auto := Button.new()
	auto.text = "Auto Complete"
	auto.pressed.connect(controller.request_auto_complete)
	btn_row.add_child(auto)

	var replay := Button.new()
	replay.text = "Replay"
	replay.pressed.connect(controller.request_replay)
	btn_row.add_child(replay)

	draw1_button = Button.new()
	draw1_button.text = "Draw-1"
	draw1_button.toggle_mode = true
	draw1_button.pressed.connect(func() -> void: controller.set_draw_mode(GameConfig.DRAW1))
	btn_row.add_child(draw1_button)

	draw3_button = Button.new()
	draw3_button.text = "Draw-3"
	draw3_button.toggle_mode = true
	draw3_button.pressed.connect(func() -> void: controller.set_draw_mode(GameConfig.DRAW3))
	btn_row.add_child(draw3_button)

	status_label = Label.new()
	status_label.text = ""
	status_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	bar.add_child(status_label)

	add_child(bar)
	bar.set_anchors_preset(Control.PRESET_BOTTOM_WIDE)
	bar.offset_top = -110
	bar.offset_bottom = -4
	bar.offset_left = 8
	bar.offset_right = -8

func _on_hint_pressed() -> void:
	board.clear_highlights()
	hint_source_key = ""
	var m := controller.request_hint()
	if m == null:
		_on_message("No legal move available")
		return
	_on_message(KlondikeRules.describe_move(controller.state, m))
	var key := _hint_key_for(m)
	if key != "":
		hint_source_key = key
		board.set_hint_key(key)

func _hint_key_for(m: Move) -> String:
	if m.type != Move.MoveType.MOVE_CARD:
		return ""
	if m.from_pile.type == PileType.WASTE:
		return "waste"
	if m.from_pile.type == PileType.FOUNDATION:
		return "fnd%d" % m.from_pile.index
	if m.from_pile.type == PileType.TABLEAU:
		return "tab%d_%d" % [m.from_pile.index, m.from_index]
	return ""

func _on_state_changed(state: GameState) -> void:
	if state == null:
		return
	board.refresh(state)
	draw1_button.button_pressed = (state.draw_mode == GameConfig.DRAW1)
	draw3_button.button_pressed = (state.draw_mode == GameConfig.DRAW3)
	if state.status == GameStatus.Status.WON:
		_on_message("You won! Foundations complete.")
	elif hint_source_key != "" and not _hint_still_valid(state):
		hint_source_key = ""
		board.clear_highlights()

func _hint_still_valid(state: GameState) -> bool:
	if hint_source_key == "":
		return false
	for key in _hint_keys_current(state):
		if key == hint_source_key:
			return true
	return false

func _hint_keys_current(state: GameState) -> Array[String]:
	var keys: Array[String] = []
	keys.push_back("waste")
	for i in PileType.FOUNDATION_COUNT:
		keys.push_back("fnd%d" % i)
	for c in PileType.TABLEAU_COUNT:
		for j in state.col(c).size():
			keys.push_back("tab%d_%d" % [c, j])
	return keys

func _on_message(text: String) -> void:
	if status_label != null:
		status_label.text = text

func _smoke_script(env: String) -> void:
	# Bounded scripted play used by the smoke run (SOLITAIRE_SMOKE=1).
	print("[smoke] start")
	if not controller.new_deal(GameConfig.DRAW1, 0, ""):
		print("[smoke] FAIL new_deal")
		return
	var ok := true
	ok = controller.request_draw() and ok
	if not controller.request_undo():
		ok = false
	ok = controller.request_stock_action() and ok
	ok = controller.request_new_deal() and ok
	ok = controller.request_replay() and ok
	ok = controller.set_draw_mode(GameConfig.DRAW3) and ok
	controller.request_auto_complete()  # may safely stall with no foundation move
	var m := controller.request_hint()
	if controller.state != null:
		var errs := controller.state.invariant_errors()
		if not errs.is_empty():
			print("[smoke] FAIL invariants: %s" % str(errs))
			return
	print("[smoke] end ok=%s moves=%d" % [str(ok), controller.state.move_count])
