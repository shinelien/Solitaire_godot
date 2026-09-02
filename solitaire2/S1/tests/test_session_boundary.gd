@tool
extends McpTestSuite


func suite_name() -> String:
	return "boundary_moves"


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


func test_rules_engine_rejects_replay_and_new_deal_as_non_gameplay() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = CardStateTestkit.up([_s(0, 13)])
	state.tableau[3] = CardPile.new()
	var replay := RulesEngine.validate(state, Move.replay())
	assert_false(replay.ok, "REPLAY is not a gameplay move")
	assert_eq(replay.error_code, "invalid_kind", "typed invalid_kind")
	var new_deal := RulesEngine.validate(state, Move.new_deal())
	assert_false(new_deal.ok, "NEW_DEAL is not a gameplay move")
	assert_eq(new_deal.error_code, "invalid_kind", "typed invalid_kind")
	var undo := RulesEngine.validate(state, Move.undo())
	assert_false(undo.ok, "UNDO remains rejected")
	assert_eq(undo.error_code, "invalid_kind", "undo invalid_kind")


func test_executor_rejects_boundary_moves_zero_mutation_no_snapshot() -> void:
	for boundary in [Move.replay(), Move.new_deal()]:
		var state := CardStateTestkit.make_state()
		state.tableau[0] = CardStateTestkit.up([_s(0, 13)])
		state.tableau[3] = CardPile.new()
		var baseline := state.clone()
		var history := SnapshotHistory.new()
		var result := MoveExecutor.execute(state, boundary, history)
		assert_false(result.ok, "%s rejected by ordinary execute" % boundary.description())
		assert_eq(result.error_code, "invalid_kind", "typed rejection for %s" % boundary.description())
		assert_true(result.new_state == null, "no changed state on rejection")
		assert_true(state.content_equals(baseline), "source untouched")
		assert_eq(history.size(), 0, "no snapshot recorded")


func test_execute_boundary_returns_cloned_target_with_explicit_batch() -> void:
	for boundary in [Move.replay(), Move.new_deal()]:
		var current := CardStateTestkit.make_state()
		current.tableau[0] = CardStateTestkit.up([_s(0, 13)])
		current.move_count = 7
		current.stock_passes = 3
		current.score = 40
		var target := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW1)
		assert_true(target.ok, "target ready ok")
		var target_clone := target.state.clone()
		var result := MoveExecutor.execute_boundary(current, target.state, boundary)
		assert_true(result.ok, "%s boundary ok" % boundary.description())
		assert_eq(result.batch.requested.kind, boundary.kind, "boundary requested visible")
		assert_eq(result.batch.applied.size(), 1, "single applied move")
		assert_eq(result.batch.applied[0].kind, boundary.kind, "applied boundary identity")
		assert_eq(result.new_state.move_count, 0, "counters reset in restored clone")
		assert_eq(result.new_state.stock_passes, 0, "passes reset")
		assert_eq(result.new_state.deal_index, 0, "deal identity of the target")
		assert_true(result.new_state.content_equals(target.state), "restored == target ready state")
		assert_ne(result.new_state, target.state, "distinct GameState instance")
		assert_true(CardStateTestkit.no_shared_state(target.state, result.new_state), "no shared cards/piles with target")
		assert_true(CardStateTestkit.no_shared_state(current, result.new_state), "no shared cards/piles with current")

		result.new_state.tableau[0].add_top(CardData.new(_s(1, 1), true))
		assert_true(target.state.content_equals(target_clone), "mutating the restored clone cannot touch the target")


func test_execute_boundary_rejects_non_boundary_and_null() -> void:
	var state := CardStateTestkit.make_state()
	var target := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW1)
	assert_true(target.ok, "target ok")
	var bad_kind := MoveExecutor.execute_boundary(state, target.state, Move.draw_stock())
	assert_false(bad_kind.ok, "gameplay draw is not a boundary")
	assert_eq(bad_kind.error_code, "invalid_kind", "typed rejection for non-boundary")
	var null_boundary := MoveExecutor.execute_boundary(state, target.state, null)
	assert_false(null_boundary.ok, "null boundary rejected")
	var null_target := MoveExecutor.execute_boundary(state, null, Move.replay())
	assert_false(null_target.ok, "null target rejected")
	assert_eq(null_target.error_code, "invalid_state", "typed invalid_state")
	var null_current := MoveExecutor.execute_boundary(null, target.state, Move.replay())
	assert_false(null_current.ok, "null current rejected")
	assert_eq(null_current.error_code, "invalid_state", "typed invalid_state")
	assert_true(state.content_equals(state.clone()), "source never mutated across boundary misuse")


func test_boundary_kind_names_and_factories() -> void:
	assert_eq(Move.kind_name(Move.MoveKind.REPLAY), "REPLAY", "replay kind name")
	assert_eq(Move.kind_name(Move.MoveKind.NEW_DEAL), "NEW_DEAL", "new deal kind name")
	assert_eq(Move.replay().key(), "REPLAY:unknown(-1)[-1]->unknown(-1)[-1]x1", "replay canonical key")
	assert_eq(Move.new_deal().key(), "NEW_DEAL:unknown(-1)[-1]->unknown(-1)[-1]x1", "new deal canonical key")
	assert_true(Move.undo().is_boundary() and Move.replay().is_boundary() and Move.new_deal().is_boundary(), "all boundary identities flagged")
