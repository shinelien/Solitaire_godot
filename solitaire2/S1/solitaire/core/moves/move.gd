class_name Move
extends RefCounted

## 一次接龙操作的显式、类型化描述（纯数据，WP-06）。
## Move 本身绝不修改状态：由 RulesEngine 校验，MoveExecutor 在克隆上执行。
## 自动生成的翻牌也是显式 FLIP_TABLEAU 移动（绝无隐藏修改）。
##
## 容器通过 location + index 寻址：
##   LOC_TABLEAU     index = tableau 列 0..6（底→顶，最后一个为顶）
##   LOC_FOUNDATION  index = foundation 槽 0..3（动态槽：槽位花色由槽内
##                   当前内容决定，不由槽位索引决定）
##   LOC_WASTE       index 忽略（waste 是单堆，只有顶牌可玩）
##   LOC_STOCK       index 忽略
## `count` 为移动牌数（>=1）；DRAW_STOCK/RECYCLE_STOCK 用 count = 0
## 作为“动态”标记（实际翻牌数取决于状态 draw_count 与 stock 余量）。

enum MoveKind {
	## tableau 列 → tableau 列（可携带多张连牌）。
	TABLEAU_TO_TABLEAU,
	## tableau 列顶牌 → foundation 槽。
	TABLEAU_TO_FOUNDATION,
	## waste 顶牌 → tableau 列。
	WASTE_TO_TABLEAU,
	## waste 顶牌 → foundation 槽。
	WASTE_TO_FOUNDATION,
	## foundation 槽顶牌 → tableau 列。
	FOUNDATION_TO_TABLEAU,
	## 从 stock 翻牌到 waste（实际张数由翻 1/翻 3 决定）。
	DRAW_STOCK,
	## stock 已空时把整堆 waste 倒回 stock（重翻一轮）。
	RECYCLE_STOCK,
	## 翻开 tableau 列暴露的盖牌顶。
	FLIP_TABLEAU,
	## 以下仅为会话边界身份（WP-07）：撤销走 MoveExecutor.execute_undo，
	## 重开/新牌局走 execute_boundary。它们都不是规则引擎校验的游戏操作，
	## 本身也不修改状态。
	UNDO,
	REPLAY,
	NEW_DEAL,
}

## 容器位置枚举：tableau 列 / foundation 槽 / waste 堆 / stock 堆。
enum Location {
	LOC_TABLEAU = 0,
	LOC_FOUNDATION = 1,
	LOC_WASTE = 2,
	LOC_STOCK = 3,
}

const KIND_COUNT := 11
const TABLEAU_COUNT := 7
const FOUNDATION_COUNT := 4


## 返回移动种类的稳定可读名称（用于 key、日志与调试）。
static func kind_name(kind: MoveKind) -> String:
	match kind:
		MoveKind.TABLEAU_TO_TABLEAU:
			return "TABLEAU_TO_TABLEAU"
		MoveKind.TABLEAU_TO_FOUNDATION:
			return "TABLEAU_TO_FOUNDATION"
		MoveKind.WASTE_TO_TABLEAU:
			return "WASTE_TO_TABLEAU"
		MoveKind.WASTE_TO_FOUNDATION:
			return "WASTE_TO_FOUNDATION"
		MoveKind.FOUNDATION_TO_TABLEAU:
			return "FOUNDATION_TO_TABLEAU"
		MoveKind.DRAW_STOCK:
			return "DRAW_STOCK"
		MoveKind.RECYCLE_STOCK:
			return "RECYCLE_STOCK"
		MoveKind.FLIP_TABLEAU:
			return "FLIP_TABLEAU"
		MoveKind.UNDO:
			return "UNDO"
		MoveKind.REPLAY:
			return "REPLAY"
		MoveKind.NEW_DEAL:
			return "NEW_DEAL"
	return "UNKNOWN(%d)" % kind


## 返回容器位置的稳定可读名称（用于 key、日志与调试）。
static func location_name(location: Location) -> String:
	match location:
		Location.LOC_TABLEAU:
			return "tableau"
		Location.LOC_FOUNDATION:
			return "foundation"
		Location.LOC_WASTE:
			return "waste"
		Location.LOC_STOCK:
			return "stock"
	return "unknown(%d)" % location


## 移动种类。
var kind: MoveKind = MoveKind.TABLEAU_TO_TABLEAU
## 源容器类型（Location 值）。
var source_location: int = -1
## 源容器内索引（waste/stock 忽略）。
var source_index: int = -1
## 目标容器类型（Location 值）。
var target_location: int = -1
## 目标容器内索引（waste/stock 忽略）。
var target_index: int = -1
## 移动的牌数；翻牌类操作使用 0 作为“动态”标记。
var count: int = 1


## 全字段构造函数：直接建立移动的规范坐标与数量。
func _init(
	p_kind: MoveKind = MoveKind.TABLEAU_TO_TABLEAU,
	p_source_location: int = -1,
	p_source_index: int = -1,
	p_target_location: int = -1,
	p_target_index: int = -1,
	p_count: int = 1
) -> void:
	kind = p_kind
	source_location = p_source_location
	source_index = p_source_index
	target_location = p_target_location
	target_index = p_target_index
	count = p_count


