class_name DeterministicDealSelector
extends RefCounted

## Minimal deterministic next-deal index selector (pure, no Node deps, WP-07).
## Chooses `(current_index + 1) mod pool_count` and never randomizes; it never
## reads player state, history, DDA or analytics. Unknown/singleton/invalid
## conditions return an explicit typed error instead of a fallback index.
## Preserves the caller's pool and draw mode (the caller re-deals from the
## returned index). No played-history sophistication lives here in S2.

const CODE_OK := "ok"
const CODE_INVALID_POOL_COUNT := "invalid_pool_count"
const CODE_SINGLETON_POOL := "singleton_pool"
const CODE_INVALID_CURRENT_INDEX := "invalid_current_index"


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
