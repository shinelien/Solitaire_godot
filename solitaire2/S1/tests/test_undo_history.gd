@tool
extends McpTestSuite


func suite_name() -> String:
	return "snapshot_undo"


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


## Board-only equality (piles + face flags, ignores scalar counters/status).
func _board_equals(a: GameState, b: GameState) -> bool:
	if a == null or b == null:
		return a == b
	if not a.stock.content_equals(b.stock) or not a.waste.content_equals(b.waste):
		return false
	for i in a.tableau.size():
		if not a.tableau[i].content_equals(b.tableau[i]):
			return false
	for i in a.foundation.size():
		if not a.foundation[i].content_equals(b.foundation[i]):
			return false
	return true


# ----- history container semantics -----

func test_default_capacity_is_at_least_100() -> void:
	var history := SnapshotHistory.new()
	assert_true(history.capacity() >= 100, "default capacity >= 100")
	assert_eq(history.capacity(), SnapshotHistory.DEFAULT_CAPACITY, "documented default")
	assert_eq(history.size(), 0, "starts empty")
	assert_false(history.can_undo(), "cannot undo empty")


func test_push_pop_peek_clone_isolation() -> void:
	var history := SnapshotHistory.new()
	var a := CardStateTestkit.make_state()
	a.draw_count = GameState.DRAW3
	a.stock = CardStateTestkit.down([1, 2, 3])
	assert_true(history.push(a), "push ok")
	assert_eq(history.size(), 1, "one snapshot")
	assert_true(history.can_undo(), "can undo")

	var peeked := history.peek()
	assert_true(peeked.content_equals(a), "peek equals pushed")
	assert_ne(peeked, a, "peek is a distinct state")
	assert_eq(history.size(), 1, "peek does not consume")
	peeked.draw_count = GameState.DRAW1
	var peeked2 := history.peek()
	assert_eq(peeked2.draw_count, GameState.DRAW3, "mutating peek clone does not touch history")

	var popped := history.pop()
	assert_true(popped.content_equals(a), "pop equals pushed")
	assert_ne(popped, a, "pop is distinct state")
	assert_eq(history.size(), 0, "pop consumed")
	assert_false(history.can_undo(), "empty again")
	assert_true(history.pop() == null, "pop of empty returns null")

	assert_false(history.push(null), "null push rejected")
	history.clear()
	assert_eq(history.size(), 0, "clear empties")


func test_capacity_eviction_is_deterministic_fifo() -> void:
	var history := SnapshotHistory.new(3)
	assert_eq(history.capacity(), 3, "custom capacity honored")
	for i in 5:
		var s := CardStateTestkit.make_state()
		s.move_count = i
		s.score = i * 10
		assert_true(history.push(s), "push %d" % i)
	assert_eq(history.size(), 3, "size capped at capacity")
	assert_eq(history.peek().move_count, 4, "newest retained")
	assert_true(history.pop().move_count == 4, "pop newest first")
	assert_true(history.pop().move_count == 3, "pop second")
	assert_true(history.pop().move_count == 2, "oldest retained evicted 0 and 1 first")
	assert_false(history.can_undo(), "exhausted")


func test_only_successful_executions_are_snapshotted() -> void:
	var history := SnapshotHistory.new()
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(1, 12), true]])
	var fail := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 1, 1), history)
	assert_false(fail.ok, "illegal rejected")
	assert_eq(history.size(), 0, "failure not recorded")
	state.tableau[0] = _col([[_s(0, 13), true]])
	state.tableau[3] = CardPile.new()
	var ok := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 3, 1), history)
	assert_true(ok.ok, "legal executed")
	assert_eq(history.size(), 1, "success recorded")


# ----- undo semantics per action kind -----

