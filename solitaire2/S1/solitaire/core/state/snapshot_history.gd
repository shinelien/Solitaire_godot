class_name SnapshotHistory
extends RefCounted

## Deep pre-action snapshot stack used for undo. One snapshot per successful
## user batch is pushed (failed moves are never recorded). Stored snapshots are
## deep clones, and peek()/pop() hand back fresh clones, so no caller can
## mutate history contents. Capacity default 128 (documented, >=100): when
## full, the oldest snapshot is deterministically evicted (FIFO). Undo is
## exposed through MoveExecutor.execute_undo (typed result), which pops this
## stack; an empty history is a typed failure there.

const DEFAULT_CAPACITY := 128

var _capacity: int = DEFAULT_CAPACITY
var _snapshots: Array[GameState] = []


func _init(p_capacity: int = 0) -> void:
	if p_capacity > 0:
		_capacity = p_capacity


func capacity() -> int:
	return _capacity


func size() -> int:
	return _snapshots.size()


func is_empty() -> bool:
	return _snapshots.is_empty()


func can_undo() -> bool:
	return not _snapshots.is_empty()


## Record the pre-action state. The clone is taken here so the caller's state
## is never referenced afterwards. Null input is rejected. When full the
## oldest entry is evicted first (deterministic FIFO).
func push(state: GameState) -> bool:
	if state == null:
		return false
	if _snapshots.size() >= _capacity:
		_snapshots.pop_front()
	_snapshots.append(state.clone())
	return true


## Clone of the most recent snapshot without consuming it. Null when empty.
func peek() -> GameState:
	if _snapshots.is_empty():
		return null
	return _snapshots[_snapshots.size() - 1].clone()


## Consume and return a fresh clone of the most recent snapshot. Null + the
## caller should check can_undo() first; MoveExecutor turns an empty pop into
## a typed nothing_to_undo failure.
func pop() -> GameState:
	if _snapshots.is_empty():
		return null
	var stored: GameState = _snapshots.pop_back()
	return stored.clone()


func clear() -> void:
	_snapshots.clear()
