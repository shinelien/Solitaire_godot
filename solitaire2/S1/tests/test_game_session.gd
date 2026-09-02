@tool
extends McpTestSuite


func suite_name() -> String:
	return "game_session"


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


## Board-only equality: ignores counters/score/status that legitimately drift
## across undo (undo restores the position but counts one user action).
func _board_eq(a: GameState, b: GameState) -> bool:
	if a == null or b == null:
		return false
	var ca := a.clone()
	var cb := b.clone()
	ca.move_count = 0
	ca.score = 0
	ca.stock_passes = 0
	ca.game_status = GameState.GameStatus.IN_PROGRESS
	cb.move_count = 0
	cb.score = 0
	cb.stock_passes = 0
	cb.game_status = GameState.GameStatus.IN_PROGRESS
	return ca.content_equals(cb)


## Apply up to max hint-driven legal moves; stops early when no hint remains.
func _drive_hints(session: GameSession, max_moves: int) -> int:
	var applied := 0
	for i in max_moves:
		var h := session.hint()
		if not h.ok:
			break
		var r := session.apply_move(h.move)
		if not r.ok:
			break
		applied += 1
		if session.state_snapshot().game_status == GameState.GameStatus.WON:
			break
	return applied


# ----- creation -----

func test_create_ready_state_matches_dealer_and_identity() -> void:
	for draw_mode in [GameState.DRAW1, GameState.DRAW3]:
		var created := GameSession.create("bureau1", 0, draw_mode)
		assert_true(created.ok, "session created draw%d" % draw_mode)
		var session := created.session
		assert_eq(session.deal_pool(), "bureau1", "pool")
		assert_eq(session.deal_index(), 0, "index")
		assert_eq(session.draw_count(), draw_mode, "draw mode kept")
		assert_eq(session.deal_key(), "bureau1#0", "deal key")
		var expected := LegacyDealer.deal_ready("bureau1", 0, draw_mode)
		assert_true(expected.ok, "expected deal ok")
		assert_true(session.state_snapshot().content_equals(expected.state), "owned state == fresh ready state draw%d" % draw_mode)
		assert_eq(session.history_size(), 0, "fresh session has empty history")
		assert_true(CardStateTestkit.conservation_ok(session.state_snapshot()), "52 conserved")


func test_create_rejects_invalid_pool_index_and_draw_mode() -> void:
	var bad_pool := GameSession.create("bogus", 0, GameState.DRAW1)
	assert_false(bad_pool.ok, "unknown pool rejected")
	assert_eq(bad_pool.error_code, GameSessionResult.CODE_INVALID_POOL, "invalid_pool code")

	var neg := GameSession.create("bureau1", -1, GameState.DRAW1)
	assert_false(neg.ok, "negative index rejected")
	assert_eq(neg.error_code, GameSessionResult.CODE_INDEX_OUT_OF_RANGE, "index_out_of_range code")

	var too_high := GameSession.create("bureau3", 4999, GameState.DRAW1)
	assert_false(too_high.ok, "out-of-range index rejected")
	assert_eq(too_high.error_code, GameSessionResult.CODE_INDEX_OUT_OF_RANGE, "index code")

	var bad_draw := GameSession.create("bureau1", 0, 2)
	assert_false(bad_draw.ok, "draw mode 2 rejected")
	assert_eq(bad_draw.error_code, GameSessionResult.CODE_INVALID_DRAW_COUNT, "invalid_draw_count code")


# ----- apply / undo routing -----

func test_apply_move_then_undo_routes_through_executor() -> void:
	var created := GameSession.create("bureau1", 0, GameState.DRAW1)
	assert_true(created.ok, "session created")
	var session := created.session
	var before := session.state_snapshot()
	assert_true(session.can_undo() == false, "nothing to undo initially")

	var first := session.apply_move(Move.draw_stock())
	assert_true(first.ok, "draw applied")
	assert_true(first.batch.requested.kind == Move.MoveKind.DRAW_STOCK, "requested draw visible in batch")
	assert_eq(session.history_size(), 1, "history recorded")
	assert_true(session.can_undo(), "can undo after a move")

	var after_first := session.state_snapshot()
	assert_true(after_first.waste.size() > before.waste.size(), "draw grew the waste")
	assert_false(session.state_snapshot().content_equals(before), "state advanced")

	var undo := session.undo()
	assert_true(undo.ok, "undo ok")
	assert_true(undo.undoes(), "undo result boundary identity")
	assert_true(_board_eq(undo.new_state, before), "undo restores pre-draw board")
	assert_eq(session.history_size(), 0, "history consumed")
	assert_true(_board_eq(session.state_snapshot(), before), "session state back to pre-draw board")

	var empty_undo := session.undo()
	assert_false(empty_undo.ok, "undo on empty history rejected")
	assert_eq(empty_undo.error_code, MoveExecutionResult.CODE_NOTHING_TO_UNDO, "typed nothing_to_undo")


