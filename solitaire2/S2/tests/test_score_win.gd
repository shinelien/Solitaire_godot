@tool
extends McpTestSuite


func suite_name() -> String:
	return "score_win"


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


func test_score_policy_move_delta_table_exact() -> void:
	var cases := [
		[Move.tableau_to_foundation(0, 0), 10],
		[Move.waste_to_foundation(0), 10],
		[Move.waste_to_tableau(0), 5],
		[Move.foundation_to_tableau(0, 0), -10],
		[Move.flip_tableau(0), 5],
		[Move.tableau_to_tableau(0, 1, 1), 0],
		[Move.draw_stock(), 0],
		[Move.recycle_stock(), 0],
	]
	for c in cases:
		assert_eq(LegacyScorePolicy.move_delta(c[0]), int(c[1]), "%s delta" % Move.kind_name(c[0].kind))


func test_score_policy_undo_floor_and_apply_floor() -> void:
	assert_eq(LegacyScorePolicy.undo_score(0), 0, "undo floor at 0")
	assert_eq(LegacyScorePolicy.undo_score(5), 3, "undo -2 from 5")
	assert_eq(LegacyScorePolicy.undo_score(1), 0, "undo floor from 1")
	assert_eq(LegacyScorePolicy.undo_score(-3), 0, "undo never negative")
	assert_eq(LegacyScorePolicy.apply_delta(0, 5), 5, "apply positive")
	assert_eq(LegacyScorePolicy.apply_delta(3, -10), 0, "apply floors at zero")
	assert_eq(LegacyScorePolicy.apply_delta(0, -10), 0, "apply floor from zero")


func _scored_execution(state: GameState, move: Move, history: SnapshotHistory) -> MoveExecutionResult:
	return MoveExecutor.execute(state, move, history)


func test_executor_scores_each_move_kind() -> void:
	var t2f_state := CardStateTestkit.make_state()
	t2f_state.tableau[0] = _col([[_s(0, 1), true]])
	t2f_state.score = 0
	var t2f := _scored_execution(t2f_state, Move.tableau_to_foundation(0, 0), SnapshotHistory.new())
	assert_true(t2f.ok, "t2f ok")
	assert_eq(t2f.new_state.score, 10, "tableau->foundation +10")

	var w2f_state := CardStateTestkit.make_state()
	w2f_state.waste = CardStateTestkit.up([_s(1, 1)])
	w2f_state.score = 0
	var w2f := _scored_execution(w2f_state, Move.waste_to_foundation(1), SnapshotHistory.new())
	assert_true(w2f.ok, "w2f ok")
	assert_eq(w2f.new_state.score, 10, "waste->foundation +10")

	var w2t_state := CardStateTestkit.make_state()
	w2t_state.waste = CardStateTestkit.up([_s(0, 13)])
	w2t_state.tableau[3] = CardPile.new()
	w2t_state.score = 0
	var w2t := _scored_execution(w2t_state, Move.waste_to_tableau(3), SnapshotHistory.new())
	assert_true(w2t.ok, "w2t ok")
	assert_eq(w2t.new_state.score, 5, "waste->tableau +5")

	var f2t_state := CardStateTestkit.make_state()
	f2t_state.foundation[2] = CardStateTestkit.foundation_of(2, 13)
	f2t_state.tableau[5] = CardPile.new()
	f2t_state.score = 30
	var f2t := _scored_execution(f2t_state, Move.foundation_to_tableau(2, 5), SnapshotHistory.new())
	assert_true(f2t.ok, "f2t ok")
	assert_eq(f2t.new_state.score, 20, "foundation->tableau -10")

	var tt_state := CardStateTestkit.make_state()
	tt_state.tableau[0] = CardStateTestkit.up([_s(1, 12)])
	tt_state.tableau[1] = _col([[_s(2, 13), true]])
	tt_state.score = 7
	var tt := _scored_execution(tt_state, Move.tableau_to_tableau(0, 1, 1), SnapshotHistory.new())
	assert_true(tt.ok, "tt ok")
	assert_eq(tt.new_state.score, 7, "tableau->tableau 0 delta")

	var draw_state := CardStateTestkit.make_state()
	draw_state.stock = CardStateTestkit.down([40, 41])
	draw_state.draw_count = GameState.DRAW1
	draw_state.score = 12
	var draw := _scored_execution(draw_state, Move.draw_stock(), SnapshotHistory.new())
	assert_true(draw.ok, "draw ok")
	assert_eq(draw.new_state.score, 12, "draw 0 delta")

	var recycle_state := CardStateTestkit.make_state()
	recycle_state.waste = CardStateTestkit.up([40, 41])
	recycle_state.score = 12
	var recycle := _scored_execution(recycle_state, Move.recycle_stock(), SnapshotHistory.new())
	assert_true(recycle.ok, "recycle ok")
	assert_eq(recycle.new_state.score, 12, "recycle 0 delta")


