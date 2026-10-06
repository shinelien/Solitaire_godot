@tool
extends McpTestSuite


func suite_name() -> String:
	return "move_executor"


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


# ----- immutability basics -----

func test_success_returns_deep_distinct_state_and_keeps_source() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true]])
	state.tableau[3] = CardPile.new()
	var baseline := state.clone()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 3, 1))
	assert_true(result.ok, "king move ok")
	assert_true(result.new_state != null, "new state present")
	assert_true(state.content_equals(baseline), "source unchanged")
	assert_true(CardStateTestkit.no_shared_state(state, result.new_state), "no shared piles/cards with source")
	assert_ne(result.new_state, state, "distinct GameState")
	assert_eq(result.new_state.tableau[3].top().rank, 13, "king landed")
	assert_true(result.new_state.tableau[0].is_empty(), "source column emptied")


func test_failure_keeps_source_and_exposes_no_state() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(1, 5), true]])
	var baseline := state.clone()
	var history := SnapshotHistory.new()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 1, 1), history)
	assert_false(result.ok, "illegal move rejected")
	assert_eq(result.error_code, "dest_requires_king", "typed code passed through")
	assert_true(result.new_state == null, "no changed state on failure")
	assert_true(state.content_equals(baseline), "source untouched after failure")
	assert_eq(history.size(), 0, "failed move not snapshotted")
	var result2 := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 3, 1))
	assert_false(result2.ok, "empty dest still rejects non-king")
	assert_eq(result2.validation.error_code, "dest_requires_king", "validation attached")


func test_malformed_location_move_fails_with_zero_mutation_and_no_snapshot() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true]])
	state.tableau[3] = CardPile.new()
	var baseline := state.clone()
	var bad := Move.tableau_to_tableau(0, 3, 1)
	bad.source_location = Move.Location.LOC_FOUNDATION
	var history := SnapshotHistory.new()
	var result := MoveExecutor.execute(state, bad, history)
	assert_false(result.ok, "malformed-location move rejected")
	assert_eq(result.error_code, "invalid_location", "typed location code")
	assert_eq(result.validation.error_code, "invalid_location", "validation attached")
	assert_true(result.new_state == null, "no changed state on failure")
	assert_true(state.content_equals(baseline), "source untouched after malformed move")
	assert_eq(history.size(), 0, "malformed move not snapshotted")


func test_malformed_count_move_fails_with_zero_mutation_and_no_snapshot() -> void:
	var state := CardStateTestkit.make_state()
	state.stock = CardStateTestkit.down([1, 2, 3])
	var baseline := state.clone()
	var bad := Move.draw_stock()
	bad.count = 1
	var history := SnapshotHistory.new()
	var result := MoveExecutor.execute(state, bad, history)
	assert_false(result.ok, "malformed-count draw rejected")
	assert_eq(result.error_code, "invalid_count", "typed count code")
	assert_eq(result.validation.error_code, "invalid_count", "validation attached")
	assert_true(result.new_state == null, "no changed state on failure")
	assert_true(state.content_equals(baseline), "source untouched after malformed count")
	assert_eq(history.size(), 0, "malformed count not snapshotted")


func test_executor_null_inputs() -> void:
	var state := CardStateTestkit.make_state()
	var null_state := MoveExecutor.execute(null, Move.draw_stock())
	assert_false(null_state.ok, "null state fail")
	assert_eq(null_state.error_code, "invalid_state", "null state code")
	var null_move := MoveExecutor.execute(state, null)
	assert_false(null_move.ok, "null move fail")


# ----- per-kind application semantics -----

