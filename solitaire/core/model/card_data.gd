class_name CardData
extends RefCounted

## Immutable-by-convention card identity plus its board placement state.
## Pure logic: never inherits Node, never touches UI.
##
## Legacy mapping (ADR-004):
##   id      = stored byte - ASCII '0', in [0, 51]
##   suit    = id / 13          (0..3)
##   rank    = id % 13 + 1      (1..13, 1 = Ace)
##   is_red  = suit % 2 == 1
## Legacy card id = colorType * 13 + (number - 1) (CardSprite::setCardId),
## which is exactly suit * 13 + rank - 1.

const RANKS_PER_SUIT := 13
const DECK_SIZE := 52

const SUIT_SYMBOLS := ["\u2663", "\u2666", "\u2665", "\u2660"]
const RANK_LABELS := ["A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"]

var id: int = 0
var rank: int = 1
var suit: int = 0
var face_up: bool = false

static func from_id(card_id: int) -> CardData:
	var c := CardData.new()
	c.id = card_id
	c.rank = card_id % RANKS_PER_SUIT + 1
	c.suit = card_id / RANKS_PER_SUIT
	return c

func is_red() -> bool:
	return suit % 2 == 1

func color_key() -> int:
	return suit % 2

func copy() -> CardData:
	var c := CardData.new()
	c.id = id
	c.rank = rank
	c.suit = suit
	c.face_up = face_up
	return c

func same_as(other: CardData) -> bool:
	if other == null:
		return false
	return id == other.id and rank == other.rank \
		and suit == other.suit and face_up == other.face_up

func _to_string() -> String:
	return "%s%s" % [RANK_LABELS[rank - 1], SUIT_SYMBOLS[suit]]
