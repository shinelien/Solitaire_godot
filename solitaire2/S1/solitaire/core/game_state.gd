class_name GameState
extends RefCounted

## Sole source of truth for a deal in progress (pure data, no Node deps).
## Owns stock / waste / tableau[7] / foundation[4] plus the counters and the
## deal identity. tableau/foundation use Array[CardPile] because nested typed
## arrays (Array[Array[int]]) are not supported in GDScript.

const DRAW1 := 1
const DRAW3 := 3
const TABLEAU_COUNT := 7
const FOUNDATION_COUNT := 4


enum GameStatus {
	IN_PROGRESS = 0,
	## WON arrives with the WP-06 rules engine: all four foundations are full.
	## There is intentionally no LOST state (classic Klondike is winnable until
	## the final move; a guessed LOST would be a solver decision).
	WON = 1,
}

var stock: CardPile = CardPile.new()
var waste: CardPile = CardPile.new()
var tableau: Array[CardPile] = []
var foundation: Array[CardPile] = []
var draw_count: int = DRAW1
var stock_passes: int = 0
var move_count: int = 0
var score: int = 0
var game_status: GameStatus = GameStatus.IN_PROGRESS

## Deal identity (WP-05): source pool file, zero-based index, fixed-object path.
var deal_pool: String = ""
var deal_index: int = -1
var deal_source: String = ""


func _init() -> void:
	tableau.clear()
	for i in TABLEAU_COUNT:
		tableau.append(CardPile.new())
	foundation.clear()
	for i in FOUNDATION_COUNT:
		foundation.append(CardPile.new())


func tableau_pile(col: int) -> CardPile:
	if col < 0 or col >= TABLEAU_COUNT:
		return null
	return tableau[col]


## Foundation container by slot index 0..3. Slots are dynamic: a slot is not
## pre-bound to a suit — the suit it currently builds is owned by its content.
func foundation_pile(slot: int) -> CardPile:
	if slot < 0 or slot >= FOUNDATION_COUNT:
		return null
	return foundation[slot]


## Stable deal key, e.g. "bureau1#0".
func deal_key() -> String:
	return "%s#%d" % [deal_pool, deal_index]


## True deep clone: every pile and every CardData instance is fresh; no shared
## mutable object exists between the source and the clone.
func clone() -> GameState:
	var out := GameState.new()
	out.stock = stock.clone()
	out.waste = waste.clone()
	for i in TABLEAU_COUNT:
		out.tableau[i] = tableau[i].clone()
	for i in FOUNDATION_COUNT:
		out.foundation[i] = foundation[i].clone()
	out.draw_count = draw_count
	out.stock_passes = stock_passes
	out.move_count = move_count
	out.score = score
	out.game_status = game_status
	out.deal_pool = deal_pool
	out.deal_index = deal_index
	out.deal_source = deal_source
	return out


## Total cards currently held by the state's containers.
func total_card_count() -> int:
	var n := stock.size() + waste.size()
	for pile in tableau:
		n += pile.size()
	for pile in foundation:
		n += pile.size()
	return n


## All card ids in the state, container order: stock(bottom..top),
## waste(bottom..top), each tableau column(bottom..top), each foundation.
func all_card_ids() -> Array[int]:
	var out: Array[int] = []
	out.append_array(stock.ids())
	out.append_array(waste.ids())
	for pile in tableau:
		out.append_array(pile.ids())
	for pile in foundation:
		out.append_array(pile.ids())
	return out


## Deterministic structural equality (ids, face_up and scalars).
func content_equals(other: GameState) -> bool:
	if other == null:
		return false
	if not stock.content_equals(other.stock) or not waste.content_equals(other.waste):
		return false
	for i in TABLEAU_COUNT:
		if not tableau[i].content_equals(other.tableau[i]):
			return false
	for i in FOUNDATION_COUNT:
		if not foundation[i].content_equals(other.foundation[i]):
			return false
	return (
		draw_count == other.draw_count
		and stock_passes == other.stock_passes
		and move_count == other.move_count
		and score == other.score
		and game_status == other.game_status
		and deal_pool == other.deal_pool
		and deal_index == other.deal_index
		and deal_source == other.deal_source
	)
