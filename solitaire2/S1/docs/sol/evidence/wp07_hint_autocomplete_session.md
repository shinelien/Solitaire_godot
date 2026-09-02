# WP-07 证据包：CORE-006/007 Hint + AutoComplete + Application Session + Replay/New Deal 边界

- 合同：`docs/sol/施工合同.md`（S2 v1.0，§4/§5/§6 WP-07、§8 验收矩阵）；worker-order `docs/sol/worker-order-s2-classic-2d.md`；WP-07 开工令（负责人发布，含“WP-06 证据已确认”）
- 阶段：`S2-CLASSIC-2D-CORE-LOOP`；状态：**WP-07 施工完成、待证据确认**（WP-08 保持依赖锁定，未启动）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash）
- 环境：macOS Darwin arm64；Godot `4.6.2-stable (custom_build)`；Godot AI MCP 插件/服务器 `3.2.4`；时间 2026-09-03

## 1. 会话与工程路径（MCP）

- 同一编辑器会话 `s1@0a3b`（project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`，精确目标路径）；Godot `4.6.2-stable (custom_build)`；插件/服务器 `3.2.4`；play_state stopped（**全程未运行游戏**）；readiness ready；current_scene `res://mcp_verify.tscn`（基础设施夹具原样，SHA-256 `56a31e49…` 不变）。
- 流程：filesystem `scan` settled（global_class_count 71 → 78，新增 7 个 `class_name`：HintResult/HintEngine/AutoCompletePlanResult/AutoCompletePlanner/DeterministicDealSelector/GameSession/GameSessionResult）→ MCP `test_run` 终轮全量 **passed=162 / failed=0 / skipped=0**（15 suites）→ MCP editor log = 0 行；无 parse/运行时错误，编辑器进程内零诊断。
- 新增 `.gd.uid` 源伴随文件由 Godot 编辑器扫描自动生成并逐项在库（见 §2）。

## 2. 改动文件（精确清单，含 `.gd.uid`；sha256 = 当前字节）

全部改动仅在目标工程 `solitaire2/S1` 内；无 scene/project.godot/addon/fixture/mcp_verify 改动。

新增产品源文件（7 个，含对应 `.gd.uid` 7 个）：

```
solitaire/core/hint/hint_result.gd                  0bf5907d51f827d6765009370c5c9d2cdfb9551a984d4876fbb1739bc720e774  (typed HintResult + tier/code)
solitaire/core/hint/hint_engine.gd                  7965319c714cf01f1b7ced2d6149024ba8fe61ec6ea5193a52579c24a1f9782e  (deterministic non-mutating HintEngine)
solitaire/core/autocomplete/auto_complete_plan_result.gd  1f2aa7d94193e3ad1c6320a007340660bc426f8c61800dd819e01ef0c7528715  (typed AutoCompletePlanResult)
solitaire/core/autocomplete/auto_complete_planner.gd     251f3eb01ca4d4027bb529164fff610864299cdadf975447df7622921453666b  (terminating AutoCompletePlanner, MAX_STEPS=2048)
solitaire/deal/selector/deterministic_deal_selector.gd   4695fbc0070953965d766f3a9ef53b5feaf41279ac9203b0f7614f130c5b410c  (DeterministicDealSelector)
solitaire/application/game_session.gd                f0c25a5b2878a00aae777eb13e6e2325356172d21349200f87654c64ee425685  (RefCounted GameSession)
solitaire/application/game_session_result.gd         5f8382fa815cdd66533728eb6066f43af2fc484295248fed9bc96aabdfb26822  (typed GameSessionResult)
```

新增测试源文件（4 个，含对应 `.gd.uid` 4 个）：

```
tests/test_hint_engine.gd       170ddadeeed7a81d3b4e810d2b9509f9dd58ee4bc7bbcd55f3dceb57dc2aab5e  (suite hint_engine)
tests/test_auto_complete.gd     7cb177d29d0c102919c68eaf4e3f1cecf64be51689551a2525e5b43d73ceef33  (suite auto_complete)
tests/test_game_session.gd      6ceccfbaa39557a835ac353089c5866c9e833d951dabedcf48b41d7cb5eae060  (suite game_session)
tests/test_session_boundary.gd  199e2f10d540ef0bacfabc371de11c3a01fdbc2dfa86a3b6e6dd59c745b308cf  (suite boundary_moves)
```

修改的产品源文件（4 个；`.gd.uid` 源伴随文件未重写、逐项仍在库）：

