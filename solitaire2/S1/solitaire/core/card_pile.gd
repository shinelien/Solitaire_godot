class_name CardPile
extends RefCounted

## Ordered card stack (pure data). Convention (matches legacy + fixtures):
## index 0 = bottom of pile, last element = top of pile (the playable end).
## Dealt tableau columns and the stock store their first-dealt card at index
## 0 and their face-up/stock-top card at the end.

var _cards: Array[CardData] = []


func size() -> int:
	return _cards.size()


func is_empty() -> bool:
	return _cards.is_empty()


## Top of pile (last element). Null when empty.
func top() -> CardData:
	if _cards.is_empty():
		return null
	return _cards[_cards.size() - 1]


## Bottom of pile (first element). Null when empty.
func bottom() -> CardData:
	if _cards.is_empty():
		return null
	return _cards[0]


func card_at(index: int) -> CardData:
	if index < 0 or index >= _cards.size():
		return null
	return _cards[index]


func add_top(card: CardData) -> void:
	if card != null:
		_cards.append(card)


func add_bottom(card: CardData) -> void:
	if card != null:
		_cards.insert(0, card)


## Remove and return the top card. Null when empty.
func pop_top() -> CardData:
	if _cards.is_empty():
		return null
	return _cards.pop_back()


## Remove and return the top `count` cards as a run in pile order
## (bottom..top of the removed run, i.e. the first returned card is the card
## that must satisfy the destination's rank/color rule). Empty result when
## count <= 0. Count larger than the pile size removes the whole pile.
func pop_top_n(count: int) -> Array[CardData]:
	var taken: Array[CardData] = []
	if count <= 0:
		return taken
	var n := mini(count, _cards.size())
	for i in n:
		taken.push_front(_cards.pop_back())
	return taken


## Remove and return the bottom card. Null when empty.
func pop_bottom() -> CardData:
	if _cards.is_empty():
		return null
	return _cards.pop_front()


## Shallow copy of the container (CardData references are shared).
func cards_snapshot() -> Array[CardData]:
	var out: Array[CardData] = []
	for card in _cards:
		out.append(card)
	return out


## Ids in pile order (bottom..top).
func ids() -> Array[int]:
	var out: Array[int] = []
	for card in _cards:
		out.append(card.id)
	return out


## Deep copy: new pile with freshly cloned cards (no shared CardData).
func clone() -> CardPile:
	var out := CardPile.new()
	for card in _cards:
		out.add_top(card.clone())
	return out


## Build a pile bottom..top from ids; all cards get `face_up` (or per-card
## when `face_up_flags` is supplied and long enough, indexed by pile position).
static func from_ids(ids: Array, face_up: bool = false, face_up_flags: Array = []) -> CardPile:
	var pile := CardPile.new()
	for i in ids.size():
		var flag := face_up
		if face_up_flags.size() > i:
			flag = face_up_flags[i]
		pile.add_top(CardData.new(int(ids[i]), flag))
	return pile


## Deterministic content equality (identity + face_up per card, same order).
func content_equals(other: CardPile) -> bool:
	if other == null or other.size() != size():
		return false
	for i in _cards.size():
		if not _cards[i].equals(other.card_at(i)):
			return false
	return true