func test_tableau_run_move_preserves_order_without_spurious_flip() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = CardStateTestkit.up([_s(0, 13), _s(1, 12)])
	state.tableau[4] = CardPile.new()
	var baseline := state.clone()
	var result := MoveExecutor.execute(state, Move.tableau_to_tableau(0, 4, 2))
	assert_true(result.ok, "run move ok")
	assert_eq(result.new_state.tableau[4].ids(), [_s(0, 13), _s(1, 12)], "run order preserved bottom..top")
	assert_true(result.new_state.tableau[4].card_at(0).face_up, "run cards face-up")
	assert_true(result.new_state.tableau[0].is_empty(), "source column emptied")
	assert_true(result.batch.applied.size() == 1 and result.batch.generated.is_empty(), "no flip when column empties")
	assert_eq(result.batch.applied[0].kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "applied requested")
	assert_true(state.content_equals(baseline), "source unchanged")


func test_exposed_face_down_generates_explicit_flip() -> void:
	var expose := CardStateTestkit.make_state()
	expose.tableau[0] = _col([[3, false], [_s(0, 13), true]])
	expose.tableau[4] = CardPile.new()
	var baseline := expose.clone()
	var result := MoveExecutor.execute(expose, Move.tableau_to_tableau(0, 4, 1))
	assert_true(result.ok, "king off expose ok")
	assert_true(result.batch.has_generated(), "flip generated")
	assert_eq(result.batch.generated[0].kind, Move.MoveKind.FLIP_TABLEAU, "generated move is FLIP_TABLEAU")
	assert_eq(result.batch.generated[0].source_index, 0, "flip targets source column")
	assert_eq(result.batch.applied.size(), 2, "batch = requested + generated")
	assert_true(result.new_state.tableau[0].top().face_up, "exposed card now face-up")
	assert_eq(result.new_state.tableau[0].top().id, 3, "exposed card is the old face-down card")
	assert_true(expose.content_equals(baseline), "source unchanged")

	var flip_again := MoveExecutor.execute(result.new_state, Move.flip_tableau(0))
	assert_false(flip_again.ok, "no second flip once face-up")
	assert_eq(flip_again.error_code, "not_face_down", "second-flip code")


func test_tableau_to_foundation_generates_flip_when_exposed() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 1), true]])
	var result := MoveExecutor.execute(state, Move.tableau_to_foundation(0, 0))
	assert_true(result.ok, "ace to foundation ok")
	assert_eq(result.new_state.foundation[0].ids(), [_s(0, 1)], "foundation has ace")
	assert_true(result.batch.has_generated(), "flip generated on expose")
	assert_eq(result.batch.generated[0].kind, Move.MoveKind.FLIP_TABLEAU, "flip kind")
	assert_true(result.new_state.tableau[0].top().face_up, "flip applied")

	var no_expose := CardStateTestkit.make_state()
	no_expose.tableau[0] = CardStateTestkit.up([_s(1, 2)])
	no_expose.foundation[1] = CardStateTestkit.foundation_of(1, 1)
	var r2 := MoveExecutor.execute(no_expose, Move.tableau_to_foundation(0, 1))
	assert_true(r2.ok, "heart two onto heart ace ok")
	assert_true(r2.batch.generated.is_empty(), "no flip when column empties")


func test_foundation_slots_are_dynamic_not_suit_bound() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = CardStateTestkit.up([_s(1, 1)])
	var first := MoveExecutor.execute(state, Move.tableau_to_foundation(0, 0))
	assert_true(first.ok, "heart ace into empty slot 0 ok")
	assert_eq(first.new_state.foundation[0].ids(), [_s(1, 1)], "slot 0 now owns hearts")

	var second_state := first.new_state.clone()
	second_state.tableau[0] = CardStateTestkit.up([_s(1, 2)])
	var second := MoveExecutor.execute(second_state, Move.tableau_to_foundation(0, 0))
	assert_true(second.ok, "heart two onto heart-ace slot 0 ok")
	assert_eq(second.new_state.foundation[0].ids(), [_s(1, 1), _s(1, 2)], "slot 0 builds hearts ascending")

	var wrong := CardStateTestkit.make_state()
	wrong.tableau[0] = CardStateTestkit.up([_s(0, 3)])
	wrong.foundation[0] = CardStateTestkit.foundation_of(1, 2)
	var rejected := MoveExecutor.execute(wrong, Move.tableau_to_foundation(0, 0))
	assert_false(rejected.ok, "spade three onto heart slot rejected")
	assert_eq(rejected.error_code, "foundation_suit", "wrong-suit code stable")


