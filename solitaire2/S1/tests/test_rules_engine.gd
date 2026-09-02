@tool
extends McpTestSuite


func suite_name() -> String:
	return "rules_engine"


# ----- tiny state builders (explicit bottom..top arrays) -----

func _col(entries: Array) -> CardPile:
	var ids: Array = []
	var flags: Array = []
	for entry in entries:
		ids.append(int(entry[0]))
		flags.append(bool(entry[1]))
	return CardStateTestkit.make_pile(ids, false, flags)


func _validate(state: GameState, move: Move) -> MoveValidationResult:
	return RulesEngine.validate(state, move)


func _ok(state: GameState, move: Move, label: String) -> void:
	var result := _validate(state, move)
	assert_true(result.ok, "%s: expected ok, got %s %s" % [label, result.error_code, result.error_message])


func _reject(state: GameState, move: Move, code: String, label: String) -> void:
	var result := _validate(state, move)
	assert_false(result.ok, "%s: expected rejection" % label)
	assert_eq(result.error_code, code, "%s error code" % label)


func _s(suit: int, rank: int) -> int:
	return CardStateTestkit.fid(suit, rank)


# ----- positive legality across move kinds -----

func test_tableau_run_move_positive_counts_and_runs() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	state.tableau[2] = _col([[_s(3, 12), true]])
	_ok(state, Move.tableau_to_tableau(0, 1, 2), "QJ run onto K")
	_ok(state, Move.tableau_to_tableau(0, 2, 1), "single J onto Q")


func test_king_to_empty_tableau_positive() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[4] = _col([[_s(0, 13), true]])
	state.tableau[6] = CardPile.new()
	_ok(state, Move.tableau_to_tableau(4, 6, 1), "king to empty column")
	var full_run := CardStateTestkit.make_state()
	full_run.tableau[0] = _col([[9, false], [_s(0, 13), true], [_s(1, 12), true]])
	full_run.tableau[5] = CardPile.new()
	_ok(full_run, Move.tableau_to_tableau(0, 5, 2), "run ending king to empty column")


func test_tableau_to_foundation_positive() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 1), true]])
	_ok(state, Move.tableau_to_foundation(0, 0), "ace to empty foundation")
	state.tableau[0] = _col([[_s(0, 2), true]])
	state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	_ok(state, Move.tableau_to_foundation(0, 0), "two onto ace")
	state.tableau[0] = _col([[_s(0, 3), true]])
	state.foundation[0] = CardStateTestkit.foundation_of(0, 2)
	_ok(state, Move.tableau_to_foundation(0, 0), "three onto two")


func test_waste_moves_positive() -> void:
	var king_state := CardStateTestkit.make_state()
	king_state.waste = CardStateTestkit.up([_s(0, 13)])
	king_state.tableau[4] = CardPile.new()
	_ok(king_state, Move.waste_to_tableau(4), "waste king onto empty")

	var queen_state := CardStateTestkit.make_state()
	queen_state.waste = CardStateTestkit.up([_s(0, 11)])
	queen_state.tableau[0] = _col([[_s(3, 12), true]])
	_ok(queen_state, Move.waste_to_tableau(0), "waste jack onto queen diamond (alternate)")

	var two_state := CardStateTestkit.make_state()
	two_state.waste = CardStateTestkit.up([_s(0, 1)])
	_ok(two_state, Move.waste_to_foundation(0), "waste ace to empty foundation")
	two_state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	two_state.waste = CardStateTestkit.up([_s(0, 2)])
	_ok(two_state, Move.waste_to_foundation(0), "waste two onto ace")


func test_foundation_to_tableau_positive() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[1] = CardStateTestkit.foundation_of(1, 2)
	state.tableau[0] = _col([[_s(0, 3), true]])
	_ok(state, Move.foundation_to_tableau(1, 0), "heart two onto spade three")
	var state2 := CardStateTestkit.make_state()
	state2.foundation[2] = CardStateTestkit.foundation_of(2, 13)
	state2.tableau[5] = CardPile.new()
	_ok(state2, Move.foundation_to_tableau(2, 5), "king from foundation to empty tableau")


