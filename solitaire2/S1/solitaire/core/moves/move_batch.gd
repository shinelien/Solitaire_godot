class_name MoveBatch
extends RefCounted

## 一次用户操作 = 一个请求的 Move 加上 MoveExecutor 为同一次操作执行的
## 所有显式生成 Move（按执行顺序）。系统自动生成的 tableau 翻牌是真实的
## FLIP_TABLEAU Move，并登记在 `generated` 中（绝非隐藏修改）。
## 无论批内携带多少生成移动，move_count 只递增一次。
## UNDO 批是结果/历史的边界身份；重开/新牌局行为见 WP-07。

## 用户请求的原始移动（批的首要移动）。
var requested: Move = null
## 实际执行顺序：请求移动在前，随后是各生成移动。
var applied: Array[Move] = []
## 执行器自动追加的移动（是 `applied` 的子集，绝不会排在最前）。
var generated: Array[Move] = []


## 由请求移动与全部生成移动构造一个批次。
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


## 构造撤销边界批次（requested 与 applied 均为 [Move.undo()]）。
static func undo_batch() -> MoveBatch:
	return from_moves(Move.undo())


## 返回用户请求的原始移动（可能为 null）。
func primary_move() -> Move:
	return requested


## 是否为撤销边界批次。
func is_undo_batch() -> bool:
	return requested != null and requested.is_undo()


## 是否只包含单一移动（无生成移动）。
func is_single() -> bool:
	return applied.size() == 1


## 是否带有执行器自动生成的移动。
func has_generated() -> bool:
	return not generated.is_empty()


## 返回其中全部自动翻牌移动（FLIP_TABLEAU）。
func generated_flips() -> Array[Move]:
	var flips: Array[Move] = []
	for move in generated:
		if move.kind == Move.MoveKind.FLIP_TABLEAU:
			flips.append(move)
	return flips


## 返回 applied 中每个移动的种类（调试/断言用）。
func applied_move_kinds() -> Array:
	var kinds: Array = []
	for move in applied:
		kinds.append(move.kind)
	return kinds


## 调试用字符串：撤销批次显示 undo，否则列出各移动种类。
func _to_string() -> String:
	if is_undo_batch():
		return "MoveBatch(undo)"
	var names: PackedStringArray = PackedStringArray()
	for move in applied:
		names.append(Move.kind_name(move.kind))
	return "MoveBatch([" + ", ".join(names) + "])"