func test_waste_moves_pop_only_waste_top() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[5] = CardPile.new()
	state.waste = CardStateTestkit.up([_s(0, 12), _s(1, 13)])
	var result := MoveExecutor.execute(state, Move.waste_to_tableau(5))
	assert_true(result.ok, "waste king to empty ok")
	assert_eq(result.new_state.tableau[5].top().id, _s(1, 13), "waste top (last drawn) moved")
	assert_eq(result.new_state.waste.ids(), [_s(0, 12)], "buried waste card untouched")
	assert_true(result.new_state.waste.top().face_up, "remaining waste top still face-up")

	var f := CardStateTestkit.make_state()
	f.waste = CardStateTestkit.up([_s(2, 2), _s(0, 1)])
	var fr := MoveExecutor.execute(f, Move.waste_to_foundation(0))
	assert_true(fr.ok, "waste ace to foundation ok")
	assert_eq(fr.new_state.foundation[0].ids(), [_s(0, 1)], "ace placed")
	assert_eq(fr.new_state.waste.ids(), [_s(2, 2)], "only top popped")


func test_foundation_to_tableau_pops_foundation_top() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[1] = CardStateTestkit.foundation_of(1, 2)
	state.tableau[0] = _col([[_s(0, 3), true]])
	var result := MoveExecutor.execute(state, Move.foundation_to_tableau(1, 0))
	assert_true(result.ok, "f2t ok")
	assert_eq(result.new_state.tableau[0].top().id, _s(1, 2), "heart two onto tableau")
	assert_eq(result.new_state.foundation[1].ids(), [_s(1, 1)], "foundation keeps ace")
	assert_true(result.new_state.tableau[0].card_at(0).face_up, "all face-up")


# ----- draw / recycle / conservation -----

func test_executor_draw1_and_draw3_reproduce_fixture_ready() -> void:
	for pool in ["bureau1", "bureau3"]:
		for draw_count in [GameState.DRAW1, GameState.DRAW3]:
			var key := "ready_draw%d" % draw_count
			var fixture: Dictionary = GoldenLoader.fixtures(pool)[0]
			var dealt := LegacyDealer.deal_dealt(pool, 0, draw_count)
			assert_true(dealt.ok, "%s#0 dealt ok draw%d" % [pool, draw_count])
			var result := MoveExecutor.execute(dealt.state, Move.draw_stock())
			assert_true(result.ok, "%s#0 executor draw ok draw%d" % [pool, draw_count])
			var expected_stock: Array = fixture.get(key).stock
			var expected_waste: Array = fixture.get(key).waste
			assert_eq(
				result.new_state.stock.ids(),
				GoldenLoader.ints_from(expected_stock),
				"%s#0 draw%d stock == fixture" % [pool, draw_count]
			)
			assert_eq(
				result.new_state.waste.ids(),
				GoldenLoader.ints_from(expected_waste),
				"%s#0 draw%d waste == fixture" % [pool, draw_count]
			)
			for i in result.new_state.waste.size():
				assert_true(result.new_state.waste.card_at(i).face_up, "%s#0 draw%d waste face-up" % [pool, draw_count])
			if not result.new_state.stock.is_empty():
				assert_false(result.new_state.stock.top().face_up, "%s#0 draw%d stock top face-down" % [pool, draw_count])
			assert_eq(result.new_state.move_count, 1, "%s#0 draw%d counts one user action" % [pool, draw_count])
			assert_eq(result.new_state.stock_passes, 0, "%s#0 draw%d no pass yet" % [pool, draw_count])
			assert_true(CardStateTestkit.conservation_ok(result.new_state), "%s#0 draw%d 52 conserved" % [pool, draw_count])


