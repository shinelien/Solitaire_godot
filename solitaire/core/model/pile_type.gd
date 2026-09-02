class_name PileType
extends RefCounted

## Logical pile kinds. Pure identifiers, no Node, no UI.

const STOCK := 0
const WASTE := 1
const TABLEAU := 2
const FOUNDATION := 3

const TABLEAU_COUNT := 7
const FOUNDATION_COUNT := 4

static func label(t: int) -> String:
	match t:
		STOCK:
			return "Stock"
		WASTE:
			return "Waste"
		TABLEAU:
			return "Tableau"
		FOUNDATION:
			return "Foundation"
	return "Unknown"
