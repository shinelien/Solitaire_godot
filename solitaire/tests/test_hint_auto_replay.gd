extends BaseTest

## Hint (read-only legal move), Auto Complete (foundation-only, safe stop),
## Replay (same deal + draw mode) and New Deal.

func test_hint_is_read_only_and_legal() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var before := ctrl.state.deep_copy()
	var m := ctrl.request_hint()
	check_true(ctrl.state.equals(before), "hint did not mutate state")
	if m != null:
		check_true(KlondikeRules.is_legal_move(ctrl.state, m), "hint move is legal")
		check_eq(m.type, Move.MoveType.MOVE_CARD, "hint returns a MOVE_CARD")

func test_hint_is_legal_on_hard_deal() -> void:
	# On a fresh deal with several moves available the hint must be legal and
	# executable through the same MoveExecutor pathway.
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var found_legal := false
	for attempt in 30:
		var m := ctrl.request_hint()
		if m == null:
			break
		check_true(KlondikeRules.is_legal_move(ctrl.state, m), "hint move %d legal" % attempt)
		if m.from_pile.type == PileType.TABLEAU:
			var cards := ctrl.state.col(m.from_pile.index)
			var src_index := m.from_index
			if src_index == -1:
				src_index = cards.size() - 1
			check_true(ctrl.request_move(m.from_pile, src_index, m.count, m.to_pile), "hint executable %d" % attempt)
			found_legal = true
			break
	if not found_legal:
		# Fall back to a draw to make progress; hint alone may be empty.
		check_true(ctrl.request_draw(), "draw fallback")
	var errs := ctrl.state.invariant_errors()
	check_empty(errs, "invariants after hint play")

func test_auto_complete_foundation_only_and_safe_stop() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var ok := ctrl.request_auto_complete()
	# Safe stop: after auto-complete there must be no legal foundation move.
	var m := KlondikeRules.find_foundation_move(ctrl.state)
	check_null(m, "no foundation move remains after auto complete")
	if ok:
		# Every executed move must target a foundation (or be a flip).
		for cmd in ctrl.state.history:
			if cmd.label != "Auto Complete":
				continue
			for mv in cmd.moves:
				if mv.type == Move.MoveType.FLIP_TABLEAU:
					continue
				check_eq(mv.to_pile.type, PileType.FOUNDATION, "auto complete move targets foundation")
	var errs := ctrl.state.invariant_errors()
	check_empty(errs, "invariants after auto complete")

func test_auto_complete_stalls_when_nothing_to_do() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	ctrl.request_auto_complete()
	var before := ctrl.state.deep_copy()
	check_false(ctrl.request_auto_complete(), "second auto complete stalls safely")
	check_true(ctrl.state.equals(before), "stall leaves state unchanged")

func test_replay_restores_same_deal_and_mode() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 7, ""), "new deal index 7")
	var deal_encoded := ctrl.state.encoded
	var deal_mode := ctrl.state.draw_mode
	ctrl.request_draw()
	check_true(ctrl.request_replay(), "replay")
	check_eq(ctrl.state.encoded, deal_encoded, "same encoded deal")
	check_eq(ctrl.state.draw_mode, deal_mode, "same draw mode")
	check_eq(ctrl.state.deal_index, 7, "same deal index")
	check_eq(ctrl.state.waste.size(), 1, "replayed initial state (waste 1)")
	# A fresh deal of the same record must be identical to the replayed state.
	var ctrl2 := GameController.new()
	check_true(ctrl2.new_deal(deal_mode, 7, deal_encoded), "fresh identical deal")
	check_true(ctrl.state.equals(ctrl2.state), "replay state equals fresh deal")

func test_repeated_replay_is_safe() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW3, 11, ""), "new deal")
	ctrl.request_draw()
	check_true(ctrl.request_replay(), "replay 1")
	check_true(ctrl.request_replay(), "replay 2")
	check_eq(ctrl.state.waste.size(), 3, "draw3 replay initial waste")
	check_eq(ctrl.state.encoded.length(), 52, "encoded stable length")
	var errs := ctrl.state.invariant_errors()
	check_empty(errs, "invariants after repeated replay")

func test_new_deal_valid_and_distinct() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "initial")
	var first := ctrl.state.encoded
	var distinct := false
	for i in 20:
		check_true(ctrl.request_new_deal(), "new deal %d" % i)
		var errs := ctrl.state.invariant_errors()
		check_empty(errs, "invariants after new deal")
		if ctrl.state.encoded != first:
			distinct = true
	check_true(distinct, "new deal eventually distinct from first")

func test_draw_mode_switch() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "initial draw1")
	check_true(ctrl.set_draw_mode(GameConfig.DRAW3), "switch to draw3")
	check_eq(ctrl.state.draw_mode, GameConfig.DRAW3, "mode now draw3")
	check_eq(ctrl.state.waste.size(), 3, "draw3 deal initial waste")
	check_true(ctrl.set_draw_mode(GameConfig.DRAW1), "switch to draw1")
	check_eq(ctrl.state.waste.size(), 1, "draw1 deal initial waste")
