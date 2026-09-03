class_name SolitaireDirector
extends Node

## Application/presentation controller for the pure-2D loop (WP-08).
##
## The Director owns the GameSession (a RefCounted; it is never a scene state)
## and converts every pointer/button intent into an explicit Move (via
## InputInterpreter) or an existing session boundary, then rerenders the board
## strictly from session.state_snapshot(). It never edits GameState/CardData/
## piles directly and never duplicates rule legality: attempted moves are
## validated by MoveExecutor inside the session. CardView/BoardView only
## render/forward; all game semantics stay in Core/Application.
##
## `mcp_debug_load_fixture()` is an explicit, documented non-production seam
## used only by MCP runtime acceptance to load controlled boards through the
## application layer; no player path can reach it, and it is hard-gated to the
## editor feature so a release build always refuses fixture/session injection.

const POOL_DEFAULT := "bureau1"
const DEAL_INDEX_DEFAULT := 0

const P_BOARD := "../Board"
const P_UI := "../UI"
const P_WIN := "../WinOverlay"

const SND_DEAL := "res://assets/legacy/audio/deal.mp3"
const SND_MOVECARD := "res://assets/legacy/audio/movecard.mp3"
const SND_NOMOVE := "res://assets/legacy/audio/nomove.mp3"
const SND_UNDO := "res://assets/legacy/audio/undo.mp3"
const SND_AUTO := "res://assets/legacy/audio/auto.mp3"
const SND_VICTORY := "res://assets/legacy/audio/victory.mp3"

const DRAG_THRESHOLD := 14.0
const AUTO_STEP_SEC := 0.06
const HINT_SECONDS := 1.4

const FIXTURE_NAMES := ["near_win", "near_win_waste_ace", "ops_state"]

var _session: GameSession = null
var _state: GameState = null
var _board: BoardView = null
var _ui: Control = null
var _sfx: AudioStreamPlayer = null
var _win_overlay: Control = null

var _info_label: Label = null
var _status_label: Label = null
var _buttons: Dictionary = {}

var _press: Dictionary = {}
var _drag_active := false
var _hint_timer := -1.0
var _auto_moves: Array[Move] = []
var _auto_index := 0
var _auto_active := false
var _auto_accum := 0.0
var _msg := ""

var _sounds: Dictionary = {}
var _win_label: Label = null
var _applied_safe: Rect2 = Rect2()


func _ready() -> void:
	_board = get_node_or_null(P_BOARD)
	_ui = get_node_or_null(P_UI)
	_sfx = get_node_or_null("../Sfx")
	_win_overlay = get_node_or_null(P_WIN)
	_build_ui_content()
	_build_win_overlay()
	_connect_buttons()
	if _ui != null:
		_ui.resized.connect(_layout_ui)
	if _board != null:
		_board.resized.connect(_on_board_resized)
	var win := get_window()
	if win != null and not win.size_changed.is_connected(_on_window_size_changed):
		win.size_changed.connect(_on_window_size_changed)
	_start_default_session()
	_msg = "准备就绪"
	call_deferred("_layout_ui")
	call_deferred("_refresh")


func _on_board_resized() -> void:
	_apply_current_safe_rect()
	if _state != null:
		_refresh()


func _on_window_size_changed() -> void:
	_layout_ui()


func _build_ui_content() -> void:
	if _ui == null:
		return
	_ui.mouse_filter = Control.MOUSE_FILTER_IGNORE
	_info_label = _ui.get_node_or_null("InfoLabel")
	if _info_label == null:
		_info_label = Label.new()
		_info_label.name = "InfoLabel"
		_info_label.mouse_filter = Control.MOUSE_FILTER_IGNORE
		_info_label.add_theme_font_size_override("font_size", 26)
		_ui.add_child(_info_label)
	_status_label = _ui.get_node_or_null("StatusLabel")
	if _status_label == null:
		_status_label = Label.new()
		_status_label.name = "StatusLabel"
		_status_label.mouse_filter = Control.MOUSE_FILTER_IGNORE
		_status_label.add_theme_font_size_override("font_size", 26)
		_ui.add_child(_status_label)
	var definitions := {
		"Draw1Button": "Draw 1",
		"Draw3Button": "Draw 3",
		"UndoButton": "Undo",
		"HintButton": "Hint",
		"AutoButton": "Auto",
		"ReplayButton": "Replay",
		"NewDealButton": "New Deal",
	}
	for key in definitions:
		if _ui.get_node_or_null(key) != null:
			continue
		var button := Button.new()
		button.name = key
		button.text = definitions[key]
		button.add_theme_font_size_override("font_size", 26)
		button.mouse_filter = Control.MOUSE_FILTER_STOP
		_ui.add_child(button)


