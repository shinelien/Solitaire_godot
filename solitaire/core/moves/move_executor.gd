class_name MoveExecutor
extends RefCounted

## Applies Moves to a GameState. Every mutation is validated first; invalid
## moves return failure without touching the state (the caller owns the
## working copy, so an invalid transaction is an atomic no-op).
##
## NOTE: auto-exposed tableau flips are always explicit FLIP_TABLEAU Moves,
## never implicit side effects of a MOVE_CARD.

static func apply(state: GameState, move: Move) -> MoveResult:
	if move == null:
		return MoveResult.failure("null move")
	match move.type:
		Move.MoveType.MOVE_CARD:
			return _apply_move_card(state, move)
		Move.MoveType.FLIP_TABLEAU:
			return _apply_flip(state, move)
		Move.MoveType.DRAW:
			return _apply_draw(state, move)
		Move.MoveType.RECYCLE:
			return _apply_recycle(state, move)
	return MoveResult.failure("unknown move type")

static func _apply_move_card(state: GameState, move: Move) -> MoveResult:
	if not KlondikeRules.is_legal_move(state, move):
		return MoveResult.failure("illegal move: " + str(move))
	var src: Array[CardData] = state.get_pile(move.from_pile)
	var dst: Array[CardData] = state.get_pile(move.to_pile)
	var moved: Array[CardData] = []
	if move.from_pile.type == PileType.TABLEAU:
		moved = src.slice(move.from_index, move.from_index + move.count)
		src.resize(move.from_index)
	else:
		moved.push_back(src.pop_back())
	for c in moved:
		dst.push_back(c)
	return MoveResult.success(move)

static func _apply_flip(state: GameState, move: Move) -> MoveResult:
	if move.from_pile == null or move.from_pile.type != PileType.TABLEAU:
		return MoveResult.failure("flip requires a tableau column")
	var cards := state.col(move.from_pile.index)
	if cards.is_empty():
		return MoveResult.failure("cannot flip an empty column")
	var top: CardData = cards[cards.size() - 1]
	if top.face_up:
		return MoveResult.failure("card is already face-up")
	top.face_up = true
	return MoveResult.success(move)

static func _apply_draw(state: GameState, move: Move) -> MoveResult:
	var n := KlondikeRules.draw_count_for(state)
	if n <= 0:
		return MoveResult.failure("stock is empty")
	for i in n:
		var c: CardData = state.stock.pop_back()
		c.face_up = true
		state.waste.push_back(c)
	state.draw_count += 1
	return MoveResult.success(move)

static func _apply_recycle(state: GameState, move: Move) -> MoveResult:
	if not state.stock.is_empty():
		return MoveResult.failure("stock is not empty")
	if state.waste.is_empty():
		return MoveResult.failure("waste is empty, nothing to recycle")
	while not state.waste.is_empty():
		var c: CardData = state.waste.pop_back()
		c.face_up = false
		state.stock.push_back(c)
	return MoveResult.success(move)