func test_undo_tableau_flip_move_is_atomic() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true]])
	state.tableau[4] = CardPile.new()
	var history := SnapshotHistory.new()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 4, 1), history)
	assert_true(result.ok, "move+flip ok")
	assert_true(result.batch.has_generated(), "flip in batch")
	assert_eq(result.new_state.tableau[0].top().face_up, true, "flipped before undo")

	var undo := MoveExecutor.execute_undo(result.new_state, history)
	assert_true(undo.ok, "undo ok")
	assert_true(undo.undoes(), "undo boundary identity")
	assert_true(_board_equals(undo.new_state, state), "board fully restored")
	assert_true(undo.new_state.tableau[0].card_at(0).face_up == false, "exposed card face-down again")
	assert_eq(undo.new_state.tableau[0].top().id, _s(0, 13), "king back on source column")
	assert_true(undo.new_state.tableau[4].is_empty(), "empty column restored")
	assert_eq(undo.new_state.score, 0, "undo of pre-zero flips floors at 0")
	assert_eq(undo.new_state.move_count, 1, "undo counts as one user action")
	assert_eq(history.size(), 0, "snapshot consumed")


func test_undo_draw_and_recycle_restores_exact_ready_state() -> void:
	for draw_count in [GameState.DRAW1, GameState.DRAW3]:
		var dealt := LegacyDealer.deal_dealt("bureau1", 0, draw_count)
		assert_true(dealt.ok, "dealt ok draw%d" % draw_count)
		var history := SnapshotHistory.new()
		var after_draw := MoveExecutor.execute(dealt.state, Move.draw_stock(), history)
		assert_true(after_draw.ok, "draw ok draw%d" % draw_count)
		var ready_expected := LegacyDealer.deal_ready("bureau1", 0, draw_count).state
		assert_true(_board_equals(after_draw.new_state, ready_expected), "draw board == ready fixture draw%d" % draw_count)

		var undo_draw := MoveExecutor.execute_undo(after_draw.new_state, history)
		assert_true(undo_draw.ok, "undo draw ok draw%d" % draw_count)
		assert_true(_board_equals(undo_draw.new_state, dealt.state), "undo returns to dealt board draw%d" % draw_count)
		assert_eq(undo_draw.new_state.move_count, 1, "undo counted draw%d" % draw_count)


func test_undo_recycle_restores_stock_and_waste() -> void:
	var dealt := LegacyDealer.deal_dealt("bureau1", 0, GameState.DRAW1)
	assert_true(dealt.ok, "deal ok")
	var history := SnapshotHistory.new()
	var current: GameState = dealt.state
	while current.stock.size() > 0:
		var r := MoveExecutor.execute(current, Move.draw_stock(), history)
		assert_true(r.ok, "draw ok")
		current = r.new_state
	var before_recycle := current.clone()
	var recycle := MoveExecutor.execute(current, Move.recycle_stock(), history)
	assert_true(recycle.ok, "recycle ok")
	assert_eq(recycle.new_state.stock_passes, 1, "pass recorded")

	var undo := MoveExecutor.execute_undo(recycle.new_state, history)
	assert_true(undo.ok, "undo recycle ok")
	assert_true(_board_equals(undo.new_state, before_recycle), "recycle undone exactly")
	assert_eq(undo.new_state.stock_passes, 0, "pass rolled back")
	assert_eq(undo.new_state.move_count, before_recycle.move_count + 1, "undo action count")