func _build_win_overlay() -> void:
	if _win_overlay == null:
		return
	_win_overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
	if _win_overlay.get_node_or_null("WinLabel") == null:
		var shade := ColorRect.new()
		shade.name = "WinShade"
		shade.color = Color(0, 0, 0, 0.42)
		shade.mouse_filter = Control.MOUSE_FILTER_IGNORE
		shade.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
		_win_overlay.add_child(shade)
		var label := Label.new()
		label.name = "WinLabel"
		label.text = "YOU WIN!"
		label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
		label.vertical_alignment = VERTICAL_ALIGNMENT_CENTER
		label.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
		label.add_theme_font_size_override("font_size", 96)
		label.modulate = Color(1, 0.85, 0.2)
		_win_overlay.add_child(label)
	_win_label = _win_overlay.get_node_or_null("WinLabel") as Label
	_win_overlay.visible = false


func _start_default_session() -> void:
	var result := GameSession.create(POOL_DEFAULT, DEAL_INDEX_DEFAULT, GameState.DRAW1)
	if not result.ok:
		_msg = "发牌失败: %s %s" % [result.error_code, result.error_message]
		return
	_session = result.session
	_play_sound(SND_DEAL)


func _connect_buttons() -> void:
	var names := {
		"Draw1Button": Callable(self, "_on_draw1"),
		"Draw3Button": Callable(self, "_on_draw3"),
		"UndoButton": Callable(self, "_on_undo"),
		"HintButton": Callable(self, "_on_hint"),
		"AutoButton": Callable(self, "_on_auto"),
		"ReplayButton": Callable(self, "_on_replay"),
		"NewDealButton": Callable(self, "_on_new_deal"),
	}
	for key in names:
		var button := _ui.get_node_or_null(key) if _ui != null else null
		if button != null and not button.pressed.is_connected(names[key]):
			button.pressed.connect(names[key])
			_buttons[key] = button


func _layout_ui() -> void:
	_apply_current_safe_rect()
	if _ui == null:
		return
	var h := _ui.size.y
	var w := _ui.size.x
	var button_w := 132
	var button_h := 60
	var gap := 8
	var total := 7 * button_w + 6 * gap
	var x0 := int((w - total) / 2.0)
	var y0 := h - 84.0
	var order := [
		"Draw1Button", "Draw3Button", "UndoButton",
		"HintButton", "AutoButton", "ReplayButton", "NewDealButton",
	]
	for i in order.size():
		var key: String = order[i]
		var button: Button = _buttons.get(key)
		if button == null:
			continue
		button.set_position(Vector2(x0 + i * (button_w + gap), y0))
		button.set_size(Vector2(button_w, button_h))
	if _info_label != null:
		_info_label.set_position(Vector2(16, h - 196.0))
	if _status_label != null:
		_status_label.set_position(Vector2(16, h - 150.0))


# ----- safe-area content rect (WP-08 correction 1) -----

## Current canvas coordinate content size (design 1080x1920 base; follows the
## actual root canvas when running).
func _content_size() -> Vector2:
	var vp := get_viewport()
	if vp != null and vp.get_visible_rect().size.x > 0.0:
		return vp.get_visible_rect().size
	return Vector2(1080, 1920)


## Device-safe area mapped into canvas coordinates (full window == identity).
func _current_safe_rect(content: Vector2) -> Rect2:
	var win := get_window()
	var device_window: Rect2
	var safe_device: Rect2
	if win != null and not DisplayServer.get_name().is_empty():
		device_window = Rect2(win.position, win.size)
	else:
		device_window = Rect2(
			DisplayServer.window_get_position(),
			Vector2(DisplayServer.window_get_size())
		)
	safe_device = DisplayServer.get_display_safe_area()
	return SafeAreaLayout.content_safe_rect(content, device_window, safe_device)


