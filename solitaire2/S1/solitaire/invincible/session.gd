class_name InvincibleSession
extends RefCounted

## InvincibleWarrior product session; the existing pure rules remain reusable.
var state: GameState
var original_ids: Array[int] = []
var history: Array[Dictionary] = []
var used_undo := false
var magic_used := 0

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
	magic_used = 0
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

func magic_plan() -> Dictionary:
	if state == null or state.game_status == GameState.GameStatus.WON:
		return {}
	# SpriteManager::isMagic first searches covered tableau cards, then
	# stock/waste, then exposed tableau tops that can go to a foundation.
	var covered: Array[CardData] = []
	var exposed: Array[CardData] = []
	for pile in state.tableau:
		for card in pile.cards_snapshot():
			if not card.face_up:
				covered.append(card)
		if not pile.is_empty() and pile.top().face_up:
			exposed.append(pile.top())
	var waiting: Array[CardData] = state.waste.cards_snapshot()
	waiting.append_array(state.stock.cards_snapshot())
	var candidates := _magic_candidates(covered)
	if candidates.is_empty():
		candidates = _magic_candidates(waiting)
	if candidates.is_empty():
		exposed.append_array(covered)
		exposed.append_array(waiting)
		for card in exposed:
			if not _magic_foundation(card).is_empty():
				candidates.append(card)
	if candidates.is_empty():
		return {}
	var selected: CardData = candidates[randi_range(0, candidates.size() - 1)]
	var plan := _magic_destination(selected)
	plan.card_id = selected.id
	return plan

func _magic_candidates(cards: Array[CardData]) -> Array[CardData]:
	var candidates: Array[CardData] = []
	var minimum: CardData = null
	for card in cards:
		if card.rank == 1 or not _magic_tableau(card).is_empty():
			candidates.append(card)
		# Original shuffle(vec) adds only the lowest next foundation card.
		if card.rank > 1 and not _magic_foundation(card).is_empty():
			if minimum == null or card.rank < minimum.rank:
				minimum = card
	if minimum != null and minimum not in candidates:
		candidates.append(minimum)
	return candidates

func _magic_foundation(card: CardData) -> Dictionary:
	for index in 4:
		var top := state.foundation[index].top()
		if top != null and top.suit == card.suit and top.rank + 1 == card.rank:
			return {"kind": "foundation", "index": index}
	if card.rank == 1:
		for index in 4:
			if state.foundation[index].is_empty():
				return {"kind": "foundation", "index": index}
	return {}

func _magic_tableau(card: CardData) -> Dictionary:
	for index in 7:
		var top := state.tableau[index].top()
		if top != null and top.face_up and top.rank == card.rank + 1 and top.suit % 2 != card.suit % 2:
			return {"kind": "tableau", "index": index}
	if card.rank == 13:
		for index in 7:
			if state.tableau[index].is_empty():
				return {"kind": "tableau", "index": index}
	return {}

func _magic_destination(card: CardData) -> Dictionary:
	var foundation := _magic_foundation(card)
	return foundation if not foundation.is_empty() else _magic_tableau(card)

func apply_magic(plan: Dictionary) -> bool:
	if state == null or plan.is_empty() or state.game_status == GameState.GameStatus.WON:
		return false
	var id := int(plan.get("card_id", -1))
	var working := state.clone()
	var source: CardPile
	var source_kind := ""
	var source_index := -1
	for pile in [working.stock, working.waste]:
		if id in pile.ids():
			source = pile
			source_kind = "stock" if pile == working.stock else "waste"
	for index in 7:
		if id in working.tableau[index].ids():
			source = working.tableau[index]
			source_kind = "tableau"
			source_index = index
	if source == null:
		return false
	var remaining := CardPile.new()
	var selected: CardData
	for card in source.cards_snapshot():
		if card.id == id:
			selected = card
		else:
			remaining.add_top(card)
	if source_kind == "tableau" and selected.face_up and selected.id != source.top().id:
		return false
	var destination := _magic_destination(selected)
	if destination.is_empty() or destination.kind != plan.get("kind") or destination.index != plan.get("index"):
		return false
	var flip_score := 0
	if source_kind == "tableau":
		working.tableau[source_index] = remaining
		if not remaining.is_empty() and not remaining.top().face_up:
			remaining.top().face_up = true
			revealed_targets[remaining.top().id] = true
			flip_score = 5
	elif source_kind == "stock":
		working.stock = remaining
	else:
		working.waste = remaining
	selected.face_up = true
	if destination.kind == "foundation":
		working.foundation[destination.index].add_top(selected)
	else:
		working.tableau[destination.index].add_top(selected)
	working.score += (10 if destination.kind == "foundation" else 5) + flip_score
	working.move_count += 1
	WinEvaluator.update_status(working)
	state = working
	revealed_targets[id] = true
	# Cocos clears move history after magic; inventory cannot be restored by undo.
	history.clear()
	magic_used += 1
	return true

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
