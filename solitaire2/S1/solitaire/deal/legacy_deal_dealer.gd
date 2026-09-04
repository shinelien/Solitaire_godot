class_name LegacyDealer
extends RefCounted

## 确定性发牌器（纯数据，无 Node 依赖）：把一条旧版 bureau 记录转换为
## “已发牌”GameState 快照（28 张 tableau + 24 张 stock，waste 为空），
## 或额外把 draw_count（1 或 3）张牌从 stock 顶自动翻入 waste 的
## “玩家就绪”快照。绝不随机化；每条失败路径都返回显式 LegacyDealResult。

const TABLEAU_COLUMNS := 7


## 从命名牌池 + 序号读取记录并生成“已发牌”快照。
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


## 从命名牌池 + 序号生成“玩家就绪”快照（发牌后自动翻牌）。
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


## 从显式 52 字符记录生成“已发牌”快照（`source` 用于记录出处）。
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


## 从显式 52 字符记录生成“玩家就绪”快照。
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


## 核心建态逻辑：按列主序 1..7 摆放 tableau
## （每列最后一张翻开），其余 24 张作为盖牌存入 stock。
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


## 从 stock 顶（数组末尾）弹出至多 draw_count 张翻开牌放入 waste。
## 按弹出顺序消费，因此最后翻出的牌成为 waste 顶牌（可操作端）。
static func _apply_initial_draw(state: GameState) -> void:
	var n := mini(state.draw_count, state.stock.size())
	for i in n:
		var card := state.stock.pop_top()
		if card == null:
			break
		card.face_up = true
		state.waste.add_top(card)


## 把牌池读取错误字典转换为类型化 LegacyDealResult 失败。
static func _result_from_record_error(record_result: Dictionary) -> LegacyDealResult:
	var code: String = record_result.get("error_code", LegacyDealResult.CODE_IO_ERROR)
	return LegacyDealResult.failure(code, record_result.get("error_message", ""))
