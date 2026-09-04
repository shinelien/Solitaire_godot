class_name DeterministicDealSelector
extends RefCounted

## 极简确定性“下一牌局”序号选择器（纯逻辑，无 Node 依赖，WP-07）。
## 规则为 `(current_index + 1) mod pool_count`，绝不随机化；
## 不读取玩家状态、历史、DDA 或统计数据。
## 未知牌池/单张牌池/非法序号等情况返回显式类型化错误，绝不回退索引。
## 保留调用方的牌池与翻牌模式（由调用方用返回的序号重新发牌）。
## S2 中不做基于已玩历史的复杂选择。

const CODE_OK := "ok"
const CODE_INVALID_POOL_COUNT := "invalid_pool_count"
const CODE_SINGLETON_POOL := "singleton_pool"
const CODE_INVALID_CURRENT_INDEX := "invalid_current_index"


## 计算下一局序号。成功返回 {"ok": true, "next_index": int}；
## 失败返回带稳定错误码的字典。
static func next_index(current_index: int, pool_count: int) -> Dictionary:
	if pool_count < 0:
		return {
			"ok": false,
			"error_code": CODE_INVALID_POOL_COUNT,
			"error_message": "pool_count %d is negative" % pool_count,
		}
	if pool_count < 2:
		return {
			"ok": false,
			"error_code": CODE_SINGLETON_POOL,
			"error_message": "pool_count %d cannot offer a different deal (a deterministic next index requires >= 2 deals)" % pool_count,
		}
	if current_index < 0 or current_index >= pool_count:
		return {
			"ok": false,
			"error_code": CODE_INVALID_CURRENT_INDEX,
			"error_message": "current_index %d outside [0,%d)" % [current_index, pool_count],
		}
	return {"ok": true, "next_index": (current_index + 1) % pool_count}
