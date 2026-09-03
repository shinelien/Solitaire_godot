class_name BoardGeometry
extends RefCounted

## Layout geometry helpers for the pure-2D board (WP-08). Pure functions with
## no Node/Control dependency so the responsive-compression behaviour can be
## unit tested directly. None of this changes game rules: it only decides how
## close stacked cards are drawn within a bounded vertical area (legacy feel:
## 148x220 card, 66px between two open cards, 30px otherwise; compressed only
## when a very tall tableau column would overflow the available band).

const CARD_W := 148
const CARD_H := 220
const FAN_OPEN := 66
const FAN_COVERED := 30
const MIN_GAP := 4


static func gap_between(below_face_up: bool, above_face_up: bool) -> int:
	if below_face_up and above_face_up:
		return FAN_OPEN
	return FAN_COVERED


## Vertical gaps for a tableau column given the per-card face flags
## (index 0 = bottom). If the full fan (CARD_H + gaps) fits in
## available_height the legacy gaps are kept untouched; otherwise every gap is
## scaled by the same factor so the whole column fits. `valid` is false only
## when the area is too short for a single card.
static func tableau_offsets(face_flags: Array, available_height: int) -> Dictionary:
	var depth := face_flags.size()
	if available_height < CARD_H:
		return {"valid": false, "offsets": [], "used": 0, "compressed": false}
	if depth <= 1:
		return {"valid": true, "offsets": [], "used": CARD_H, "compressed": false}
	var gaps: Array[int] = []
	for i in range(0, depth - 1):
		gaps.append(gap_between(bool(face_flags[i]), bool(face_flags[i + 1])))
	var fan := 0
	for g in gaps:
		fan += g
	var used := CARD_H + fan
	if used <= available_height:
		return {"valid": true, "offsets": gaps, "used": used, "compressed": false}
	var headroom := available_height - CARD_H
	if headroom < MIN_GAP:
		return {"valid": false, "offsets": [], "used": 0, "compressed": false}
	var scale := float(headroom) / float(fan)
	var out: Array[int] = []
	for g in gaps:
		out.append(maxi(MIN_GAP, int(floor(g * scale))))
	used = CARD_H
	for g in out:
		used += g
	return {"valid": true, "offsets": out, "used": used, "compressed": true}


## Cumulative top positions from a base top y and the gap offsets.
static func positions(top: int, offsets: Array) -> Array:
	var out: Array = []
	var y := top
	out.append(y)
	for g in offsets:
		y += int(g)
		out.append(y)
	return out


## Waste fan shows the up-to-`fan_size` most recently drawn cards, newest on
## the left (adjacent to the stock, mirroring the legacy draw fan). Returns
## x offsets for the fan cards relative to the waste slot origin, oldest
## rightmost.
static func waste_fan_offsets(count: int, max_fan: int) -> Array:
	var out: Array = []
	var visible := mini(count, max_fan)
	for i in visible:
		out.append((visible - 1 - i) * 36)
	return out
