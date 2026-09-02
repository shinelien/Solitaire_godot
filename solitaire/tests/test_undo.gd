extends BaseTest

## Undo: snapshot-based restore of the whole command boundary (draw mode,
## stock, waste, tableau, foundation, status, counters, history, session)
## and deep-copy alias isolation.

func test_undo_restores_exact_precommand_state() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 3, ""), "new deal")
	ctrl.request_draw()
	ctrl.request_draw()
	var before_last := ctrl.state.deep_copy()
	ctrl.request_stock_action()  # another draw
	check_false(ctrl.state.equals(before_last), "state advanced")
	check_true(ctrl.request_undo(), "undo ok")
	check_true(ctrl.state.equals(before_last), "exact state restored after undo")
	check_eq(ctrl.state.move_count, before_last.move_count, "move count restored")
	check_eq(ctrl.state.draw_count, before_last.draw_count, "draw count restored")
	check_eq(ctrl.state.history.size(), before_last.history.size(), "history restored")

func test_undo_restores_flip_and_mode_and_session() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW3, 5, ""), "new deal draw3")
	var before := ctrl.state.deep_copy()
	# Perform a real legal move with auto-flip, then undo.
	var moved := false
	for c in PileType.TABLEAU_COUNT:
		var cards := ctrl.state.col(c)
		if cards.is_empty():
			continue
		var top: CardData = cards[cards.size() - 1]
		if not top.face_up:
			continue
		if KlondikeRules.matching_foundation(ctrl.state, top) != -1:
			var f := KlondikeRules.matching_foundation(ctrl.state, top)
			if ctrl.request_move(Location.tableau(c), cards.size() - 1, 1, Location.foundation(f)):
				moved = true
		if moved:
			break
	if moved:
		check_true(ctrl.request_undo(), "undo move")
		check_true(ctrl.state.equals(before), "undo restored flip+move")
		check_eq(ctrl.state.draw_mode, before.draw_mode, "draw mode restored")
	check_false(ctrl.request_undo(), "second undo rejected (stack empty after single snapshot)")
	check_eq(ctrl.state.encoded, before.encoded, "encoded restored")

func test_empty_undo_is_rejected() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var before := ctrl.state.deep_copy()
	check_false(ctrl.request_undo(), "undo with empty stack rejected")
	check_true(ctrl.state.equals(before), "nothing changed")

func test_snapshot_alias_isolation() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var snap := ctrl.state.deep_copy()
	var state_snap := snap.deep_copy()
	# Mutate the live state aggressively; the snapshots must not be affected.
	ctrl.state.waste.clear()
	ctrl.state.stock.clear()
	for c in PileType.TABLEAU_COUNT:
		ctrl.state.col(c).clear()
	for f in PileType.FOUNDATION_COUNT:
		ctrl.state.fnd(f).clear()
	for c in PileType.TABLEAU_COUNT:
		var cards := ctrl.state.col(c)
		if not cards.is_empty():
			cards[cards.size() - 1].face_up = false
	check_true(snap.equals(state_snap), "snapshot isolated from live mutations")
	check_true(state_snap.equals(snap), "symmetric snapshot isolation")
	check_true(not snap.waste.is_empty(), "snapshot waste intact")
	var total := 0
	for c in snap.col(0):
		total += 1
	check_true(total > 0, "snapshot tableau intact")

func test_undo_restores_replay_session() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 2, ""), "new deal")
	var session_before := ctrl.state.session.size()
	ctrl.request_draw()
	check_true(ctrl.request_undo(), "undo")
	check_eq(ctrl.state.session.size(), session_before, "session log restored")

func test_multi_undo() -> void:
	var ctrl := GameController.new()
	check_true(ctrl.new_deal(GameConfig.DRAW1, 0, ""), "new deal")
	var s0 := ctrl.state.deep_copy()
	ctrl.request_draw()
	var s1 := ctrl.state.deep_copy()
	ctrl.request_draw()
	var s2 := ctrl.state.deep_copy()
	ctrl.request_draw()
	check_true(ctrl.request_undo(), "undo 1")
	check_true(ctrl.state.equals(s2), "back to s2")
	check_true(ctrl.request_undo(), "undo 2")
	check_true(ctrl.state.equals(s1), "back to s1")
	check_true(ctrl.request_undo(), "undo 3")
	check_true(ctrl.state.equals(s0), "back to s0")