## Apply the safe content rect to Board / UI / WinOverlay via anchors+offsets
## so top piles and bottom controls stay inside the safe rect while the
## background (a sibling full-bleed TextureRect) remains full window.
func _apply_current_safe_rect() -> void:
	if _board == null and _ui == null and _win_overlay == null:
		return
	var content := _content_size()
	var safe := _current_safe_rect(content)
	if safe == _applied_safe:
		return
	_applied_safe = safe
	var m := SafeAreaLayout.margins(content, safe)
	for node in [_board, _ui, _win_overlay]:
		if node == null:
			continue
		node.anchor_left = 0.0
		node.anchor_top = 0.0
		node.anchor_right = 1.0
		node.anchor_bottom = 1.0
		node.offset_left = m.left
		node.offset_top = m.top
		node.offset_right = -m.right
		node.offset_bottom = -m.bottom


# ----- render (dumb projection only) -----

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventKey and event.pressed and not event.echo:
		if event.is_action("sol_draw1"):
			_on_draw1()
		elif event.is_action("sol_draw3"):
			_on_draw3()
		elif event.is_action("sol_undo"):
			_on_undo()
		elif event.is_action("sol_hint"):
			_on_hint()
		elif event.is_action("sol_auto"):
			_on_auto()
		elif event.is_action("sol_replay"):
			_on_replay()
		elif event.is_action("sol_new_deal"):
			_on_new_deal()


func _refresh() -> void:
	if _session == null:
		return
	_state = _session.state_snapshot()
	if _state != null and _state.game_status != GameState.GameStatus.WON:
		_hide_win()
	if _board == null:
		return
	_board.controller_press = _on_card_press
	_board.controller_release = _on_card_release
	_board.controller_double = _on_card_double
	_board.set_stock_callback(_on_stock)
	var data := SnapshotProjector.project(_state)
	_board.render(data)
	_update_labels()


func _update_labels() -> void:
	if _state == null:
		return
	var mode := "Draw-1" if _state.draw_count == GameState.DRAW1 else "Draw-3"
	var pool: String = _state.deal_pool if _state.deal_pool != "" else "-"
	if _info_label != null:
		_info_label.text = "Deal %s#%d  |  %s  |  Score %d  |  Moves %d  |  Stock %d  |  Status %s" % [
			pool,
			_state.deal_index,
			mode,
			_state.score,
			_state.move_count,
			_state.stock.size(),
			SnapshotProjector.status_name(_state.game_status),
		]
	if _status_label != null:
		_status_label.text = _msg


# ----- button actions (explicit session transitions) -----

func _on_draw1() -> void:
	_switch_draw_mode(GameState.DRAW1)


func _on_draw3() -> void:
	_switch_draw_mode(GameState.DRAW3)


func _switch_draw_mode(draw_count: int) -> void:
	_stop_auto("已停止自动")
	if _session == null:
		return
	if _session.draw_count() == draw_count:
		_msg = "当前已是 Draw-%d 模式" % draw_count
		_update_labels()
		return
	var result := GameSession.create(_session.deal_pool(), _session.deal_index(), draw_count)
	if not result.ok:
		_msg = "切换失败: %s" % result.error_message
		_play_sound(SND_NOMOVE)
		return
	_session = result.session
	_play_sound(SND_DEAL)
	_msg = "已切换 Draw-%d 模式（同牌局重发就绪态）" % draw_count
	_refresh()


func _on_undo() -> void:
	_stop_auto("已停止自动")
	if _session == null:
		return
	var result := _session.undo()
	if not result.ok:
		_msg = "无法撤销: %s" % result.error_message
		_play_sound(SND_NOMOVE)
		_update_labels()
		return
	_msg = "已撤销上一步"
	_play_sound(SND_UNDO)
	_refresh()


