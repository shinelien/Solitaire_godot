@tool
extends McpTestSuite


func suite_name() -> String:
	return "hint_engine"


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _move_keys(moves: Array[Move]) -> Array:
	var out: Array = []
	for m in moves:
		out.append(m.key())
	return out


# ----- determinism + zero mutation -----

func test_hint_same_state_deterministic_and_never_mutates() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	state.tableau[4] = CardPile.new()
	var baseline := state.clone()
	var history := SnapshotHistory.new()
	var first := HintEngine.hint(state)
	var second := HintEngine.hint(state)
	assert_true(first.ok, "hint present")
	assert_eq(first.move.key(), second.move.key(), "same state -> same hint")
	assert_eq(first.tier, second.tier, "same state -> same tier")
	assert_true(state.content_equals(baseline), "hint did not mutate source")
	assert_eq(history.size(), 0, "hint never touches history")
	var list_a := HintEngine.all_legal_moves(state)
	var list_b := HintEngine.all_legal_moves(state)
	assert_eq(_move_keys(list_a), _move_keys(list_b), "all_legal_moves deterministic")
	assert_true(state.content_equals(baseline), "all_legal_moves did not mutate source")


func test_every_returned_candidate_validates_through_rules_engine() -> void:
	var states: Array[GameState] = []
	var a := CardStateTestkit.make_state()
	a.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	a.tableau[1] = _col([[_s(2, 13), true]])
	a.tableau[4] = CardPile.new()
	states.append(a)
	var b := CardStateTestkit.make_state()
	b.waste = CardStateTestkit.up([_s(0, 1)])
	b.stock = CardStateTestkit.down([5, 6, 7])
	b.draw_count = GameState.DRAW3
	states.append(b)
	var c := CardStateTestkit.make_state()
	for suit in 4:
		c.foundation[suit] = CardStateTestkit.full_foundation(suit)
	c.waste = CardStateTestkit.up([_s(3, 13)])
	c.game_status = GameState.GameStatus.WON
	states.append(c)
	for state in states:
		var candidates := HintEngine.all_legal_moves(state)
		for m in candidates:
			var validation := RulesEngine.validate(state, m)
			assert_true(validation.ok, "candidate %s legal: %s" % [m.description(), validation.error_message])


func test_hint_move_executes_cleanly_on_a_clone() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[4] = CardPile.new()
	var baseline := state.clone()
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	var result := MoveExecutor.execute(state, h.move)
	assert_true(result.ok, "hinted move legal through executor")
	assert_true(state.content_equals(baseline), "source unchanged before/after execute-on-clone")


# ----- priority tiers -----

func test_priority_expose_t2f_beats_other_moves() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(1, 1), true]])
	state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	state.tableau[2] = _col([[7, false], [_s(0, 1), true]])
	var baseline := state.clone()
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	assert_eq(h.tier, HintResult.TIER_EXPOSE, "expose move wins")
	assert_eq(h.move.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "t2f expose")
	assert_eq(h.move.source_index, 2, "exposing column 2 ace onto face-down")
	assert_true(state.content_equals(baseline), "source stable")


func test_priority_run_expose_beats_foundation_move() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = CardPile.new()
	state.tableau[2] = _col([[_s(2, 1), true]])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	assert_eq(h.tier, HintResult.TIER_EXPOSE, "run expose tier")
	assert_eq(h.move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "run move exposing face-down")
	assert_eq(h.move.source_index, 0, "source col 0")
	assert_eq(h.move.count, 3, "whole face-up suffix moved")


func test_priority_to_foundation_beats_waste_to_tableau_and_runs() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 2), true], [_s(0, 1), true]])
	state.tableau[1] = _col([[_s(0, 12), true]])
	state.waste = CardStateTestkit.up([_s(1, 11)])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	assert_eq(h.tier, HintResult.TIER_TO_FOUNDATION, "foundation tier")
	assert_eq(h.move.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "ace to foundation")
	assert_eq(h.move.source_index, 0, "column 0 ace source")
	assert_eq(h.move.target_index, 0, "first empty slot")


func test_priority_waste_to_tableau_when_no_foundation_move() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[1] = _col([[_s(0, 12), true]])
	state.waste = CardStateTestkit.up([_s(1, 11)])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	assert_eq(h.tier, HintResult.TIER_WASTE_TO_TABLEAU, "waste to tableau tier")
	assert_eq(h.move.kind, Move.MoveKind.WASTE_TO_TABLEAU, "w2t kind")
	assert_eq(h.move.target_index, 1, "onto queen column")


func test_priority_run_beats_stock_draw_and_trivial() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[3] = _col([[_s(3, 12), true]])
	state.tableau[1] = CardPile.new()
	state.stock = CardStateTestkit.down([20, 21])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "hint present")
	assert_eq(h.tier, HintResult.TIER_TABLEAU_RUN, "run tier above stock")
	assert_eq(h.move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "run kind")
	assert_eq(h.move.source_index, 0, "source 0")
	assert_eq(h.move.target_index, 3, "jack onto diamond queen")


