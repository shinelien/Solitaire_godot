@tool
extends McpTestSuite


func suite_name() -> String:
	return "legacy_dealer"


func test_deal_dealt_bureau1_record0_draw1() -> void:
	var result := LegacyDealer.deal_dealt("bureau1", 0, GameState.DRAW1)
	assert_true(result.ok, "deal ok")
	assert_true(result.state != null, "state present")
	var state: GameState = result.state
	assert_eq(state.deal_pool, "bureau1", "deal_pool")
	assert_eq(state.deal_index, 0, "deal_index")
	assert_eq(state.deal_source, "Resources/data/bureau1.d", "deal_source")
	assert_eq(state.draw_count, GameState.DRAW1, "draw_count stored")
	assert_eq(state.tableau.size(), 7, "7 tableau columns")
	assert_eq(state.stock.size(), 24, "24 stock cards")
	assert_eq(state.waste.size(), 0, "waste empty in dealt snapshot")
	assert_true(state.foundation[0].is_empty(), "foundation empty")
	assert_eq(state.game_status, GameState.GameStatus.IN_PROGRESS, "status in progress")


func test_deal_ready_draw1_and_draw3_sizes_and_face_up() -> void:
	var r1 := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW1)
	assert_true(r1.ok, "ready draw1 ok")
	assert_eq(r1.state.stock.size(), 23, "draw1 stock 23")
	assert_eq(r1.state.waste.size(), 1, "draw1 waste 1")
	assert_true(r1.state.waste.top().face_up, "draw1 waste top face-up")
	assert_false(r1.state.stock.top().face_up, "draw1 remaining stock top face-down")

	var r3 := LegacyDealer.deal_ready("bureau1", 0, GameState.DRAW3)
	assert_true(r3.ok, "ready draw3 ok")
	assert_eq(r3.state.stock.size(), 21, "draw3 stock 21")
	assert_eq(r3.state.waste.size(), 3, "draw3 waste 3")
	assert_eq(r3.state.waste.ids(), [23, 42, 43], "draw3 waste bottom..top from stock top pops")
	assert_true(r3.state.waste.top().face_up, "draw3 waste top face-up")
	assert_eq(r3.state.waste.card_at(0).id, 23, "first popped bottom of waste")
	assert_eq(r3.state.waste.card_at(2).id, 43, "last popped is waste top (playable)")


func test_dealt_and_ready_are_distinct_no_shared_cards() -> void:
	var dealt := LegacyDealer.deal_dealt("bureau3", 7, GameState.DRAW3)
	var ready := LegacyDealer.deal_ready("bureau3", 7, GameState.DRAW3)
	assert_true(dealt.ok and ready.ok, "both ok")
	assert_true(dealt.state.waste.is_empty(), "dealt waste empty")
	assert_eq(ready.state.waste.size(), 3, "ready waste populated")
	assert_ne(dealt.state.stock, ready.state.stock, "separate stock piles")
	assert_ne(dealt.state.stock.top(), ready.state.stock.top(), "separate card instances")


func test_dealer_deterministic_two_runs_equal() -> void:
	var a := LegacyDealer.deal_ready("bureau1", 5, GameState.DRAW3)
	var b := LegacyDealer.deal_ready("bureau1", 5, GameState.DRAW3)
	assert_true(a.ok and b.ok, "both ok")
	assert_true(a.state.content_equals(b.state), "two deals identical")
	assert_ne(a.state, b.state, "distinct states")
	assert_true(a.state.waste.content_equals(b.state.waste), "waste identical")


func test_dealer_source_record_not_mutated() -> void:
	var fetch := LegacyDealRepository.get_record("bureau1", 0)
	var text_before: String = fetch.record
	var result := LegacyDealer.deal_ready_from_record(
		String(fetch.record), "bureau1", 0, GameState.DRAW3, "Resources/data/bureau1.d"
	)
	assert_true(result.ok, "deal ok")
	assert_eq(String(fetch.record), text_before, "record string unchanged by dealer")


func test_dealer_rejects_invalid_draw_count() -> void:
	var fetch := LegacyDealRepository.get_record("bureau1", 0)
	for bad in [0, 2, 4, -1]:
		var result := LegacyDealer.deal_dealt_from_record(
			fetch.record, "bureau1", 0, bad, "Resources/data/bureau1.d"
		)
		assert_false(result.ok, "reject draw_count %d" % bad)
		assert_eq(result.error_code, "invalid_draw_count", "draw_count code %d" % bad)
		assert_true(result.state == null, "no state on failure")


func test_dealer_rejects_invalid_record() -> void:
	var result := LegacyDealer.deal_dealt_from_record("short", "bureau1", 0, 1, "x")
	assert_false(result.ok, "reject short record")
	assert_eq(result.error_code, "invalid_record", "record error code")
	var bad_bytes_result := LegacyDealer.deal_dealt_from_record("x".repeat(52), "bureau1", 0, 1, "x")
	assert_false(bad_bytes_result.ok, "reject illegal-byte record")


func test_dealer_rejects_unknown_pool_and_out_of_range_index() -> void:
	var unknown := LegacyDealer.deal_dealt("nope", 0, GameState.DRAW1)
	assert_false(unknown.ok, "unknown pool rejected")
	assert_eq(unknown.error_code, "invalid_pool", "pool error code")

	var neg := LegacyDealer.deal_dealt("bureau1", -1, GameState.DRAW1)
	assert_false(neg.ok, "negative index rejected")
	assert_eq(neg.error_code, "index_out_of_range", "negative index code")

	var past := LegacyDealer.deal_dealt("bureau1", 32084, GameState.DRAW1)
	assert_false(past.ok, "past-end index rejected")
	assert_eq(past.error_code, "index_out_of_range", "past-end code")

	var past3 := LegacyDealer.deal_dealt("bureau3", 4999, GameState.DRAW1)
	assert_false(past3.ok, "bureau3 past-end rejected")
