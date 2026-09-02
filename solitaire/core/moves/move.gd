class_name Move
extends RefCounted

## One primitive game mutation. Pure logic object.
## Multi-step user actions are MoveCommand transactions composed of Moves
## (e.g. a tableau move plus its explicit FlipTableau).

enum MoveType { MOVE_CARD, FLIP_TABLEAU, DRAW, RECYCLE }

var type: int = MoveType.MOVE_CARD
var from_pile: Location = null
var from_index: int = -1
var count: int = 1
var to_pile: Location = null
var card_id: int = -1

static func flip_tableau(col: int) -> Move:
	var m := Move.new()
	m.type = MoveType.FLIP_TABLEAU
	m.from_pile = Location.tableau(col)
	return m

static func draw() -> Move:
	var m := Move.new()
	m.type = MoveType.DRAW
	return m

static func recycle() -> Move:
	var m := Move.new()
	m.type = MoveType.RECYCLE
	return m

func clone() -> Move:
	var m := Move.new()
	m.type = type
	m.from_index = from_index
	m.count = count
	m.card_id = card_id
	if from_pile != null:
		m.from_pile = from_pile.clone()
	if to_pile != null:
		m.to_pile = to_pile.clone()
	return m

func same_as(other: Move) -> bool:
	if other == null:
		return false
	if type != other.type or from_index != other.from_index \
			or count != other.count or card_id != other.card_id:
		return false
	if from_pile == null and other.from_pile != null:
		return false
	if from_pile != null and not from_pile.same_as(other.from_pile):
		return false
	if to_pile == null and other.to_pile != null:
		return false
	if to_pile != null and not to_pile.same_as(other.to_pile):
		return false
	return true

func _to_string() -> String:
	match type:
		MoveType.MOVE_CARD:
			return "MoveCard %s[%d]x%d -> %s" % [from_pile, from_index, count, to_pile]
		MoveType.FLIP_TABLEAU:
			return "Flip %s" % from_pile
		MoveType.DRAW:
			return "Draw"
		MoveType.RECYCLE:
			return "Recycle"
	return "Move?"
