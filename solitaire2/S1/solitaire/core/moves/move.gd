class_name Move
extends RefCounted

## Explicit, typed description of one solitaire action (pure data, WP-06).
## A Move never mutates state by itself: RulesEngine validates it and
## MoveExecutor applies it on a clone. Generated automatic flips are explicit
## FLIP_TABLEAU moves (never a hidden mutation).
##
## Containers are addressed by location + index:
##   LOC_TABLEAU   index = tableau column 0..6 (bottom..top, last = top)
##   LOC_FOUNDATION index = foundation slot 0..3 (dynamic; a slot's suit is
##                   owned by its current content, never by its index)
##   LOC_WASTE    index ignored (waste is a single pile; only its top is playable)
##   LOC_STOCK    index ignored
## `count` is the number of cards moved (>=1); DRAW_STOCK/RECYCLE_STOCK use
## count = 0 as a "dynamic" marker (the actual drawn amount comes from the
## state draw_count and the stock remainder).

enum MoveKind {
	TABLEAU_TO_TABLEAU,
	TABLEAU_TO_FOUNDATION,
	WASTE_TO_TABLEAU,
	WASTE_TO_FOUNDATION,
	FOUNDATION_TO_TABLEAU,
	DRAW_STOCK,
	RECYCLE_STOCK,
	FLIP_TABLEAU,
	## Boundary identities only (WP-07): undo is routed through MoveExecutor
	## execute_undo, replay/new deal through execute_boundary. None of them is a
	## RulesEngine-legality gameplay move and none mutates state by itself.
	UNDO,
	REPLAY,
	NEW_DEAL,
}

enum Location {
	LOC_TABLEAU = 0,
	LOC_FOUNDATION = 1,
	LOC_WASTE = 2,
	LOC_STOCK = 3,
}

const KIND_COUNT := 11
const TABLEAU_COUNT := 7
const FOUNDATION_COUNT := 4


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


var kind: MoveKind = MoveKind.TABLEAU_TO_TABLEAU
var source_location: int = -1
var source_index: int = -1
var target_location: int = -1
var target_index: int = -1
var count: int = 1


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


## Stable canonical identity (suits result/history/equality boundaries).
func key() -> String:
	return "%s:%s[%d]->%s[%d]x%d" % [
		kind_name(kind),
		location_name(source_location),
		source_index,
		location_name(target_location),
		target_index,
		count,
	]


func is_undo() -> bool:
	return kind == MoveKind.UNDO


## Session-boundary identities (REPLAY / NEW_DEAL), never gameplay moves.
func is_boundary() -> bool:
	return kind == MoveKind.UNDO or kind == MoveKind.REPLAY or kind == MoveKind.NEW_DEAL


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


func _to_string() -> String:
	return "Move(%s)" % description()


# ----- typed factories (source/target coordinates, documented counts) -----

static func tableau_to_tableau(from_col: int, to_col: int, run_count: int) -> Move:
	return Move.new(MoveKind.TABLEAU_TO_TABLEAU, Location.LOC_TABLEAU, from_col, Location.LOC_TABLEAU, to_col, run_count)


static func tableau_to_foundation(from_col: int, slot: int) -> Move:
	return Move.new(MoveKind.TABLEAU_TO_FOUNDATION, Location.LOC_TABLEAU, from_col, Location.LOC_FOUNDATION, slot, 1)


static func waste_to_tableau(to_col: int) -> Move:
	return Move.new(MoveKind.WASTE_TO_TABLEAU, Location.LOC_WASTE, -1, Location.LOC_TABLEAU, to_col, 1)


static func waste_to_foundation(slot: int) -> Move:
	return Move.new(MoveKind.WASTE_TO_FOUNDATION, Location.LOC_WASTE, -1, Location.LOC_FOUNDATION, slot, 1)


static func foundation_to_tableau(from_slot: int, to_col: int) -> Move:
	return Move.new(MoveKind.FOUNDATION_TO_TABLEAU, Location.LOC_FOUNDATION, from_slot, Location.LOC_TABLEAU, to_col, 1)


static func draw_stock() -> Move:
	return Move.new(MoveKind.DRAW_STOCK, Location.LOC_STOCK, -1, Location.LOC_WASTE, -1, 0)


static func recycle_stock() -> Move:
	return Move.new(MoveKind.RECYCLE_STOCK, Location.LOC_WASTE, -1, Location.LOC_STOCK, -1, 0)


static func flip_tableau(col: int) -> Move:
	return Move.new(MoveKind.FLIP_TABLEAU, Location.LOC_TABLEAU, col, Location.LOC_TABLEAU, -1, 1)


static func undo() -> Move:
	return Move.new(MoveKind.UNDO, -1, -1, -1, -1, 1)


static func replay() -> Move:
	return Move.new(MoveKind.REPLAY, -1, -1, -1, -1, 1)


static func new_deal() -> Move:
	return Move.new(MoveKind.NEW_DEAL, -1, -1, -1, -1, 1)
