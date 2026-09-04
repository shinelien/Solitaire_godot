@tool
extends McpTestSuite


func suite_name() -> String:
	return "wp08_interaction"


func fid(suit: int, rank: int) -> int:
	return suit * 13 + rank - 1


func test_drag_translation_tableau_run() -> void:
	var state := FixtureStates.ops_state()
	var source := {"kind": "tableau", "index": 1, "card_index": 5}
	var target := {"kind": "tableau", "index": 2}
	var move := InputInterpreter.build_drag_move(state, source, target)
	assert_true(move != null, "run drag produces a move")
	assert_eq(move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "run kind")
	assert_eq(move.source_index, 1, "run source column")
	assert_eq(move.target_index, 2, "run target column")
	assert_eq(move.count, 7, "run count = column size - grabbed index")
	assert_true(state.total_card_count() == 52, "interpreter read-only")


func test_drag_translation_face_down_and_middle_restrictions() -> void:
	var state := FixtureStates.ops_state()
	var face_down := {"kind": "tableau", "index": 6, "card_index": 0}
	assert_true(
		InputInterpreter.build_drag_move(state, face_down, {"kind": "tableau", "index": 0}) == null,
		"face-down source cannot be dragged"
	)
	var not_top := {"kind": "tableau", "index": 1, "card_index": 3}
	assert_true(
		InputInterpreter.build_drag_move(state, not_top, {"kind": "foundation", "index": 0}) == null,
		"foundation destination only accepts the column top"
	)
	var same_col := {"kind": "tableau", "index": 1, "card_index": 11}
	assert_true(
		InputInterpreter.build_drag_move(state, same_col, {"kind": "tableau", "index": 1}) == null,
		"self column drop is rejected at translation"
	)


func test_drag_translation_waste_and_foundation() -> void:
	var state := FixtureStates.ops_state()
	var waste_to_found := InputInterpreter.build_drag_move(
		state, {"kind": "waste", "index": -1, "card_index": 0}, {"kind": "foundation", "index": 0}
	)
	assert_eq(waste_to_found.kind, Move.MoveKind.WASTE_TO_FOUNDATION, "waste -> foundation kind")
	assert_eq(waste_to_found.target_index, 0, "waste foundation slot")
	var waste_to_tableau := InputInterpreter.build_drag_move(
		state, {"kind": "waste", "index": -1, "card_index": 0}, {"kind": "tableau", "index": 4}
	)
	assert_eq(waste_to_tableau.kind, Move.MoveKind.WASTE_TO_TABLEAU, "waste -> tableau kind")
	assert_true(
		InputInterpreter.build_drag_move(state, {"kind": "waste", "index": -1, "card_index": 0}, {"kind": "waste", "index": -1}) == null,
		"no move onto a waste target"
	)
	var near := FixtureStates.near_win()
	var foundation_to_tableau := InputInterpreter.build_drag_move(
		near, {"kind": "foundation", "index": 0, "card_index": 0}, {"kind": "tableau", "index": 1}
	)
	assert_eq(foundation_to_tableau.kind, Move.MoveKind.FOUNDATION_TO_TABLEAU, "foundation top -> tableau")


func test_stock_click_translation() -> void:
	var deal1 := GameSession.create("bureau1", 0, GameState.DRAW1)
	var state1 := deal1.session.state_snapshot()
	assert_true(state1.stock.size() > 0, "bureau1#0 draw1 has stock")
	var draw := InputInterpreter.stock_click_move(state1)
	assert_eq(draw.kind, Move.MoveKind.DRAW_STOCK, "non-empty stock draws")
	var ops := FixtureStates.ops_state()
	var recycle := InputInterpreter.stock_click_move(ops)
	assert_eq(recycle.kind, Move.MoveKind.RECYCLE_STOCK, "empty stock with waste recycles")
	var won := FixtureStates.near_win()
	assert_true(InputInterpreter.stock_click_move(won) == null, "empty stock and empty waste: nothing")


