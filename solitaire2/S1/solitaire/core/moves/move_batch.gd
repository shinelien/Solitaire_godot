class_name MoveBatch
extends RefCounted

## One user action = a requested Move plus every explicit generated Move that
## the MoveExecutor performed as part of that same action (in execution order).
## A generated automatic tableau flip is a real FLIP_TABLEAU Move listed in
## `generated` (never a hidden mutation). The batch increments move_count once
## regardless of how many generated moves it carries. An UNDO batch is the
## boundary identity for result/history; replay/session behavior is WP-07.

var requested: Move = null
## Requested move first, then generated moves, in execution order.
var applied: Array[Move] = []
## Moves the executor added automatically (subset of `applied`, never first).
var generated: Array[Move] = []


## Build a batch from a requested move plus its generated moves.
static func from_moves(requested_move: Move, generated_moves: Array[Move] = []) -> MoveBatch:
	var batch := MoveBatch.new()
	batch.requested = requested_move
	if requested_move != null:
		batch.applied.append(requested_move)
	for generated_move in generated_moves:
		if generated_move == null:
			continue
		batch.applied.append(generated_move)
		batch.generated.append(generated_move)
	return batch


## Build the UNDO boundary batch (requested + applied = [Move.undo()]).
static func undo_batch() -> MoveBatch:
	return from_moves(Move.undo())


func primary_move() -> Move:
	return requested


func is_undo_batch() -> bool:
	return requested != null and requested.is_undo()


func is_single() -> bool:
	return applied.size() == 1


func has_generated() -> bool:
	return not generated.is_empty()


func generated_flips() -> Array[Move]:
	var flips: Array[Move] = []
	for move in generated:
		if move.kind == Move.MoveKind.FLIP_TABLEAU:
			flips.append(move)
	return flips


func applied_move_kinds() -> Array:
	var kinds: Array = []
	for move in applied:
		kinds.append(move.kind)
	return kinds


func _to_string() -> String:
	if is_undo_batch():
		return "MoveBatch(undo)"
	var names: PackedStringArray = PackedStringArray()
	for move in applied:
		names.append(Move.kind_name(move.kind))
	return "MoveBatch([" + ", ".join(names) + "])"