func test_draw_recycle_flip_positive() -> void:
	var draw1 := CardStateTestkit.make_state()
	draw1.stock = CardStateTestkit.down([20, 21, 22, 23])
	_ok(draw1, Move.draw_stock(), "draw with stock (draw1)")
	var draw3 := CardStateTestkit.make_state()
	draw3.draw_count = GameState.DRAW3
	draw3.stock = CardStateTestkit.down([30, 31, 32, 33, 34, 35])
	_ok(draw3, Move.draw_stock(), "draw with stock (draw3)")

	var recycle := CardStateTestkit.make_state()
	recycle.waste = CardStateTestkit.up([10, 11, 12])
	_ok(recycle, Move.recycle_stock(), "recycle empty stock + waste")

	var flip_state := CardStateTestkit.make_state()
	flip_state.tableau[0] = _col([[5, false]])
	_ok(flip_state, Move.flip_tableau(0), "flip exposed face-down top")


func test_opposite_color_helper() -> void:
	assert_true(RulesEngine.suit_is_red(1) and RulesEngine.suit_is_red(3), "hearts/diamonds red")
	assert_false(RulesEngine.suit_is_red(0) or RulesEngine.suit_is_red(2), "spades/clubs black")
	assert_true(RulesEngine.opposite_color(0, 1), "spade vs heart opposite")
	assert_true(RulesEngine.opposite_color(1, 2), "heart vs club opposite")
	assert_false(RulesEngine.opposite_color(0, 2), "spade vs club not opposite")
	assert_false(RulesEngine.opposite_color(1, 3), "heart vs diamond not opposite")


# ----- negative legality -----

func test_invalid_indices_and_self_move() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 13), true]])
	_reject(state, Move.tableau_to_tableau(7, 0, 1), "invalid_index", "source col 7")
	_reject(state, Move.tableau_to_tableau(-1, 0, 1), "invalid_index", "source col -1")
	_reject(state, Move.tableau_to_tableau(0, 7, 1), "invalid_index", "target col 7")
	_reject(state, Move.tableau_to_tableau(0, 0, 1), "self_move", "same column")
	_reject(state, Move.tableau_to_foundation(7, 0), "invalid_index", "t2f col 7")
	_reject(state, Move.tableau_to_foundation(0, -1), "invalid_index", "t2f slot -1")
	_reject(state, Move.tableau_to_foundation(0, 4), "invalid_index", "t2f slot 4")
	_reject(state, Move.waste_to_tableau(7), "invalid_index", "w2t col 7")
	_reject(state, Move.waste_to_foundation(4), "invalid_index", "w2f slot 4")
	_reject(state, Move.foundation_to_tableau(-1, 0), "invalid_index", "f2t slot -1")
	_reject(state, Move.foundation_to_tableau(0, 7), "invalid_index", "f2t col 7")
	_reject(state, Move.flip_tableau(7), "invalid_index", "flip col 7")


