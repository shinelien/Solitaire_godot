class_name SnapshotHistory
extends RefCounted

## 用于撤销的“动作前状态”深快照栈。每个成功的用户批次推入一个快照
## （失败移动从不记录）。存储的快照均为深克隆，peek()/pop() 也返回全新
## 克隆，因此调用方无法修改历史内容。容量默认 128（>=100 的约定值）：
## 满员时确定性淘汰最旧快照（FIFO）。撤销经由 MoveExecutor.execute_undo
## （类型化结果）弹出本栈；历史为空在那里表现为类型化失败。

const DEFAULT_CAPACITY := 128

## 快照栈最大容量（满员后淘汰最旧项）。
var _capacity: int = DEFAULT_CAPACITY
## 快照存储（栈顶为最近一次）。
var _snapshots: Array[GameState] = []


## 构造：可指定正数容量；不传或传 0 时使用默认容量 128。
func _init(p_capacity: int = 0) -> void:
	if p_capacity > 0:
		_capacity = p_capacity


## 当前容量上限。
func capacity() -> int:
	return _capacity


## 当前已记录的快照数量。
func size() -> int:
	return _snapshots.size()


## 历史是否为空。
func is_empty() -> bool:
	return _snapshots.is_empty()


## 是否可执行一次撤销（历史非空）。
func can_undo() -> bool:
	return not _snapshots.is_empty()


## 记录动作前状态。克隆在此处完成，因此之后不再持有调用方的状态引用。
## null 输入被拒绝。满员时先淘汰最旧记录（确定性 FIFO）。
func push(state: GameState) -> bool:
	if state == null:
		return false
	if _snapshots.size() >= _capacity:
		_snapshots.pop_front()
	_snapshots.append(state.clone())
	return true


## 返回最近快照的克隆（不消费该快照）；为空时返回 null。
func peek() -> GameState:
	if _snapshots.is_empty():
		return null
	return _snapshots[_snapshots.size() - 1].clone()


## 消费并返回最近快照的全新克隆。为空时返回 null；
## 调用方应先用 can_undo() 检查——MoveExecutor 会把空弹出转换为
## 类型化 nothing_to_undo 失败。
func pop() -> GameState:
	if _snapshots.is_empty():
		return null
	var stored: GameState = _snapshots.pop_back()
	return stored.clone()


## 清空全部历史。
func clear() -> void:
	_snapshots.clear()