func test_multi_action_undo_walks_back_each_snapshot() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[4, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	state.tableau[2] = _col([[_s(3, 12), true]])
	state.tableau[4] = CardPile.new()
	state.stock = CardStateTestkit.down([18, 19, 20])
	state.draw_count = GameState.DRAW3
	var moves := [
		Move.tableau_to_tableau(0, 2, 1),
		Move.tableau_to_tableau(0, 1, 1),
		Move.tableau_to_tableau(0, 4, 1),
		Move.draw_stock(),
		Move.recycle_stock(),
		Move.draw_stock(),
	]
	var history := SnapshotHistory.new()
	var current := state.clone()
	var pre_boards: Array = []
	var pre_scores: Array = []
	for move in moves:
		pre_boards.append(current.clone())
		pre_scores.append(current.score)
		var r := MoveExecutor.execute(current, move, history)
		assert_true(r.ok, "action ok: %s %s" % [move.description(), r.error_message])
		current = r.new_state
	assert_eq(history.size(), moves.size(), "all actions snapshotted")
	assert_eq(current.score, 5, "only the flip scored (king move 0 + flip 5)")

	var idx := moves.size()
	while history.can_undo():
		idx -= 1
		var undo := MoveExecutor.execute_undo(current, history)
		assert_true(undo.ok, "undo step %d ok" % idx)
		assert_true(
			_board_equals(undo.new_state, pre_boards[idx]),
			"undo step %d restores exact board" % idx
		)
		var want_score := LegacyScorePolicy.undo_score(int(pre_scores[idx]))
		assert_eq(undo.new_state.score, want_score, "undo step %d score policy" % idx)
		var snapshot_state: GameState = pre_boards[idx]
		assert_eq(undo.new_state.move_count, snapshot_state.move_count + 1, "undo step %d action count" % idx)
		current = undo.new_state
	assert_eq(idx, 0, "walked back through every action")
	assert_true(_board_equals(current, state), "final board equals original")
	var empty_undo := MoveExecutor.execute_undo(current, history)
	assert_false(empty_undo.ok, "empty undo fails")
	assert_eq(empty_undo.error_code, MoveExecutionResult.CODE_NOTHING_TO_UNDO, "typed empty undo code")
	assert_true(empty_undo.new_state == null, "empty undo no state")


func test_undo_after_win_returns_to_in_progress_and_exact() -> void:
	var state := CardStateTestkit.make_state()
	for suit in 3:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	state.foundation[3] = CardStateTestkit.foundation_of(3, 12)
	state.waste = CardStateTestkit.up([_s(3, 13)])
	var history := SnapshotHistory.new()
	var win := MoveExecutor.execute(state, Move.waste_to_foundation(3), history)
	assert_true(win.ok, "win move ok")
	assert_eq(win.new_state.game_status, GameState.GameStatus.WON, "now won")
	var undo := MoveExecutor.execute_undo(win.new_state, history)
	assert_true(undo.ok, "undo win ok")
	assert_eq(undo.new_state.game_status, GameState.GameStatus.IN_PROGRESS, "back in progress")
	assert_true(_board_equals(undo.new_state, state), "exact pre-win board")
	assert_eq(undo.new_state.foundation[3].size(), 12, "foundation truncated")
	assert_eq(undo.new_state.score, LegacyScorePolicy.undo_score(state.score), "score policy at win undo")


func test_execute_undo_with_null_or_empty_history_is_typed_failure() -> void:
	var state := CardStateTestkit.make_state()
	var null_result := MoveExecutor.execute_undo(state, null)
	assert_false(null_result.ok, "null history fails")
	assert_eq(null_result.error_code, "nothing_to_undo", "null history code")
	var fresh := SnapshotHistory.new()
	var empty_result := MoveExecutor.execute_undo(state, fresh)
	assert_false(empty_result.ok, "empty history fails")
	assert_eq(empty_result.error_code, "nothing_to_undo", "empty history code")
	assert_true(empty_result.new_state == null, "no state exposed")


func test_undo_restores_no_shared_references() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true]])
	state.tableau[4] = CardPile.new()
	var history := SnapshotHistory.new()
	var forward := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 4, 1), history)
	assert_true(forward.ok, "forward ok")
	var undo := MoveExecutor.execute_undo(forward.new_state, history)
	assert_true(undo.ok, "undo ok")
	assert_true(CardStateTestkit.no_shared_state(forward.new_state, undo.new_state), "no shared refs with pre-undo state")
	assert_true(CardStateTestkit.no_shared_state(state, undo.new_state), "no shared refs with original")
	var snapshot := history.peek()
	assert_true(snapshot == null, "history empty after single undo")


func test_undo_result_new_state_never_aliases_history() -> void:
	var history := SnapshotHistory.new(2)
	for i in 2:
		var s := CardStateTestkit.make_state()
		s.score = i
		history.push(s)
	var undo := MoveExecutor.execute_undo(CardStateTestkit.make_state(), history)
	assert_true(undo.ok, "undo ok")
	assert_eq(undo.new_state.score, 0, "snapshot 0 score floored")
	assert_eq(history.size(), 1, "one left")
	var second := MoveExecutor.execute_undo(CardStateTestkit.make_state(), history)
	assert_true(second.ok, "second undo ok")
	assert_eq(second.new_state.score, 0, "second snapshot score floored")
	assert_true(history.is_empty(), "history exhausted")
