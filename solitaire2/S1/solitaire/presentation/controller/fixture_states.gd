class_name FixtureStates
extends RefCounted

## Explicit, documented non-production test fixtures (WP-08). These builders
## only assemble full 52-card permutations through the public Core data types
## (GameState/CardPile/CardData) so the interactive acceptance matrix can be
## driven on controlled boards. They are not reachable from any player UI and
## are never called by the gameplay loop; the Director exposes them solely
## through the documented `mcp_debug_load_fixture` seam used by MCP runtime
## verification.

## suit 0..3, rank 1..13 -> id.
static func fid(suit: int, rank: int) -> int:
	return suit * 13 + rank - 1


## A+1..K ids of one suit (rank ascending).
static func suit_ids_rank1to13(suit: int) -> Array:
	var out: Array = []
	for rank in range(1, 14):
		out.append(fid(suit, rank))
	return out


## Every id in 0..51 not already in `used`.
static func _remaining(used: Array) -> Array:
	var seen := PackedByteArray()
	seen.resize(52)
	for id in used:
		seen[id] = 1
	var out: Array = []
	for id in 52:
		if seen[id] == 0:
			out.append(id)
	return out


static func _add_run(pile: CardPile, ids: Array, face_up: bool) -> void:
	for id in ids:
		pile.add_top(CardData.new(id, face_up))


static func _fill_remainder(state: GameState, used: Array) -> void:
	var rest := _remaining(used)
	for id in rest:
		state.tableau_pile(6).add_top(CardData.new(id, false))


static func _fill_three_foundations(state: GameState, used: Array) -> void:
	for suit in 3:
		var pile := state.foundation_pile(suit)
		for rank in range(1, 14):
			pile.add_top(CardData.new(fid(suit, rank), true))
			used.append(fid(suit, rank))


## Controlled near-win: three full foundations (suits 0..2) and the whole
## fourth suit as a face-up tableau run K..A in column 0. AutoComplete must
## reach WON through one legal TABLEAU_TO_FOUNDATION move per card.
static func near_win() -> GameState:
	var state := GameState.new()
	var used: Array = []
	_fill_three_foundations(state, used)
	_add_run(state.tableau_pile(0), _desc(fid(3, 13), 13), true)
	return state


## Near-win variant whose playable Ace sits on the waste (double-click
## target); column 0 then holds only K..2 of the same suit.
static func near_win_waste_ace() -> GameState:
	var state := GameState.new()
	var used: Array = []
	_fill_three_foundations(state, used)
	state.waste.add_top(CardData.new(fid(3, 1), true))
	used.append(fid(3, 1))
	_add_run(state.tableau_pile(0), _desc(fid(3, 13), 12), true)
	return state


## Controlled mixed-operation board: empty column (king-drop test), waste Ace
## (double-click), a 12-card suit run in column 1 (drag to foundation), and a
## tableau pair enabling a legal single-card run move. Runtime interaction
## matrix only; never used for auto-complete.
static func ops_state() -> GameState:
	var state := GameState.new()
	var used: Array = []
	state.waste.add_top(CardData.new(fid(3, 1), true))
	used.append(fid(3, 1))
	var run := _desc(fid(3, 13), 12)
	_add_run(state.tableau_pile(1), run, true)
	used.append_array(run)
	state.tableau_pile(4).add_top(CardData.new(fid(1, 6), true))
	used.append(fid(1, 6))
	state.tableau_pile(5).add_top(CardData.new(fid(0, 5), true))
	used.append(fid(0, 5))
	_fill_remainder(state, used)
	return state


## Bottom..top descending ids starting from `top_id`, count cards.
static func _desc(top_id: int, count: int) -> Array:
	var out: Array = []
	var id := top_id
	for i in count:
		out.append(id)
		id -= 1
	return out
