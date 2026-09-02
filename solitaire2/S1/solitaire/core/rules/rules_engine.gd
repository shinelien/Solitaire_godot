class_name RulesEngine
extends RefCounted

## The only legality authority for classic Klondike moves (pure functions, no
## Node deps, never mutates state). Every check returns a typed
## MoveValidationResult with a stable code + message. Scoring is deliberately
## absent here: score is applied by MoveExecutor only after a move is legal.

## suit -> color group; 0=black(spades/clubs), 1=red(hearts/diamonds).
static func suit_is_red(suit: int) -> bool:
	return suit == 1 or suit == 3


## Opposite color check for alternating tableau builds.
static func opposite_color(a_suit: int, b_suit: int) -> bool:
	return suit_is_red(a_suit) != suit_is_red(b_suit)


static func validate(state: GameState, move: Move) -> MoveValidationResult:
	if state == null:
		return MoveValidationResult.failure(
			MoveValidationResult.CODE_INVALID_STATE,
			"cannot validate a move against a null state"
		)
	if move == null:
		return MoveValidationResult.failure(
			MoveValidationResult.CODE_INVALID_KIND,
			"move is null"
		)
	if state.game_status == GameState.GameStatus.WON:
		return MoveValidationResult.failure(
			MoveValidationResult.CODE_ALREADY_WON,
			"game is already won; no further moves are legal"
		)
	## Coordinate/count shape is checked before any board legality: a hand-built
	## or mutated Move whose source_location/target_location/count contradicts
	## its kind can never execute with its canonical key/source/target lying.
	var shape := _check_move_shape(move)
	if not shape.ok:
		return shape
	match move.kind:
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			return _validate_tableau_to_tableau(state, move)
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			return _validate_tableau_to_foundation(state, move)
		Move.MoveKind.WASTE_TO_TABLEAU:
			return _validate_waste_to_tableau(state, move)
		Move.MoveKind.WASTE_TO_FOUNDATION:
			return _validate_waste_to_foundation(state, move)
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			return _validate_foundation_to_tableau(state, move)
		Move.MoveKind.DRAW_STOCK:
			return _validate_draw_stock(state)
		Move.MoveKind.RECYCLE_STOCK:
			return _validate_recycle_stock(state)
		Move.MoveKind.FLIP_TABLEAU:
			return _validate_flip_tableau(state, move)
	return MoveValidationResult.failure(
		MoveValidationResult.CODE_INVALID_KIND,
		"unknown move kind %d" % move.kind
	)


## Canonical per-kind shape contract (the exact shape the typed factories on
## `Move` guarantee). Each MoveKind must carry exactly its documented
## source_location/target_location and count convention; TABLEAU_TO_TABLEAU's
## run count is left to its own legality rule. UNDO and unknown kinds are
## rejected here as non-gameplay identities.
static func _check_move_shape(move: Move) -> MoveValidationResult:
	var src := move.source_location
	var dst := move.target_location
	match move.kind:
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			if src != Move.Location.LOC_TABLEAU or dst != Move.Location.LOC_TABLEAU:
				return _shape_location_failure(move)
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			if src != Move.Location.LOC_TABLEAU or dst != Move.Location.LOC_FOUNDATION:
				return _shape_location_failure(move)
			if move.count != 1:
				return _shape_count_failure(move, "1")
		Move.MoveKind.WASTE_TO_TABLEAU:
			if src != Move.Location.LOC_WASTE or dst != Move.Location.LOC_TABLEAU:
				return _shape_location_failure(move)
			if move.count != 1:
				return _shape_count_failure(move, "1")
		Move.MoveKind.WASTE_TO_FOUNDATION:
			if src != Move.Location.LOC_WASTE or dst != Move.Location.LOC_FOUNDATION:
				return _shape_location_failure(move)
			if move.count != 1:
				return _shape_count_failure(move, "1")
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			if src != Move.Location.LOC_FOUNDATION or dst != Move.Location.LOC_TABLEAU:
				return _shape_location_failure(move)
			if move.count != 1:
				return _shape_count_failure(move, "1")
		Move.MoveKind.DRAW_STOCK:
			if src != Move.Location.LOC_STOCK or dst != Move.Location.LOC_WASTE:
				return _shape_location_failure(move)
			if move.count != 0:
				return _shape_count_failure(move, "0 (dynamic)")
		Move.MoveKind.RECYCLE_STOCK:
			if src != Move.Location.LOC_WASTE or dst != Move.Location.LOC_STOCK:
				return _shape_location_failure(move)
			if move.count != 0:
				return _shape_count_failure(move, "0 (dynamic)")
		Move.MoveKind.FLIP_TABLEAU:
			if src != Move.Location.LOC_TABLEAU or dst != Move.Location.LOC_TABLEAU:
				return _shape_location_failure(move)
			if move.count != 1:
				return _shape_count_failure(move, "1")
		Move.MoveKind.UNDO:
			return MoveValidationResult.failure(
				MoveValidationResult.CODE_INVALID_KIND,
				"UNDO is a result/history boundary identity, not a gameplay move; use MoveExecutor.execute_undo"
			)
		Move.MoveKind.REPLAY:
			return MoveValidationResult.failure(
				MoveValidationResult.CODE_INVALID_KIND,
				"REPLAY is a session-boundary identity, not a gameplay move; use MoveExecutor.execute_boundary"
			)
		Move.MoveKind.NEW_DEAL:
			return MoveValidationResult.failure(
				MoveValidationResult.CODE_INVALID_KIND,
				"NEW_DEAL is a session-boundary identity, not a gameplay move; use MoveExecutor.execute_boundary"
			)
		_:
			return MoveValidationResult.failure(
				MoveValidationResult.CODE_INVALID_KIND,
				"unknown move kind %d" % move.kind
			)
	return MoveValidationResult.success()


