class_name GameController
extends RefCounted

## Application layer. Owns the authoritative GameState and the undo snapshot
## stack. Every gameplay operation (player, hint-selected, auto-complete,
## replay/restart) funnels through MoveExecutor as a MoveCommand transaction;
## invalid transactions are atomic no-ops. Presentation only renders
## state and calls these intent methods.

signal state_changed(state: GameState)
signal message(text: String)

var repository: LegacyDealRepository
var selector: DealSelector
var rng := RandomNumberGenerator.new()
var state: GameState = null
var undo_stack: Array[GameState] = []

func _init() -> void:
	repository = LegacyDealRepository.new()
	selector = DealSelector.new()

# ---------------------------------------------------------------- new game

## Starts a new game. Precedence: explicit `encoded` > explicit `deal_index`
## > selector random. Returns false (with a message) on any malformed deal;
## never substitutes a random fallback for a requested deal.
func new_deal(draw_mode: int = -1, deal_index: int = -1, encoded: String = "") -> bool:
	var mode: int = draw_mode
	if mode != GameConfig.DRAW1 and mode != GameConfig.DRAW3:
		mode = GameConfig.DRAW1
	var rec := ""
	var idx := deal_index
	if not encoded.is_empty():
		rec = encoded
	else:
		var total := repository.count_for(mode)
		if deal_index < 0 or deal_index >= total:
			idx = selector.select_index(total, rng)
			if idx < 0:
				message.emit("Deal library is empty")
				return false
		rec = repository.get_record(mode, idx)
		if rec.is_empty():
			message.emit("Requested deal %d is not available" % idx)
			return false
	if not LegacyDealDecoder.is_valid(rec):
		message.emit("Malformed deal data; refusing to start")
		return false
	var ids := LegacyDealDecoder.decode(rec)
	var built := LegacyDealBuilder.build(ids)
	var new_state := GameState.new()
	new_state.draw_mode = mode
	new_state.encoded = rec
	new_state.deal_index = idx
	new_state.status = GameStatus.Status.PLAYING
	new_state.tableau = built["tableau"]
	new_state.stock = built["stock"]
	new_state.move_count = 0
	new_state.draw_count = 0
	new_state.history.clear()
	new_state.session.clear()
	new_state.session.push_back({"encoded": rec, "draw_mode": mode, "index": idx})
	state = new_state
	undo_stack.clear()
	# Legacy auto-draws the first packet onto the waste right after the deal.
	if not _apply_initial_draw():
		message.emit("Initial draw failed")
		return false
	state_changed.emit(state)
	return true

func _apply_initial_draw() -> bool:
	var res := MoveExecutor.apply(state, Move.draw())
	if not res.ok:
		return false
	state.move_count = 0
	state.history.clear()
	return true

# ---------------------------------------------------------------- commands

func request_stock_action() -> bool:
	if state == null:
		return false
	if state.stock.is_empty():
		return request_recycle()
	return request_draw()

func request_draw() -> bool:
	if state == null or state.stock.is_empty():
		return false
	var cmd := MoveCommand.new()
	cmd.label = "Draw"
	cmd.moves.push_back(Move.draw())
	return _execute_command(cmd)

func request_recycle() -> bool:
	if state == null or state.waste.is_empty() or not state.stock.is_empty():
		return false
	var cmd := MoveCommand.new()
	cmd.label = "Recycle"
	cmd.moves.push_back(Move.recycle())
	return _execute_command(cmd)

func request_move(from_loc: Location, from_index: int, count: int, to_loc: Location) -> bool:
	if state == null:
		return false
	var primary := Move.new()
	primary.type = Move.MoveType.MOVE_CARD
	primary.from_pile = from_loc
	primary.from_index = from_index
	primary.count = count
	primary.to_pile = to_loc
	primary.card_id = _moved_card_id(from_loc, from_index)
	if not KlondikeRules.is_legal_move(state, primary):
		message.emit("Illegal move")
		return false
	var cmd := _build_command_with_flip(primary)
	if cmd == null:
		return false
	return _execute_command(cmd)

