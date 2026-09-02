class_name CardData
extends RefCounted

## Pure-data solitaire card (WP-05 CORE-001). No Node/Control/Texture deps.
## identity contract: id in 0..51; rank = id % 13 + 1; suit = id / 13
## (0=spades,1=hearts,2=clubs,3=diamonds).

const MIN_ID := 0
const MAX_ID := 51
const SUIT_COUNT := 4
const RANK_COUNT := 13

var id: int = 0
var rank: int = 1
var suit: int = 0
var face_up: bool = false


func _init(p_id: int = 0, p_face_up: bool = false) -> void:
	id = p_id
	rank = p_id % RANK_COUNT + 1
	suit = p_id / RANK_COUNT
	face_up = p_face_up


## Fresh instance with identical identity (deep-copy building block).
func clone() -> CardData:
	return CardData.new(id, face_up)


## id in [0,51] and rank/suit consistent with the identity contract.
func is_valid() -> bool:
	return id >= MIN_ID and id <= MAX_ID and rank == id % RANK_COUNT + 1 and suit == id / RANK_COUNT


func equals(other: CardData) -> bool:
	if other == null:
		return false
	return id == other.id and face_up == other.face_up


func _to_string() -> String:
	var color := "D"
	if suit == 0:
		color = "S"
	elif suit == 1:
		color = "H"
	elif suit == 2:
		color = "C"
	return "%s%d%s" % [color, rank, "U" if face_up else "D"]
