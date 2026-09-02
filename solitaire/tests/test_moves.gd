extends BaseTest

## MoveExecutor: valid moves apply, illegal moves are atomic no-ops,
## explicit FlipTableau, draw, recycle. Also verifies the flip-after-move
## transaction recorded by the controller.

func _card(id: int, face_up: bool = true) -> CardData:
	var c := CardData.from_id(id)
	c.face_up = face_up
	return c

func _mk_state() -> GameState:
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW1
	return st

func test_move_card_applies() -> void:
	var st := _mk_state()
	st.waste.push_back(_card(1 * 13 + 6))  # 7 hearts
	st.tableau[0] = typed_col([_card(0 * 13 + 7)])    # 8 spades
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.waste()
	m.from_index = 0
	m.count = 1
	m.to_pile = Location.tableau(0)
	var res := MoveExecutor.apply(st, m)
	check_true(res.ok, "apply success")
	check_true(st.waste.is_empty(), "waste emptied")
	check_eq(st.col(0).size(), 2, "column grew")
	check_eq(st.col(0)[1].id, 1 * 13 + 6, "moved card on top")

func test_illegal_move_is_atomic_noop() -> void:
	var st := _mk_state()
	st.waste.push_back(_card(1 * 13 + 6))
	st.tableau[0] = typed_col([_card(0 * 13 + 8)])  # 9 spades (wrong rank)
	var snap := st.deep_copy()
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.waste()
	m.from_index = 0
	m.count = 1
	m.to_pile = Location.tableau(0)
	var res := MoveExecutor.apply(st, m)
	check_false(res.ok, "rejected")
	check_true(st.equals(snap), "state identical after illegal move")

func test_flip_tableau() -> void:
	var st := _mk_state()
	st.tableau[0] = typed_col([_card(0, false), _card(1 * 13 + 6, false)])
	var fl := Move.flip_tableau(0)
	var res := MoveExecutor.apply(st, fl)
	check_true(res.ok, "flip ok")
	check_true(st.col(0)[1].face_up, "top card flipped face-up")
	check_false(st.col(0)[0].face_up, "bottom card still face-down")
	# flip an already face-up top must fail
	res = MoveExecutor.apply(st, fl)
	check_false(res.ok, "flip face-up rejected")
	# flip empty column fails
	var st2 := _mk_state()
	res = MoveExecutor.apply(st2, Move.flip_tableau(3))
	check_false(res.ok, "flip empty column rejected")

func test_draw_and_recycle_moves() -> void:
	var st := _mk_state()
	st.stock = typed_col([_card(0, false), _card(1, false), _card(2, false)])
	var res := MoveExecutor.apply(st, Move.draw())
	check_true(res.ok, "draw ok")
	check_eq(st.waste.size(), 1, "one drawn")
	check_true(st.waste[0].face_up, "drawn card face-up")
	check_eq(st.stock.size(), 2, "stock reduced")
	check_eq(st.waste[0].id, 2, "top card drawn first")
	res = MoveExecutor.apply(st, Move.recycle())
	check_false(res.ok, "recycle with stock non-empty rejected")
	while not st.stock.is_empty():
		check_true(MoveExecutor.apply(st, Move.draw()).ok, "draw")
	res = MoveExecutor.apply(st, Move.recycle())
	check_true(res.ok, "recycle ok")
	check_true(st.stock.is_empty() == false, "stock refilled")
	check_true(st.waste.is_empty(), "waste emptied")
	check_eq(st.stock.size(), 3, "three recycled")
	check_false(st.stock[0].face_up, "recycled cards face-down")
	res = MoveExecutor.apply(st, Move.recycle())
	check_false(res.ok, "double recycle rejected")

func test_sequence_move_and_auto_flip_transaction() -> void:
	# A tableau move that exposes a face-down card must record an explicit
	# FlipTableau move inside the same command.
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var st := ctrl.state
	# Find a tableau column with a face-down card under a movable sequence.
	var moved := false
	for c in PileType.TABLEAU_COUNT:
		var cards := st.col(c)
		if cards.size() < 2:
			continue
		var bottom: CardData = cards[0]
		var top: CardData = cards[cards.size() - 1]
		if bottom.face_up or not top.face_up:
			continue
		# Move top card somewhere legal if possible, else skip.
		var found_target := -1
		for t in PileType.TABLEAU_COUNT:
			if t == c or st.col(t).is_empty():
				continue
			var dst_top: CardData = st.col(t)[st.col(t).size() - 1]
			if KlondikeRules.tableau_accepts(dst_top, top):
				found_target = t
				break
		if found_target == -1:
			continue
		var before := st.deep_copy()
		check_true(ctrl.request_move(Location.tableau(c), cards.size() - 1, 1, Location.tableau(found_target)), "move ok")
		check_false(before.equals(ctrl.state), "state changed")
		var last_cmd: MoveCommand = ctrl.state.history[ctrl.state.history.size() - 1]
		var has_flip := false
		for mv in last_cmd.moves:
			if mv.type == Move.MoveType.FLIP_TABLEAU:
				has_flip = true
		check_true(has_flip, "auto flip recorded in transaction")
		moved = true
		break
	check_true(moved, "constructed a column with a face-down bottom")
	var errs := st.invariant_errors()
	check_empty(errs, "invariants after sequence move")

func test_whole_command_atomic_on_late_failure() -> void:
	# A command whose later move is illegal must be an atomic no-op: the
	# controller applies on a working copy and discards it on failure, so
	# GameState, history and the undo stack are untouched.
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var before := ctrl.state.deep_copy()
	var before_undo := ctrl.undo_stack.size()
	var cmd := MoveCommand.new()
	cmd.label = "Bad"
	var draw := Move.draw()
	cmd.moves.push_back(draw)
	# Illegal: waste top card likely cannot go to col 6 (arbitrary), but to be
	# deterministic we force an illegal move by choosing an out-of-range index.
	var bad := Move.new()
	bad.type = Move.MoveType.MOVE_CARD
	bad.from_pile = Location.waste()
	bad.from_index = 999
	bad.count = 1
	bad.to_pile = Location.tableau(6)
	cmd.moves.push_back(bad)
	check_false(ctrl._execute_command(cmd), "command rejected")
	check_true(ctrl.state.equals(before), "state untouched by failed transaction")
	check_eq(ctrl.state.history.size(), before.history.size(), "history untouched")
	check_eq(ctrl.undo_stack.size(), before_undo, "undo stack untouched")