static func _shape_location_failure(move: Move) -> MoveValidationResult:
	return _fail(
		MoveValidationResult.CODE_INVALID_LOCATION,
		"%s has source/target location %s[%d]->%s[%d] which contradicts the kind's documented coordinates"
		% [
			Move.kind_name(move.kind),
			Move.location_name(move.source_location),
			move.source_index,
			Move.location_name(move.target_location),
			move.target_index,
		]
	)


static func _shape_count_failure(move: Move, expected: String) -> MoveValidationResult:
	return _fail(
		MoveValidationResult.CODE_INVALID_COUNT,
		"%s requires count %s but has count %d"
		% [Move.kind_name(move.kind), expected, move.count]
	)


# ----- tableau -> tableau (run move) -----

static func _validate_tableau_to_tableau(state: GameState, move: Move) -> MoveValidationResult:
	var from_col := move.source_index
	var to_col := move.target_index
	if from_col < 0 or from_col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "source tableau column %d out of range" % from_col)
	if to_col < 0 or to_col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "target tableau column %d out of range" % to_col)
	if from_col == to_col:
		return _fail(MoveValidationResult.CODE_SELF_MOVE, "tableau column %d cannot move onto itself" % from_col)
	if move.count < 1:
		return _fail(MoveValidationResult.CODE_INVALID_COUNT, "move count %d must be >= 1" % move.count)

	var source := state.tableau_pile(from_col)
	if source.is_empty():
		return _fail(MoveValidationResult.CODE_EMPTY_SOURCE, "source tableau column %d is empty" % from_col)
	if move.count > source.size():
		return _fail(
			MoveValidationResult.CODE_INVALID_COUNT,
			"move count %d exceeds source tableau column %d size %d" % [move.count, from_col, source.size()]
		)

	var run := _top_run(source, move.count)
	var face_check := _check_run_face_up(run)
	if not face_check.ok:
		return face_check
	var run_check := _check_run_order(run)
	if not run_check.ok:
		return run_check

	var target := state.tableau_pile(to_col)
	return _check_tableau_destination(target, run[0])


# ----- into foundation -----

static func _validate_tableau_to_foundation(state: GameState, move: Move) -> MoveValidationResult:
	var from_col := move.source_index
	var slot := move.target_index
	if from_col < 0 or from_col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "source tableau column %d out of range" % from_col)
	if slot < 0 or slot >= GameState.FOUNDATION_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "foundation slot %d out of range" % slot)

	var source := state.tableau_pile(from_col)
	if source.is_empty():
		return _fail(MoveValidationResult.CODE_EMPTY_SOURCE, "source tableau column %d is empty" % from_col)
	var card := source.top()
	if not card.face_up:
		return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "tableau column %d top is face-down; only face-up cards reach the foundation" % from_col)
	return _check_foundation_destination(state, slot, card)