func test_double_click_translation_uses_core_legal_moves() -> void:
	var waste_ace := FixtureStates.near_win_waste_ace()
	var from_waste := InputInterpreter.double_click_move(
		waste_ace, {"kind": "waste", "index": -1, "card_index": 0}
	)
	assert_true(from_waste != null, "waste ace double click has a move")
	assert_eq(from_waste.kind, Move.MoveKind.WASTE_TO_FOUNDATION, "waste double click kind")
	var near := FixtureStates.near_win()
	var from_tableau := InputInterpreter.double_click_move(near, {"kind": "tableau", "index": 0, "card_index": 12})
	assert_true(from_tableau != null, "tableau top double click has a move")
	assert_eq(from_tableau.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "tableau double click kind")
	assert_eq(from_tableau.target_index, 3, "suit-3 ace targets the empty slot 3")
	var buried := InputInterpreter.double_click_move(near, {"kind": "tableau", "index": 0, "card_index": 5})
	assert_true(buried == null, "buried card has no double-click foundation move")


func test_auto_find_prefers_foundation_over_tableau_attach() -> void:
	var state := GameState.new()
	state.tableau_pile(0).add_top(CardData.new(fid(1, 1), true))
	state.tableau_pile(1).add_top(CardData.new(fid(0, 2), true))
	var move := InputInterpreter.auto_find_move(
		state, {"kind": "tableau", "index": 0, "card_index": 0}
	)
	assert_true(move != null, "heart ace has a destination")
	assert_eq(move.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "foundation slot wins over tableau attach")
	assert_eq(move.target_index, 0, "ace targets the first empty foundation slot")


func test_auto_find_tableau_top_attaches_to_tableau_run() -> void:
	var state := GameState.new()
	state.tableau_pile(0).add_top(CardData.new(fid(1, 6), true))
	state.tableau_pile(1).add_top(CardData.new(fid(0, 7), true))
	var move := InputInterpreter.auto_find_move(
		state, {"kind": "tableau", "index": 0, "card_index": 0}
	)
	assert_true(move != null, "heart 6 can attach under spade 7")
	assert_eq(move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "tableau-to-tableau found when no foundation slot matches")
	assert_eq(move.source_index, 0, "run source column")
	assert_eq(move.target_index, 1, "run target column")
	assert_eq(move.count, 1, "column top moves as a single card")


func test_auto_find_waste_attaches_to_tableau_run() -> void:
	var state := GameState.new()
	state.waste.add_top(CardData.new(fid(1, 6), true))
	state.tableau_pile(0).add_top(CardData.new(fid(0, 7), true))
	var move := InputInterpreter.auto_find_move(
		state, {"kind": "waste", "index": -1, "card_index": 0}
	)
	assert_true(move != null, "waste heart 6 can attach under spade 7")
	assert_eq(move.kind, Move.MoveKind.WASTE_TO_TABLEAU, "waste-to-tableau found when no foundation slot matches")
	assert_eq(move.target_index, 0, "waste attaches to tableau column 0")


func test_auto_find_buried_tableau_card_moves_legal_run_suffix() -> void:
	var state := GameState.new()
	state.tableau_pile(0).add_top(CardData.new(fid(1, 9), true))
	state.tableau_pile(0).add_top(CardData.new(fid(0, 8), true))
	state.tableau_pile(0).add_top(CardData.new(fid(1, 7), true))
	state.tableau_pile(1).add_top(CardData.new(fid(1, 9), true))
	var move := InputInterpreter.auto_find_move(
		state, {"kind": "tableau", "index": 0, "card_index": 1}
	)
	assert_true(move != null, "spade 8 suffix can attach under heart 9")
	assert_eq(move.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "run suffix move kind")
	assert_eq(move.source_index, 0, "run suffix source column")
	assert_eq(move.target_index, 1, "run suffix target column")
	assert_eq(move.count, 2, "clicked card plus the legal cards above it move together")


