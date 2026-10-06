class_name LegacyScorePolicy
extends RefCounted

## 从固定参考实现（SpriteManager.cpp 的经典规则）提取的基础旧版计分：
## 仅在移动通过 RulesEngine 之后由 MoveExecutor 应用，因此计分绝不影响合法性。
## tableau 列间移动、翻牌与整堆重翻不计分；
## 撤销使用固定 -2，并对“还原后的动作前分数”施加 0 下限。

## 送入 foundation 的加分（10 分/张）。
const FOUNDATION_DELTA := 10
## waste 顶牌移到 tableau 的加分（5 分/张）。
const WASTE_TO_TABLEAU_DELTA := 5
## foundation 顶牌退回 tableau 的扣分（-10 分/张）。
const FOUNDATION_TO_TABLEAU_DELTA := -10
## 系统自动翻牌（暴露盖牌）的加分（5 分/张）。
const GENERATED_FLIP_DELTA := 5
## 下列操作不计分。
const TABLEAU_TO_TABLEAU_DELTA := 0
const DRAW_DELTA := 0
const RECYCLE_DELTA := 0
## 撤销固定罚分。
const UNDO_PENALTY := -2


## 单个“已通过合法性”移动种类的分数变化：
## tableau 列间移动、翻牌与整堆重翻为 0；撤销不属于规则移动（见 undo_score）。
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


## 整批已执行移动的总分变化（含请求动作与系统自动生成的翻牌）。
static func batch_delta(batch: MoveBatch) -> int:
	if batch == null:
		return 0
	var total := 0
	for move in batch.applied:
		total += move_delta(move)
	return total


## 旧版累加器更新：固定参考将增量加到当前分并截断到 0 下限
## （GameViewHD::updateScore），因此无论扣分多大，总分都不会为负。
static func apply_delta(score: int, delta: int) -> int:
	return maxi(0, score + delta)


## 将整批执行移动的分数变化应用到累计分（下限为 0）。
static func apply_batch(score: int, batch: MoveBatch) -> int:
	return apply_delta(score, batch_delta(batch))


## 撤销扣分：还原后的“动作前分数”减 2，下限为 0。
## 由执行器撤销路径调用，绝不进入 RulesEngine 内部。
static func undo_score(pre_action_score: int) -> int:
	return maxi(0, pre_action_score + UNDO_PENALTY)