static func _validate_waste_to_foundation(state: GameState, move: Move) -> MoveValidationResult:
	var slot := move.target_index
	if slot < 0 or slot >= GameState.FOUNDATION_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "foundation slot %d out of range" % slot)
	if state.waste.is_empty():
		return _fail(MoveValidationResult.CODE_WASTE_EMPTY, "waste is empty")
	var card := state.waste.top()
	if not card.face_up:
		return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "waste top is face-down; only the face-up waste top is playable")
	return _check_foundation_destination(state, slot, card)


# ----- out of the waste -----

static func _validate_waste_to_tableau(state: GameState, move: Move) -> MoveValidationResult:
	var to_col := move.target_index
	if to_col < 0 or to_col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "target tableau column %d out of range" % to_col)
	if state.waste.is_empty():
		return _fail(MoveValidationResult.CODE_WASTE_EMPTY, "waste is empty")
	var card := state.waste.top()
	if not card.face_up:
		return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "waste top is face-down; only the face-up waste top is playable")
	var target := state.tableau_pile(to_col)
	return _check_tableau_destination(target, card)


# ----- foundation -> tableau (top only, one card) -----

## A foundation slot is addressed by slot index and its top is movable onto a
## tableau destination under the classic tableau rule regardless of which suit
## currently owns the slot (dynamic slots, matching the fixed reference's
## checkACardPos which never binds a slot index to a suit).
static func _validate_foundation_to_tableau(state: GameState, move: Move) -> MoveValidationResult:
	var from_slot := move.source_index
	var to_col := move.target_index
	if from_slot < 0 or from_slot >= GameState.FOUNDATION_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "source foundation slot %d out of range" % from_slot)
	if to_col < 0 or to_col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "target tableau column %d out of range" % to_col)

	var source := state.foundation_pile(from_slot)
	if source.is_empty():
		return _fail(MoveValidationResult.CODE_EMPTY_SOURCE, "foundation slot %d is empty" % from_slot)
	var card := source.top()
	if not card.face_up:
		return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "foundation slot %d top is face-down (malformed state)" % from_slot)
	var target := state.tableau_pile(to_col)
	return _check_tableau_destination(target, card)


# ----- stock / recycle / flip -----

static func _validate_draw_stock(state: GameState) -> MoveValidationResult:
	if state.draw_count != GameState.DRAW1 and state.draw_count != GameState.DRAW3:
		return _fail(
			MoveValidationResult.CODE_INVALID_DRAW_COUNT,
			"state draw_count %d is not 1 or 3" % state.draw_count
		)
	if state.stock.is_empty():
		return _fail(MoveValidationResult.CODE_STOCK_EMPTY, "stock is empty; nothing to draw")
	return MoveValidationResult.success()


static func _validate_recycle_stock(state: GameState) -> MoveValidationResult:
	if not state.stock.is_empty():
		return _fail(MoveValidationResult.CODE_STOCK_NOT_EMPTY, "recycle requires an empty stock (still %d cards)" % state.stock.size())
	if state.waste.is_empty():
		return _fail(MoveValidationResult.CODE_WASTE_EMPTY, "recycle requires a non-empty waste")
	return MoveValidationResult.success()


static func _validate_flip_tableau(state: GameState, move: Move) -> MoveValidationResult:
	var col := move.source_index
	if col < 0 or col >= GameState.TABLEAU_COUNT:
		return _fail(MoveValidationResult.CODE_INVALID_INDEX, "tableau column %d out of range" % col)
	var pile := state.tableau_pile(col)
	if pile.is_empty():
		return _fail(MoveValidationResult.CODE_EMPTY_SOURCE, "tableau column %d is empty; nothing to flip" % col)
	var top := pile.top()
	if top.face_up:
		return _fail(
			MoveValidationResult.CODE_NOT_FACE_DOWN,
			"tableau column %d top is already face-up; flip is only valid for an exposed face-down top" % col
		)
	return MoveValidationResult.success()