func test_apply_boundary_identities_rejected_typed_without_mutation() -> void:
	var created := GameSession.create("bureau1", 0, GameState.DRAW1)
	assert_true(created.ok, "created")
	var session := created.session
	var baseline := session.state_snapshot()
	var replay := session.apply_move(Move.replay())
	assert_false(replay.ok, "REPLAY is not an ordinary gameplay move")
	assert_eq(replay.error_code, "invalid_kind", "typed invalid_kind for REPLAY")
	var new_deal := session.apply_move(Move.new_deal())
	assert_false(new_deal.ok, "NEW_DEAL is not an ordinary gameplay move")
	assert_eq(new_deal.error_code, "invalid_kind", "typed invalid_kind for NEW_DEAL")
	var undo := session.apply_move(Move.undo())
	assert_false(undo.ok, "UNDO not accepted through apply_move")
	assert_eq(undo.error_code, "invalid_kind", "typed invalid_kind for UNDO")
	assert_true(session.state_snapshot().content_equals(baseline), "state untouched by rejected boundaries")
	assert_eq(session.history_size(), 0, "history untouched by rejected boundaries")


# ----- replay / new deal boundaries -----

func test_replay_restores_exact_initial_ready_state_and_clears_history() -> void:
	var created := GameSession.create("bureau1", 0, GameState.DRAW3)
	assert_true(created.ok, "created")
	var session := created.session
	var initial := session.state_snapshot()
	var applied := _drive_hints(session, 40)
	assert_true(applied >= 1, "several moves were applied (got %d)" % applied)
	assert_true(session.history_size() >= 1, "history non-empty before replay")

	var replay := session.replay()
	assert_true(replay.ok, "replay ok")
	assert_eq(replay.batch.requested.kind, Move.MoveKind.REPLAY, "boundary move visible")
	assert_eq(replay.batch.applied[0].kind, Move.MoveKind.REPLAY, "applied is the REPLAY identity")
	assert_eq(session.deal_key(), "bureau1#0", "deal identity unchanged")
	assert_eq(session.history_size(), 0, "history cleared")
	var restored := session.state_snapshot()
	assert_true(restored.content_equals(initial), "board equals the initial ready state")
	assert_eq(restored.move_count, 0, "move counter reset")
	assert_eq(restored.stock_passes, 0, "pass counter reset")
	var fresh := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW3)
	assert_true(fresh.ok, "fresh ready ok")
	assert_true(restored.content_equals(fresh.state), "replayed state == freshly dealt ready state")
	assert_true(CardStateTestkit.conservation_ok(restored), "52 conserved after replay")


func test_new_deal_deterministic_next_index_same_mode_clears_history() -> void:
	var created := GameSession.create("bureau3", 5, GameState.DRAW3)
	assert_true(created.ok, "created")
	var session := created.session
	var applied := _drive_hints(session, 10)
	assert_true(applied >= 1 or session.state_snapshot().move_count > 0 or session.history_size() > 0, "session advanced")
	assert_eq(session.deal_index(), 5, "starts at index 5")

	var nd := session.new_deal()
	assert_true(nd.ok, "new deal ok")
	assert_eq(nd.batch.requested.kind, Move.MoveKind.NEW_DEAL, "boundary move visible")
	assert_eq(nd.batch.applied[0].kind, Move.MoveKind.NEW_DEAL, "applied is the NEW_DEAL identity")
	assert_eq(session.deal_index(), 6, "deterministic next index")
	assert_eq(session.deal_pool(), "bureau3", "same pool")
	assert_eq(session.draw_count(), GameState.DRAW3, "same draw mode")
	assert_eq(session.history_size(), 0, "history cleared")
	var expected := LegacyDealer.deal_ready("bureau3", 6, GameState.DRAW3)
	assert_true(expected.ok, "expected deal ok")
	assert_true(session.state_snapshot().content_equals(expected.state), "state == freshly dealt bureau3#6")
	assert_true(CardStateTestkit.conservation_ok(session.state_snapshot()), "52 conserved")


