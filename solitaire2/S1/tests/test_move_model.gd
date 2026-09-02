@tool
extends McpTestSuite


func suite_name() -> String:
	return "move_model"


func test_move_factories_set_kind_coordinates_and_count() -> void:
	var tt := Move.tableau_to_tableau(3, 5, 2)
	assert_eq(tt.kind, Move.MoveKind.TABLEAU_TO_TABLEAU, "tt kind")
	assert_eq(tt.source_location, Move.Location.LOC_TABLEAU, "tt src loc")
	assert_eq(tt.source_index, 3, "tt src col")
	assert_eq(tt.target_location, Move.Location.LOC_TABLEAU, "tt dst loc")
	assert_eq(tt.target_index, 5, "tt dst col")
	assert_eq(tt.count, 2, "tt count")

	var tf := Move.tableau_to_foundation(1, 2)
	assert_eq(tf.kind, Move.MoveKind.TABLEAU_TO_FOUNDATION, "tf kind")
	assert_eq(tf.source_index, 1, "tf src col")
	assert_eq(tf.target_location, Move.Location.LOC_FOUNDATION, "tf dst loc")
	assert_eq(tf.target_index, 2, "tf suit")
	assert_eq(tf.count, 1, "tf count 1")

	var wt := Move.waste_to_tableau(6)
	assert_eq(wt.kind, Move.MoveKind.WASTE_TO_TABLEAU, "wt kind")
	assert_eq(wt.source_location, Move.Location.LOC_WASTE, "wt src loc")
	assert_eq(wt.target_index, 6, "wt col")

	var wf := Move.waste_to_foundation(0)
	assert_eq(wf.kind, Move.MoveKind.WASTE_TO_FOUNDATION, "wf kind")
	assert_eq(wf.target_location, Move.Location.LOC_FOUNDATION, "wf dst loc")
	assert_eq(wf.target_index, 0, "wf suit")

	var ft := Move.foundation_to_tableau(3, 4)
	assert_eq(ft.kind, Move.MoveKind.FOUNDATION_TO_TABLEAU, "ft kind")
	assert_eq(ft.source_location, Move.Location.LOC_FOUNDATION, "ft src loc")
	assert_eq(ft.source_index, 3, "ft suit")
	assert_eq(ft.target_index, 4, "ft col")

	var draw := Move.draw_stock()
	assert_eq(draw.kind, Move.MoveKind.DRAW_STOCK, "draw kind")
	assert_eq(draw.source_location, Move.Location.LOC_STOCK, "draw src loc")
	assert_eq(draw.count, 0, "draw dynamic count marker")

	var recycle := Move.recycle_stock()
	assert_eq(recycle.kind, Move.MoveKind.RECYCLE_STOCK, "recycle kind")

	var flip := Move.flip_tableau(2)
	assert_eq(flip.kind, Move.MoveKind.FLIP_TABLEAU, "flip kind")
	assert_eq(flip.source_index, 2, "flip col")

	var undo := Move.undo()
	assert_eq(undo.kind, Move.MoveKind.UNDO, "undo kind")
	assert_true(undo.is_undo(), "undo identity")
	assert_false(draw.is_undo(), "draw not undo")


func test_move_kind_name_roundtrip_all_kinds() -> void:
	var moves := [
		Move.tableau_to_tableau(0, 1, 1),
		Move.tableau_to_foundation(0, 0),
		Move.waste_to_tableau(0),
		Move.waste_to_foundation(0),
		Move.foundation_to_tableau(0, 0),
		Move.draw_stock(),
		Move.recycle_stock(),
		Move.flip_tableau(0),
		Move.undo(),
	]
	assert_eq(moves.size(), 9, "all MoveKind values have a factory")
	var seen: Dictionary = {}
	for move in moves:
		var name := Move.kind_name(move.kind)
		assert_true(Move.kind_name(move.kind).length() > 0, "kind name non-empty")
		seen[name] = true
	assert_eq(seen.size(), 9, "all kind names distinct")