func test_invalid_counts_and_empty_sources() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	_reject(state, Move.tableau_to_tableau(0, 1, 0), "invalid_count", "count zero")
	_reject(state, Move.tableau_to_tableau(0, 1, -2), "invalid_count", "count negative")
	_reject(state, Move.tableau_to_tableau(0, 1, 5), "invalid_count", "count exceeds pile")
	_reject(state, Move.tableau_to_tableau(5, 1, 1), "empty_source", "empty source col")
	_reject(state, Move.tableau_to_foundation(5, 0), "empty_source", "t2f empty source")
	_reject(state, Move.waste_to_tableau(1), "waste_empty", "waste move on empty waste")
	_reject(state, Move.waste_to_foundation(1), "waste_empty", "w2f empty waste")
	var foundation_empty := CardStateTestkit.make_state()
	_reject(foundation_empty, Move.foundation_to_tableau(0, 1), "empty_source", "f2t empty foundation")

	var foundation := CardStateTestkit.make_state()
	foundation.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	foundation.tableau[0] = _col([[_s(0, 1), true]])
	_reject(foundation, Move.tableau_to_foundation(0, 0), "foundation_rank", "ace onto ace (not ascending)")
	foundation.tableau[0] = _col([[_s(0, 3), true]])
	_reject(foundation, Move.tableau_to_foundation(0, 0), "foundation_rank", "three onto ace (skips two)")
	foundation.tableau[0] = _col([[_s(1, 2), true]])
	_reject(foundation, Move.tableau_to_foundation(0, 0), "foundation_suit", "heart two onto a slot whose top is the spade ace")


func test_face_down_and_run_invalidity() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	_reject(state, Move.tableau_to_tableau(0, 1, 4), "face_down_card", "run includes face-down card")

	var rank_state := CardStateTestkit.make_state()
	rank_state.tableau[0] = _col([[_s(1, 12), true], [_s(0, 10), true]])
	rank_state.tableau[1] = _col([[_s(2, 13), true]])
	_reject(rank_state, Move.tableau_to_tableau(0, 1, 2), "run_rank", "rank skip inside run")

	var color_state := CardStateTestkit.make_state()
	color_state.tableau[0] = _col([[_s(1, 12), true], [_s(3, 11), true]])
	color_state.tableau[1] = _col([[_s(2, 13), true]])
	_reject(color_state, Move.tableau_to_tableau(0, 1, 2), "run_color", "same color inside run")

	var jack := CardStateTestkit.make_state()
	jack.tableau[0] = _col([[_s(0, 11), true]])
	_reject(jack, Move.tableau_to_tableau(0, 1, 1), "dest_requires_king", "non-king to empty")
	jack.tableau[1] = _col([[_s(2, 13), true]])
	_reject(jack, Move.tableau_to_tableau(0, 1, 1), "dest_rank", "jack onto king")
	jack.tableau[1] = _col([[_s(0, 12), true]])
	_reject(jack, Move.tableau_to_tableau(0, 1, 1), "dest_color", "jack onto spade queen (same color)")
	jack.tableau[1] = _col([[_s(3, 12), true]])
	_ok(jack, Move.tableau_to_tableau(0, 1, 1), "jack onto diamond queen")

	var foundation_empty := CardStateTestkit.make_state()
	foundation_empty.tableau[0] = _col([[_s(0, 5), true]])
	_reject(foundation_empty, Move.tableau_to_foundation(0, 0), "foundation_requires_ace", "five to empty foundation")

	var face_down_top := CardStateTestkit.make_state()
	face_down_top.tableau[0] = _col([[9, false]])
	face_down_top.tableau[1] = _col([[_s(2, 13), true]])
	_reject(face_down_top, Move.tableau_to_foundation(0, 0), "face_down_card", "face-down top to foundation")

	var movable := CardStateTestkit.make_state()
	movable.tableau[0] = _col([[9, false], [_s(0, 11), true]])
	movable.tableau[1] = _col([[_s(1, 12), true]])
	_ok(movable, Move.tableau_to_tableau(0, 1, 1), "face-up top above face-down is movable")

	var waste := CardStateTestkit.make_state()
	waste.tableau[2] = _col([[_s(2, 12), true]])
	waste.waste = CardStateTestkit.up([_s(0, 11)])
	_reject(waste, Move.waste_to_tableau(2), "dest_color", "jack spade onto queen club same color")
	waste.waste = CardStateTestkit.up([_s(0, 13)])
	_reject(waste, Move.waste_to_tableau(2), "dest_rank", "king onto queen (rank mismatch)")
	waste.waste = CardStateTestkit.up([_s(1, 11)])
	_ok(waste, Move.waste_to_tableau(2), "jack heart onto queen club")


