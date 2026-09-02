@tool
extends McpTestSuite


func suite_name() -> String:
	return "golden_deal"


const CANONICAL_RECORD0 := "935879b0483480ea8f936cdc2c2b236d532d2b9531f800b19173f8dd50d620e3"


func test_dealt_matches_all_fixtures() -> void:
	for pool in ["bureau1", "bureau3"]:
		var problems: Array[String] = []
		for fixture in GoldenLoader.fixtures(pool):
			var index := int(fixture.index)
			var result := LegacyDealer.deal_dealt(pool, index, GameState.DRAW1)
			if not result.ok:
				problems.append("%s#%d deal failed: %s" % [pool, index, result.error_message])
				continue
			var state: GameState = result.state
			if state.deal_pool != pool or state.deal_index != index:
				problems.append("%s#%d deal identity wrong" % [pool, index])
			var decode := LegacyDealDecoder.decode_record(String(fixture.raw_deal))
			if not decode.ok or decode.ids != GoldenLoader.ints_from(fixture.consumption):
				problems.append("%s#%d consumption mismatch" % [pool, index])
			var expected_ids := GoldenLoader.tableau_ids_from(fixture.dealt.tableau)
			var expected_flags := GoldenLoader.tableau_face_up_from(fixture.dealt.tableau)
			if state.tableau.size() != expected_ids.size():
				problems.append("%s#%d tableau column count" % [pool, index])
			for col in state.tableau.size():
				if col >= expected_ids.size():
					break
				if state.tableau[col].ids() != expected_ids[col]:
					problems.append("%s#%d tableau col %d ids" % [pool, index, col])
				for row in state.tableau[col].size():
					var want_flag := bool(expected_flags[col][row])
					if state.tableau[col].card_at(row).face_up != want_flag:
						problems.append("%s#%d tableau col %d row %d face_up" % [pool, index, col, row])
			if state.stock.ids() != GoldenLoader.ints_from(fixture.dealt.stock):
				problems.append("%s#%d stock ids" % [pool, index])
			if not state.waste.is_empty():
				problems.append("%s#%d dealt waste not empty" % [pool, index])
			var digest := LegacyDealDigest.dealt_sha256(state)
			if digest != String(fixture.dealt_canonical_sha256):
				problems.append("%s#%d canonical digest %s" % [pool, index, digest])
		assert_true(
			problems.is_empty(),
			"dealt fixtures %s mismatches: %s" % [pool, str(problems.slice(0, 12))]
		)


func test_dealt_layout_independent_of_draw_mode() -> void:
	for pool in ["bureau1", "bureau3"]:
		var problems: Array[String] = []
		for fixture in GoldenLoader.fixtures(pool):
			var index := int(fixture.index)
			var d1 := LegacyDealer.deal_dealt(pool, index, GameState.DRAW1)
			var d3 := LegacyDealer.deal_dealt(pool, index, GameState.DRAW3)
			if not (d1.ok and d3.ok):
				problems.append("%s#%d not ok" % [pool, index])
				continue
			if not d1.state.stock.content_equals(d3.state.stock):
				problems.append("%s#%d stock differs by mode" % [pool, index])
			for col in 7:
				if not d1.state.tableau[col].content_equals(d3.state.tableau[col]):
					problems.append("%s#%d tableau col %d differs by mode" % [pool, index, col])
					break
			if LegacyDealDigest.dealt_sha256(d1.state) != LegacyDealDigest.dealt_sha256(d3.state):
				problems.append("%s#%d digest differs by mode" % [pool, index])
		assert_true(problems.is_empty(), "draw-mode independence %s: %s" % [pool, str(problems.slice(0, 12))])


