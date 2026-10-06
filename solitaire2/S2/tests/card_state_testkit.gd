@tool
class_name CardStateTestkit
extends RefCounted

## Test-only helpers for building focused GameStates and asserting structural
## properties (never used by production core/rules/moves code).

## id for a suit (0..3) and rank (1..13): id = suit*13 + rank - 1.
static func fid(suit: int, rank: int) -> int:
	return suit * 13 + rank - 1


static func make_pile(ids: Array, face_up: bool = false, face_flags: Array = []) -> CardPile:
	return CardPile.from_ids(ids, face_up, face_flags)


## A whole pile face-up (bottom..top), e.g. a movable face-up run.
static func up(ids: Array) -> CardPile:
	return CardPile.from_ids(ids, true, [])


## A whole pile face-down.
static func down(ids: Array) -> CardPile:
	return CardPile.from_ids(ids, false, [])


## Face-up run ascending ranks 1..`top` of one suit, ending face-up at top.
static func foundation_of(suit: int, top_rank: int) -> CardPile:
	var ids: Array = []
	for rank in range(1, top_rank + 1):
		ids.append(fid(suit, rank))
	return up(ids)


## Full 13-card A..K foundation of a suit.
static func full_foundation(suit: int) -> CardPile:
	return foundation_of(suit, 13)


static func make_state() -> GameState:
	return GameState.new()


static func is_full_permutation(ids: Array) -> bool:
	if ids.size() != 52:
		return false
	var seen := PackedByteArray()
	seen.resize(52)
	for id in ids:
		if id < 0 or id > 51:
			return false
		if seen[id] == 1:
			return false
		seen[id] = 1
	return true


## Cross-state isolation: two states must be distinct instances and share no
## CardPile or CardData instance anywhere (deep-copy contract). Every pile
## object in every container of A is compared against every pile object in
## every container of B, and every CardData reachable from A against every
## CardData reachable from B — regardless of which container/position holds
## them — so a reference shared across *differing* containers or positions is
## still detected (the previous per-container, per-position blind spot).
static func no_shared_state(a: GameState, b: GameState) -> bool:
	if a == null or b == null or a == b:
		return false
	var a_piles := _all_piles(a)
	var b_piles := _all_piles(b)
	for pa in a_piles:
		for pb in b_piles:
			if pa == pb:
				return false
	var a_cards := _all_cards(a_piles)
	var b_cards := _all_cards(b_piles)
	for card_a in a_cards:
		for card_b in b_cards:
			if card_a == card_b:
				return false
	return true


static func _all_piles(state: GameState) -> Array:
	var piles: Array = [state.stock, state.waste]
	piles.append_array(state.tableau)
	piles.append_array(state.foundation)
	return piles


static func _all_cards(piles: Array) -> Array:
	var cards: Array = []
	for pile in piles:
		if pile != null:
			cards.append_array(pile.cards_snapshot())
	return cards


## Total count including every container must stay 52 and unique across steps.
static func conservation_ok(state: GameState) -> bool:
	return state.total_card_count() == 52 and is_full_permutation(state.all_card_ids())
