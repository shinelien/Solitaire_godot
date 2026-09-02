class_name LegacyScorePolicy
extends RefCounted

## Basic legacy scoring extracted from the fixed reference (SpriteManager.cpp
## classically): applied by MoveExecutor AFTER a move passes RulesEngine, so
## score can never influence legality. Tableau<->tableau, draw and recycle are
## score-neutral. Undo uses a flat -2 with a floor at zero applied against the
## restored pre-action score.

const FOUNDATION_DELTA := 10
const WASTE_TO_TABLEAU_DELTA := 5
const FOUNDATION_TO_TABLEAU_DELTA := -10
const GENERATED_FLIP_DELTA := 5
const TABLEAU_TO_TABLEAU_DELTA := 0
const DRAW_DELTA := 0
const RECYCLE_DELTA := 0
const UNDO_PENALTY := -2


## Score change for one already-legal move kind. Tableau->tableau, stock draw
## and recycle score 0; undo is not a RulesEngine move (see undo_score).
static func move_delta(move: Move) -> int:
	if move == null:
		return 0
	match move.kind:
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			return FOUNDATION_DELTA
		Move.MoveKind.WASTE_TO_FOUNDATION:
			return FOUNDATION_DELTA
		Move.MoveKind.WASTE_TO_TABLEAU:
			return WASTE_TO_TABLEAU_DELTA
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			return FOUNDATION_TO_TABLEAU_DELTA
		Move.MoveKind.FLIP_TABLEAU:
			return GENERATED_FLIP_DELTA
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			return TABLEAU_TO_TABLEAU_DELTA
		Move.MoveKind.DRAW_STOCK:
			return DRAW_DELTA
		Move.MoveKind.RECYCLE_STOCK:
			return RECYCLE_DELTA
	return 0


## Total score change of a whole executed batch (requested + generated flips).
static func batch_delta(batch: MoveBatch) -> int:
	if batch == null:
		return 0
	var total := 0
	for move in batch.applied:
		total += move_delta(move)
	return total


## Legacy accumulator update: the fixed reference adds the delta to the running
## score and floors the result at zero (GameViewHD::updateScore), so the score
## never goes negative no matter how large a negative move delta is.
static func apply_delta(score: int, delta: int) -> int:
	return maxi(0, score + delta)


## Apply a whole executed batch's delta to a running score (floored at zero).
static func apply_batch(score: int, batch: MoveBatch) -> int:
	return apply_delta(score, batch_delta(batch))


## Undo penalty: the restored pre-action snapshot's score, minus 2, floored at
## zero. Applied by the executor undo path, never inside RulesEngine.
static func undo_score(pre_action_score: int) -> int:
	return maxi(0, pre_action_score + UNDO_PENALTY)
