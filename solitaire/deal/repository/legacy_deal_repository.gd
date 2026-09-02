class_name LegacyDealRepository
extends RefCounted

## Loads the byte-imported legacy libraries and serves raw records.
## Records are validated on demand by LegacyDealDecoder; the repository never
## fabricates or falls back to a random deal.

var _records_1: PackedStringArray = PackedStringArray()
var _records_3: PackedStringArray = PackedStringArray()

func _init() -> void:
	_records_1 = _read_records(GameConfig.DEAL_PATH_1)
	_records_3 = _read_records(GameConfig.DEAL_PATH_3)

func _read_records(path: String) -> PackedStringArray:
	var out := PackedStringArray()
	var f := FileAccess.open(path, FileAccess.READ)
	if f == null:
		push_error("LegacyDealRepository: cannot open %s" % path)
		return out
	var text := f.get_as_text()
	f.close()
	for line in text.split("\n", false):
		if line.length() == 0:
			continue
		out.push_back(line)
	return out

func count_for(draw_mode: int) -> int:
	if draw_mode == GameConfig.DRAW3:
		return _records_3.size()
	return _records_1.size()

## Raw 52-char record at index, or "" if out of range.
func get_record(draw_mode: int, index: int) -> String:
	var records := _records_for(draw_mode)
	if index < 0 or index >= records.size():
		return ""
	return records[index]

func _records_for(draw_mode: int) -> PackedStringArray:
	if draw_mode == GameConfig.DRAW3:
		return _records_3
	return _records_1

func all_records(draw_mode: int) -> PackedStringArray:
	return _records_for(draw_mode)
