class_name MoveCommand
extends RefCounted

## A user-command transaction. Executed atomically by MoveExecutor through
## GameController; one undo snapshot covers the whole transaction.

var label: String = ""
var moves: Array[Move] = []

func clone() -> MoveCommand:
	var c := MoveCommand.new()
	c.label = label
	for m in moves:
		c.moves.push_back(m.clone())
	return c

func _to_string() -> String:
	return "%s[%d moves]" % [label, moves.size()]