func test_ready_draw1_matches_all_fixtures() -> void:
	for pool in ["bureau1", "bureau3"]:
		var problems: Array[String] = []
		for fixture in GoldenLoader.fixtures(pool):
			var index := int(fixture.index)
			var result := LegacyDealer.deal_ready(pool, index, GameState.DRAW1)
			if not result.ok:
				problems.append("%s#%d deal failed" % [pool, index])
				continue
			var state: GameState = result.state
			if state.stock.ids() != GoldenLoader.ints_from(fixture.ready_draw1.stock):
				problems.append("%s#%d ready1 stock" % [pool, index])
			if state.waste.ids() != GoldenLoader.ints_from(fixture.ready_draw1.waste):
				problems.append("%s#%d ready1 waste" % [pool, index])
			for row in state.waste.size():
				if not state.waste.card_at(row).face_up:
					problems.append("%s#%d ready1 waste card %d face-down" % [pool, index, row])
			if not state.stock.is_empty() and state.stock.top().face_up:
				problems.append("%s#%d ready1 stock top face-up" % [pool, index])
			if state.total_card_count() != 52:
				problems.append("%s#%d ready1 conservation" % [pool, index])
		assert_true(problems.is_empty(), "ready draw1 %s: %s" % [pool, str(problems.slice(0, 12))])


func test_ready_draw3_matches_all_fixtures() -> void:
	for pool in ["bureau1", "bureau3"]:
		var problems: Array[String] = []
		for fixture in GoldenLoader.fixtures(pool):
			var index := int(fixture.index)
			var result := LegacyDealer.deal_ready(pool, index, GameState.DRAW3)
			if not result.ok:
				problems.append("%s#%d deal failed" % [pool, index])
				continue
			var state: GameState = result.state
			if state.stock.ids() != GoldenLoader.ints_from(fixture.ready_draw3.stock):
				problems.append("%s#%d ready3 stock" % [pool, index])
			if state.waste.ids() != GoldenLoader.ints_from(fixture.ready_draw3.waste):
				problems.append("%s#%d ready3 waste" % [pool, index])
			for row in state.waste.size():
				if not state.waste.card_at(row).face_up:
					problems.append("%s#%d ready3 waste card %d face-down" % [pool, index, row])
			if state.total_card_count() != 52:
				problems.append("%s#%d ready3 conservation" % [pool, index])
		assert_true(problems.is_empty(), "ready draw3 %s: %s" % [pool, str(problems.slice(0, 12))])


func test_record0_canonical_digest() -> void:
	for draw_count in [GameState.DRAW1, GameState.DRAW3]:
		var result := LegacyDealer.deal_dealt("bureau1", 0, draw_count)
		assert_true(result.ok, "record0 dealt ok draw%d" % draw_count)
		assert_eq(
			LegacyDealDigest.dealt_sha256(result.state),
			CANONICAL_RECORD0,
			"record0 canonical digest draw%d" % draw_count
		)
	var meta := GoldenLoader.meta("bureau1")
	var expected: String = meta.get("record0", {}).get("canonical_dealt_sha256", "")
	assert_eq(CANONICAL_RECORD0, expected, "fixture meta pins the same canonical hash")


func test_52_of_52_conserved_and_unique_in_every_state() -> void:
	for pool in ["bureau1", "bureau3"]:
		var problems: Array[String] = []
		for fixture in GoldenLoader.fixtures(pool):
			var index := int(fixture.index)
			for draw_count in [GameState.DRAW1, GameState.DRAW3]:
				var result := LegacyDealer.deal_ready(pool, index, draw_count)
				if not result.ok:
					problems.append("%s#%d draw%d not ok" % [pool, index, draw_count])
					continue
				var ids := result.state.all_card_ids()
				if ids.size() != 52:
					problems.append("%s#%d draw%d size %d" % [pool, index, draw_count, ids.size()])
					continue
				var seen := PackedByteArray()
				seen.resize(52)
				for id in ids:
					seen[id] = 1
				var complete := true
				for i in 52:
					if seen[i] == 0:
						complete = false
						break
				if not complete:
					problems.append("%s#%d draw%d not a full 0..51 permutation" % [pool, index, draw_count])
		assert_true(problems.is_empty(), "conservation %s: %s" % [pool, str(problems.slice(0, 12))])