```
solitaire/core/moves/move.gd                  0629f1a921b81e04f464c3094fc91f711cc57aa2ac9323325c1dc86e2161412e  (MoveKind +REPLAY/NEW_DEAL, KIND_COUNT 9→11, factories/key/kind_name/is_boundary)
solitaire/core/moves/move_execution_result.gd 03bc9f7ebf2beb123b60fe57163b8f98e91938ab9d926767b937d2a0533e2871  (+CODE_INVALID_KIND 常量)
solitaire/core/moves/move_executor.gd         5d5104b121edbd81b8f2098cde7873656af93d4ea5ab3123450feb5b59a8d028  (+execute_boundary 会话边界入口；行为零回归)
solitaire/core/rules/rules_engine.gd          255b185cffa1ca28e3b4d3ed0d4cdc3cbe57d7d77028ea0d3085220300b0ad53  (REPLAY/NEW_DEAL 显式 typed 拒绝 = 非玩法移动)
```

修改的测试文件（1 个）：`tests/test_move_model.gd` `97e44b16…`（kind roundtrip 9→11，含 replay/new_deal 工厂与 is_boundary 断言）。

未改：`card_data.gd/card_pile.gd/game_state.gd/move_batch.gd/snapshot_history.gd/legacy_*`、WP-05/06 其余测试文件、`data/legacy/*` fixtures（bureau1 `36414bfc…`、bureau3 `0bf9409a…` 不变）、`addons/**`、`mcp_verify.tscn`、`project.godot`。

## 3. 公开接口/架构要点

- 层次（新增 application 与 deal/selector，方向正确）：core/hint、core/autocomplete（纯 RefCounted 静态服务，零实例/全局状态）→ 复用 core moves/rules/state；application/game_session（RefCounted，非 Node，永不入 SceneTree）只依赖 core + deal；deal/selector（DeterministicDealSelector）只读无依赖。全工程仍无 Node/Control/Texture/CanvasItem/Presentation/Firebase。
- `HintEngine.hint(state) -> HintResult` 与 `all_legal_moves(state) -> Array[Move]`。**总序（已文档化+表驱动测试）**：T0 暴露面下牌（自动翻牌）的合法 tableau 移动 → T1 tableau/waste 顶→foundation（源扫描 tableau 列 0..6 后 waste；槽 0..3 升序）→ T2 waste→tableau → T3 其他非暴露 tableau run 移动 → T4 DRAW_STOCK/RECYCLE_STOCK → T5 foundation→tableau（最后兜底）→ T6 无新意的 King/整 run→空列平移（仅当 T0..T5 不存在才返回）。同层按规范枚举序取首。每个候选都先经 `RulesEngine.validate` 才可返回；`HintResult` 携带 move+tier 或 typed 无提示原因（`invalid_state/already_won/no_legal_move`）。
- `AutoCompletePlanner.plan(state) -> AutoCompletePlanResult`。资格：tableau 28 张全 face-up；仅发 `TABLEAU_TO_FOUNDATION/WASTE_TO_FOUNDATION/DRAW_STOCK/RECYCLE_STOCK` 四种普通玩法移动；模拟只经 `MoveExecutor.execute` 于克隆（源状态与历史零接触）；**不**发 tableau 重排/foundation 回滚/直发 FLIP/身份变更/Assist。动态 foundation 目的地：先找同花色槽顶升 1 级者（槽索引升序），Ace 取首个空槽。终止：canonical 状态签名（容器排列+face-up+draw 模式，排除 move/score/stock_passes 计数器以捕获 draw/recycle 循环）+ `MAX_STEPS=2048`（≥512）。结果 typed：eligible/eligibility_code/stop_reason（`won/no_progress/no_legal_move/max_steps`）/moves/step_count/visited_count/final_state_snapshot()（深克隆）。
- `GameSession`：`create(pool,index,draw_count) -> GameSessionResult`（typed deal 错误：invalid_pool/index_out_of_range/invalid_draw_count/invalid_record/io_error）；私有 `_state/_history/_pool/_index/_draw_count`；对外 `state_snapshot()` 与每个返回 `MoveExecutionResult.new_state` 均为深克隆。`apply_move`（MoveExecutor.execute，边界身份经 executor typed 拒绝）、`undo`（execute_undo）、`replay()`（按当前 pool/index/draw 重新发 ready 态，REPLAY 边界，清历史）、`new_deal()`（`(index+1) mod pool_count`，NEW_DEAL 边界，清历史）、`hint()/plan_auto_complete()`（只读委托，不触 _state/_history）。
- `Move`：`MoveKind` 增 `REPLAY`、`NEW_DEAL`（KIND_COUNT 9→11），工厂 `Move.replay()/Move.new_deal()`、`is_boundary()`；RulesEngine 形状门显式把二者与 UNDO 一样作为非玩法身份 typed 拒绝（`invalid_kind`）。`MoveExecutor.execute_boundary(current, target, boundary)`：只接受 REPLAY/NEW_DEAL，返回 target 深克隆 + 显式单边界批次，不改输入、不触碰历史（会话边界清历史由 GameSession 负责）。
- `DeterministicDealSelector.next_index(current, pool_count) -> Dictionary`：`(current+1) mod pool_count`；`invalid_current_index/invalid_pool_count/singleton_pool` 显式拒绝；绝不随机、不读玩家状态/历史/DDA。