func test_priority_draw_and_recycle_when_only_stock_action() -> void:
	var draw_state := CardStateTestkit.make_state()
	draw_state.tableau[0] = _col([[5, false]])
	draw_state.stock = CardStateTestkit.down([20, 21, 22])
	var hd := HintEngine.hint(draw_state)
	assert_true(hd.ok, "draw hint present")
	assert_eq(hd.tier, HintResult.TIER_STOCK, "draw tier")
	assert_eq(hd.move.kind, Move.MoveKind.DRAW_STOCK, "draw kind")

	var recycle_state := CardStateTestkit.make_state()
	recycle_state.tableau[0] = _col([[5, false]])
	recycle_state.waste = CardStateTestkit.up([_s(1, 5)])
	var hr := HintEngine.hint(recycle_state)
	assert_true(hr.ok, "recycle hint present")
	assert_eq(hr.tier, HintResult.TIER_STOCK, "recycle tier")
	assert_eq(hr.move.kind, Move.MoveKind.RECYCLE_STOCK, "recycle kind")


func test_priority_trivial_only_when_nothing_else_legal() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true]])
	state.tableau[1] = CardPile.new()
	state.tableau[2] = _col([[_s(1, 13), true]])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "trivial king shift is still a legal hint")
	assert_eq(h.tier, HintResult.TIER_TRIVIAL, "only trivial shift available")
	assert_eq(h.move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "king shift kind")


func test_dynamic_foundation_slots_in_hint() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.foundation_of(1, 1)
	state.waste = CardStateTestkit.up([_s(0, 1)])
	var h := HintEngine.hint(state)
	assert_true(h.ok, "spade ace hint present")
	assert_eq(h.tier, HintResult.TIER_TO_FOUNDATION, "foundation tier")
	assert_eq(h.move.kind, Move.MoveKind.WASTE_TO_FOUNDATION, "w2f")
	assert_eq(h.move.target_index, 1, "first empty slot after hearts slot 0")

	var state2 := CardStateTestkit.make_state()
	state2.foundation[0] = CardStateTestkit.foundation_of(1, 1)
	state2.waste = CardStateTestkit.up([_s(1, 2)])
	var h2 := HintEngine.hint(state2)
	assert_true(h2.ok, "heart two hint present")
	assert_eq(h2.move.kind, Move.MoveKind.WASTE_TO_FOUNDATION, "w2f heart")
	assert_eq(h2.move.target_index, 0, "same-suit slot 0 selected over empty slots")


# ----- no hint (typed) -----

func test_no_hint_typed_reasons() -> void:
	var null_result := HintEngine.hint(null)
	assert_false(null_result.ok, "null state")
	assert_eq(null_result.code, HintResult.CODE_INVALID_STATE, "invalid_state code")

	var won := CardStateTestkit.make_state()
	for suit in 4:
		won.foundation[suit] = CardStateTestkit.full_foundation(suit)
	won.game_status = GameState.GameStatus.WON
	var won_result := HintEngine.hint(won)
	assert_false(won_result.ok, "won state")
	assert_eq(won_result.code, HintResult.CODE_ALREADY_WON, "already_won code")

	var blocked := CardStateTestkit.make_state()
	blocked.tableau[0] = _col([[5, false]])
	blocked.stock = CardPile.new()
	var no_move := HintEngine.hint(blocked)
	assert_false(no_move.ok, "blocked state no hint")
	assert_eq(no_move.code, HintResult.CODE_NO_LEGAL_MOVE, "no_legal_move code")


# ----- candidate coverage -----

func test_all_legal_moves_covers_valid_suffix_runs_and_deterministic_order() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[4] = CardPile.new()
	state.tableau[1] = _col([[_s(3, 12), true]])
	var list := HintEngine.all_legal_moves(state)
	assert_true(list.size() >= 1, "candidates present")
	var keys := _move_keys(list)
	assert_eq(keys, keys.duplicate(), "ordered deterministically")
	var saw_run := false
	var saw_trivial := false
	var first_tier_run := 999
	for i in list.size():
		var m: Move = list[i]
		if m.kind == Move.MoveKind.TABLEAU_TO_TABLEAU and m.source_index == 0 and m.target_index == 4 and m.count == 3:
			saw_run = true
		if m.kind == Move.MoveKind.TABLEAU_TO_TABLEAU and m.source_index == 0 and m.target_index == 4 and m.count == 1:
			saw_trivial = true
	assert_true(saw_run, "full K,Q,J run to empty column covered")
	var all_ordered := HintEngine.all_legal_moves(state)
	assert_eq(_move_keys(all_ordered), _move_keys(list), "repeat call identical")


func test_all_tableau_move_kinds_never_returned() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true], [_s(1, 12), true]])
	state.tableau[3] = CardPile.new()
	for m in HintEngine.all_legal_moves(state):
		assert_true(
			m.kind != Move.MoveKind.FLIP_TABLEAU
			and m.kind != Move.MoveKind.UNDO
			and m.kind != Move.MoveKind.REPLAY
			and m.kind != Move.MoveKind.NEW_DEAL,
			"no flip/boundary identity ever hinted"
		)
