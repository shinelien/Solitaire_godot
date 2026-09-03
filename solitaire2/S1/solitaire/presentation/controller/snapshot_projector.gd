class_name SnapshotProjector
extends RefCounted

## Presentation-only read projection of a GameState into plain data (WP-08).
## BoardView renders exclusively from this projection so the view tree is a
## dumb snapshot and can never mutate GameState/CardData/piles. The projection
## returns primitive dictionaries only (no CardData/CardPile references), so
## later view mutations cannot leak back into the session state. The source
## GameState is never modified (the projector is read-only by construction).

static func status_name(status: int) -> String:
	match status:
		GameState.GameStatus.WON:
			return "WON"
	return "IN_PROGRESS"


static func cards(pile: CardPile) -> Array:
	var out: Array = []
	if pile == null:
		return out
	for card in pile.cards_snapshot():
		out.append({"id": card.id, "face_up": card.face_up})
	return out


static func project(state: GameState) -> Dictionary:
	var tableau: Array = []
	for col in GameState.TABLEAU_COUNT:
		tableau.append(cards(state.tableau_pile(col)))
	var foundation: Array = []
	for slot in GameState.FOUNDATION_COUNT:
		foundation.append(cards(state.foundation_pile(slot)))
	return {
		"draw_count": state.draw_count,
		"score": state.score,
		"move_count": state.move_count,
		"stock_passes": state.stock_passes,
		"status": status_name(state.game_status),
		"deal_pool": state.deal_pool,
		"deal_index": state.deal_index,
		"stock": cards(state.stock),
		"waste": cards(state.waste),
		"tableau": tableau,
		"foundation": foundation,
	}
