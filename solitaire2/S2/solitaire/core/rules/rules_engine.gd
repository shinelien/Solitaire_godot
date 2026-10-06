class_name RulesEngine
extends RefCounted

## 经典 Klondike 移动合法性的唯一裁决权威（纯函数，无 Node 依赖，绝不改动状态）。
## 每项检查都返回带稳定错误码与消息的类型化 MoveValidationResult。
## 此处刻意不含计分：只有移动合法后，才由 MoveExecutor 应用计分。

## 判断花色是否属于红色组（1=红心, 3=方块；0=黑桃, 2=梅花 为黑色组）。
static func suit_is_red(suit: int) -> bool:
	return suit == 1 or suit == 3


## 判断两个花色是否颜色相反（用于 tableau 交替叠放校验）。
static func opposite_color(a_suit: int, b_suit: int) -> bool:
	return suit_is_red(a_suit) != suit_is_red(b_suit)


## 移动合法性总入口：先拒绝 null 状态、null 移动与已胜利牌局，
## 再按移动种类分发到对应的专项校验。
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
	## 先于棋盘合法性检查坐标/数量形状：手工构造或被外部改动的 Move，
	## 若 source_location/target_location/count 与种类矛盾，其规范 key/source/target
	## 就不可信，永远不应进入执行。
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


## 每种移动的规范形状契约（与 `Move` 上类型化工厂的保证一致）：
## 每个 MoveKind 必须携带其文档约定的 source_location/target_location 与数量；
## TABLEAU_TO_TABLEAU 的连牌数量由专门规则自行判定。
## UNDO 与未知种类在此作为“非游戏身份”被拒绝。
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


## 构造“源/目标位置与种类约定矛盾”的失败结果。
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


## 构造“移动数量与种类约定矛盾”的失败结果。
static func _shape_count_failure(move: Move, expected: String) -> MoveValidationResult:
	return _fail(
		MoveValidationResult.CODE_INVALID_COUNT,
		"%s requires count %s but has count %d"
		% [Move.kind_name(move.kind), expected, move.count]
	)


# ----- tableau -> tableau（连牌移动）-----

## 校验 tableau 列→列的连牌移动：源/目标列范围、禁止自移、数量合法性、
## 被移连牌须全翻开且降序交替、以及目标列收牌规则。
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


# ----- 送入 foundation -----

## 校验 tableau 顶牌送入 foundation：仅翻开顶牌可移，并符合动态槽收牌规则。
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


## 校验 waste 顶牌送入 foundation：waste 非空且顶牌翻开，再按动态槽规则放置。
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


# ----- 从 waste 移出 -----

## 校验 waste 顶牌移到 tableau 列：只有翻开的 waste 顶牌可移，按经典 tableau 规则收牌。
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


# ----- foundation -> tableau（仅顶牌一张）-----

## foundation 槽按槽位索引寻址；无论该槽当前由哪个花色持有，其顶牌
## 都可按经典 tableau 规则移到 tableau 列（动态槽语义，与固定参考
## checkACardPos 一致——它从不把槽位索引绑定到特定花色）。
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


# ----- stock / 整堆重翻 / 翻盖牌 -----

## 校验翻牌（DRAW_STOCK）：draw_count 必须为 1 或 3，且 stock 非空。
static func _validate_draw_stock(state: GameState) -> MoveValidationResult:
	if state.draw_count != GameState.DRAW1 and state.draw_count != GameState.DRAW3:
		return _fail(
			MoveValidationResult.CODE_INVALID_DRAW_COUNT,
			"state draw_count %d is not 1 or 3" % state.draw_count
		)
	if state.stock.is_empty():
		return _fail(MoveValidationResult.CODE_STOCK_EMPTY, "stock is empty; nothing to draw")
	return MoveValidationResult.success()


## 校验整堆重翻（RECYCLE_STOCK）：stock 必须已空且 waste 非空，
## 即把整副弃牌按规则倒回发牌堆。
static func _validate_recycle_stock(state: GameState) -> MoveValidationResult:
	if not state.stock.is_empty():
		return _fail(MoveValidationResult.CODE_STOCK_NOT_EMPTY, "recycle requires an empty stock (still %d cards)" % state.stock.size())
	if state.waste.is_empty():
		return _fail(MoveValidationResult.CODE_WASTE_EMPTY, "recycle requires a non-empty waste")
	return MoveValidationResult.success()


## 校验 tableau 翻开盖牌（FLIP_TABLEAU）：该列非空且顶牌确实为盖牌。
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


# ----- 共享的目标堆/连牌校验 -----

## 经典 tableau 收牌规则：空列只收 K；非空列要求来牌比翻开的顶牌
## 恰好小 1 点且颜色相反。
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


## 经典动态 foundation 收牌规则（与固定参考 SpriteManager::checkACardPos /
## CardSprite::checkAPos 一致）：空槽接受任意花色的翻开 A；非空槽只接受
## 与槽顶同花色、且点数恰好高 1 的翻开牌——槽正在收集的花色由槽内牌决定，
## 绝不预先绑定槽位索引。合法状态下 foundation 顶牌恒为翻开；盖牌顶说明
## 状态损坏，予以拒绝。
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


## 取牌堆顶部 count 张牌，作为保序的连牌（连牌内部为底→顶）。
static func _top_run(pile: CardPile, count: int) -> Array[CardData]:
	return pile.cards_snapshot().slice(pile.size() - count)


## 校验连牌中每张牌都是翻开状态。
static func _check_run_face_up(run: Array[CardData]) -> MoveValidationResult:
	for card in run:
		if not card.face_up:
			return _fail(MoveValidationResult.CODE_FACE_DOWN_CARD, "moved run contains a face-down card")
	return MoveValidationResult.success()


## 校验连牌排列：沿堆顶向下每两张牌必须点数降 1、颜色交替。
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


## 统一构造失败结果（稳定错误码 + 消息）。
static func _fail(code: String, message: String) -> MoveValidationResult:
	return MoveValidationResult.failure(code, message)
