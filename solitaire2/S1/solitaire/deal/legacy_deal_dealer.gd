class_name LegacyDealer
extends RefCounted

## Deterministic dealer (pure data, no Node deps): turns a legacy bureau record
## into a dealt GameState snapshot (28-tableau + 24-stock, empty waste) or a
## player-ready snapshot that additionally auto-draws draw_count cards (1 or 3)
## from the stock top into the waste. Never randomizes; every failure path
## returns an explicit LegacyDealResult.

const TABLEAU_COLUMNS := 7


## Dealt snapshot from a named pool + index (reads the exported pool file).
static func deal_dealt(pool: String, index: int, draw_count: int) -> LegacyDealResult:
	var record_result := LegacyDealRepository.get_record(pool, index)
	if not record_result.get("ok", false):
		return _result_from_record_error(record_result)
	return deal_dealt_from_record(
		record_result.record,
		pool,
		index,
		draw_count,
		LegacyDealRepository.source_path(pool)
	)


## Player-ready snapshot from a named pool + index.
static func deal_ready(pool: String, index: int, draw_count: int) -> LegacyDealResult:
	var record_result := LegacyDealRepository.get_record(pool, index)
	if not record_result.get("ok", false):
		return _result_from_record_error(record_result)
	return deal_ready_from_record(
		record_result.record,
		pool,
		index,
		draw_count,
		LegacyDealRepository.source_path(pool)
	)


## Dealt snapshot from an explicit 52-char record (source for provenance).
static func deal_dealt_from_record(
	record: String,
	pool: String,
	index: int,
	draw_count: int,
	source: String
) -> LegacyDealResult:
	var decode := LegacyDealDecoder.decode_record(record)
	if not decode.get("ok", false):
		return LegacyDealResult.failure(
			LegacyDealResult.CODE_INVALID_RECORD,
			"record %s#%d rejected: %s" % [pool, index, decode.get("error_message", "")]
		)
	if draw_count != GameState.DRAW1 and draw_count != GameState.DRAW3:
		return LegacyDealResult.failure(
			LegacyDealResult.CODE_INVALID_DRAW_COUNT,
			"draw_count %d not in {1,3}" % draw_count
		)
	var state := _build_dealt_state(decode.ids, pool, index, draw_count, source)
	return LegacyDealResult.success(state)


## Player-ready snapshot from an explicit 52-char record.
static func deal_ready_from_record(
	record: String,
	pool: String,
	index: int,
	draw_count: int,
	source: String
) -> LegacyDealResult:
	var dealt_result := deal_dealt_from_record(record, pool, index, draw_count, source)
	if not dealt_result.ok:
		return dealt_result
	var ready := dealt_result.state.clone()
	_apply_initial_draw(ready)
	return LegacyDealResult.success(ready)


static func _build_dealt_state(
	ids: Array[int],
	pool: String,
	index: int,
	draw_count: int,
	source: String
) -> GameState:
	var state := GameState.new()
	state.deal_pool = pool
	state.deal_index = index
	state.deal_source = source
	state.draw_count = draw_count

	var cursor := 0
	for col in TABLEAU_COLUMNS:
		var column_size := col + 1
		var column_ids: Array[int] = []
		var flags: Array = []
		for row in column_size:
			column_ids.append(ids[cursor])
			flags.append(row == column_size - 1)
			cursor += 1
		state.tableau[col] = CardPile.from_ids(column_ids, false, flags)

	var stock_ids: Array[int] = []
	for i in range(24):
		stock_ids.append(ids[cursor + i])
	state.stock = CardPile.from_ids(stock_ids, false)
	return state


## Pop up to draw_count cards off the stock top (array end) into the waste;
## drawn cards are face-up. Stock tops are consumed in pop order, so the last
## drawn card ends up as the waste top (playable end).
static func _apply_initial_draw(state: GameState) -> void:
	var n := mini(state.draw_count, state.stock.size())
	for i in n:
		var card := state.stock.pop_top()
		if card == null:
			break
		card.face_up = true
		state.waste.add_top(card)


static func _result_from_record_error(record_result: Dictionary) -> LegacyDealResult:
	var code: String = record_result.get("error_code", LegacyDealResult.CODE_IO_ERROR)
	return LegacyDealResult.failure(code, record_result.get("error_message", ""))
