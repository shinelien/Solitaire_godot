@tool
extends McpTestSuite


func suite_name() -> String:
	return "core_model"


func test_card_data_rank_suit_mapping_for_all_ids() -> void:
	for id in range(52):
		var card := CardData.new(id)
		assert_eq(card.id, id, "id preserved %d" % id)
		assert_eq(card.rank, id % 13 + 1, "rank for id %d" % id)
		assert_eq(card.suit, id / 13, "suit for id %d" % id)
		assert_true(card.is_valid(), "is_valid for id %d" % id)
		assert_false(card.face_up, "default face_down id %d" % id)


func test_card_data_out_of_range_invalid() -> void:
	for bad in [-1, 52, 100]:
		var card := CardData.new(bad)
		assert_false(card.is_valid(), "invalid id %d" % bad)


func test_card_data_face_up_flag_and_clone() -> void:
	var card := CardData.new(0, true)
	assert_true(card.face_up, "face_up honored")
	var copy := card.clone()
	assert_eq(copy.id, card.id, "clone id")
	assert_eq(copy.rank, card.rank, "clone rank")
	assert_eq(copy.suit, card.suit, "clone suit")
	assert_eq(copy.face_up, card.face_up, "clone face_up")
	assert_ne(copy, card, "clone is a distinct instance")


func _assert_not_node(obj: RefCounted, label: String) -> void:
	var probe: Variant = obj
	assert_false(probe is Node, "%s is not a Node" % label)


func test_card_data_is_refcounted_not_node() -> void:
	var card := CardData.new(7, true)
	assert_true(card is RefCounted, "CardData is RefCounted")
	_assert_not_node(card, "CardData")


func test_card_pile_stack_order() -> void:
	var pile := CardPile.from_ids([3, 11, 2], true)
	assert_eq(pile.size(), 3, "size")
	assert_eq(pile.bottom().id, 3, "bottom first-dealt id")
	assert_eq(pile.top().id, 2, "top last-dealt id")
	assert_true(pile.top().face_up, "top face_up")
	var ids := pile.ids()
	assert_eq(ids, [3, 11, 2], "ids in pile order")
	assert_true(pile.card_at(0).id == 3 and pile.card_at(2).id == 2, "card_at order")


func test_card_pile_is_refcounted_not_node() -> void:
	var pile := CardPile.new()
	assert_true(pile is RefCounted, "CardPile is RefCounted")
	_assert_not_node(pile, "CardPile")


func test_card_pile_clone_is_deep() -> void:
	var source := CardPile.from_ids([0, 13, 26], true)
	var clone := source.clone()
	assert_true(source.content_equals(clone), "clone content equal")
	assert_ne(source, clone, "distinct piles")
	var source_top := source.top()
	var clone_top := clone.top()
	assert_ne(source_top, clone_top, "cards are distinct instances")
	clone_top.face_up = false
	assert_true(source_top.face_up, "source unaffected by clone card mutation")
	assert_true(source.card_at(1).id == clone.card_at(1).id, "ids match")
	assert_ne(source.card_at(1), clone.card_at(1), "middle cards also distinct")


func test_game_state_containers_and_scalars() -> void:
	var state := GameState.new()
	assert_eq(state.tableau.size(), GameState.TABLEAU_COUNT, "7 tableau piles")
	assert_eq(state.foundation.size(), GameState.FOUNDATION_COUNT, "4 foundation piles")
	for pile in state.tableau:
		assert_true(pile.is_empty(), "empty tableau pile")
	for pile in state.foundation:
		assert_true(pile.is_empty(), "empty foundation pile")
	assert_true(state.stock.is_empty() and state.waste.is_empty(), "empty stock/waste")
	assert_eq(state.draw_count, GameState.DRAW1, "default draw_count 1")
	assert_eq(state.stock_passes, 0, "stock_passes 0")
	assert_eq(state.move_count, 0, "move_count 0")
	assert_eq(state.score, 0, "score 0")
	assert_eq(state.game_status, GameState.GameStatus.IN_PROGRESS, "status in progress")
	assert_eq(state.total_card_count(), 0, "no cards yet")


func test_game_state_is_refcounted_not_node() -> void:
	var state := GameState.new()
	assert_true(state is RefCounted, "GameState is RefCounted")
	_assert_not_node(state, "GameState")


func test_game_state_deep_clone_isolation() -> void:
	var source := GameState.new()
	source.stock = CardPile.from_ids([0, 1, 2])
	source.waste = CardPile.from_ids([3])
	source.tableau[0] = CardPile.from_ids([4], true)
	source.tableau[3] = CardPile.from_ids([5, 6], false, [false, true])
	source.foundation[2] = CardPile.from_ids([7])
	source.draw_count = GameState.DRAW3
	source.stock_passes = 1
	source.move_count = 4
	source.score = 42
	source.deal_pool = "bureau1"
	source.deal_index = 9
	source.deal_source = "Resources/data/bureau1.d"

	var clone := source.clone()
	assert_true(clone.content_equals(source), "clone equals source")
	assert_ne(clone, source, "distinct GameState")
	assert_ne(clone.stock, source.stock, "distinct stock pile")
	assert_ne(clone.waste, source.waste, "distinct waste pile")

	## Mutate deep structures in the clone; source must be untouched.
	clone.stock.top().face_up = true
	clone.waste.add_top(CardData.new(9))
	clone.tableau[0].top().face_up = false
	clone.tableau[3].card_at(0).face_up = true
	clone.foundation[2].pop_top()
	clone.draw_count = GameState.DRAW1
	clone.move_count = 99
	assert_false(source.stock.top().face_up, "source stock unaffected")
	assert_eq(source.waste.size(), 1, "source waste unaffected")
	assert_true(source.tableau[0].top().face_up, "source tableau[0] unaffected")
	assert_false(source.tableau[3].card_at(0).face_up, "source tableau[3] unaffected")
	assert_eq(source.foundation[2].size(), 1, "source foundation unaffected")
	assert_eq(source.draw_count, GameState.DRAW3, "source draw_count unaffected")
	assert_eq(source.move_count, 4, "source move_count unaffected")


func test_game_state_total_and_all_ids_52_conservation_ready() -> void:
	var dealt_result := LegacyDealer.deal_dealt("bureau1", 0, GameState.DRAW3)
	assert_true(dealt_result.ok, "deal ok")
	var state: GameState = dealt_result.state
	assert_eq(state.total_card_count(), 52, "52/52 dealt")
	assert_eq(state.all_card_ids().size(), 52, "52 ids listed")
	var ids := state.all_card_ids()
	var seen := PackedByteArray()
	seen.resize(52)
	for id in ids:
		seen[id] = 1
	var all_seen := true
	for i in 52:
		if seen[i] == 0:
			all_seen = false
	assert_true(all_seen, "complete 0..51 permutation dealt")