func test_auto_find_rejects_face_down_and_other_kinds() -> void:
	var state := GameState.new()
	state.tableau_pile(0).add_top(CardData.new(fid(1, 6), false))
	var face_down := InputInterpreter.auto_find_move(
		state, {"kind": "tableau", "index": 0, "card_index": 0}
	)
	assert_true(face_down == null, "face-down card is never auto-targeted")
	assert_true(
		InputInterpreter.auto_find_move(state, {"kind": "stock", "index": -1, "card_index": -1}) == null,
		"stock source is not auto-targeted (stock click deals)"
	)
	assert_true(
		InputInterpreter.auto_find_move(state, {"kind": "foundation", "index": 0, "card_index": 0}) == null,
		"foundation source is not auto-targeted"
	)


func test_illegal_drop_is_zero_mutation() -> void:
	var created := GameSession.debug_create_state(FixtureStates.ops_state(), GameState.DRAW1)
	assert_true(created.ok, "debug session created")
	var session := created.session
	var before := session.state_snapshot()
	var illegal := InputInterpreter.build_drag_move(
		before, {"kind": "tableau", "index": 1, "card_index": 11}, {"kind": "tableau", "index": 0}
	)
	assert_eq(illegal.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "single non-king to empty column candidate")
	var result := session.apply_move(illegal)
	assert_false(result.ok, "illegal king-only drop rejected")
	var after := session.state_snapshot()
	assert_true(before.content_equals(after), "illegal drop leaves the state identical")
	assert_false(session.can_undo(), "no snapshot recorded for an illegal move")


func test_legal_run_move_applies_through_session() -> void:
	var created := GameSession.debug_create_state(FixtureStates.ops_state(), GameState.DRAW1)
	var session := created.session
	var legal := InputInterpreter.build_drag_move(
		session.state_snapshot(), {"kind": "tableau", "index": 5, "card_index": 0}, {"kind": "tableau", "index": 4}
	)
	assert_eq(legal.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "legal single run candidate")
	var result := session.apply_move(legal)
	assert_true(result.ok, "legal run move accepted")
	var after := session.state_snapshot()
	assert_true(after.tableau_pile(5).is_empty(), "source column emptied")
	assert_eq(after.tableau_pile(4).top().rank, 5, "destination top is the moved spade 5")
	assert_true(after.total_card_count() == 52, "52 conservation after move")
	assert_true(session.can_undo(), "successful action recorded for undo")


func test_snapshot_projection_is_read_only_and_deterministic() -> void:
	var state := FixtureStates.ops_state()
	var original := state.clone()
	var first := SnapshotProjector.project(state)
	assert_true(original.content_equals(state), "projection did not mutate the source")
	var second := SnapshotProjector.project(state)
	assert_true(first.get("deal_pool", "x") == second.get("deal_pool", "x"), "deterministic deal identity")
	var deep: Array = first.get("waste", [])
	deep[0]["id"] = -1
	assert_true(original.content_equals(state), "mutating the projection cannot touch state")


func test_board_geometry_compression_within_bounds() -> void:
	var short_flags: Array = [false, false, false, true]
	var short := BoardGeometry.tableau_offsets(short_flags, 900)
	assert_true(short.valid, "short column valid")
	assert_false(short.compressed, "short column uses legacy offsets untouched")
	assert_eq(short.offsets, [30, 30, 30], "legacy offsets: only a face-up pair fans wide")
	var deep_flags: Array = []
	for i in 24:
		deep_flags.append(true)
	var deep := BoardGeometry.tableau_offsets(deep_flags, 900)
	assert_true(deep.valid, "deep column valid")
	assert_true(deep.compressed, "deep column compressed")
	assert_true(deep.used <= 900, "deep column fits the available band")
	var positions := BoardGeometry.positions(286, deep.offsets)
	assert_eq(int(positions[0]), 286, "starts at top")
	for i in range(1, positions.size()):
		assert_true(int(positions[i]) > int(positions[i - 1]), "monotonic fan positions")
	assert_true(int(positions[positions.size() - 1]) + BoardGeometry.CARD_H <= 286 + 900, "fan bottom within band")


