class_name WinEvaluator
extends RefCounted

## 严格胜利判定（纯函数，无 Node 依赖）。foundation[4] 是四个动态槽位
## （与固定参考 checkACardPos 一致——槽位不绑定花色），因此胜利与
## 哪个花色位于哪个槽无关。WON 当且仅当：四个槽各自恰好持有某完整
## 花色 13 张唯一实体牌（A..K 升序且全部翻开），且四个槽花色互不相同
## （4 花色 + 4 个完整序列意味着集体恰好是 {0,1,2,3}）。
## 因此整组换槽的完整花色可判胜；重复花色、混色、不足、乱序、
## 盖牌或身份损坏的基础堆均不能判胜。
## 设计上不存在 LOST/猜测状态：一局要么胜利，要么继续。

const FOUNDATION_FULL := 13
const FOUNDATION_COUNT := 4
const RANK_COUNT := 13
const SUIT_COUNT := 4


## 胜利判定入口：四座基础堆各自为完整且互异花色的 A..K 全收牌时返回 true。
static func is_won(state: GameState) -> bool:
	if state == null:
		return false
	if state.foundation.size() != FOUNDATION_COUNT:
		return false
	var seen_suits := {}
	for slot in FOUNDATION_COUNT:
		var suit := _complete_run_suit(state.foundation[slot])
		if suit < 0 or seen_suits.has(suit):
			return false
		seen_suits[suit] = true
	return seen_suits.size() == SUIT_COUNT


## 槽内必须是某花色的完整 13 张实体（位置 p 的牌 id 必须等于 suit*13+p，
## 即按 A..K 升序），且每张都翻开。成功时返回该槽花色，否则返回 -1。
## 由于逐位绑定精确 id/点数/花色，重复花色的槽不可能被误判为另一花色，
## 不完整或损坏的序列也绝不会被接受。
static func _complete_run_suit(pile: CardPile) -> int:
	if pile == null or pile.size() != FOUNDATION_FULL:
		return -1
	var suit := -1
	for p in RANK_COUNT:
		var card := pile.card_at(p)
		if card == null:
			return -1
		if not card.face_up:
			return -1
		if p == 0:
			if card.rank != 1 or card.id % RANK_COUNT != 0:
				return -1
			suit = card.suit
			if card.id != suit * RANK_COUNT:
				return -1
			continue
		if card.suit != suit:
			return -1
		if card.id != suit * RANK_COUNT + p or card.rank != p + 1:
			return -1
	return suit


## 当严格胜利不变量成立时，把 state.game_status 置为 WON。
## 由 MoveExecutor 在成功批处理后调用；此函数不修改任何牌面数据。
static func update_status(state: GameState) -> void:
	if state == null:
		return
	if is_won(state):
		state.game_status = GameState.GameStatus.WON