func test_draw_recycle_flip_negatives() -> void:
	var empty := CardStateTestkit.make_state()
	_reject(empty, Move.draw_stock(), "stock_empty", "draw empty stock")
	var with_stock := CardStateTestkit.make_state()
	with_stock.stock = CardStateTestkit.down([1, 2])
	_reject(with_stock, Move.recycle_stock(), "stock_not_empty", "recycle while stock non-empty")
	var empty_both := CardStateTestkit.make_state()
	empty_both.stock = CardPile.new()
	_reject(empty_both, Move.recycle_stock(), "waste_empty", "recycle empty waste")
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[_s(0, 11), true]])
	_reject(state, Move.flip_tableau(0), "not_face_down", "flip face-up top")
	state.tableau[1] = CardPile.new()
	_reject(state, Move.flip_tableau(1), "empty_source", "flip empty column")
	var bad_draw := CardStateTestkit.make_state()
	bad_draw.draw_count = 2
	bad_draw.stock = CardStateTestkit.down([1, 2])
	_reject(bad_draw, Move.draw_stock(), "invalid_draw_count", "draw_count 2")


func test_already_won_rejects_every_move_kind() -> void:
	var state := CardStateTestkit.make_state()
	for suit in 4:
		state.foundation[suit] = CardStateTestkit.full_foundation(suit)
	state.game_status = GameState.GameStatus.WON
	state.tableau[0] = _col([[_s(0, 13), true]])
	state.tableau[1] = CardPile.new()
	state.waste = CardStateTestkit.up([_s(1, 1)])
	state.stock = CardStateTestkit.down([1])
	var moves := [
		Move.tableau_to_tableau(0, 1, 1),
		Move.tableau_to_foundation(0, 0),
		Move.waste_to_tableau(0),
		Move.waste_to_foundation(0),
		Move.foundation_to_tableau(0, 0),
		Move.draw_stock(),
		Move.recycle_stock(),
		Move.flip_tableau(0),
	]
	for move in moves:
		_reject(state, move, "already_won", "post-won %s" % Move.kind_name(move.kind))


func test_null_and_undo_kind_rejected() -> void:
	var state := CardStateTestkit.make_state()
	var null_state := RulesEngine.validate(null, Move.tableau_to_tableau(0, 1, 1))
	assert_false(null_state.ok, "null state rejected")
	assert_eq(null_state.error_code, "invalid_state", "null state code")
	var null_move := RulesEngine.validate(state, null)
	assert_false(null_move.ok, "null move rejected")
	assert_eq(null_move.error_code, "invalid_kind", "null move code")
	var undo := RulesEngine.validate(state, Move.undo())
	assert_false(undo.ok, "undo rejected by rules engine")
	assert_eq(undo.error_code, "invalid_kind", "undo code")
	var unknown := RulesEngine.validate(state, Move.new(999, 0, 0, 0, 0, 1))
	assert_false(unknown.ok, "unknown kind rejected")
	assert_eq(unknown.error_code, "invalid_kind", "unknown kind code")


# ----- dynamic foundation slots: empty any Ace, nonempty same-suit ascending -----

func test_any_suit_ace_into_any_empty_foundation_slot_positive() -> void:
	for suit in 4:
		for slot in GameState.FOUNDATION_COUNT:
			var t := CardStateTestkit.make_state()
			t.tableau[0] = _col([[_s(suit, 1), true]])
			_ok(t, Move.tableau_to_foundation(0, slot), "t2f suit %d ace into empty slot %d" % [suit, slot])
			var w := CardStateTestkit.make_state()
			w.waste = CardStateTestkit.up([_s(suit, 1)])
			_ok(w, Move.waste_to_foundation(slot), "w2f suit %d ace into empty slot %d" % [suit, slot])