func _on_hint() -> void:
	_stop_auto("已停止自动")
	if _session == null:
		return
	var hint := _session.hint()
	if not hint.ok or hint.move == null:
		_msg = "提示: %s" % hint.message
		_update_labels()
		return
	_msg = "提示: %s" % hint.move.description()
	var source := _source_of_move(hint.move)
	var target := _target_of_move(hint.move)
	if _board != null:
		_board.show_hint(source, target)
	_hint_timer = Time.get_ticks_msec() / 1000.0 + HINT_SECONDS
	_update_labels()


func _on_auto() -> void:
	if _session == null:
		return
	if _auto_active:
		_stop_auto("已停止自动")
		return
	var plan := _session.plan_auto_complete()
	if not plan.eligible:
		_msg = "自动不可用: %s" % plan.eligibility_message
		_update_labels()
		return
	if plan.moves.is_empty():
		_msg = "自动无移动: %s" % plan.stop_message
		_update_labels()
		return
	_auto_moves = plan.moves.duplicate()
	_auto_index = 0
	_auto_active = true
	_auto_accum = 0.0
	_play_sound(SND_AUTO)
	_msg = "自动收牌中 (共 %d 步)…" % _auto_moves.size()
	_update_labels()


func _on_replay() -> void:
	_stop_auto("已停止自动")
	if _session == null:
		return
	var result := _session.replay()
	if not result.ok:
		_msg = "重开失败: %s" % result.error_message
		_play_sound(SND_NOMOVE)
		return
	_play_sound(SND_DEAL)
	_msg = "已按原牌局重发"
	_refresh()


func _on_new_deal() -> void:
	_stop_auto("已停止自动")
	if _session == null:
		return
	var result := _session.new_deal()
	if not result.ok:
		_msg = "新牌局失败: %s" % result.error_message
		_play_sound(SND_NOMOVE)
		return
	_play_sound(SND_DEAL)
	_msg = "已开新牌局"
	_refresh()


func _on_stock() -> void:
	if _session == null or _state == null:
		return
	var move := InputInterpreter.stock_click_move(_state)
	if move == null:
		_msg = "牌库与废牌区都空了"
		_play_sound(SND_NOMOVE)
		_update_labels()
		return
	_commit(move)


# ----- pointer intent translation -----

func _on_card_press(view: CardView, _global_pos: Vector2) -> void:
	if _session == null or _state == null:
		return
	if _auto_active:
		_stop_auto("已手动打断")
	if view.source.get("kind", "") == "stock":
		_press = {}
		_on_stock()
		return
	_press = {"source": view.source.duplicate(), "start": _global_pos, "last": _global_pos}


func _on_card_double(view: CardView, _global_pos: Vector2) -> void:
	if _session == null or _state == null:
		return
	_press = {}
	if _drag_active:
		_end_drag()
	if not view.source.get("kind", "") in ["waste", "tableau"]:
		return
	var move := InputInterpreter.double_click_move(_state, view.source)
	if move == null:
		_msg = "该顶牌不能送到基牌区"
		_play_sound(SND_NOMOVE)
		_update_labels()
		return
	_msg = "双击: %s" % move.description()
	_commit(move)


func _board_origin() -> Vector2:
	if _board == null:
		return Vector2.ZERO
	return _board.get_global_transform().origin


func _on_card_release(_view: CardView, global_pos: Vector2) -> void:
	var press := _press
	_press = {}
	if press.is_empty():
		return
	if _drag_active:
		var local := global_pos - _board_origin()
		var target := {}
		if _board != null:
			target = _board.slot_at(local)
		_end_drag()
		if target.is_empty():
			_msg = "已取消拖动"
			_update_labels()
			return
		var move := InputInterpreter.build_drag_move(_state, press.source, target)
		if move == null:
			_msg = "不能把牌放到这里"
			_play_sound(SND_NOMOVE)
			_update_labels()
			return
		_commit(move)


func _commit(move: Move) -> void:
	if _session == null:
		return
	var result := _session.apply_move(move)
	if not result.ok:
		_msg = "不可行: %s" % result.error_message
		_play_sound(SND_NOMOVE)
		_update_labels()
		return
	var kinds := result.batch.applied_move_kinds()
	_play_move_sound(kinds)
	var was_win := false
	_refresh()
	if _state.game_status == GameState.GameStatus.WON:
		was_win = true
		_show_win()
	if not was_win:
		_msg = "已执行: %s" % move.description()
		_update_labels()


