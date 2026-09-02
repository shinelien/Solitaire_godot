extends BaseTest

## Source-boundary guarantees:
##   - core/** never inherits Node/Control (pure logic objects);
##   - presentation/** never mutates pile/card data directly;
##   - the runtime decoder/controller never self-generate golden expectations.

const CORE_PATHS := [
	"res://core/model/card_data.gd",
	"res://core/model/location.gd",
	"res://core/model/pile_type.gd",
	"res://core/state/game_state.gd",
	"res://core/state/game_status.gd",
	"res://core/rules/klondike_rules.gd",
	"res://core/moves/move.gd",
	"res://core/moves/move_command.gd",
	"res://core/moves/move_result.gd",
	"res://core/moves/move_executor.gd",
]

const PRESENTATION_PATHS := [
	"res://presentation/cards/card_view.gd",
	"res://presentation/board/board_view.gd",
	"res://presentation/input/input_handler.gd",
]

const NODE_EXTENDS := ["extends Node", "extends Node2D", "extends Node3D", \
	"extends CanvasItem", "extends Control", "extends Sprite2D", "extends NodePath"]

const MUTATION_TOKENS := ["push_back", "push_front", "pop_back", "pop_front", \
	"erase(", ".resize(", "face_up =", "face_up=", "assign("]

## Mutation-style access to the authoritative pile fields. Reading piles
## (state.stock[i], state.col(c), .is_empty()) is allowed for rendering;
## writing through them is not.
const PILE_MUTATION := ["state.stock.push", "state.stock.pop", "state.stock.resize", \
	"state.stock.clear", "state.stock.erase", "state.stock.assign", \
	"state.waste.push", "state.waste.pop", "state.waste.resize", \
	"state.waste.clear", "state.waste.erase", "state.waste.assign", \
	"state.tableau", "state.foundations"]

func _read(path: String) -> String:
	var f := FileAccess.open(path, FileAccess.READ)
	if f == null:
		return ""
	return f.get_as_text()

func test_core_classes_do_not_inherit_node() -> void:
	for path in CORE_PATHS:
		var text := _read(path)
		check(text != "", "%s readable" % path)
		for token in NODE_EXTENDS:
			check_false(text.contains(token), "%s must not contain %s" % [path, token])

func test_core_classes_are_pure_objects() -> void:
	var instantiable := [
		CardData.new(), Location.new(), GameState.new(), Move.new(),
		MoveCommand.new(), MoveResult.new(), MoveExecutor.new(),
		KlondikeRules.new(), LegacyDealDecoder.new(), LegacyDealBuilder.new(),
		LegacyDealRepository.new(), DealSelector.new(), GameController.new(),
	]
	for obj in instantiable:
		check_true(obj is RefCounted, "%s is RefCounted" % obj.get_class())
		check_false(obj is Node, "%s is NOT a Node" % obj.get_class())

func test_presentation_never_mutates_pile_data() -> void:
	for path in PRESENTATION_PATHS:
		var text := _read(path)
		check(text != "", "%s readable" % path)
		for token in MUTATION_TOKENS:
			check_false(text.contains(token), "%s must not contain %s" % [path, token])
		for token in PILE_MUTATION:
			check_false(text.contains(token), "%s must not contain %s" % [path, token])

func test_presentation_never_assigns_controller_state() -> void:
	var re := RegEx.new()
	re.compile("controller\\.state\\s*=\\s*[^=]")
	for path in PRESENTATION_PATHS:
		var text := _read(path)
		check(re.search(text) == null, "%s never assigns controller.state" % path)

func test_golden_not_generated_at_runtime() -> void:
	# The golden fixtures live as a static JSON file; no runtime code path
	# may write or regenerate them during a test run.
	check_true(FileAccess.file_exists("res://data/legacy/golden/golden_draw1.json"), "golden file exists")
	for path in CORE_PATHS:
		var text := _read(path)
		check_false(text.contains("golden_draw1.json"), "core %s never references golden file" % path)
	for path in PRESENTATION_PATHS:
		var text := _read(path)
		check_false(text.contains("golden_draw1.json"), "presentation %s never references golden file" % path)
	var ctrl_text := _read("res://application/game_controller.gd")
	check_false(ctrl_text.contains("golden_draw1.json"), "controller never writes golden file")