# ----- shared destination/run checks -----

## Classic tableau destination: empty column accepts only a King; otherwise the
## incoming card must be exactly one rank below a face-up top with alternating
## color.
static func _check_tableau_destination(target: CardPile, incoming: CardData) -> MoveValidationResult:
	if target.is_empty():
		if incoming.rank != 13:
			return _fail(
				MoveValidationResult.CODE_DEST_REQUIRES_KING,
				"empty tableau column accepts only a King, not rank %d" % incoming.rank
			)
		return MoveValidationResult.success()
	var top := target.top()
	if not top.face_up:
		return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "destination tableau top is face-down (not accessible)")
	if top.rank != incoming.rank + 1:
		return _fail(
			MoveValidationResult.CODE_DEST_RANK,
			"rank %d cannot attach to tableau rank %d (must be one lower)" % [incoming.rank, top.rank]
		)
	if not opposite_color(incoming.suit, top.suit):
		return _fail(
			MoveValidationResult.CODE_DEST_COLOR,
			"suit %d color must alternate with destination suit %d color" % [incoming.suit, top.suit]
		)
	return MoveValidationResult.success()


## Classic dynamic foundation destination (matches the fixed reference
## SpriteManager::checkACardPos / CardSprite::checkAPos): an empty slot accepts
## any face-up Ace regardless of suit; a nonempty slot accepts a face-up card
## only when it is the same suit as the slot's top and exactly one rank higher
## — the suit a slot builds is owned by its content, never pre-bound to the slot
## index. Foundation tops are always face-up in valid states; a face-down top is
## a malformed state and is rejected.
static func _check_foundation_destination(state: GameState, slot: int, card: CardData) -> MoveValidationResult:
	if card == null:
		return _fail(MoveValidationResult.CODE_INVALID_STATE, "incoming card is null (malformed state)")
	var pile := state.foundation_pile(slot)
	if pile.is_empty():
		if card.rank != 1:
			return _fail(
				MoveValidationResult.CODE_FOUNDATION_REQUIRES_ACE,
				"empty foundation slot accepts only an Ace, not rank %d" % card.rank
			)
		return MoveValidationResult.success()
	var top := pile.top()
	if top == null:
		return _fail(MoveValidationResult.CODE_INVALID_STATE, "foundation slot %d top is null (malformed state)" % slot)
	if not top.face_up:
		return _fail(
			MoveValidationResult.CODE_FACE_DOWN_CARD,
			"foundation slot %d top is face-down (malformed state)" % slot
		)
	if card.suit != top.suit:
		return _fail(
			MoveValidationResult.CODE_FOUNDATION_SUIT,
			"suit %d cannot stack on foundation slot %d whose top is suit %d (must match the slot's current suit)"
			% [card.suit, slot, top.suit]
		)
	if top.rank != card.rank - 1:
		return _fail(
			MoveValidationResult.CODE_FOUNDATION_RANK,
			"rank %d cannot stack on foundation rank %d (must be exactly one higher)" % [card.rank, top.rank]
		)
	return MoveValidationResult.success()


## The top `count` cards of a pile as an ordered run (bottom..top of the run).
static func _top_run(pile: CardPile, count: int) -> Array[CardData]:
	return pile.cards_snapshot().slice(pile.size() - count)


static func _check_run_face_up(run: Array[CardData]) -> MoveValidationResult:
	for card in run:
		if not card.face_up:
			return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "moved run contains a face-down card")
	return MoveValidationResult.success()


static func _check_run_order(run: Array[CardData]) -> MoveValidationResult:
	for i in range(1, run.size()):
		var upper := run[i]
		var lower := run[i - 1]
		if upper.rank != lower.rank - 1:
			return _fail(
				MoveValidationResult.CODE_RUN_RANK,
				"run ranks %d then %d are not descending by one" % [lower.rank, upper.rank]
			)
		if not opposite_color(upper.suit, lower.suit):
			return _fail(
				MoveValidationResult.CODE_RUN_COLOR,
				"run suits %d and %d do not alternate color" % [lower.suit, upper.suit]
			)
	return MoveValidationResult.success()


static func _fail(code: String, message: String) -> MoveValidationResult:
	return MoveValidationResult.failure(code, message)