func _play_move_sound(kinds: Array) -> void:
	for kind in kinds:
		if kind == Move.MoveKind.FLIP_TABLEAU:
			_play_sound(SND_MOVECARD)
			return
	_play_sound(SND_MOVECARD)


func _show_win() -> void:
	if _win_overlay != null:
		_win_overlay.visible = true
	_play_sound(SND_VICTORY)
	_msg = "胜利！所有牌都已收齐"
	_update_labels()


func _hide_win() -> void:
	if _win_overlay != null:
		_win_overlay.visible = false


# ----- drag state machine (visual only) -----

func _process(delta: float) -> void:
	if _drag_active:
		var mouse := get_viewport().get_mouse_position()
		if _board != null:
			_board.move_ghost(mouse - _board_origin())
	if _hint_timer > 0.0 and Time.get_ticks_msec() / 1000.0 >= _hint_timer:
		_hint_timer = -1.0
		if _board != null:
			_board.clear_hint()
	if _press.has("source") and not _drag_active:
		var now := get_viewport().get_mouse_position()
		var start: Vector2 = _press.get("start", now)
		if now.distance_to(start) > DRAG_THRESHOLD:
			_start_drag(now)
	if _auto_active:
		_auto_accum += delta
		if _auto_accum >= AUTO_STEP_SEC:
			_auto_accum = 0.0
			_step_auto()


func _start_drag(at_pos: Vector2) -> void:
	if _session == null or _state == null:
		return
	var source: Dictionary = _press.get("source", {})
	var desc := _drag_source_desc(source)
	if desc.is_empty():
		return
	if _board != null:
		_board.begin_ghost(desc.card_id, desc.run_count, at_pos - _board_origin())
	_drag_active = true


func _drag_source_desc(source: Dictionary) -> Dictionary:
	var kind: String = source.get("kind", "")
	var index := int(source.get("index", -1))
	var card_index := int(source.get("card_index", -1))
	var pile: CardPile = null
	if kind == "tableau":
		pile = _state.tableau_pile(index)
	elif kind == "waste":
		pile = _state.waste
	elif kind == "foundation":
		pile = _state.foundation_pile(index)
	if pile == null or pile.is_empty():
		return {}
	var top_index := pile.size() - 1
	var ci := card_index
	if ci < 0:
		ci = top_index
	if ci != top_index and kind == "tableau":
		var candidate := pile.card_at(ci)
		if candidate == null or not candidate.face_up:
			return {}
	else:
		ci = top_index
	var card := pile.card_at(ci)
	if card == null or not card.face_up:
		return {}
	return {"card_id": card.id, "run_count": pile.size() - ci}


func _end_drag() -> void:
	_drag_active = false
	if _board != null:
		_board.end_ghost()


func _stop_auto(message: String) -> void:
	if not _auto_active:
		return
	_auto_active = false
	_auto_moves.clear()
	_auto_index = 0
	_msg = message
	_update_labels()


func _step_auto() -> void:
	if _auto_index >= _auto_moves.size():
		_refresh()
		if _state != null and _state.game_status == GameState.GameStatus.WON:
			_show_win()
			_msg = "自动收牌完成"
		else:
			_msg = "自动完成（计划移动已耗尽）"
		_auto_active = false
		_update_labels()
		return
	var move: Move = _auto_moves[_auto_index]
	_auto_index += 1
	var result := _session.apply_move(move)
	if not result.ok:
		_msg = "自动中断: %s" % result.error_message
		_auto_active = false
		_update_labels()
		return
	_refresh()
	if _state != null and _state.game_status == GameState.GameStatus.WON:
		_show_win()
		_msg = "自动收牌完成"
		_auto_active = false
		_update_labels()
		return
	if _auto_index >= _auto_moves.size():
		_msg = "自动完成（计划移动已耗尽）"
		_auto_active = false
		_update_labels()


# ----- sound helper -----

