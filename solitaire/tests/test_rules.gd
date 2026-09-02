extends BaseTest

## Klondike rule unit coverage (section 10 item 6):
## descending alternating tableau, King to empty, same-suit ascending
## foundations, empty-tableau non-King rejection, illegal foundation returns.

func _card(id: int, face_up: bool = true) -> CardData:
	var c := CardData.from_id(id)
	c.face_up = face_up
	return c

func _mk_state() -> GameState:
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW1
	return st

func test_tableau_accepts_rules() -> void:
	# Legacy suits: 0=spades, 1=hearts, 2=clubs, 3=diamonds. Even suit = black.
	var eight_spades := _card(0 * 13 + 7)  # rank 8, black
	var seven_hearts := _card(1 * 13 + 6)  # rank 7, red
	check_true(KlondikeRules.tableau_accepts(eight_spades, seven_hearts), "descending alternating red on black")
	# same color rejected
	var seven_clubs := _card(2 * 13 + 6)  # rank 7, black
	check_false(KlondikeRules.tableau_accepts(eight_spades, seven_clubs), "same color rejected")
	# wrong rank rejected
	var six_hearts := _card(1 * 13 + 5)
	check_false(KlondikeRules.tableau_accepts(eight_spades, six_hearts), "wrong rank rejected")
	# empty tableau only King
	check_true(KlondikeRules.tableau_accepts(null, _card(0 * 13 + 12)), "king to empty")
	check_true(KlondikeRules.tableau_accepts(null, _card(1 * 13 + 12)), "red king to empty")
	check_false(KlondikeRules.tableau_accepts(null, _card(0 * 13 + 11)), "queen to empty rejected")
	check_false(KlondikeRules.tableau_accepts(null, _card(0)), "ace to empty rejected")

func test_foundation_accepts_rules() -> void:
	var ace_hearts := _card(1 * 13 + 0)
	var two_hearts := _card(1 * 13 + 1)
	var three_hearts := _card(1 * 13 + 2)
	check_true(KlondikeRules.foundation_accepts(ace_hearts, two_hearts), "two on ace")
	check_false(KlondikeRules.foundation_accepts(ace_hearts, three_hearts), "skip rank rejected")
	check_false(KlondikeRules.foundation_accepts(ace_hearts, _card(2 * 13 + 1)), "wrong suit rejected")
	check_false(KlondikeRules.foundation_accepts(ace_hearts, _card(3 * 13 + 1)), "other suit rejected")
	check_true(KlondikeRules.foundation_accepts(null, ace_hearts), "ace to empty")
	check_false(KlondikeRules.foundation_accepts(null, two_hearts), "two to empty rejected")

func test_sequence_valid() -> void:
	var seq: Array[CardData] = [
		_card(0 * 13 + 7),  # 8 spades
		_card(1 * 13 + 6),  # 7 hearts
		_card(2 * 13 + 5),  # 6 clubs
	]
	check_true(KlondikeRules.sequence_valid(seq), "valid alternating descending")
	var bad: Array[CardData] = [
		_card(0 * 13 + 7),
		_card(0 * 13 + 6),  # 7 spades, same color
		_card(1 * 13 + 5),
	]
	check_false(KlondikeRules.sequence_valid(bad), "same color breaks sequence")

func test_move_legality_through_rules() -> void:
	var st := _mk_state()
	st.waste.push_back(_card(1 * 13 + 6))  # 7 hearts face-up
	st.tableau[0] = typed_col([_card(0 * 13 + 7)])   # 8 spades
	st.tableau[1] = typed_col([])
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.waste()
	m.from_index = 0
	m.count = 1
	m.to_pile = Location.tableau(0)
	check_true(KlondikeRules.is_legal_move(st, m), "waste 7h onto 8s")
	m.to_pile = Location.tableau(1)
	check_false(KlondikeRules.is_legal_move(st, m), "7h onto empty tableau rejected (not King)")

func test_illegal_foundation_return() -> void:
	# Moving a foundation top back out: legal only to a fitting tableau;
	# must be rejected for mismatched destinations and never corrupt state.
	var st := _mk_state()
	st.foundations[0] = typed_col([_card(0 * 13 + 1)])  # 2 spades in foundation
	var snap := st.deep_copy()
	var m := Move.new()
	m.type = Move.MoveType.MOVE_CARD
	m.from_pile = Location.foundation(0)
	m.from_index = -1
	m.count = 1
	m.to_pile = Location.foundation(1)  # empty foundation expects Ace
	check_false(KlondikeRules.is_legal_move(st, m), "foundation 2 to empty foundation rejected")
	var res := MoveExecutor.apply(st, m)
	check_false(res.ok, "executor rejects")
	check_true(st.equals(snap), "state unchanged after illegal foundation move")

func test_draw_count_for() -> void:
	var st := _mk_state()
	st.draw_mode = GameConfig.DRAW3
	st.stock = typed_col([_card(0), _card(1), _card(2)])
	check_eq(KlondikeRules.draw_count_for(st), 3, "draw 3 of 3")
	st.stock = typed_col([_card(0)])
	check_eq(KlondikeRules.draw_count_for(st), 1, "last partial packet 1")
	st.stock = typed_col([])
	check_eq(KlondikeRules.draw_count_for(st), 0, "empty stock")
	st.draw_mode = GameConfig.DRAW1
	st.stock = typed_col([_card(0), _card(1)])
	check_eq(KlondikeRules.draw_count_for(st), 1, "draw 1 of 2")
