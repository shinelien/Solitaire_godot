class_name HintEngine
extends RefCounted

## Deterministic, non-mutating classic-Klondike hint provider (pure service,
## no Node deps, WP-07). Never mutates GameState/history and never returns a
## move that RulesEngine would reject: every candidate is validated through
## RulesEngine.validate before it may be returned.
##
## Total ordering (documented, tested):
##   TIER 0  TIER_EXPOSE            a legal tableau move whose execution exposes
##                                  a face-down card (auto-flip) — the only tier
##                                  that reveals new cards
##   TIER 1  TIER_TO_FOUNDATION     a legal tableau/waste top -> foundation move
##                                  (source scan: tableau columns 0..6 then waste;
##                                  destination: foundation slots 0..3 ascending)
##   TIER 2  TIER_WASTE_TO_TABLEAU  waste top -> tableau column (columns ascending)
##   TIER 3  TIER_TABLEAU_RUN       other legal non-exposing tableau run moves
##   TIER 4  TIER_STOCK             DRAW_STOCK, or RECYCLE_STOCK when legal
##   TIER 5  TIER_FOUNDATION_ROLLBACK  foundation top -> tableau (last-resort fallback)
##   TIER 6  TIER_TRIVIAL           trivial King/full-run -> empty-column shifts
##                                  that reveal nothing (only selected when no
##                                  move in tiers 0..5 exists)
## Among candidates of the same tier the first in the canonical enumeration
## order wins. `all_legal_moves` returns every legal candidate grouped by tier
## (ascending), deterministic for an identical state.

## Suit -> color group; mirrors RulesEngine so expose checks stay in Core.
static func suit_is_red(suit: int) -> bool:
	return suit == 1 or suit == 3


static func tier_name(tier: int) -> String:
	match tier:
		HintResult.TIER_EXPOSE:
			return "expose"
		HintResult.TIER_TO_FOUNDATION:
			return "to_foundation"
		HintResult.TIER_WASTE_TO_TABLEAU:
			return "waste_to_tableau"
		HintResult.TIER_TABLEAU_RUN:
			return "tableau_run"
		HintResult.TIER_STOCK:
			return "stock"
		HintResult.TIER_FOUNDATION_ROLLBACK:
			return "foundation_rollback"
		HintResult.TIER_TRIVIAL:
			return "trivial"
	return "none"


static func hint(state: GameState) -> HintResult:
	if state == null:
		return HintResult.failure(
			HintResult.CODE_INVALID_STATE,
			"cannot hint a null state"
		)
	if state.game_status == GameState.GameStatus.WON:
		return HintResult.failure(
			HintResult.CODE_ALREADY_WON,
			"game is already won; no further moves are legal"
		)
	var ranked := _ranked(state)
	if ranked.is_empty():
		return HintResult.failure(
			HintResult.CODE_NO_LEGAL_MOVE,
			"no legal hintable move exists in this state"
		)
	var best: Dictionary = ranked[0]
	return HintResult.success(best.move, int(best.tier), tier_name(int(best.tier)))


## Every legal hintable move, deterministic: grouped by tier ascending, within
## a tier in canonical enumeration order. Read-only.
static func all_legal_moves(state: GameState) -> Array[Move]:
	if state == null or state.game_status == GameState.GameStatus.WON:
		return []
	var ranked := _ranked(state)
	var out: Array[Move] = []
	for entry in ranked:
		out.append(entry.move)
	return out


# ----- ranking -----

static func _ranked(state: GameState) -> Array:
	var candidates := _enumerate(state)
	if candidates.is_empty():
		return []
	var ranked: Array = []
	for tier in range(HintResult.TIER_EXPOSE, HintResult.TIER_TRIVIAL + 1):
		for entry in candidates:
			if int(entry.tier) == tier:
				ranked.append(entry)
	return ranked


