class_name Location
extends RefCounted

## Identifies a specific pile on the board. Pure logic object.

var type: int = PileType.STOCK
var index: int = 0

static func stock() -> Location:
	return Location.new().with(PileType.STOCK, 0)

static func waste() -> Location:
	return Location.new().with(PileType.WASTE, 0)

static func tableau(i: int) -> Location:
	return Location.new().with(PileType.TABLEAU, i)

static func foundation(i: int) -> Location:
	return Location.new().with(PileType.FOUNDATION, i)

func with(t: int, i: int) -> Location:
	type = t
	index = i
	return self

func clone() -> Location:
	return Location.new().with(type, index)

func same_as(other: Location) -> bool:
	if other == null:
		return false
	return type == other.type and index == other.index

func _to_string() -> String:
	return "%s[%d]" % [PileType.label(type), index]