func test_nonempty_foundation_requires_same_suit_ascending() -> void:
	var nonempty := CardStateTestkit.make_state()
	nonempty.tableau[0] = _col([[_s(1, 2), true]])
	nonempty.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	_reject(nonempty, Move.tableau_to_foundation(0, 0), "foundation_suit", "heart two onto a spade-ace slot")
	nonempty.waste = CardStateTestkit.up([_s(1, 2)])
	nonempty.tableau[0] = CardPile.new()
	_reject(nonempty, Move.waste_to_foundation(0), "foundation_suit", "w2f heart two onto a spade-ace slot")

	var rank_bad := CardStateTestkit.make_state()
	rank_bad.tableau[0] = _col([[_s(0, 1), true]])
	rank_bad.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	_reject(rank_bad, Move.tableau_to_foundation(0, 0), "foundation_rank", "ace onto ace (not ascending)")
	rank_bad.tableau[0] = _col([[_s(0, 3), true]])
	_reject(rank_bad, Move.tableau_to_foundation(0, 0), "foundation_rank", "three onto ace (skips two)")

	var dynamic := CardStateTestkit.make_state()
	dynamic.tableau[0] = _col([[_s(1, 2), true]])
	dynamic.foundation[0] = CardStateTestkit.foundation_of(1, 1)
	_ok(dynamic, Move.tableau_to_foundation(0, 0), "heart two onto a heart-ace slot (slot 0 owns hearts)")


func test_foundation_to_tableau_uses_slot_index_not_suit_identity() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.foundation_of(1, 2)
	state.tableau[0] = _col([[_s(0, 3), true]])
	_ok(state, Move.foundation_to_tableau(0, 0), "heart two from slot 0 (suit != index) onto spade three")
	var state2 := CardStateTestkit.make_state()
	state2.foundation[0] = CardStateTestkit.foundation_of(3, 13)
	state2.tableau[5] = CardPile.new()
	_ok(state2, Move.foundation_to_tableau(0, 5), "diamond king from slot 0 (suit != index) to empty tableau")


func test_foundation_to_tableau_rejects_malformed_face_down_top() -> void:
	var state := CardStateTestkit.make_state()
	state.foundation[0] = CardStateTestkit.down([_s(1, 2)])
	state.tableau[0] = _col([[_s(0, 3), true]])
	_reject(state, Move.foundation_to_tableau(0, 0), "face_down_card", "face-down foundation top cannot leave the slot")


# ----- coordinate/count shape contract (malformed Move locations) -----

func test_malformed_move_locations_rejected_before_legality() -> void:
	var state := CardStateTestkit.make_state()
	var cases: Array = []
	var tt := Move.tableau_to_tableau(0, 1, 1)
	tt.source_location = Move.Location.LOC_FOUNDATION
	cases.append([tt, "tt src loc"])
	var tf := Move.tableau_to_foundation(0, 0)
	tf.target_location = Move.Location.LOC_TABLEAU
	cases.append([tf, "tf dst loc"])
	var wt := Move.waste_to_tableau(0)
	wt.source_location = Move.Location.LOC_STOCK
	cases.append([wt, "wt src loc"])
	var wf := Move.waste_to_foundation(0)
	wf.target_location = Move.Location.LOC_STOCK
	cases.append([wf, "wf dst loc"])
	var ft := Move.foundation_to_tableau(0, 0)
	ft.source_location = Move.Location.LOC_TABLEAU
	cases.append([ft, "ft src loc"])
	var draw := Move.draw_stock()
	draw.target_location = Move.Location.LOC_STOCK
	cases.append([draw, "draw dst loc"])
	var recycle := Move.recycle_stock()
	recycle.source_location = Move.Location.LOC_TABLEAU
	cases.append([recycle, "recycle src loc"])
	var flip := Move.flip_tableau(0)
	flip.target_location = Move.Location.LOC_FOUNDATION
	cases.append([flip, "flip dst loc"])
	for c in cases:
		_reject(state, c[0], "invalid_location", c[1])