func test_generated_flip_scores_without_extra_move_count() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true]])
	state.tableau[4] = CardPile.new()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 4, 1))
	assert_true(result.ok, "move+flip ok")
	assert_eq(result.new_state.score, 5, "only flip +5")
	assert_eq(result.new_state.move_count, 1, "single user action despite flip")
	assert_eq(result.batch.applied.size(), 2, "flip explicit in batch")


func test_negative_move_delta_floors_at_zero() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[2] = CardStateTestkit.foundation_of(2, 13)
	state.tableau[5] = CardPile.new()
	state.score = 0
	var result := MoveExecutor.execute(state, Move.foundation_to_tableau(2, 5))
	assert_true(result.ok, "f2t ok")
	assert_eq(result.new_state.score, 0, "score never negative")


func test_score_never_decides_legality() -> void:
	var state := CardStateTestkit.make_state()
	state.score = 1000
	state.tableau[0] = _col([[_s(1, 5), true]])
	state.tableau[3] = CardPile.new()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 3, 1))
	assert_false(result.ok, "huge score does not legalize a five onto empty")
	assert_eq(result.error_code, "dest_requires_king", "legality code unchanged")
	var state2 := CardStateTestkit.make_state()
	state2.score = -5
	state2.tableau[0] = _col([[_s(0, 13), true]])
	state2.tableau[3] = CardPile.new()
	var ok := MoveExecutor.execute(state2, Move.tableau_to_tableau(0, 3, 1))
	assert_true(ok.ok, "low/negative score does not block a legal king move")


func test_win_only_on_four_complete_foundations() -> void:
	var state := CardStateTestkit.make_state()
	for suit in 4:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	assert_true(WinEvaluator.is_won(state), "four complete foundations win")

	var near := CardStateTestkit.make_state()
	for suit in 3:
		near.foundation[suit] = CardStateTestkit.full_foundation(suit)
	near.foundation[3] = CardStateTestkit.foundation_of(3, 12)
	assert_false(WinEvaluator.is_won(near), "near-win does not win")

	var empty := CardStateTestkit.make_state()
	assert_false(WinEvaluator.is_won(empty), "empty board not won")
	assert_false(WinEvaluator.is_won(null), "null never wins")


func test_malformed_foundations_do_not_win() -> void:
	var mixed_suit := CardStateTestkit.make_state()
	for suit in 3:
		mixed_suit.foundation[suit] = CardStateTestkit.full_foundation(suit)
	var ids: Array = []
	for rank in range(1, 13):
		ids.append(_s(3, rank))
	ids.append(_s(0, 13))
	mixed_suit.foundation[3] = CardStateTestkit.up(ids)
	assert_false(WinEvaluator.is_won(mixed_suit), "13th card wrong suit does not win")

	var unordered := CardStateTestkit.make_state()
	for suit in 3:
		unordered.foundation[suit] = CardStateTestkit.full_foundation(suit)
	var reverse: Array = []
	for rank in range(13, 0, -1):
		reverse.append(_s(3, rank))
	unordered.foundation[3] = CardStateTestkit.up(reverse)
	assert_false(WinEvaluator.is_won(unordered), "non-ascending foundation does not win")

	var short := CardStateTestkit.make_state()
	for suit in 3:
		short.foundation[suit] = CardStateTestkit.full_foundation(suit)
	short.foundation[3] = CardStateTestkit.foundation_of(3, 11)
	assert_false(WinEvaluator.is_won(short), "undersized foundation does not win")


