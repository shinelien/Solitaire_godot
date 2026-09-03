## Card faces/backs come from fixed legacy sheets via the face mapper only.
class_name LegacyFaceMapper
extends RefCounted

## Presentation-only mapping from a pure CardData identity (rank 1..13,
## suit 0..3, id = suit*13+rank-1) to the region names the fixed legacy
## product uses inside the exported atlas sheets (WP-08). The mapping mirrors
## the reference implementation semantics (AtlasManager::getKey for the
## default face skin 0): the card face is composed from a shared base region
## ("card_fronts"), a rank region ("card_0" + rank, e.g. card_01/card_013) and
## a suit/colour region ("card_0_" + suit letter A..D, with an 11/12/13 suffix
## for J/Q/K). Core never sees this mapping and these strings are never baked.
##
## This file is deliberately free of texture/image loading so it can be unit
## tested without any ResourceLoader access.

const ATLAS_FACES_IMAGE := "res://assets/legacy/images/car_new_0_6.png"
const ATLAS_FACES_FILE := "res://assets/legacy/images/car_new_0_6.atlas"
const ATLAS_BACK_IMAGE := "res://assets/legacy/images/car_new_0_1.png"
const ATLAS_BACK_FILE := "res://assets/legacy/images/car_new_0_1.atlas"

const REGION_BASE := "card_fronts"
const REGION_BACK := "card_bg_5"
const SUIT_LETTERS := ["A", "B", "C", "D"]


## Region of the shared face base (identical across every card).
static func base_region() -> String:
	return REGION_BASE


## Region of the small rank/court glyph used in the face composition.
static func rank_region(rank: int) -> String:
	return "card_0%d" % rank


## Region of the large suit/colour emblem. Mirrors AtlasManager::getKey
## case 6 for the default skin (picType 0): ranks 1..10 share the plain
## suit-letter region; courts 11..13 carry the numeric suffix.
static func suit_region(rank: int, suit: int) -> String:
	var letter: String = SUIT_LETTERS[suit]
	if rank > 10:
		return "card_0_%s%d" % [letter, rank]
	return "card_0_%s" % letter


## Classic colour of a suit group (red = hearts/diamonds), matching the
## product's black/red split (colorType % 2) used to tint the rank glyph.
static func is_red_suit(suit: int) -> bool:
	return suit == 1 or suit == 3


## Region name used as the card back.
static func back_region() -> String:
	return REGION_BACK


## Face composition descriptor for one card.
static func face_parts(rank: int, suit: int) -> Dictionary:
	return {
		"base": base_region(),
		"rank": rank_region(rank),
		"suit": suit_region(rank, suit),
		"red": is_red_suit(suit),
	}