func test_draw_modes_and_auto_complete_to_won() -> void:
	var deal1 := GameSession.create("bureau1", 0, GameState.DRAW1)
	var deal3 := GameSession.create("bureau1", 0, GameState.DRAW3)
	assert_true(deal1.ok and deal3.ok, "both draw modes deal")
	assert_eq(deal1.session.draw_count(), GameState.DRAW1, "draw1 mode")
	assert_eq(deal3.session.draw_count(), GameState.DRAW3, "draw3 mode")
	var s1 := deal1.session.state_snapshot()
	var s3 := deal3.session.state_snapshot()
	assert_eq(s1.waste.size(), 1, "draw1 ready waste has 1 card")
	assert_eq(s3.waste.size(), 3, "draw3 ready waste has 3 cards")
	assert_true(s1.total_card_count() == 52 and s3.total_card_count() == 52, "both keep 52 cards")

	var created := GameSession.debug_create_state(FixtureStates.near_win(), GameState.DRAW1)
	assert_true(created.ok, "near-win session created")
	var session := created.session
	var plan := session.plan_auto_complete()
	assert_true(plan.eligible, "near-win is auto-eligible")
	assert_true(plan.completed, "planner predicts a win")
	assert_true(plan.moves.size() == 13, "13 tableau-to-foundation moves expected")
	for move in plan.moves:
		assert_eq(move.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "allowed kind only")
		var step := session.apply_move(move)
		assert_true(step.ok, "auto move applies one at a time")
		assert_true(step.new_state.total_card_count() == 52, "52 conservation through auto")
	var final_state := session.state_snapshot()
	assert_eq(final_state.game_status, GameState.GameStatus.WON, "auto complete reaches WON")
	assert_eq(session.history_size(), 13, "each auto move is a recorded user action")
	assert_eq(final_state.move_count, 13, "move counter matches")


func _render_empty_board(board: BoardView) -> void:
	board.set_size(Vector2(1080, 1920))
	var empty_pile: Array = []
	var tableau: Array = []
	for i in 7:
		tableau.append(empty_pile.duplicate())
	var foundation: Array = []
	for i in 4:
		foundation.append(empty_pile.duplicate())
	board.render({
		"draw_count": GameState.DRAW1,
		"score": 0,
		"move_count": 0,
		"stock_passes": 0,
		"status": "IN_PROGRESS",
		"stock": empty_pile.duplicate(),
		"waste": empty_pile.duplicate(),
		"tableau": tableau,
		"foundation": foundation,
	})


func test_hint_shows_two_distinguishable_overlays() -> void:
	var board := BoardView.new()
	_render_empty_board(board)
	var source := {"kind": "tableau", "index": 0}
	var target := {"kind": "foundation", "index": 0}
	board.show_hint(source, target)
	assert_true(board.hint_active(), "hint layer active")
	assert_eq(board.hint_overlay_count(), 2, "both source and target overlays rendered")
	var rects := board.hint_overlay_rects()
	assert_eq(rects.size(), 2, "two overlay rects reported")
	assert_eq(rects[0], board.zone_rect("tableau", 0), "source overlay covers the source zone")
	assert_eq(rects[1], board.zone_rect("foundation", 0), "target overlay covers the target zone")
	var colors := board.hint_overlay_colors()
	assert_eq(colors.size(), 2, "two overlay colours reported")
	assert_true(colors[0] != colors[1], "source and target overlays are distinguishable colours")
	board.clear_hint()
	assert_eq(board.hint_overlay_count(), 0, "clear removes both overlays")


func test_hint_single_overlay_when_target_missing() -> void:
	var board := BoardView.new()
	_render_empty_board(board)
	board.show_hint({"kind": "tableau", "index": 0}, {"kind": "foundation", "index": 9})
	assert_eq(board.hint_overlay_count(), 1, "only the valid source overlay renders when target zone is missing")
	board.clear_hint()