func test_malformed_move_counts_rejected() -> void:
	var state := CardStateTestkit.make_state()
	var cases: Array = []
	var tf := Move.tableau_to_foundation(0, 0)
	tf.count = 2
	cases.append([tf, "tf count 2"])
	var wt := Move.waste_to_tableau(0)
	wt.count = 0
	cases.append([wt, "wt count 0"])
	var wf := Move.waste_to_foundation(0)
	wf.count = 2
	cases.append([wf, "wf count 2"])
	var ft := Move.foundation_to_tableau(0, 0)
	ft.count = 3
	cases.append([ft, "ft count 3"])
	var draw := Move.draw_stock()
	draw.count = 1
	cases.append([draw, "draw count 1"])
	var recycle := Move.recycle_stock()
	recycle.count = 1
	cases.append([recycle, "recycle count 1"])
	var flip := Move.flip_tableau(0)
	flip.count = 0
	cases.append([flip, "flip count 0"])
	for c in cases:
		_reject(state, c[0], "invalid_count", c[1])


func test_rules_engine_never_mutates_state() -> void:
	var state := CardStateTestkit.make_state()
	state.tableau[0] = _col([[3, false], [_s(0, 13), true], [_s(1, 12), true], [_s(0, 11), true]])
	state.tableau[1] = _col([[_s(2, 13), true]])
	state.waste = CardStateTestkit.up([_s(3, 2), _s(0, 1)])
	state.foundation[0] = CardStateTestkit.foundation_of(0, 1)
	var baseline := state.clone()
	var moves := [
		Move.tableau_to_tableau(0, 1, 2),
		Move.tableau_to_tableau(0, 1, 5),
		Move.tableau_to_tableau(0, 1, 0),
		Move.tableau_to_tableau(3, 1, 1),
		Move.tableau_to_tableau(0, 0, 1),
		Move.tableau_to_foundation(0, 3),
		Move.waste_to_foundation(1),
		Move.waste_to_tableau(1),
		Move.foundation_to_tableau(0, 0),
		Move.draw_stock(),
		Move.recycle_stock(),
		Move.flip_tableau(0),
	]
	for move in moves:
		_validate(state, move)
		assert_true(state.content_equals(baseline), "state unchanged after %s" % Move.kind_name(move.kind))

	var malformed := _malformed_moves()
	for move in malformed:
		_validate(state, move)
		assert_true(state.content_equals(baseline), "state unchanged after malformed %s" % Move.kind_name(move.kind))


## One hand-corrupted Move per ordinary MoveKind (location and count variants).
func _malformed_moves() -> Array[Move]:
	var out: Array[Move] = []
	var tt := Move.tableau_to_tableau(0, 1, 1)
	tt.source_location = Move.Location.LOC_FOUNDATION
	out.append(tt)
	var tf := Move.tableau_to_foundation(0, 0)
	tf.target_location = Move.Location.LOC_TABLEAU
	tf.count = 2
	out.append(tf)
	var wt := Move.waste_to_tableau(0)
	wt.source_location = Move.Location.LOC_STOCK
	out.append(wt)
	var wf := Move.waste_to_foundation(0)
	wf.target_location = Move.Location.LOC_STOCK
	wf.count = 2
	out.append(wf)
	var ft := Move.foundation_to_tableau(0, 0)
	ft.source_location = Move.Location.LOC_TABLEAU
	out.append(ft)
	var draw := Move.draw_stock()
	draw.target_location = Move.Location.LOC_STOCK
	draw.count = 1
	out.append(draw)
	var recycle := Move.recycle_stock()
	recycle.source_location = Move.Location.LOC_TABLEAU
	recycle.count = 1
	out.append(recycle)
	var flip := Move.flip_tableau(0)
	flip.target_location = Move.Location.LOC_FOUNDATION
	out.append(flip)
	return out