func test_partial_final_draw_pulls_min_of_stock_and_draw_count() -> void:
	for stock_count in [1, 2]:
		var state := CardStateTestkit.make_state()
		state.draw_count = GameState.DRAW3
		var stock_ids: Array = []
		for i in stock_count:
			stock_ids.append(i)
		state.stock = CardStateTestkit.down(stock_ids)
		var result := MoveExecutor.execute(state, Move.draw_stock())
		assert_true(result.ok, "partial draw ok stock=%d" % stock_count)
		assert_eq(result.new_state.waste.size(), stock_count, "draws min(3, remaining)")
		assert_true(result.new_state.stock.is_empty(), "stock emptied")
		for i in result.new_state.waste.size():
			assert_true(result.new_state.waste.card_at(i).face_up, "partial waste face-up")
		assert_eq(result.new_state.stock_passes, 0, "no recycle on partial draw")


func test_draw1_full_cycle_then_recycle_order_and_passes() -> void:
	var dealt := LegacyDealer.deal_dealt("bureau1", 0, GameState.DRAW1)
	assert_true(dealt.ok, "deal ok")
	var state := dealt.state
	var draws := 0
	while state.stock.size() > 0:
		var result := MoveExecutor.execute(state, Move.draw_stock())
		assert_true(result.ok, "draw ok stock=%d" % state.stock.size())
		state = result.new_state
		draws += 1
		assert_true(CardStateTestkit.conservation_ok(state), "conservation draw step %d" % draws)
	assert_eq(state.waste.size(), 24, "whole stock drawn into waste")
	assert_eq(draws, 24, "draw1 needs 24 draws")

	var recycle := MoveExecutor.execute(state, Move.recycle_stock())
	assert_true(recycle.ok, "recycle ok")
	assert_eq(recycle.new_state.stock_passes, 1, "one pass recorded")
	assert_true(recycle.new_state.waste.is_empty(), "waste emptied")
	assert_eq(recycle.new_state.stock.size(), 24, "stock refilled")
	for i in recycle.new_state.stock.size():
		assert_false(recycle.new_state.stock.card_at(i).face_up, "recycled stock face-down")
	assert_true(CardStateTestkit.conservation_ok(recycle.new_state), "conservation after recycle")

	var top_back := recycle.new_state.stock.top()
	var next := MoveExecutor.execute(recycle.new_state, Move.draw_stock())
	assert_true(next.ok, "draw after recycle ok")
	assert_eq(next.new_state.waste.top().id, top_back.id, "draw-after-recycle reproduces prior waste top")


func test_draw3_recycle_preserves_deterministic_waste_group() -> void:
	var dealt := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW3)
	assert_true(dealt.ok, "ready ok")
	var state := dealt.state
	var first_waste := state.waste.ids()
	while state.stock.size() > 0:
		var result := MoveExecutor.execute(state, Move.draw_stock())
		assert_true(result.ok, "draw ok")
		state = result.new_state
	var recycle := MoveExecutor.execute(state, Move.recycle_stock())
	assert_true(recycle.ok, "recycle ok")
	var redraw := MoveExecutor.execute(recycle.new_state, Move.draw_stock())
	assert_true(redraw.ok, "redraw ok")
	assert_eq(redraw.new_state.waste.ids(), first_waste, "recycled draw reproduces exact waste group")
	assert_true(CardStateTestkit.conservation_ok(redraw.new_state), "52 conserved")


func test_repeated_recycle_passes_and_52_conservation_sequence() -> void:
	var dealt := LegacyDealer.deal_ready("bureau3", 3, GameState.DRAW1)
	assert_true(dealt.ok, "ready ok")
	var state := dealt.state
	var passes := 0
	for round in 3:
		while state.stock.size() > 0:
			var r := MoveExecutor.execute(state, Move.draw_stock())
			assert_true(r.ok, "round %d draw ok" % round)
			state = r.new_state
		var recycle := MoveExecutor.execute(state, Move.recycle_stock())
		assert_true(recycle.ok, "round %d recycle ok" % round)
		state = recycle.new_state
		passes += 1
		assert_eq(state.stock_passes, passes, "stock_passes increments")
		assert_true(CardStateTestkit.conservation_ok(state), "round %d conservation" % round)
	assert_eq(passes, 3, "three unlimited passes allowed")