func test_permuted_complete_suit_slots_win() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.full_foundation(1)
	state.foundation[1] = CardStateTestkit.full_foundation(0)
	state.foundation[2] = CardStateTestkit.full_foundation(3)
	state.foundation[3] = CardStateTestkit.full_foundation(2)
	assert_true(WinEvaluator.is_won(state), "four complete suits in permuted slot order win")
	WinEvaluator.update_status(state)
	assert_eq(state.game_status, GameState.GameStatus.WON, "permuted full set becomes WON")

	var rotated := CardStateTestkit.make_state()
	rotated.foundation[0] = CardStateTestkit.full_foundation(1)
	rotated.foundation[1] = CardStateTestkit.full_foundation(2)
	rotated.foundation[2] = CardStateTestkit.full_foundation(3)
	rotated.foundation[3] = CardStateTestkit.full_foundation(0)
	assert_true(WinEvaluator.is_won(rotated), "rotated suits (every slot != index) still win")


func test_duplicate_suit_full_runs_do_not_win() -> void:
	var dup_two := CardStateTestkit.make_state()
	dup_two.foundation[0] = CardStateTestkit.full_foundation(0)
	dup_two.foundation[1] = CardStateTestkit.full_foundation(0)
	dup_two.foundation[2] = CardStateTestkit.full_foundation(1)
	dup_two.foundation[3] = CardStateTestkit.full_foundation(1)
	assert_false(WinEvaluator.is_won(dup_two), "two spade + two heart full runs do not win")
	WinEvaluator.update_status(dup_two)
	assert_eq(dup_two.game_status, GameState.GameStatus.IN_PROGRESS, "duplicate-suit board stays in progress")

	var state := CardStateTestkit.make_state()
	for slot in 4:
		state.foundation[slot] = CardStateTestkit.full_foundation(0)
	assert_false(WinEvaluator.is_won(state), "four duplicate spade runs do not win")
	WinEvaluator.update_status(state)
	assert_eq(state.game_status, GameState.GameStatus.IN_PROGRESS, "four-spade board stays in progress")


func test_face_down_foundation_card_does_not_win() -> void:
	var state := CardStateTestkit.make_state()
	for slot in 4:
		state.foundation[slot] = CardStateTestkit.full_foundation(slot)
	state.foundation[3].card_at(0).face_up = false
	assert_false(WinEvaluator.is_won(state), "face-down bottom card of a full foundation does not win")
	var top_down := CardStateTestkit.make_state()
	for slot in 4:
		top_down.foundation[slot] = CardStateTestkit.full_foundation(slot)
	top_down.foundation[1].top().face_up = false
	assert_false(WinEvaluator.is_won(top_down), "face-down top card of a full foundation does not win")


func test_win_evaluator_update_status_only_sets_when_won() -> void:
	var near := CardStateTestkit.make_state()
	for suit in 3:
		near.foundation[suit] = CardStateTestkit.full_foundation(suit)
	near.foundation[3] = CardStateTestkit.foundation_of(3, 12)
	near.game_status = GameState.GameStatus.IN_PROGRESS
	WinEvaluator.update_status(near)
	assert_eq(near.game_status, GameState.GameStatus.IN_PROGRESS, "near-win stays in progress")

	var full := CardStateTestkit.make_state()
	for suit in 4:
		full.foundation[suit] = CardStateTestkit.full_foundation(suit)
	full.game_status = GameState.GameStatus.IN_PROGRESS
	WinEvaluator.update_status(full)
	assert_eq(full.game_status, GameState.GameStatus.WON, "full set becomes WON")


func test_executor_does_not_mark_won_on_malformed_near_win() -> void:
	var state := CardStateTestkit.make_state()
	for suit in 3:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	var ids: Array = []
	for rank in range(1, 13):
		ids.append(_s(3, rank))
	ids.append(_s(0, 13))
	state.foundation[3] = CardStateTestkit.up(ids)
	state.tableau[0] = _col([[_s(1, 12), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 1, 1))
	assert_true(result.ok, "tableau move ok on malformed near-win")
	assert_eq(result.new_state.game_status, GameState.GameStatus.IN_PROGRESS, "malformed state never becomes WON")