func test_new_deal_wraps_and_selector_rejects_invalid() -> void:
	var created := GameSession.create("bureau3", 4998, GameState.DRAW1)
	assert_true(created.ok, "created at last bureau3 index")
	var session := created.session
	var nd := session.new_deal()
	assert_true(nd.ok, "wrap new deal ok")
	assert_eq(session.deal_index(), 0, "wraps to index 0")
	var expected := LegacyDealer.deal_ready("bureau3", 0, GameState.DRAW1)
	assert_true(expected.ok, "expected ok")
	assert_true(session.state_snapshot().content_equals(expected.state), "wrapped state == bureau3#0")
	assert_eq(session.draw_count(), GameState.DRAW1, "draw mode preserved")

	var neg := DeterministicDealSelector.next_index(-1, 4999)
	assert_false(neg.ok, "negative current rejected")
	assert_eq(neg.error_code, "invalid_current_index", "current-index code")
	var over := DeterministicDealSelector.next_index(4999, 4999)
	assert_false(over.ok, "out-of-range current rejected")
	var singleton := DeterministicDealSelector.next_index(0, 1)
	assert_false(singleton.ok, "singleton pool rejected")
	assert_eq(singleton.error_code, "singleton_pool", "singleton code")
	var bad_count := DeterministicDealSelector.next_index(0, -3)
	assert_false(bad_count.ok, "negative pool count rejected")
	var ok_sel := DeterministicDealSelector.next_index(32083, 32084)
	assert_true(ok_sel.ok, "valid selector")
	assert_eq(ok_sel.next_index, 0, "(last+1) mod count wraps to 0")


# ----- read-only hint/plan + clone-safe getters -----

func test_hint_and_plan_never_mutate_session() -> void:
	var created := GameSession.create("bureau1", 0, GameState.DRAW1)
	assert_true(created.ok, "created")
	var session := created.session
	var baseline := session.state_snapshot()
	var history_before := session.history_size()
	var h := session.hint()
	if h.ok:
		assert_eq(h.move.key(), session.hint().move.key(), "session hint deterministic")
	var plan := session.plan_auto_complete()
	assert_true(plan != null, "typed plan result always returned")
	assert_true(session.state_snapshot().content_equals(baseline), "hint/plan left session state unchanged")
	assert_eq(session.history_size(), history_before, "hint/plan left history unchanged")


func test_state_getter_returns_independent_clone() -> void:
	var created := GameSession.create("bureau1", 0, GameState.DRAW3)
	assert_true(created.ok, "created")
	var session := created.session
	var baseline := session.state_snapshot()
	var tampered := session.state_snapshot()
	tampered.stock.add_top(CardData.new(_s(3, 5), false))
	tampered.waste.top().face_up = false
	if tampered.tableau[0].size() > 0:
		tampered.tableau[0].top().face_up = false
	assert_true(session.state_snapshot().content_equals(baseline), "mutating the returned clone cannot corrupt the session")

	var apply_result := session.apply_move(Move.draw_stock())
	assert_true(apply_result.ok, "draw ok")
	var expected_after := session.state_snapshot()
	apply_result.new_state.foundation[0].add_top(CardData.new(_s(2, 1), true))
	assert_true(session.state_snapshot().content_equals(expected_after), "mutating a returned result state cannot corrupt the session")


func test_two_sessions_same_deal_share_hint_and_plan_determinism() -> void:
	var a := GameSession.create("bureau1", 3, GameState.DRAW1)
	var b := GameSession.create("bureau1", 3, GameState.DRAW1)
	assert_true(a.ok and b.ok, "both created")
	var ha := a.session.hint()
	var hb := b.session.hint()
	assert_eq(ha.ok, hb.ok, "hint availability identical")
	if ha.ok and hb.ok:
		assert_eq(ha.move.key(), hb.move.key(), "identical deals hint identically")
	var pa := a.session.plan_auto_complete()
	var pb := b.session.plan_auto_complete()
	assert_eq(pa.eligible, pb.eligible, "plan eligibility identical")
