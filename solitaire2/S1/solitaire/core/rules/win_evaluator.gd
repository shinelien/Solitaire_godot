class_name WinEvaluator
extends RefCounted

## Strict win detection (pure, no Node deps). Foundation[4] are four dynamic
## slots (matching the fixed reference's checkACardPos, which never binds a
## slot index to a suit), so a win does NOT depend on which suit lives in which
## slot. WON iff every one of the four slots holds exactly the 13 unique
## physical identities of one complete suit run — A..K ascending, every card
## face-up — and the four slots' suits are all distinct (which, with exactly 4
## suits and 4 complete runs, means they are collectively {0,1,2,3}). Swapped
## complete suits therefore win; duplicate-suit, mixed, short, unordered,
## face-down or identity-malformed foundations do not. There is intentionally
## no LOST/guess state: a deal only wins or stays in progress.

const FOUNDATION_FULL := 13
const FOUNDATION_COUNT := 4
const RANK_COUNT := 13
const SUIT_COUNT := 4


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


## The slot must hold exactly the 13 physical identities suit*13..suit*13+12 in
## A..K order (card at position p must be identity suit*13+p), every card
## face-up. Returns the slot's suit on success, -1 otherwise. Because the check
## binds the exact id/rank/suit per position, a duplicate-suit slot is
## impossible to misread as a different suit and a partial/corrupt run is never
## accepted.
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


## Update a state's game_status to WON when the strict invariant holds.
## Called by MoveExecutor after a successful batch; never mutates the board.
static func update_status(state: GameState) -> void:
	if state == null:
		return
	if is_won(state):
		state.game_status = GameState.GameStatus.WON
