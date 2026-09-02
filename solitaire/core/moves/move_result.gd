class_name MoveResult
extends RefCounted

var ok: bool = false
var error: String = ""
var move: Move = null

static func success(move: Move) -> MoveResult:
	var r := MoveResult.new()
	r.ok = true
	r.move = move
	return r

static func failure(error: String) -> MoveResult:
	var r := MoveResult.new()
	r.ok = false
	r.error = error
	return r
