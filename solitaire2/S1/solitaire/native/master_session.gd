class_name MasterSession
extends RefCounted

## Product session for the selected Cocos master. The older deterministic
## repository remains available to its original tests, not to player new-game.
var state: GameState
var original_ids: Array[int] = []
var history: Array[Dictionary] = []
var used_undo := false

func start(draw_count: int, replay := false) -> void:
	if not replay or original_ids.is_empty():
		original_ids.clear()
		var available: Array[int] = []
		for id in 52:
			available.append(id)
		while not available.is_empty():
			var i := randi_range(0, available.size() - 1)
			original_ids.append(available.pop_at(i))
	state = GameState.new()
	state.draw_count = draw_count
	state.deal_pool = "master-random"
	var cursor := 0
	for col in 7:
		for row in col + 1:
			state.tableau[col].add_top(CardData.new(original_ids[cursor], row == col))
			cursor += 1
	for i in range(28, 52):
		state.stock.add_top(CardData.new(original_ids[i], false))
	# Master automatically draws the first group after the deal animation.
	for i in draw_count:
		var card := state.stock.pop_top()
		card.face_up = true
		state.waste.add_top(card)
	history.clear()
	used_undo = false
	WinEvaluator.update_status(state)

func apply(move: Move) -> MoveExecutionResult:
	var result := MoveExecutor.execute(state, move)
	if not result.ok:
		return result
	var delta := _score_delta(move)
	for generated in result.batch.generated:
		if generated.kind == Move.MoveKind.FLIP_TABLEAU:
			delta += 5
	history.append({"state": state.clone(), "delta": delta})
	result.new_state.score = maxi(0, state.score + delta)
	state = result.new_state
	return result

func undo() -> bool:
	if history.is_empty():
		return false
	var entry: Dictionary = history.pop_back()
	var restored: GameState = entry.state
	# Cocos undoes the score delta, adds a move, then charges two points.
	# Recycling is not refunded in the master undo implementation.
	var refund := int(entry.delta) if int(entry.delta) >= 0 else int(entry.delta)
	if int(entry.delta) in [-20, -100]:
		refund = 0
	restored.score = maxi(0, state.score - refund - 2)
	restored.move_count = state.move_count + 1
	state = restored
	used_undo = true
	return true

func _score_delta(move: Move) -> int:
	match move.kind:
		Move.MoveKind.TABLEAU_TO_FOUNDATION, Move.MoveKind.WASTE_TO_FOUNDATION:
			return 10
		Move.MoveKind.WASTE_TO_TABLEAU:
			return 5
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			return -15
		Move.MoveKind.FLIP_TABLEAU:
			return 5
		Move.MoveKind.RECYCLE_STOCK:
			return -100 if state.draw_count == 3 else -20
	return 0

func hint_options() -> Array[Move]:
	return HintEngine.hint_options(state, 3)

func auto_plan() -> AutoCompletePlanResult:
	return AutoCompletePlanner.plan(state)

func can_auto() -> bool:
	for pile in state.tableau:
		for card in pile.cards_snapshot():
			if not card.face_up:
				return false
	return state.game_status != GameState.GameStatus.WON