func _play_sound(path: String) -> void:
	if _sfx == null:
		return
	var stream: AudioStream = _sounds.get(path)
	if stream == null:
		stream = load(path)
		if stream == null:
			return
		_sounds[path] = stream
	_sfx.stream = stream
	_sfx.play()


# ----- hint move -> geometry -----

func _source_of_move(move: Move) -> Dictionary:
	match move.source_location:
		Move.Location.LOC_TABLEAU:
			return {"kind": "tableau", "index": move.source_index}
		Move.Location.LOC_WASTE:
			return {"kind": "waste", "index": -1}
		Move.Location.LOC_FOUNDATION:
			return {"kind": "foundation", "index": move.source_index}
		Move.Location.LOC_STOCK:
			return {"kind": "stock", "index": -1}
	return {}


func _target_of_move(move: Move) -> Dictionary:
	match move.target_location:
		Move.Location.LOC_TABLEAU:
			return {"kind": "tableau", "index": move.target_index}
		Move.Location.LOC_FOUNDATION:
			return {"kind": "foundation", "index": move.target_index}
		Move.Location.LOC_WASTE:
			return {"kind": "waste", "index": -1}
		Move.Location.LOC_STOCK:
			return {"kind": "stock", "index": -1}
	return {}


# ----- MCP runtime verification helpers (read-only + documented seam) -----

func mcp_state() -> Dictionary:
	if _state == null:
		return {}
	return SnapshotProjector.project(_state)


func mcp_can_undo() -> bool:
	return _session != null and _session.can_undo()


func mcp_hint_text() -> String:
	if _session == null:
		return "no_session"
	var hint := _session.hint()
	if not hint.ok:
		return hint.code + ": " + hint.message
	return hint.move.description()


## Explicit, documented non-production fixture seam for MCP acceptance only.
## Release boundary: hard-gated on the "editor" feature — outside the editor
## this always returns false and no fixture/session mutation can occur. Player
## controls never reach this method; it is callable only through MCP eval.
func mcp_debug_load_fixture(fixture: String) -> bool:
	if not OS.has_feature("editor"):
		return false
	if _session == null or not fixture in FIXTURE_NAMES:
		return false
	var state: GameState = null
	if fixture == "near_win":
		state = FixtureStates.near_win()
	elif fixture == "near_win_waste_ace":
		state = FixtureStates.near_win_waste_ace()
	elif fixture == "ops_state":
		state = FixtureStates.ops_state()
	if state == null:
		return false
	var draw := _session.draw_count()
	var result := GameSession.debug_create_state(state, draw)
	if not result.ok:
		return false
	_session = result.session
	_hide_win()
	_msg = "已载入受控测试牌局 (%s)" % fixture
	_refresh()
	return true


# ----- MCP read/introspection helpers (read-only; no state mutation) -----

## Current safe-area content rect and the rects of the content controls.
func mcp_safe_layout() -> Dictionary:
	var content := _content_size()
	var safe := _current_safe_rect(content)
	var m := SafeAreaLayout.margins(content, safe)
	return {
		"content_size": content,
		"safe": safe,
		"has_insets": SafeAreaLayout.has_insets(content, safe),
		"margins": m,
		"board_rect": _board.get_rect() if _board != null else Rect2(),
		"ui_rect": _ui.get_rect() if _ui != null else Rect2(),
	}


## Live hint overlay introspection (count + per-overlay rects/colours).
func mcp_hint_overlays() -> Dictionary:
	if _board == null:
		return {"active": false, "count": 0, "rects": [], "colors": []}
	return {
		"active": _board.hint_active(),
		"count": _board.hint_overlay_count(),
		"rects": _board.hint_overlay_rects(),
		"colors": _board.hint_overlay_colors(),
	}


func mcp_double_tap_ms() -> int:
	return CardView.DOUBLE_TAP_MS


## Canvas-space global rect of one board zone (click-target helpers).
func mcp_zone_global_rect(kind: String, index: int) -> Rect2:
	if _board == null:
		return Rect2()
	var zone := _board.zone_rect(kind, index)
	if not zone.has_area():
		return Rect2()
	var origin := _board.get_global_transform() * zone.position
	return Rect2(origin, zone.size)
