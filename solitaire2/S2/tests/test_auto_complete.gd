@tool
extends McpTestSuite


func suite_name() -> String:
	return "auto_complete"


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


## Three full foundations (spades/hearts/clubs) + diamonds A..top in slot 3.
## top defaults to 12 (Q) so the only remaining diamond is the K. Full 52-card
## conservation holds for every produced state.
func _near_win(top: int = 12) -> GameState:
	var state := CardStateTestkit.make_state()
	for suit in 3:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	state.foundation[3] = CardStateTestkit.foundation_of(3, top)
	state.draw_count = GameState.DRAW1
	return state


func _allowed_kind(kind: int) -> bool:
	return (
		kind == Move.MoveKind.TABLEAU_TO_FOUNDATION
		or kind == Move.MoveKind.WASTE_TO_FOUNDATION
		or kind == Move.MoveKind.DRAW_STOCK
		or kind == Move.MoveKind.RECYCLE_STOCK
	)


# ----- eligibility -----

func test_plan_requires_all_tableau_face_up() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 1), true]])
	var baseline := state.clone()
	var plan := AutoCompletePlanner.plan(state)
	assert_false(plan.eligible, "hidden tableau card rejects planning")
	assert_eq(plan.eligibility_code, AutoCompletePlanResult.CODE_TABLEAU_NOT_FACE_UP, "typed reason")
	assert_true(plan.moves.is_empty(), "no plan moves when hidden cards")
	assert_false(plan.completed, "not completed")
	assert_true(state.content_equals(baseline), "planner never mutates source")
	assert_true(plan.final_state_snapshot() == null, "no simulated state when not eligible")


func test_plan_max_steps_budget_is_documented_and_adequate() -> void:
	assert_true(AutoCompletePlanner.MAX_STEPS >= 512, "max step bound >= 512")


# ----- completion on representative full-deck near-complete states -----

func test_plan_waste_top_reaches_won() -> void:
	var state := _near_win()
	state.waste = CardStateTestkit.up([_s(3, 13)])
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	assert_true(plan.completed, "plan completed")
	assert_eq(plan.stop_reason, AutoCompletePlanResult.STOP_WON, "won stop reason")
	assert_eq(plan.moves.size(), 1, "single w2f move")
	assert_eq(plan.moves[0].kind, Move.MoveKind.WASTE_TO_FOUNDATION, "w2f kind")
	assert_eq(plan.moves[0].target_index, 3, "diamond slot")
	assert_eq(plan.final_state_snapshot().game_status, GameState.GameStatus.WON, "final state WON")
	assert_true(CardStateTestkit.conservation_ok(plan.final_state_snapshot()), "52 conserved")
	assert_true(state.total_card_count() == 52, "source still full 52")


func test_plan_tableau_tops_sequence_reaches_won() -> void:
	var state := _near_win(10)
	state.tableau[0] = _col([[_s(3, 11), true]])
	state.tableau[1] = _col([[_s(3, 12), true]])
	state.tableau[2] = _col([[_s(3, 13), true]])
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	assert_true(plan.completed, "completed")
	assert_eq(plan.stop_reason, AutoCompletePlanResult.STOP_WON, "won")
	assert_eq(plan.moves.size(), 3, "J then Q then K")
	for m in plan.moves:
		assert_eq(m.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "only t2f emitted")
		assert_true(_allowed_kind(m.kind), "allowed kind")
	assert_eq(plan.moves[0].source_index, 0, "column 0 first")
	assert_eq(plan.moves[1].source_index, 1, "column 1 second")
	assert_eq(plan.moves[2].source_index, 2, "column 2 third")
	assert_true(CardStateTestkit.conservation_ok(plan.final_state_snapshot()), "52 conserved")


func test_plan_stock_draw_then_waste_reaches_won_both_draw_modes() -> void:
	for draw_mode in [GameState.DRAW1, GameState.DRAW3]:
		var state := _near_win()
		state.draw_count = draw_mode
		state.stock = CardStateTestkit.down([_s(3, 13)])
		var plan := AutoCompletePlanner.plan(state)
		assert_true(plan.eligible, "eligible draw%d" % draw_mode)
		assert_true(plan.completed, "completed draw%d" % draw_mode)
		assert_eq(plan.stop_reason, AutoCompletePlanResult.STOP_WON, "won draw%d" % draw_mode)
		assert_eq(plan.moves.size(), 2, "two steps draw%d" % draw_mode)
		assert_eq(plan.moves[0].kind, Move.MoveKind.DRAW_STOCK, "draw first draw%d" % draw_mode)
		assert_eq(plan.moves[1].kind, Move.MoveKind.WASTE_TO_FOUNDATION, "w2f second draw%d" % draw_mode)
		assert_true(CardStateTestkit.conservation_ok(plan.final_state_snapshot()), "52 conserved draw%d" % draw_mode)


# ----- determinism / zero mutation / replayability -----

func test_plan_deterministic_and_source_zero_mutation() -> void:
	var state := _near_win(10)
	state.tableau[0] = _col([[_s(3, 11), true]])
	state.tableau[1] = _col([[_s(3, 12), true]])
	state.tableau[2] = _col([[_s(3, 13), true]])
	var baseline := state.clone()
	var first := AutoCompletePlanner.plan(state)
	var second := AutoCompletePlanner.plan(state)
	assert_eq(_plan_key(first), _plan_key(second), "same state -> identical plan")
	assert_true(state.content_equals(baseline), "planner never mutates source")
	assert_true(CardStateTestkit.no_shared_state(state, first.final_state_snapshot()), "final state is a distinct deep clone")