func test_hint_no_overlay_when_no_valid_zone() -> void:
	var board := BoardView.new()
	_render_empty_board(board)
	board.show_hint({"kind": "foundation", "index": 9}, {"kind": "foundation", "index": 8})
	assert_eq(board.hint_overlay_count(), 0, "no overlay when neither zone is valid")
	assert_false(board.hint_active(), "hint layer is torn down when nothing to show")


func test_repeated_hints_do_not_stack_overlays() -> void:
	var board := BoardView.new()
	_render_empty_board(board)
	board.show_hint({"kind": "tableau", "index": 0}, {"kind": "foundation", "index": 0})
	board.show_hint({"kind": "tableau", "index": 1}, {"kind": "foundation", "index": 1})
	assert_eq(board.hint_overlay_count(), 2, "second hint replaces, never stacks")
	var rects := board.hint_overlay_rects()
	assert_eq(rects[0], board.zone_rect("tableau", 1), "source overlay moved to the second source")
	board.clear_hint()


func test_hint_top_card_overlay_is_card_height_not_full_column() -> void:
	var board := BoardView.new()
	board.set_size(Vector2(1080, 1920))
	var empty: Array = []
	var tableau: Array = []
	for col in 7:
		if col == 0:
			tableau.append([
				{"id": fid(0, 13), "face_up": true},
				{"id": fid(1, 12), "face_up": true},
			])
		else:
			tableau.append(empty.duplicate())
	var foundation: Array = []
	for slot in 4:
		foundation.append(empty.duplicate())
	board.render({
		"draw_count": GameState.DRAW1,
		"score": 0,
		"move_count": 0,
		"stock_passes": 0,
		"status": "IN_PROGRESS",
		"stock": empty.duplicate(),
		"waste": empty.duplicate(),
		"tableau": tableau,
		"foundation": foundation,
	})
	var zone := board.zone_rect("tableau", 0)
	board.show_hint(
		{"kind": "tableau", "index": 0, "card_index": 1, "count": 1},
		{"kind": "tableau", "index": 1}
	)
	var rects := board.hint_overlay_rects()
	assert_eq(rects.size(), 2, "source and drop overlays rendered")
	assert_eq(rects[0].size.y, float(BoardGeometry.CARD_H), "top-card hint covers only the playable card, not the column")
	assert_true(rects[0].position.y > zone.position.y, "source highlight starts at the card, below the column top")
	assert_eq(rects[1].size.y, float(BoardGeometry.CARD_H), "empty-column drop target is the slot height")
	assert_true(rects[1].size.y < zone.size.y, "drop target is not the full-height column")
	board.clear_hint()


func test_hint_run_source_overlay_spans_only_moved_cards() -> void:
	var board := BoardView.new()
	board.set_size(Vector2(1080, 1920))
	var empty: Array = []
	var tableau: Array = []
	for col in 7:
		if col == 0:
			tableau.append([
				{"id": 3, "face_up": false},
				{"id": fid(0, 13), "face_up": true},
				{"id": fid(1, 12), "face_up": true},
				{"id": fid(0, 11), "face_up": true},
			])
		else:
			tableau.append(empty.duplicate())
	var foundation: Array = []
	for slot in 4:
		foundation.append(empty.duplicate())
	board.render({
		"draw_count": GameState.DRAW1,
		"score": 0,
		"move_count": 0,
		"stock_passes": 0,
		"status": "IN_PROGRESS",
		"stock": empty.duplicate(),
		"waste": empty.duplicate(),
		"tableau": tableau,
		"foundation": foundation,
	})
	board.show_hint(
		{"kind": "tableau", "index": 0, "card_index": 2, "count": 2},
		{"kind": "tableau", "index": 1}
	)
	var rects := board.hint_overlay_rects()
	assert_eq(rects.size(), 2, "run source and drop overlays rendered")
	assert_eq(
		rects[0].size.y,
		float(BoardGeometry.CARD_H + BoardGeometry.FAN_OPEN),
		"run hint spans only the moved Q+J suffix"
	)
	assert_true(rects[0].position.y > float(BoardView.TAB_TOP), "run overlay starts at the moved card, not the covered column bottom")
	board.clear_hint()


