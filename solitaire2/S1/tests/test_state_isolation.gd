@tool
extends McpTestSuite


func suite_name() -> String:
	return "state_isolation"


func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


# ----- no_shared_state: any-container / any-position reference isolation -----

func test_deep_clone_states_share_nothing_anywhere() -> void:
	var a := CardStateTestkit.make_state()
	a.tableau[0] = _col([[3, false], [_s(0, 13), true]])
	a.stock = CardStateTestkit.down([5, 6])
	a.waste = CardStateTestkit.up([_s(1, 1)])
	a.foundation[2] = CardStateTestkit.foundation_of(2, 3)
	var b := a.clone()
	assert_ne(b, a, "clone is a distinct GameState")
	assert_true(CardStateTestkit.no_shared_state(a, b), "deep clone shares no pile/card anywhere")
	assert_true(CardStateTestkit.no_shared_state(b, a), "isolation check is symmetric")


func test_fresh_independent_states_with_equal_content_share_nothing() -> void:
	var a := CardStateTestkit.make_state()
	a.tableau[1] = CardStateTestkit.up([_s(3, 7)])
	a.foundation[0] = CardStateTestkit.foundation_of(0, 2)
	var b := CardStateTestkit.make_state()
	b.tableau[1] = CardStateTestkit.up([_s(3, 7)])
	b.foundation[0] = CardStateTestkit.foundation_of(0, 2)
	assert_true(a.content_equals(b), "content equal")
	assert_true(CardStateTestkit.no_shared_state(a, b), "equal content, distinct instances, no sharing")


func test_same_card_reference_in_a_different_container_is_detected() -> void:
	var a := CardStateTestkit.make_state()
	a.foundation[0] = CardStateTestkit.up([_s(0, 1), _s(0, 2)])
	a.stock = CardStateTestkit.down([9, 10])
	var b := a.clone()
	var shared: CardData = a.foundation[0].card_at(1)
	b.waste.add_top(shared)
	assert_eq(shared, b.waste.top(), "same CardData instance now reachable from B waste")
	assert_false(CardStateTestkit.no_shared_state(a, b), "cross-container shared card must be detected")


func test_same_card_reference_at_a_different_position_is_detected() -> void:
	var a := CardStateTestkit.make_state()
	a.tableau[2] = CardStateTestkit.up([_s(0, 10), _s(1, 11)])
	var b := a.clone()
	var shared: CardData = a.tableau[2].card_at(0)
	b.tableau[2].add_top(shared)
	assert_eq(shared, b.tableau[2].top(), "shared card sits at a different position in B")
	assert_false(CardStateTestkit.no_shared_state(a, b), "cross-position shared card must be detected")


func test_same_pile_object_in_a_different_container_is_detected() -> void:
	var a := CardStateTestkit.make_state()
	a.waste = CardStateTestkit.up([3, 4, 5])
	var b := CardStateTestkit.make_state()
	b.stock = a.waste
	assert_eq(b.stock, a.waste, "one CardPile instance reused as a different container")
	assert_false(CardStateTestkit.no_shared_state(a, b), "cross-container shared pile must be detected")