func request_auto_foundation(loc: Location) -> bool:
	if state == null:
		return false
	var src := state.get_pile(loc)
	if src.is_empty():
		return false
	var card: CardData = src[src.size() - 1]
	if not card.face_up:
		return false
	var f := KlondikeRules.matching_foundation(state, card)
	if f == -1:
		message.emit("Card cannot be sent to a foundation")
		return false
	var from_index := src.size() - 1
	if loc.type == PileType.WASTE or loc.type == PileType.FOUNDATION:
		from_index = src.size() - 1
	return request_move(loc, from_index, 1, Location.foundation(f))

func request_undo() -> bool:
	if state == null or undo_stack.is_empty():
		message.emit("Nothing to undo")
		return false
	state = undo_stack.pop_back()
	state_changed.emit(state)
	return true

## Read-only: returns a legal move suggestion, never mutates state.
func request_hint() -> Move:
	if state == null:
		return null
	return KlondikeRules.find_hint_move(state)

func request_auto_complete() -> bool:
	if state == null:
		return false
	if KlondikeRules.is_won(state):
		return false
	var working := state.deep_copy()
	var moves: Array[Move] = []
	var guard := 0
	while guard < GameConfig.AUTO_COMPLETE_LIMIT:
		guard += 1
		var m := KlondikeRules.find_foundation_move(working)
		if m == null:
			break
		var res := MoveExecutor.apply(working, m)
		if not res.ok:
			break
		moves.push_back(m)
		if m.from_pile.type == PileType.TABLEAU:
			var cards := working.col(m.from_pile.index)
			if not cards.is_empty() and not cards[cards.size() - 1].face_up:
				var fl := Move.flip_tableau(m.from_pile.index)
				var fres := MoveExecutor.apply(working, fl)
				if fres.ok:
					moves.push_back(fl)
		if KlondikeRules.is_won(working):
			break
	if moves.is_empty():
		message.emit("No foundation moves available")
		return false
	var cmd := MoveCommand.new()
	cmd.label = "Auto Complete"
	cmd.moves = moves
	_commit(cmd, working)
	return true

## Restarts the exact same deal and draw mode.
func request_replay() -> bool:
	if state == null or state.session.is_empty():
		return false
	var last: Dictionary = state.session[state.session.size() - 1]
	return new_deal(last["draw_mode"], last["index"], last["encoded"])

## Random fresh deal in the current draw mode.
func request_new_deal() -> bool:
	if state == null:
		return false
	return new_deal(state.draw_mode, -1, "")

func set_draw_mode(mode: int) -> bool:
	if mode != GameConfig.DRAW1 and mode != GameConfig.DRAW3:
		return false
	if state != null and state.draw_mode == mode:
		return true
	return new_deal(mode, -1, "")

# ---------------------------------------------------------------- internals

func _moved_card_id(loc: Location, from_index: int) -> int:
	if state == null:
		return -1
	var p := state.get_pile(loc)
	if p.is_empty():
		return -1
	var i := from_index
	if i < 0 or i >= p.size():
		i = p.size() - 1
	return p[i].id

func _build_command_with_flip(primary: Move) -> MoveCommand:
	var cmd := MoveCommand.new()
	cmd.label = "Move"
	cmd.moves.push_back(primary)
	if primary.from_pile.type == PileType.TABLEAU:
		var sim := state.deep_copy()
		var res := MoveExecutor.apply(sim, primary)
		if res.ok:
			var cards := sim.col(primary.from_pile.index)
			if not cards.is_empty() and not cards[cards.size() - 1].face_up:
				cmd.moves.push_back(Move.flip_tableau(primary.from_pile.index))
	return cmd

func _execute_command(cmd: MoveCommand) -> bool:
	if state == null or cmd.moves.is_empty():
		return false
	var working := state.deep_copy()
	for m in cmd.moves:
		var res := MoveExecutor.apply(working, m)
		if not res.ok:
			message.emit("Illegal move: %s" % res.error)
			return false
	_commit(cmd, working)
	return true

func _commit(cmd: MoveCommand, new_state: GameState) -> void:
	undo_stack.push_back(state.deep_copy())
	if undo_stack.size() > GameConfig.MAX_UNDO:
		undo_stack.pop_front()
	state = new_state
	state.move_count += 1
	state.history.push_back(cmd)
	if KlondikeRules.is_won(state):
		state.status = GameStatus.Status.WON
	state_changed.emit(state)
