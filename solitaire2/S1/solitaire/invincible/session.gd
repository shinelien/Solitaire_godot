class_name InvincibleSession
extends RefCounted

## InvincibleWarrior product session; the existing pure rules remain reusable.
var state: GameState
var original_ids: Array[int] = []
var history: Array[Dictionary] = []
var used_undo := false

var replay_record := ""
var level: Dictionary = {}
var elapsed := 0.0
var revealed_targets: Dictionary = {}

func start(draw_count: int, replay := false, record := "", random_deal := false) -> void:
	if replay:
		record = replay_record
	elif record.is_empty():
		if random_deal:
			var ids: Array[int] = []
			for id in 52:
				ids.append(id)
			ids.shuffle()
			for id in ids:
				record += char(48 + id)
		else:
			var path := "res://assets/invincible/data/bureau%d.d" % draw_count
			var bytes := FileAccess.get_file_as_bytes(path)
			var count := bytes.size() / 53
			var index := randi_range(0, count - 1)
			record = bytes.slice(index * 53, index * 53 + 52).get_string_from_ascii()
	replay_record = record
	var result := LegacyDealer.deal_ready_from_record(record, "invincible", -1, draw_count, "origin/InvincibleWarrior")
	assert(result.ok, result.error_message)
	state = result.state
	history.clear()
	used_undo = false
	elapsed = 0
	revealed_targets.clear()

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
	# InvincibleWarrior refunds +15 for foundation-to-tableau, although
	# the forward move costs 10; preserve the source behaviour.
	var refund := int(entry.delta)
	if int(entry.delta) == -10:
		refund = -15
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
			return -10
		Move.MoveKind.FLIP_TABLEAU:
			return 5
		Move.MoveKind.RECYCLE_STOCK:
			return 0
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

func objective() -> Dictionary:
	if level.is_empty():
		return {"won": state.game_status == GameState.GameStatus.WON, "lost": false}
	var type: String = level.type
	var won := state.game_status == GameState.GameStatus.WON
	if type == "LimitScore":
		won = state.score >= int(level.score)
	elif type == "CollectPoker":
		won = true
		for key: String in level.poker:
			var parts := key.split("_")
			var id := int(parts[1]) * 13 + int(parts[0]) - 1
			var collected := false
			for pile in state.foundation:
				for card in pile.cards_snapshot():
					if card.id == id:
						collected = true
			won = won and collected
	elif type == "TargetPoker":
		for col in 7:
			for i in state.tableau[col].size():
				var card := state.tableau[col].card_at(i)
				if card.face_up:
					revealed_targets[card.id] = true
		var decoded := LegacyDealDecoder.decode_record(replay_record)
		var cursor := 0
		won = true
		for col in 7:
			for row in col + 1:
				var key := "%d_%d" % [col, row]
				if key in level.poker:
					won = won and revealed_targets.has(decoded.ids[cursor])
				cursor += 1
	var time_limit := int(float(level.get("times", 0)) * 2.5) / 10 * 10
	var lost := not won and (level.has("moves") and state.move_count >= int(level.moves) or type == "LimitTime" and elapsed >= time_limit)
	return {"won": won, "lost": lost}
