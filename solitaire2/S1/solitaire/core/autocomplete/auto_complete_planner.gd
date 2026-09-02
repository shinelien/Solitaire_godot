class_name AutoCompletePlanner
extends RefCounted

## Deterministic, terminating auto-complete *planner* (pure service, no Node
## deps, WP-07). It is deliberately NOT a second rules engine/executor: it
## simulates exclusively by routing each chosen ordinary move through
## MoveExecutor on deep clones, so source GameState and SnapshotHistory are
## never touched.
##
## Permitted emitted moves (ordinary gameplay kinds only):
##   TABLEAU_TO_FOUNDATION, WASTE_TO_FOUNDATION, DRAW_STOCK, RECYCLE_STOCK.
## It never emits tableau rearrangement, foundation rollback, a direct
## FLIP_TABLEAU, card identity changes, or any special auto-only mutation.
##
## Termination: simulation is bounded by a documented max step count (>=512)
## and by canonical board signatures (containers + face-up state + draw mode,
## counters deliberately excluded so recycle/draw cycles are caught). A
## repeated signature stops with a typed no_progress reason; running out of
## steps stops with max_steps; nothing left to do stops with no_legal_move.
## All results are typed AutoCompletePlanResult objects; the planner never
## hangs.

const MAX_STEPS := 2048


static func plan(state: GameState) -> AutoCompletePlanResult:
	if state == null:
		return AutoCompletePlanResult.not_eligible(
			AutoCompletePlanResult.CODE_INVALID_STATE,
			"cannot auto-complete a null state"
		)
	if state.game_status == GameState.GameStatus.WON:
		return AutoCompletePlanResult.eligible_result(
			true,
			AutoCompletePlanResult.STOP_WON,
			"game already won",
			[],
			state,
			0,
			1
		)
	if not _all_tableau_face_up(state):
		return AutoCompletePlanResult.not_eligible(
			AutoCompletePlanResult.CODE_TABLEAU_NOT_FACE_UP,
			"auto-complete requires every tableau card face-up"
		)

	var working := state.clone()
	var plan_moves: Array[Move] = []
	var visited := {}
	var steps := 0
	while true:
		var sig := _signature(working)
		if visited.has(sig):
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_PROGRESS,
				"state signature repeated; no foundation progress possible within a deterministic cycle",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		visited[sig] = true
		if working.game_status == GameState.GameStatus.WON:
			return AutoCompletePlanResult.eligible_result(
				true,
				AutoCompletePlanResult.STOP_WON,
				"all four foundations are complete",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		if steps >= MAX_STEPS:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_MAX_STEPS,
				"step budget of %d exhausted without reaching WON" % MAX_STEPS,
				plan_moves,
				working,
				steps,
				visited.size()
			)
		var move := _select_move(working)
		if move == null:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
				"no permitted auto-complete move is legal in this state",
				plan_moves,
				working,
				steps,
				visited.size()
			)
		var result := MoveExecutor.execute(working, move, null)
		if not result.ok:
			return AutoCompletePlanResult.eligible_result(
				false,
				AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
				"permitted move %s was rejected by the executor: %s" % [move.description(), result.error_message],
				plan_moves,
				working,
				steps,
				visited.size()
			)
		plan_moves.append(move)
		working = result.new_state
		steps += 1
	return AutoCompletePlanResult.eligible_result(
		false,
		AutoCompletePlanResult.STOP_NO_LEGAL_MOVE,
		"unreachable",
		plan_moves,
		working,
		steps,
		visited.size()
	)


## Deterministic best-next ordinary move in priority order:
##   1. tableau top -> foundation (column ascending; slot via dynamic scan)
##   2. waste top -> foundation
##   3. DRAW_STOCK (stock non-empty)
##   4. RECYCLE_STOCK (stock empty, waste non-empty)
## Returns null when none is legal. Every returned move is pre-validated
## through RulesEngine so replaying it through MoveExecutor stays legal.
static func _select_move(state: GameState) -> Move:
	for col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(col)
		if pile == null or pile.is_empty() or not pile.top().face_up:
			continue
		var slot := _foundation_slot_for_card(state, pile.top())
		if slot >= 0:
			return Move.tableau_to_foundation(col, slot)
	if not state.waste.is_empty() and state.waste.top().face_up:
		var waste_slot := _foundation_slot_for_card(state, state.waste.top())
		if waste_slot >= 0:
			return Move.waste_to_foundation(waste_slot)
	if not state.stock.is_empty():
		return Move.draw_stock()
	if not state.waste.is_empty():
		return Move.recycle_stock()
	return null


## Deterministic dynamic foundation destination (validated through RulesEngine):
## for an Ace the first empty slot (any suit) is used; otherwise the first slot
## (ascending index) whose current top is the same suit and exactly one rank
## below the card. Returns the slot index or -1 when the card cannot be placed.
static func _foundation_slot_for_card(state: GameState, card: CardData) -> int:
	if card == null:
		return -1
	for slot in GameState.FOUNDATION_COUNT:
		var pile := state.foundation_pile(slot)
		if pile == null:
			continue
		if pile.is_empty():
			if card.rank == 1:
				return slot
			continue
		var top := pile.top()
		if top == null or not top.face_up:
			continue
		if top.suit == card.suit and top.rank == card.rank - 1:
			return slot
	return -1


## All 28 tableau cards (7 columns, every position) must be face-up.
static func _all_tableau_face_up(state: GameState) -> bool:
	for col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(col)
		if pile == null:
			return false
		for card in pile.cards_snapshot():
			if not card.face_up:
				return false
	return true


## Canonical board signature: card identity + face-up state of every container
## in a fixed order plus the draw mode. Move/score/pass counters and deal
## identity are deliberately excluded so a recycle/draw cycle that returns to
## the same layout is detected as no-progress instead of running forever.
static func _signature(state: GameState) -> String:
	var parts: Array[String] = []
	parts.append(_pile_sig(state.stock))
	parts.append(_pile_sig(state.waste))
	for col in GameState.TABLEAU_COUNT:
		parts.append(_pile_sig(state.tableau_pile(col)))
	for slot in GameState.FOUNDATION_COUNT:
		parts.append(_pile_sig(state.foundation_pile(slot)))
	parts.append("draw=%d" % state.draw_count)
	return "|".join(parts)


static func _pile_sig(pile: CardPile) -> String:
	if pile == null:
		return "-"
	var parts: Array[String] = []
	for card in pile.cards_snapshot():
		parts.append("%d%s" % [card.id, "u" if card.face_up else "d"])
	return "[%s]" % ",".join(parts)