## 稳定的规范身份字符串（作为结果/历史/相等比较的边界）。
func key() -> String:
	return "%s:%s[%d]->%s[%d]x%d" % [
		kind_name(kind),
		location_name(source_location),
		source_index,
		location_name(target_location),
		target_index,
		count,
	]


## 是否为撤销边界身份。
func is_undo() -> bool:
	return kind == MoveKind.UNDO


## 是否为会话边界身份（UNDO/REPLAY/NEW_DEAL），这些都不是游戏移动。
func is_boundary() -> bool:
	return kind == MoveKind.UNDO or kind == MoveKind.REPLAY or kind == MoveKind.NEW_DEAL


## 人类可读的移动描述（面向日志、提示与调试）。
func description() -> String:
	match kind:
		MoveKind.TABLEAU_TO_TABLEAU:
			return "move %d tableau card(s) from column %d to column %d" % [count, source_index, target_index]
		MoveKind.TABLEAU_TO_FOUNDATION:
			return "move tableau column %d top to foundation slot %d" % [source_index, target_index]
		MoveKind.WASTE_TO_TABLEAU:
			return "move waste top to tableau column %d" % target_index
		MoveKind.WASTE_TO_FOUNDATION:
			return "move waste top to foundation slot %d" % target_index
		MoveKind.FOUNDATION_TO_TABLEAU:
			return "move foundation slot %d top to tableau column %d" % [source_index, target_index]
		MoveKind.DRAW_STOCK:
			return "draw %d card(s) from stock into waste" % count
		MoveKind.RECYCLE_STOCK:
			return "recycle waste into stock (stock_passes +1)"
		MoveKind.FLIP_TABLEAU:
			return "flip exposed face-down top of tableau column %d" % source_index
		MoveKind.UNDO:
			return "undo previous user action"
		MoveKind.REPLAY:
			return "replay current deal (session boundary, clears history)"
		MoveKind.NEW_DEAL:
			return "start next deterministic deal (session boundary, clears history)"
	return "unknown move"


## 调试用字符串：返回 "Move(<描述>)"。
func _to_string() -> String:
	return "Move(%s)" % description()


# ----- 类型化工厂（固定源/目标坐标与约定数量）-----

## 构造 tableau 列间连牌移动：from_col → to_col，携带 run_count 张。
static func tableau_to_tableau(from_col: int, to_col: int, run_count: int) -> Move:
	return Move.new(MoveKind.TABLEAU_TO_TABLEAU, Location.LOC_TABLEAU, from_col, Location.LOC_TABLEAU, to_col, run_count)


## 构造 tableau 列顶牌 → foundation 槽（单张）移动。
static func tableau_to_foundation(from_col: int, slot: int) -> Move:
	return Move.new(MoveKind.TABLEAU_TO_FOUNDATION, Location.LOC_TABLEAU, from_col, Location.LOC_FOUNDATION, slot, 1)


## 构造 waste 顶牌 → tableau 列（单张）移动。
static func waste_to_tableau(to_col: int) -> Move:
	return Move.new(MoveKind.WASTE_TO_TABLEAU, Location.LOC_WASTE, -1, Location.LOC_TABLEAU, to_col, 1)


## 构造 waste 顶牌 → foundation 槽（单张）移动。
static func waste_to_foundation(slot: int) -> Move:
	return Move.new(MoveKind.WASTE_TO_FOUNDATION, Location.LOC_WASTE, -1, Location.LOC_FOUNDATION, slot, 1)


## 构造 foundation 槽顶牌 → tableau 列（单张）移动。
static func foundation_to_tableau(from_slot: int, to_col: int) -> Move:
	return Move.new(MoveKind.FOUNDATION_TO_TABLEAU, Location.LOC_FOUNDATION, from_slot, Location.LOC_TABLEAU, to_col, 1)


## 构造翻牌移动（stock → waste，数量动态）。
static func draw_stock() -> Move:
	return Move.new(MoveKind.DRAW_STOCK, Location.LOC_STOCK, -1, Location.LOC_WASTE, -1, 0)


## 构造整堆重翻移动（waste → stock）。
static func recycle_stock() -> Move:
	return Move.new(MoveKind.RECYCLE_STOCK, Location.LOC_WASTE, -1, Location.LOC_STOCK, -1, 0)


## 构造翻开 tableau 盖牌顶移动。
static func flip_tableau(col: int) -> Move:
	return Move.new(MoveKind.FLIP_TABLEAU, Location.LOC_TABLEAU, col, Location.LOC_TABLEAU, -1, 1)


## 构造撤销边界身份。
static func undo() -> Move:
	return Move.new(MoveKind.UNDO, -1, -1, -1, -1, 1)


## 构造重开当前牌局边界身份。
static func replay() -> Move:
	return Move.new(MoveKind.REPLAY, -1, -1, -1, -1, 1)


## 构造下一确定性牌局边界身份。
static func new_deal() -> Move:
	return Move.new(MoveKind.NEW_DEAL, -1, -1, -1, -1, 1)
