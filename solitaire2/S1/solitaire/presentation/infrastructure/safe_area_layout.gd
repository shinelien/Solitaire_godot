class_name SafeAreaLayout
extends RefCounted

## Safe-area layout adapter (WP-08 correction 1). Pure geometry with no Node /
## DisplayServer dependency so identity and inset cases are unit-testable
## without a window. The presentation director reads
## DisplayServer.get_display_safe_area() / window geometry once and passes the
## numbers here; Core never references this helper and never sees platform
## logic. Background art stays full bleed behind the safe content rect.

## Map a device-space display safe area into viewport content-canvas
## coordinates.
##   content_size:       canvas coordinate size (e.g. Vector2(1080, 1920)).
##   window_rect_device: Rect2(window_position, window_size) in the same
##                       device coordinate basis as safe_area_device.
##   safe_area_device:   DisplayServer.get_display_safe_area() result.
## The mapping keeps width exactly filled (project stretch: canvas_items +
## aspect keep_width), so a single uniform scale is used. A safe area that
## equals the whole window (full-window display) maps to the identity content
## rect.
static func content_safe_rect(
	content_size: Vector2,
	window_rect_device: Rect2,
	safe_area_device: Rect2
) -> Rect2:
	if content_size.x <= 0.0 or window_rect_device.size.x <= 0.0:
		return Rect2(Vector2.ZERO, content_size)
	var scale := content_size.x / window_rect_device.size.x
	var local := Rect2(
		(safe_area_device.position - window_rect_device.position) * scale,
		safe_area_device.size * scale
	)
	return local.intersection(Rect2(Vector2.ZERO, content_size))


## Content insets (in canvas units) implied by a content-space safe rect.
## left/top >= 0; right/bottom >= 0 when the safe rect is inside the content.
static func margins(content_size: Vector2, content_safe: Rect2) -> Dictionary:
	return {
		"left": maxf(0.0, content_safe.position.x),
		"top": maxf(0.0, content_safe.position.y),
		"right": maxf(0.0, content_size.x - content_safe.end.x),
		"bottom": maxf(0.0, content_size.y - content_safe.end.y),
	}


## True when the safe rect does not cover the whole content window (an inset
## display, e.g. a notch cut-out) and content must be inset accordingly.
static func has_insets(content_size: Vector2, content_safe: Rect2) -> bool:
	var m := margins(content_size, content_safe)
	return m.left > 0.0 or m.top > 0.0 or m.right > 0.0 or m.bottom > 0.0