func test_debug_create_state_refuses_invalid_permutations() -> void:
	var not52 := GameSession.debug_create_state(GameState.new(), GameState.DRAW1)
	assert_false(not52.ok, "empty state is refused")
	assert_eq(not52.error_code, GameSessionResult.CODE_INVALID_STATE, "typed structural failure")
	var dup := FixtureStates.near_win()
	var wrong_draw := GameSession.debug_create_state(dup, 7)
	assert_false(wrong_draw.ok, "bad draw count refused")
	assert_eq(wrong_draw.error_code, GameSessionResult.CODE_INVALID_DRAW_COUNT, "typed draw-count failure")


func test_safe_area_layout_identity_and_insets() -> void:
	var content := Vector2(1080, 1920)
	var window := Rect2(0, 0, 540, 960)
	var full := SafeAreaLayout.content_safe_rect(content, window, Rect2(0, 0, 540, 960))
	assert_eq(full, Rect2(0, 0, 1080, 1920), "full-window safe area is identity")
	assert_false(SafeAreaLayout.has_insets(content, full), "full window has no insets")
	var m := SafeAreaLayout.margins(content, full)
	assert_eq(m.left + m.top + m.right + m.bottom, 0.0, "identity margins are zero")

	var inset := SafeAreaLayout.content_safe_rect(content, window, Rect2(0, 40, 540, 880))
	assert_eq(inset.position, Vector2(0, 80), "top inset scaled to canvas units")
	assert_eq(inset.size, Vector2(1080, 1760), "bottom inset scaled to canvas units")
	assert_true(SafeAreaLayout.has_insets(content, inset), "inset window detected")
	var mi := SafeAreaLayout.margins(content, inset)
	assert_eq(mi.top, 80.0, "top piles start below the top inset")
	assert_eq(mi.bottom, 80.0, "bottom controls stay above the bottom inset")
	assert_eq(mi.left, 0.0, "no horizontal inset")

	var off := SafeAreaLayout.content_safe_rect(content, window, Rect2(60, 0, 480, 960))
	assert_eq(off.position, Vector2(120, 0), "left inset scaled to canvas units")
	assert_eq(off.size.x, 960.0, "right inset leaves safe width in canvas units")


func test_board_geometry_full_card_is_visible_in_available_band() -> void:
	var flags: Array = [true]
	var single := BoardGeometry.tableau_offsets(flags, 400)
	assert_true(single.valid, "single open card fits")
	assert_eq(single.used, BoardGeometry.CARD_H, "single card uses one full card height")
	assert_false(single.compressed, "never compressed for a single card")


func test_drag_ghost_carries_whole_run_suffix() -> void:
	var board := BoardView.new()
	_render_empty_board(board)
	var run_ids: Array = [1, 14, 27]
	board.begin_ghost(run_ids, Vector2(540, 500))
	assert_eq(board._ghost_cards.size(), 3, "ghost shows clicked card plus every card stacked below it")
	assert_true(board._ghost_cards[0].position.y < board._ghost_cards[1].position.y, "run fans downward like the tableau")
	assert_eq(
		board._ghost_cards[1].position.y - board._ghost_cards[0].position.y,
		float(BoardGeometry.FAN_OPEN),
		"open-card ghost gap matches the tableau fan"
	)
	board.move_ghost(Vector2(540, 1850))
	var last: CardView = board._ghost_cards[board._ghost_cards.size() - 1]
	assert_true(
		last.position.y + last.size.y <= board.size.y,
		"run ghost is clamped inside the board"
	)
	board.end_ghost()
	assert_eq(board._ghost_cards.size(), 0, "end_ghost releases every run card")
