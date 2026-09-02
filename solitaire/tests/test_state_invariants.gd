extends BaseTest

## GameState invariants across play and win detection via 4x13 foundation
## status (never UI/score/text based).

func _card(id: int, face_up: bool = true) -> CardData:
	var c := CardData.from_id(id)
	c.face_up = face_up
	return c

func test_invariants_hold_through_scripted_play() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	for deal in [GameConfig.DRAW1, GameConfig.DRAW3]:
		check_true(ctrl.new_deal(deal, 5, ""), "deal mode %d" % deal)
		for step in 60:
			var before := ctrl.state.deep_copy()
			var advanced := false
			if step % 3 == 0:
				advanced = ctrl.request_stock_action()
			elif step % 3 == 1:
				var m := ctrl.request_hint()
				if m != null:
					var src_index := m.from_index
					if m.from_pile.type != PileType.TABLEAU:
						src_index = ctrl.state.get_pile(m.from_pile).size() - 1
					advanced = ctrl.request_move(m.from_pile, src_index, m.count, m.to_pile)
			else:
				advanced = ctrl.request_auto_complete()
			if advanced:
				var errs := ctrl.state.invariant_errors()
				check_empty(errs, "invariants after step %d mode %d" % [step, deal])
				check_true(ctrl.request_undo(), "undo step %d" % step)
				var errs2 := ctrl.state.invariant_errors()
				check_empty(errs2, "invariants after undo step %d" % step)
				check_true(ctrl.state.equals(before), "undo returned to prior state step %d" % step)

func test_win_detection_uses_foundations() -> void:
	var ctrl := GameController.new()
	# Synthesize a near-win: foundations 0..2 full, foundation 3 needs its King.
	var st := GameState.new()
	st.draw_mode = GameConfig.DRAW1
	for f in 3:
		for r in 13:
			var c := CardData.from_id(f * 13 + r)
			c.face_up = true
			st.foundations[f].push_back(c)
	for r in 12:
		var c := CardData.from_id(3 * 13 + r)
		c.face_up = true
		st.foundations[3].push_back(c)
	var king := CardData.from_id(3 * 13 + 12)
	king.face_up = true
	st.waste.push_back(king)
	ctrl.state = st
	check_false(KlondikeRules.is_won(ctrl.state), "not won yet")
	check_true(ctrl.request_move(Location.waste(), 0, 1, Location.foundation(3)), "final king to foundation")
	check_true(KlondikeRules.is_won(ctrl.state), "won now")
	check_eq(ctrl.state.status, GameStatus.Status.WON, "status is WON")
	for f in PileType.FOUNDATION_COUNT:
		check_eq(ctrl.state.fnd(f).size(), 13, "foundation %d full" % f)
	var errs := ctrl.state.invariant_errors()
	check_empty(errs, "winning state invariants")

func test_win_not_reported_by_pile_shapes_alone() -> void:
	# A tableau column of length 13 is NOT a win; only foundations matter.
	var st := GameState.new()
	for i in 13:
		var c := CardData.from_id(0 * 13 + i)
		c.face_up = true
		st.tableau[0].push_back(c)
	check_false(KlondikeRules.is_won(st), "tableau run is not a win")