## Canonical deterministic enumeration. Every entry is a Dictionary
## {"tier": int, "move": Move} and every move already passed RulesEngine.
static func _enumerate(state: GameState) -> Array:
	var out: Array = []
	for src_col in GameState.TABLEAU_COUNT:
		var pile := state.tableau_pile(src_col)
		if pile == null or pile.is_empty():
			continue
		_append_run_moves(out, state, src_col)
		for slot in GameState.FOUNDATION_COUNT:
			var tf := Move.tableau_to_foundation(src_col, slot)
			if RulesEngine.validate(state, tf).ok:
				out.append({"tier": _classify(state, tf), "move": tf})
	if not state.waste.is_empty():
		for to_col in GameState.TABLEAU_COUNT:
			var wt := Move.waste_to_tableau(to_col)
			if RulesEngine.validate(state, wt).ok:
				out.append({"tier": _classify(state, wt), "move": wt})
		for slot in GameState.FOUNDATION_COUNT:
			var wf := Move.waste_to_foundation(slot)
			if RulesEngine.validate(state, wf).ok:
				out.append({"tier": _classify(state, wf), "move": wf})
	var draw := Move.draw_stock()
	if RulesEngine.validate(state, draw).ok:
		out.append({"tier": _classify(state, draw), "move": draw})
	var recycle := Move.recycle_stock()
	if RulesEngine.validate(state, recycle).ok:
		out.append({"tier": _classify(state, recycle), "move": recycle})
	for slot in GameState.FOUNDATION_COUNT:
		var slot_pile := state.foundation_pile(slot)
		if slot_pile == null or slot_pile.is_empty():
			continue
		for to_col in GameState.TABLEAU_COUNT:
			var ft := Move.foundation_to_tableau(slot, to_col)
			if RulesEngine.validate(state, ft).ok:
				out.append({"tier": _classify(state, ft), "move": ft})
	return out


## All legal tableau run moves (T2T) for one source column: for every target
## column the (at most one) run count whose bottom card fits is emitted, so
## every valid movable suffix of the face-up run is covered.
static func _append_run_moves(out: Array, state: GameState, src_col: int) -> void:
	var pile := state.tableau_pile(src_col)
	var max_run := _face_up_valid_run_length(pile)
	if max_run <= 0:
		return
	for dst_col in GameState.TABLEAU_COUNT:
		if dst_col == src_col:
			continue
		for count in range(1, max_run + 1):
			var move := Move.tableau_to_tableau(src_col, dst_col, count)
			if RulesEngine.validate(state, move).ok:
				out.append({"tier": _classify(state, move), "move": move})


## Longest top face-up suffix that is a valid descending alternating run.
## Walking from the pile top downward, every next (lower) card must be exactly
## one rank higher and of the opposite color.
static func _face_up_valid_run_length(pile: CardPile) -> int:
	if pile == null or pile.is_empty():
		return 0
	if not pile.top().face_up:
		return 0
	var length := 1
	var prev := pile.top()
	var i := pile.size() - 2
	while i >= 0:
		var card := pile.card_at(i)
		if card == null or not card.face_up:
			break
		if card.rank != prev.rank + 1:
			break
		if suit_is_red(card.suit) == suit_is_red(prev.suit):
			break
		length += 1
		prev = card
		i -= 1
	return length


static func _classify(state: GameState, move: Move) -> int:
	match move.kind:
		Move.MoveKind.TABLEAU_TO_TABLEAU:
			var source := state.tableau_pile(move.source_index)
			var exposed_face_down := (
				move.count < source.size()
				and source.card_at(source.size() - move.count - 1) != null
				and not source.card_at(source.size() - move.count - 1).face_up
			)
			if exposed_face_down:
				return HintResult.TIER_EXPOSE
			if state.tableau_pile(move.target_index).is_empty() and move.count == source.size():
				return HintResult.TIER_TRIVIAL
			return HintResult.TIER_TABLEAU_RUN
		Move.MoveKind.TABLEAU_TO_FOUNDATION:
			var t_source := state.tableau_pile(move.source_index)
			if (
				t_source.size() > 1
				and t_source.card_at(t_source.size() - 2) != null
				and not t_source.card_at(t_source.size() - 2).face_up
			):
				return HintResult.TIER_EXPOSE
			return HintResult.TIER_TO_FOUNDATION
		Move.MoveKind.WASTE_TO_FOUNDATION:
			return HintResult.TIER_TO_FOUNDATION
		Move.MoveKind.WASTE_TO_TABLEAU:
			return HintResult.TIER_WASTE_TO_TABLEAU
		Move.MoveKind.DRAW_STOCK, Move.MoveKind.RECYCLE_STOCK:
			return HintResult.TIER_STOCK
		Move.MoveKind.FOUNDATION_TO_TABLEAU:
			return HintResult.TIER_FOUNDATION_ROLLBACK
	return HintResult.TIER_NONE
