@tool
extends McpTestSuite

func suite_name() -> String:
	return "newhd_magic"

func fill_stock(state: GameState) -> void:
	var used := state.all_card_ids()
	for id in 52:
		if id not in used:
			state.stock.add_top(CardData.new(id))

func test_magic_prefers_covered_card_and_preserves_the_original_state() -> void:
	var session := NewHDSession.new()
	session.state = GameState.new()
	session.state.tableau[0] = CardPile.from_ids([19, 2], false, [false, true]) # H7 under S3.
	session.state.tableau[1] = CardPile.from_ids([7], true) # S8 receives H7.
	fill_stock(session.state)
	session.state.score = 42
	session.state.move_count = 12
	session.history.append({"state": session.state.clone(), "delta": 0})
	var original := session.state
	var before := original.clone()
	var plan := session.magic_plan()
	assert_eq(plan.card_id, 19, "covered useful card has priority over waiting cards")
	assert_true(session.apply_magic(plan))
	assert_true(original.content_equals(before), "magic applies on a deep clone")
	assert_eq(session.state.tableau[0].ids(), [2])
	assert_eq(session.state.tableau[1].ids(), [7, 19])
	assert_eq(session.state.score, 47)
	assert_eq(session.state.move_count, 13)
	assert_eq(session.state.total_card_count(), 52)
	assert_eq(session.magic_used, 1)
	assert_true(session.history.is_empty())
	assert_false(session.undo(), "magic clears the earlier undo history")
	assert_true(session.revealed_targets.has(19), "extracted level target is recorded")

func test_magic_can_extract_and_append_within_the_same_column() -> void:
	var session := NewHDSession.new()
	session.state = GameState.new()
	session.state.tableau[0] = CardPile.from_ids([6, 20], false, [false, true])
	fill_stock(session.state)
	var plan := session.magic_plan()
	assert_eq(plan.card_id, 6)
	assert_eq(plan.index, 0)
	assert_true(session.apply_magic(plan))
	assert_eq(session.state.tableau[0].ids(), [20, 6])
	assert_eq(session.state.total_card_count(), 52)

func test_magic_prefers_foundation_when_the_card_also_fits_tableau() -> void:
	var session := NewHDSession.new()
	session.state = GameState.new()
	session.state.foundation[3] = CardPile.from_ids([0], true)
	session.state.tableau[0] = CardPile.from_ids([1, 20], false, [false, true])
	session.state.tableau[1] = CardPile.from_ids([15], true)
	fill_stock(session.state)
	var plan := session.magic_plan()
	assert_eq(plan.card_id, 1)
	assert_eq(plan.kind, "foundation")
	assert_eq(plan.index, 3)
	assert_true(session.apply_magic(plan))
	assert_eq(session.state.foundation[3].ids(), [0, 1])
	assert_eq(session.state.score, 10)

func test_magic_fallback_collects_exposed_top_and_flips_the_new_top() -> void:
	var session := NewHDSession.new()
	session.state = GameState.new()
	session.state.foundation[0] = CardPile.from_ids([0], true)
	for suit in range(1, 4):
		for rank in 13:
			session.state.foundation[suit].add_top(CardData.new(suit * 13 + rank, true))
	session.state.tableau[0] = CardPile.from_ids([2, 1], false, [false, true])
	for index in range(1, 7):
		session.state.tableau[index] = CardPile.from_ids([index + 2], true)
	fill_stock(session.state)
	var plan := session.magic_plan()
	assert_eq(plan.card_id, 1, "neither covered nor waiting cards fit; use exposed S2")
	assert_true(session.apply_magic(plan))
	assert_eq(session.state.foundation[0].ids(), [0, 1])
	assert_true(session.state.tableau[0].top().face_up)
	assert_eq(session.state.score, 15, "foundation +10 and newly exposed card +5")
	assert_eq(session.state.move_count, 1)
	assert_eq(session.state.total_card_count(), 52)

func test_magic_rejects_stale_or_invalid_plans_without_changing_state() -> void:
	var session := NewHDSession.new()
	session.state = GameState.new()
	session.state.tableau[0] = CardPile.from_ids([0, 2], false, [false, true])
	fill_stock(session.state)
	var before := session.state.clone()
	assert_false(session.apply_magic({"card_id": 0, "kind": "tableau", "index": 0}))
	assert_true(session.state.content_equals(before))
	var plan := session.magic_plan()
	assert_true(session.apply_magic(plan))
	before = session.state.clone()
	assert_false(session.apply_magic(plan))
	assert_true(session.state.content_equals(before))

func test_repeated_magic_keeps_52_unique_cards_and_valid_foundations() -> void:
	var session := NewHDSession.new()
	for draw in [1, 3]:
		for deal in 5:
			session.start(draw)
			for use in 20:
				var plan := session.magic_plan()
				if plan.is_empty():
					break
				assert_true(session.apply_magic(plan))
				var ids := session.state.all_card_ids()
				ids.sort()
				assert_eq(ids, range(52), "no cards are lost or duplicated")
				for pile in session.state.foundation:
					for index in pile.size():
						assert_eq(pile.card_at(index).rank, index + 1)
						assert_eq(pile.card_at(index).suit, pile.bottom().suit)
						assert_true(pile.card_at(index).face_up)
