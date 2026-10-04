class_name SolitaireAdService
extends Node

## Replace this disabled provider with a platform adapter. Rewards must only
## follow reward_earned, never closed/unavailable. Reserve measured banner
## space through banner_height_changed; gameplay knows no vendor SDK.
signal reward_earned(placement: String, request_id: int)
signal request_finished(placement: String, request_id: int, result: String)
signal banner_height_changed(height: float)
signal availability_changed(placement: String, available: bool)
var _request_id := 0

func is_available(_placement: String) -> bool:
	return false

func request_rewarded(placement: String) -> int:
	_request_id += 1
	request_finished.emit(placement, _request_id, "unavailable")
	return _request_id

func request_interstitial(placement: String) -> void:
	request_finished.emit(placement, 0, "disabled")

func show_banner() -> void:
	banner_height_changed.emit(0.0)

func hide_banner() -> void:
	banner_height_changed.emit(0.0)
