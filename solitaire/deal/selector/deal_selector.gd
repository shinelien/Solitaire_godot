class_name DealSelector
extends RefCounted

## Neutral deal selector. No DDA, no difficulty, no assisted swapping
## (ADR-005). Uniform random pick over the repository's deals.

func select_index(total: int, rng: RandomNumberGenerator) -> int:
	if total <= 0:
		return -1
	return rng.randi_range(0, total - 1)