func test_move_key_stable_and_discriminating() -> void:
	var a := Move.tableau_to_tableau(0, 1, 1)
	var b := Move.tableau_to_tableau(0, 1, 1)
	assert_eq(a.key(), b.key(), "same config same key")
	assert_eq(Move.tableau_to_tableau(0, 2, 1).key(), Move.tableau_to_tableau(0, 2, 1).key(), "other dest stable")
	var keys := [a.key(), Move.tableau_to_tableau(0, 2, 1).key(), Move.tableau_to_tableau(1, 2, 1).key()]
	assert_eq(keys, keys.duplicate(), "deterministic keys")


func test_move_is_pure_data_refcounted_not_node() -> void:
	var move: Variant = Move.tableau_to_tableau(0, 1, 1)
	assert_true(move is RefCounted, "Move is RefCounted")
	assert_false(move is Node, "Move is not a Node")
	assert_false(move is Control, "Move is not a Control")


func test_move_batch_composition_and_undo_identity() -> void:
	var requested := Move.tableau_to_tableau(0, 4, 1)
	var flip := Move.flip_tableau(0)
	var batch := MoveBatch.from_moves(requested, [flip])
	assert_eq(batch.requested, requested, "requested stored")
	assert_eq(batch.applied.size(), 2, "applied = requested + generated")
	assert_eq(batch.applied[0], requested, "requested first")
	assert_eq(batch.applied[1], flip, "flip second")
	assert_eq(batch.generated.size(), 1, "generated listed")
	assert_eq(batch.generated[0], flip, "flip in generated")
	assert_true(batch.has_generated(), "has generated")
	assert_eq(batch.generated_flips().size(), 1, "one generated flip")
	assert_false(batch.is_single(), "not single")
	assert_false(batch.is_undo_batch(), "not undo")
	assert_eq(batch.applied_move_kinds(), [requested.kind, flip.kind], "applied kinds in order")

	var single := MoveBatch.from_moves(Move.waste_to_foundation(0))
	assert_true(single.is_single(), "single requested batch")
	assert_true(single.generated.is_empty(), "no generated")

	var undo := MoveBatch.undo_batch()
	assert_true(undo.is_undo_batch(), "undo batch identity")
	assert_eq(undo.requested.kind, Move.MoveKind.UNDO, "undo requested kind")
	assert_eq(undo.applied.size(), 1, "undo applied single")


func test_move_execution_result_success_and_failure() -> void:
	var state := CardStateTestkit.make_state()
	var batch := MoveBatch.from_moves(Move.draw_stock())
	var ok := MoveExecutionResult.success(state, batch)
	assert_true(ok.ok, "success ok")
	assert_eq(ok.error_code, MoveExecutionResult.CODE_OK, "success code")
	assert_eq(ok.new_state, state, "success carries state")
	assert_eq(ok.batch, batch, "success carries batch")
	assert_false(ok.undoes(), "normal batch not undo")

	var fail := MoveExecutionResult.failure(MoveExecutionResult.CODE_NOTHING_TO_UNDO, "empty")
	assert_false(fail.ok, "failure not ok")
	assert_eq(fail.error_code, "nothing_to_undo", "failure code")
	assert_true(fail.new_state == null, "failure no state")
	assert_true(fail.batch == null, "failure no batch")

	var undo_result := MoveExecutionResult.success(state, MoveBatch.undo_batch())
	assert_true(undo_result.undoes(), "undo result boundary identity")


func test_move_validation_result_stable_codes() -> void:
	var s := MoveValidationResult.success()
	assert_true(s.ok, "success ok")
	var f := MoveValidationResult.failure(MoveValidationResult.CODE_SELF_MOVE, "self")
	assert_false(f.ok, "failure not ok")
	assert_eq(f.error_code, "self_move", "stable code")
	assert_eq(MoveValidationResult.CODE_ALREADY_WON, "already_won", "won code stable")
	assert_eq(MoveValidationResult.CODE_FOUNDATION_REQUIRES_ACE, "foundation_requires_ace", "ace code stable")