# ----- win boundary through the executor -----

func test_last_foundation_move_marks_won_and_blocks_further_moves() -> void:
	var state := CardStateTestkit.make_state()
	for suit in 3:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	state.foundation[3] = CardStateTestkit.foundation_of(3, 12)
	state.waste = CardStateTestkit.up([_s(3, 13)])
	assert_eq(state.game_status, GameState.GameStatus.IN_PROGRESS, "near-win in progress")
	var history := SnapshotHistory.new()
	var win := MoveExecutor.execute(state, Move.waste_to_foundation(3), history)
	assert_true(win.ok, "winning move ok")
	assert_eq(win.new_state.game_status, GameState.GameStatus.WON, "status becomes WON")
	assert_eq(win.new_state.foundation[3].size(), 13, "foundation 4 complete")
	assert_eq(win.new_state.score, 10, "winning move scored +10")
	assert_eq(win.new_state.move_count, 1, "win counts one action")
	assert_eq(history.size(), 1, "winning action snapshotted")
	assert_true(CardStateTestkit.conservation_ok(win.new_state), "52 conserved at win")

	var state2 := win.new_state.clone()
	var baseline2 := state2.clone()
	var after := MoveExecutor.execute(state2, Move.draw_stock(), history)
	assert_false(after.ok, "post-win draw rejected")
	assert_eq(after.error_code, "already_won", "already_won code")
	assert_true(state2.content_equals(baseline2), "post-win failed move mutates nothing")
	assert_eq(history.size(), 1, "post-win failure not snapshotted")

	var undo := MoveExecutor.execute_undo(state2, history)
	assert_true(undo.ok, "undo after win ok")
	assert_eq(undo.new_state.game_status, GameState.GameStatus.IN_PROGRESS, "undo returns to in-progress")
	assert_eq(undo.new_state.foundation[3].size(), 12, "winning move rolled back")


# ----- immutability for every move kind (table-driven) -----

func test_executor_table_driven_immutability_across_kinds() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	state.tableau[2] = _col([[_s(3, 12), true]])
	state.tableau[6] = CardPile.new()
	state.waste = CardStateTestkit.up([_s(1, 1)])
	state.stock = CardStateTestkit.down([5, 6, 7])
	state.draw_count = GameState.DRAW3
	var baseline := state.clone()
	var cases := [
		[Move.tableau_to_tableau(0, 1, 2), true],
		[Move.tableau_to_tableau(0, 2, 1), true],
		[Move.tableau_to_tableau(0, 1, 4), false],
		[Move.tableau_to_tableau(0, 6, 1), false],
		[Move.tableau_to_tableau(0, 0, 1), false],
		[Move.tableau_to_foundation(1, 0), false],
		[Move.waste_to_tableau(0), false],
		[Move.waste_to_foundation(1), true],
		[Move.foundation_to_tableau(0, 0), false],
		[Move.draw_stock(), true],
		[Move.recycle_stock(), false],
		[Move.flip_tableau(0), false],
	]
	for c in cases:
		var history := SnapshotHistory.new()
		var result := MoveExecutor.execute(state, c[0], history)
		assert_eq(result.ok, bool(c[1]), "%s ok? %s" % [c[0].description(), result.error_message])
		assert_true(state.content_equals(baseline), "%s source unchanged" % c[0].description())
		if result.ok:
			assert_true(result.new_state != null, "%s returns state" % c[0].description())
			assert_true(CardStateTestkit.no_shared_state(state, result.new_state), "%s no shared refs" % c[0].description())
			assert_eq(history.size(), 1, "%s snapshotted on success" % c[0].description())
		else:
			assert_true(result.new_state == null, "%s no state on failure" % c[0].description())
			assert_eq(history.size(), 0, "%s nothing recorded on failure" % c[0].description())