## 4. MCP 测试结果与诊断

- McpTestSuite 全量（终轮干净复跑，同一会话）：**passed=162 / failed=0 / skipped=0**，**15 suites**（WP-05 5 + WP-06 6 + WP-07 4），editor log 0 行、无 game log。
- 修复记录：首轮 4 项 hint 失败全部源于 `_face_up_valid_run_length` 的降序关系写反（使 run 候选过短），修正后 162/162 干净通过。
- 实测断言数（`test_run(verbose=true)` 逐项累计，终轮值）：WP-05 = core_model 322 + golden_deal 15 + legacy_dealer 56 + legacy_decode 77 + library_integrity 41 = **511**（与 WP-05 证据一致）；WP-06 = move_executor 364 + move_model 86 + rules_engine 223 + score_win 58 + snapshot_undo 149 + state_isolation 11 = **891**；WP-07 = auto_complete 124 + boundary_moves 56 + game_session 104 + hint_engine 82 = **366**；**全量断言合计 1768**。说明：WP-06 证据记载的 888 系该 WP 提交口径；本终轮用同一 runner 对未改的 WP-05/06 suite 复测为 511/891（其中 `test_move_model` 依 WP-07 要求扩展 REPLAY/NEW_DEAL 覆盖，78→86，+8），差异均不影响断言成立性。
- 覆盖要点（WP-07，选列）：
  - hint：同状态确定性+零变异（源 content_equals + history 0）；每个返回候选经 RulesEngine 全绿；**优先级表驱动**（暴露面下 T2F/run 均胜 foundation；foundation 胜 waste→tableau 胜 run 胜 draw；draw/recycle 兜底；仅剩平移 King 时才返回 trivial 层）；**动态 foundation 槽**（空槽任意 Ace 取首个空槽、同花色升序槽优先）；blocked/won/null typed 无提示；`all_legal_moves` 覆盖 K,Q,J 整 run 等全部合法 suffix run 且确定性有序。
  - autocomplete：隐藏 tableau 卡拒绝（typed hidden_tableau_cards）；代表可完成整 52 牌近终局经 waste/tableau 顶/stock draw 三种路径均达 WON（Draw-1 与 Draw-3 双测）；计划移动逐一经 MoveExecutor 按序重放合法且终态 == simulated final、52 守恒；源零变异+确定性；**draw/recycle 循环在两种 draw 模式均 typed `no_progress` 终止且步数 < 2048**；blocked typed `no_legal_move`；动态槽（heartK→hearts 槽 0、Ace→首个空槽）；整局 eligible 计划仅含 4 种允许 kind。
  - session/boundary：apply/undo 全程 executor 路由、undo 还原、空历史 typed nothing_to_undo；REPLAY/NEW_DEAL/UNDO 经普通 execute typed invalid_kind 且零变异零快照；`execute_boundary` 返回克隆 target+显式批次（REPLAY/NEW_DEAL），拒绝非边界/null，克隆隔离（改返回态不动 target/current）；replay 精确还原初始 ready 态（move/score/stock_passes 归零、历史清空、deal 身份不变）；new_deal 确定性下一索引+同 pool/同 draw 模式+清历史，bureau3 末索引 wrap→0；getter/返回态深克隆隔离（改克隆不影响会话）；会话 hint/plan 零变异。
- 诊断：MCP editor log 0 行；plugin log 无 error/warning；无 game log（全程未运行游戏）。

## 5. 依赖/约束静态检查

- `rg "extends Node/Node2D/Node3D/Control|CanvasItem|Texture|\.tscn|preload|ResourceLoader|Firebase|get_node|SceneTree"` 于 `solitaire/core/hint`、`solitaire/core/autocomplete`、`solitaire/application`、`solitaire/deal/selector`：仅命中注释（game_session.gd 头注释自述“never a Node/SceneTree”），无实际依赖。
- 方向性：`rg "LegacyDeal|DeterministicDeal|GameSession|LegacyDealer|LegacyDealRepository" solitaire/core` → 仅 move_executor.gd 注释提及（描述 execute_boundary 语义），无代码依赖；core 不依赖 deal/application。
- `project.godot` SHA-256 = `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9`（权威字节基线，未改）；无 main scene/display/input。
- `mcp_verify.tscn` SHA-256 `56a31e49b2312581b4f753529e6fa9b90ba9db2a000acdc69ef7b10f90bbc67f`（夹具原样）；addon 未动；`.godot/**` 与新增 `.gd.uid` 之外的编辑器可再生缓存照例披露。