func _plan_key(plan: AutoCompletePlanResult) -> String:
	var parts: Array[String] = []
	for m in plan.moves:
		parts.append(m.key())
	return "%s|%s|%d" % [plan.stop_reason, ",".join(parts), plan.step_count]


func test_plan_moves_replay_through_executor_in_sequence() -> void:
	var state := _near_win(10)
	state.tableau[0] = _col([[_s(3, 11), true]])
	state.tableau[1] = _col([[_s(3, 12), true]])
	state.tableau[2] = _col([[_s(3, 13), true]])
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.completed, "completed")
	var working := state.clone()
	for i in plan.moves.size():
		var m: Move = plan.moves[i]
		var result := MoveExecutor.execute(working, m)
		assert_true(result.ok, "plan move %d legal in sequence: %s" % [i, result.error_message])
		working = result.new_state
	assert_true(CardStateTestkit.conservation_ok(working), "52 conserved after replay")
	assert_eq(working.game_status, GameState.GameStatus.WON, "replay reaches WON")
	assert_true(working.content_equals(plan.final_state_snapshot()), "replayed state == simulated final state")


# ----- termination on cycles / blocked states -----

func test_draw_recycle_cycle_terminates_typed_both_draw_modes() -> void:
	for draw_mode in [GameState.DRAW1, GameState.DRAW3]:
		var state := CardStateTestkit.make_state()
		state.draw_count = draw_mode
		state.tableau[0] = _col([[_s(2, 5), true]])
		var stock_ids: Array = []
		for i in range(12):
			stock_ids.append(_s(2, 2 + i))
		for i in range(12):
			stock_ids.append(_s(3, 2 + i))
		state.stock = CardStateTestkit.down(stock_ids)
		var plan := AutoCompletePlanner.plan(state)
		assert_true(plan.eligible, "eligible draw%d" % draw_mode)
		assert_false(plan.completed, "cycle never completes draw%d" % draw_mode)
		assert_eq(plan.stop_reason, AutoCompletePlanResult.STOP_NO_PROGRESS, "typed no_progress draw%d" % draw_mode)
		assert_true(plan.step_count < AutoCompletePlanner.MAX_STEPS, "bounded steps draw%d" % draw_mode)
		assert_true(plan.visited_count > 0, "metrics present draw%d" % draw_mode)
		assert_true(plan.moves.size() >= 1, "some moves were attempted draw%d" % draw_mode)
		for m in plan.moves:
			assert_true(_allowed_kind(m.kind), "only allowed kinds draw%d" % draw_mode)


func test_blocked_state_stops_no_legal_move() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(2, 5), true]])
	state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	assert_false(plan.completed, "not completed")
	assert_eq(plan.stop_reason, AutoCompletePlanResult.STOP_NO_LEGAL_MOVE, "typed no_legal_move")
	assert_true(plan.moves.is_empty(), "zero emitted moves")
	assert_true(plan.step_count == 0, "zero steps")


# ----- dynamic foundation destinations / ordering -----

func test_plan_dynamic_foundation_destination_same_suit_slot_first() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.foundation_of(1, 12)
	state.foundation[1] = CardStateTestkit.foundation_of(0, 13)
	state.tableau[0] = _col([[_s(1, 13), true]])
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	assert_true(plan.moves.size() >= 1, "heart king is moved")
	assert_eq(plan.moves[0].kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "t2f first")
	assert_eq(plan.moves[0].source_index, 0, "column 0 source")
	assert_eq(plan.moves[0].target_index, 0, "heart king goes to the hearts-owning slot 0, not the full spades slot 1")


func test_plan_ace_goes_to_first_empty_foundation_slot() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	state.foundation[1] = CardStateTestkit.foundation_of(2, 3)
	state.tableau[0] = _col([[_s(1, 1), true]])
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	assert_true(plan.moves.size() >= 1, "at least one move")
	assert_eq(plan.moves[0].kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "t2f first")
	assert_eq(plan.moves[0].target_index, 2, "heart ace skips occupied slots 0/1 to first empty slot 2")
	assert_true(state.tableau[0].top().rank == 1, "source unchanged by planning")


# ----- forbidden kinds on a broader eligible board -----

func test_plan_never_emits_forbidden_kinds_on_full_eligible_state() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.foundation_of(1, 5)
	state.foundation[1] = CardStateTestkit.foundation_of(0, 4)
	state.tableau[0] = _col([[_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(1, 6), true]])
	state.tableau[2] = _col([[_s(0, 5), true]])
	state.tableau[3] = _col([[_s(2, 13), true]])
	state.stock = CardStateTestkit.down([_s(2, 2), _s(3, 2), _s(2, 3), _s(3, 3)])
	state.draw_count = GameState.DRAW1
	var plan := AutoCompletePlanner.plan(state)
	assert_true(plan.eligible, "eligible")
	for m in plan.moves:
		assert_true(
			_allowed_kind(m.kind),
			"forbidden kind %s never emitted" % Move.kind_name(m.kind)
		)
	assert_true(plan.stop_reason.length() > 0, "typed stop reason always present")