## 6. 旧工程 pre/post 与边界

- 固定参考 `WTF-Solitaire`（`/Volumes/Mac studio pro/solitaire/WTF-Solitaire`，HEAD `515710ad…`，非产品参考对象）：本次仅只读引证，未 checkout/写入；其 5 项未跟踪 Xcode 工程目录为既有状态（`proj.ios_mac/…`），前后一致、与本次无关。
- godot 父仓库工作树中 `solitaire2/S1` 之外的变更 = 0；旧 `godot/solitaire` Godot 工程零变化。
- 全程无 commit/push/下载/凭证/破坏性动作；未改动 addons、project.godot、fixtures、mcp_verify.tscn、data/legacy 数据。

## 7. 验收结果（WP-07 十条）

1. Hint 确定性、合法、typed、优先级表驱动测试、零变异；无提示 typed（invalid_state/already_won/no_legal_move）；候选全部经 RulesEngine ✓
2. AutoComplete 全 tableau face-up 才激活；只发 4 种允许 kind；仅经 MoveExecutor 于克隆模拟；源不变；动态 foundation 槽正确 ✓
3. 代表可完成终局在 Draw-1/Draw-3 均达 WON；循环/阻塞态在 MAX_STEPS 内 typed 终止；整 52 牌测试 52 守恒、无身份变更 ✓
4. GameSession 无 Node/SceneTree，私有 _state/_history/_index/_pool/_draw_count；getter 与结果态深克隆；apply/undo/replay/new_deal 全走 MoveExecutor；hint/plan 不变异 ✓
5. replay 精确重建同一 legacy ready 态/身份/draw 模式且计数器归零、历史清空；new_deal 确定性不同索引（含 wrap）、同 pool/同模式、清历史；无随机/DDA/assist ✓
6. REPLAY/NEW_DEAL 非 RulesEngine 玩法移动；普通 execute typed 拒绝；专用 `execute_boundary` typed 通过；RulesEngine/executor/boundary/会话四层测试 ✓
7. WP-05/06/07 全量 162/162 通过、15 suites、editor log 0 行、游戏停止、无 scene/project 设置改动 ✓
8. core/application/deal 方向正确；无 Node/Control/Texture/CanvasItem/场景/纹理/Firebase 依赖；无 WP-08 文件 ✓
9. project.godot 权威字节基线不变；旧参考/旧 Godot 工程 pre/post 不变；无意外文件；改动清单精确记账（11 个新增 `.gd`+`.gd.uid`、4 产品+1 测试 .gd 修改）✓
10. 本证据如实报告公开 API、确定性总序与界、精确文件+UID+hash、测试/suite/断言、MCP 会话/路径/版本/结果/日志、限制与停止；WP-07 止于“待证据确认”，WP-08 未启动 ✓

## 8. 未验证项/限制

- 全部验证在 @tool 上下文 MCP 完成；未运行游戏进程（WP-08 范围）。
- AutoComplete 是贪心确定性规划器（每次取第一个可达 foundation 的普通移动），非穷尽求解器/搜索；对需要 tableau 重排才能解的真实局不承诺可达 WON——验收按“代表可完成近终局 + 循环/阻塞 typed 终止”界定，与合同排除 Solver 一致。
- hint 的 F2T/trivial 层仅作“最后合法兜底”返回，可能被 UI 用于“无更优”提示；与 legacy 产品无自动按钮差异由 WP-08 呈现层决定。
- replay/new_deal 以会话当前 deal 身份（pool/draw 固定、index=当前）重发；S2 无难度/DDA/历史选择逻辑（DeterministicDealSelector 保持最小）。
- undo 沿用 WP-06 线性模型（无 redo、undo 不可再被 undo）；会话层未引入新裁决需求。

## 9. 依赖与停止

- WP-08（UI-001 Pure 2D Playable Loop）依赖本证据包获得 TD“证据确认”；**WP-08 保持依赖锁定**，执行者在收到证据确认前不启动 WP-08。
- 停止项：WP-07（Hint + AutoComplete + Application Session + Replay/New Deal 边界 + DeterministicDealSelector）施工完成并已提交本证据；执行者停止，等待技术总监证据确认。
