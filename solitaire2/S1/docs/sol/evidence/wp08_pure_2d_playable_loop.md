# WP-08 证据包：UI-001 Pure 2D Playable Loop（修正 2 · 自包含完整 delta）

- 合同：`docs/sol/施工合同.md`（S2 v1.0，§6 WP-08、§8 十二项验收矩阵、§9 证据与停止）；worker-order `docs/sol/worker-order-s2-classic-2d.md`；修正 2 指令（Sol 评审 · WP-08 correction-2 closeout）
- 阶段：`S2-CLASSIC-2D-CORE-LOOP`；状态：**WP-08 修正 2 施工完成、待证据确认**（已停工；不声明阶段 PASS，未开始任何 S3/收尾）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash）
- 环境：macOS Darwin arm64；Godot `4.6.2-stable (custom_build)`；Godot AI MCP 插件/服务器 `3.2.4`；时间 2026-09-03
- 说明：本文件取代 WP-08 修正 1 证据版，作为**自包含的修正 2 证据包**：完整枚举相对父 Git HEAD `3be833b`（WP-07 施工完成）的 WP-08 delta（不再仅列修正 1 路径）；并附确定性完整清单 `wp08_changed_files_manifest.txt`。本包不声明零告警，逐条披露现行 reload 告警（全部为 WP-05..07 既有样式），并证明 WP-08 文件当前零告警。

## 1. 会话与工程路径（MCP）

- 修正 2 会话 `s1@e452`（project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`）；current_scene `res://scenes/main.tscn`；readiness ready；play 终态 stopped。
- MCP 动作：filesystem scan（多次）；`McpTestSuite` test_run（suite 与全量）；project_run(mode=main) 复核 + project_manage stop；game_eval（只读运行时复核：scene_file_path/`mcp_safe_layout`/`mcp_state`/`mcp_hint_overlays`/`mcp_hint_text`/`mcp_double_tap_ms`）；editor/game logs_read（含 `logs_clear` + Debugger Errors 清空后重载再读）；editor_state。
- `mcp_verify.tscn` 不变：SHA-256 `56a31e49b2312581b4f753529e6fa9b90ba9db2a000acdc69ef7b10f90bbc67f`（与 WP-07/WP-08 修正 1 一致）。

## 2. WP-08 完整 delta（相对 HEAD `3be833b`；本证据核心修正）

修正 1 版证据称“首次 WP-08 其余文件不变、仅列修正 1 路径”；该表述不足。WP-08 首次交付与修正 1、修正 2 均未提交，现行工作树即完整 delta。**修正 2 改为全量枚举**，权威逐行（status/字节/SHA-256）见 **`docs/sol/evidence/wp08_changed_files_manifest.txt`**，共 **65 行（M 6 + A 59）**，聚合 SHA-256 `8fb0dbf511148e27ecac6225ef9bac05df766699ea2412ba1947b361a7b73cee`（聚合定义见清单尾部；本证据 md 与清单自身不计入聚合，避免自引用）。类别摘要：

1. M｜引擎配置与核心应用层（3）：`project.godot`、`solitaire/application/game_session.gd`、`solitaire/application/game_session_result.gd`。
2. M｜docs/sol 治理文档（3）：`当前任务.md`、`项目状态.md`、`证据索引.md`（本包同步为修正 2 口径）。
3. A｜`solitaire/presentation/**` 源码（20：10 `.gd` + 10 `.gd.uid`）：controller `solitaire_director/fixture_states/input_interpreter/snapshot_projector`；views `card_view/board_view/board_geometry`；infrastructure `legacy_atlas/legacy_face_mapper/safe_area_layout`。
4. A｜tests（4）：`test_wp08_mapping.gd(.uid)`、`test_wp08_interaction.gd(.uid)`。
5. A｜`scenes/main.tscn`（1，纯 2D，无 Node3D）。
6. A｜`assets/legacy` 资产来源字节（13）：`MANIFEST.md` + images `background-0.png`、`car_new_0_1/0_6.png/.atlas` + audio 7 mp3。
7. A｜`assets/legacy` 生成 `.import` 侧车（12，编辑器可再生，不属来源清单）。
8. A｜证据截图 png（4）：`wp08_{draw1_initial,draw3_waste,mid_hint,auto_won}.png`。
9. A｜证据截图 `.import` 侧车（4，编辑器可再生）。
10. A｜证据文档（1）：本 md。

排除规则（明文）：`.godot/**` 可再生缓存不列入、不计入聚合（编辑器运行态再生，清单标注其当前数量）；`.import` 侧车与 `.gd.uid` 属随库/编辑器生成，前者列入并标注可再生，后者随 `.gd` 逐项入列。行格式 `M|A  <字节>  <sha256>  <./路径>`；确定性由重生成 diff=空 保证。

## 3. 修正 1 六项（保持生效；均为 Sol 评审后确定的功能/视觉内容）

1. rank 字形 56×56 原生左上角（`RANK_CELL=56`、`rank_rect=(0,0,56,56)`、center x=28，与 legacy `Sprite_num` 一致），base/suit/court 覆盖层整卡；未新增/烘焙图片。
2. 双击窗 `CardView.DOUBLE_TAP_MS=450`（区间 350–500 内）；删除重复常量；真机正/负例见 §7。
3. Hint 双覆盖层（源绿 `HINT_SOURCE_COLOR`/目标琥珀 `HINT_TARGET_COLOR`），只读不改状态。
4. 纯几何 `SafeAreaLayout` 安全区适配（DisplayServer 无关）；满窗恒等 + 顶/底内缩纯几何测试。
5. editor-only 接缝门：`SolitaireDirector.mcp_debug_load_fixture`、`GameSession.debug_create_state` 先 `OS.has_feature("editor")` 否则 typed 拒绝；release 不可注入。
6. main_scene 的 MCP 来源：运行期 `ProjectSettings.set_setting/save` 持久化 + read_text 复核 + mode=main 实启证实（本次修正 2 再以 mode=main 复核，见 §7）。

补充（修正 1）：WinLabel 改 WinOverlay 内 FULL_RECT + 居中；呈现层零直接 GameState/CardData/pile 修改，逻辑动作全部经 GameSession/MoveExecutor。

## 4. 修正 2 改动内容

- **源码告警治理（纯标识符改名/下划线参数，零行为与视觉变化；无测试改动）**，消除 WP-08 文件 7 处 reload 告警源（另 1 条 path="" 的瞬时条目未复现，见 §6）：
  - `board_view.gd`：`_draw_stack` 局部 `visible` → `shown`（shadow CanvasItem.visible）；`_draw_slot_placeholder` 参数 `color` → `_color`（未用参数 GDScript 惯用标注）。
  - `solitaire_director.gd`：三处 `name` 迭代/局部变量 → `key`（shadow Node.name）；`_drag_source_desc` 内层 `var card` → `candidate`（消除“declared below in parent block”）。
  - `game_session.gd`：`debug_create_state` 参数 `draw_count` → `draw_mode`（shadow 类方法 `draw_count()`；仅 WP-08 新增接缝函数，未动 WP-07 `create()`）。
- project.godot 回剔编辑器自动写入的非 WP-08 `[file_customization]` 目录着色段，逐字节复核回到修正 1 记录值 `44fbbc1b…`（见 §8）。
- 证据包重写（本文件）+ 新增确定性完整清单 `wp08_changed_files_manifest.txt`；docs/sol 三治理文档同步为修正 2。
- 复跑：全量测试 188/188 不变；现行 reload 诊断重读（§6）。

## 5. 测试（MCP `McpTestSuite`）

- **passed=188 / failed=0 / skipped=0，17 suites**（全量 run `r1377436-6` 承载；game log 每 run 仅 1 行 helper info、0 error）。WP-08 两 suite 复跑：`wp08_mapping` passed=9、`wp08_interaction` passed=17；其余 15 suite（WP-05..07）全保留通过，无回归。
- 断言类别同修正 1：52 卡 rank 56×56、CardView 布局 56×56 左上、face-down 无 rank 层、双击常量 450ms、双覆盖层计数/几何/色/重复不叠加/无 zone 销毁、`SafeAreaLayout` 恒等与内缩、`debug_create_state` typed 拒绝等。

## 6. 诊断与告警处置（修正 2 消解“提示”与“无告警”矛盾）

- 修正 1 证据 §7 将“editor 静态 reload 提示”笼统记为 WP-05..08 既有样式告警，与 §10 验收“无持续告警”自相矛盾。经现行 MCP 诊断核实：该批提示确为 GDScript::reload **静态样式告警**（非当前 run 的 parse/runtime 错误，各 run `current_run_errors=[]`/`recent_errors=[]`），但其中 **8 处实际源自 WP-08 新增代码**（board_view 2、solitaire_director 4、game_session debug_create_state 1、另 1 条 path="" line 0 的 `ready` shadow 瞬时条目未复现，判为编辑器内部瞬时，非 WP-08）。修正 2 已消除 WP-08 来源全部告警。
- **现行（logs_clear 后重载再读）editor logger 恰 17 条 reload 告警，全部为 WP-05..07 既有代码样式告警，逐条如下（本包不宣称“零告警”）：**
  - `card_data.gd:22/33` Integer division（WP-05）
  - `game_session_result.gd:25` param `session` shadow var:22（WP-07，`success()` 既有）
  - `card_pile.gd:104` param `ids` shadow func:87（WP-05/06）
  - `move.gd:48` param `kind` shadow var:88（WP-06）
  - `move_execution_result.gd:24` param `batch` shadow var:19（WP-06）
  - `hint_result.gd:33(×3)/43(×2)` params `move/tier/message/code/message` shadow（WP-07）
  - `legacy_deal_decoder.gd:72`、`legacy_deal_repository.gd:88/98` Integer division（WP-05）
  - `legacy_deal_result.gd:20` param `state` shadow var:17（WP-05）
  - `move_executor.gd:76` param `state` unused in `execute_undo()`（WP-06）
  - `game_session.gd:24` param `draw_count` shadow func:52（WP-07 `create()` 既有）
- **WP-08 文件（含修正 1、修正 2 改动）当前零 reload 告警**；game/editor 各 run 无 parse/runtime 错误；Debugger Errors 清理后当前无 WP-08 错误行。

## 7. 修正 2 实测复核（MCP 运行中，run `r1704596-7`；只读）

- `project_run(mode=main)` 启动的就是 `res://scenes/main.tscn`（`current_scene.scene_file_path` 证实）；game log 1 行 helper info、0 error；`recent_errors=[]`。
- 运行态：`mcp_double_tap_ms()=450`；bureau1#0 draw1：waste 1、stock 23、tableau 1..7 张、move_count 0、status IN_PROGRESS；`mcp_safe_layout()`：content/safe/ui/board 均 `(0,0,1080×1921)` 恒等、`has_insets=false`、margins 0（修正 1 记录值一致，含 1921 高度为实测非笔误）；hint 当前为单一可用移动文本（首局提示：`move 1 tableau card(s) from column 2 to column 0`），overlay 层仅在该移动被请求时渲染。
- 修正 1 已录真机矩阵（双击 60ms 收 Ace 正例 / 700ms 负例、非法拖零变异、合法拖 ♠5→♥6、Undo 精确还原、replay/new deal、near_win Auto→WON、WinLabel 居中、双覆盖层 rects 等）在修正 2 无行为改动前提下保留有效；修正 2 仅标识符改名，由全量 188/188 复跑证明无回归。

## 8. 截图与 project.godot 合规

- 四张必需截图在修正 1 实机运行重拍，**修正 2 无视觉/行为改动故不重拍，文件逐字节未变**：`wp08_draw1_initial.png` sha `0c6f509c7f4b9cdbb1cd0ddfdee6096c94f562b4691c161df83db88b0701966e`、`wp08_draw3_waste.png` `6b371f03bdc0c4d53eef18bfce1228ca399a1ba9c568584ccf501498e0889ec2`、`wp08_mid_hint.png` `fb845ed22e0f9a2ba3d421ebdc66e05ca224d1f495d77c2f7885792e8d35c3f7`、`wp08_auto_won.png` `cb6af9137bdb9afc88f4ff2989d9629bc27bb90d3d9ac3f6acfe07b4bdabd913`（与修正 1 记录完全一致，均可复核）。
- project.godot 现行 SHA-256 `44fbbc1be8e9ab8186d6a73e6ac80953a6881a69d3d9eb03905ef1f4d04e5cad`：键集 = WP-08 首次+修正 1（run/main_scene、display、input、autoload、editor_plugins），main_scene 为 MCP 运行期 `ProjectSettings.set_setting/save` 来源（mode=main 实启复核）。**修正 2 期间编辑器在某次 MCP 运行自动向 project.godot 写入非 WP-08 的 `[file_customization]` 目录着色段（f1dedfef…）**，已从磁盘剔除并复核回到 `44fbbc1b…`（键集/语义不变，无该编辑器偏好段）。
- `scenes/main.tscn` 层次：Control(Solitaire)/TextureRect/Control×2(含 UI/WinOverlay)/AudioStreamPlayer/Node(Director)，无 Node3D。
- 资产来源字节复核：`assets/legacy` 13 来源文件（MANIFEST + 5 image 源 + 7 mp3）SHA-256 与 `assets/legacy/MANIFEST.md` 内嵌导出值 **12/12 逐项一致**（MANIFEST 未改写、原样保留为来源清单）；12 个 `.import` 侧车为编辑器生成、不属于来源清单，清单中单独列类标注可再生。

## 9. 旧工程 pre/post 与边界

- 父 Git root `/Volumes/Mac studio pro/solitaire/godot`（HEAD `3be833b…`），pathspec `solitaire2/S1/`。
- `WTF-Solitaire`（只读，旧 Cocos 仓库 root `/Volumes/Mac studio pro/solitaire/WTF-Solitaire`，HEAD `515710ad2ff06bb405f5ee539904f6c837cb2983`）：pre/post 一致，均 5 项未跟踪 Xcode 目录（`proj.ios_mac/NewSpaceCatSolitaire*.xcodeproj/.xcworkspace`、`Pods/`）为既有状态；固定对象 `74f51802…` 未 checkout/写入。
- 旧 `godot/solitaire` 子树（同父仓库，pathspec `solitaire/`）：pre/post `git status` 均 0 条目，零变化（父仓库当前全部变更仅 `solitaire2/S1/` pathspec 内 WP-08 delta）。
- `mcp_verify.tscn`、`data/legacy/**` 逐字节不变；addons、WP-05..07 源文件未动；修正 2 仅 3 个 WP-08 源码文件纯改名。无禁入系统。

## 10. 验收（WP-08 修正 2 指令准则逐条）

1. 全量 MCP suite **passed=188/failed=0/skipped=0、17 suites**；现行 game/editor 诊断无矛盾（§6：17 条既有告警按 file:line 披露；WP-08 文件零告警；0 parse/runtime error）✓
2. WP-08 文件无当前告警；既有告警逐条列出、不称“零告警” ✓
3. 证据自包含并链接完整确定性清单（§2 + `wp08_changed_files_manifest.txt`）✓
4. 清单 65 行（M6+A59）覆盖 HEAD `3be833b` 全 delta、含全部 `.gd.uid`/资产与截图 `.import`、逐行 status/字节/SHA-256、类目计数与聚合 hash、排除 `.godot/**` 并明文声明 ✓
5. 资产来源字节与 `.import` 侧车分开核验；来源清单 `assets/legacy/MANIFEST.md` 原样保留（12/12 匹配）✓
6. 四张修正 1 截图 hash 未变仍有效（修正 2 无视觉改动）；main_scene 来源/188 或最新精确计数/MCP 动作/旧 repo pre/post/限制/停止条件均如实 ✓
7. 游戏 stopped；仅限定内改动；WP-08 保持待证据确认、不声明 PASS ✓

## 11. 限制

- 执行者模型无图像视觉：卡面视觉最终真实性由 Sol/TD 依四张截图确认（hash 未变）。本包以映射/布局断言 + 运行态几何数字替代像素目检。
- macOS 真机安全区为满窗恒等（实测 1080×1921）；顶/底内缩由 `SafeAreaLayout` 纯几何测试代表（未在刘海真机实测）。
- 双击 60/700ms 用运行中真机毫秒时钟在 CardView 生产处理路径注入（`Input.parse_input_event` 在该环境不触发 GUI picking，已如实披露；语义层与鼠标/触摸共用 `_handle_press/_handle_release`）。
- 17 条 reload 样式告警为 WP-05..07 既有（非 WP-08），按最小改动原则未清改旧包；如 Sol 要求可单独立项清理。
- 编辑器可能在后续 MCP 运行再向 project.godot 自动写 `[file_customization]`；如需防写，宜在编辑器偏好层设置，不在本包范围。

## 12. 停止项

WP-08 修正 2 施工完成并提交本证据（证据 md + 完整清单 + 治理同步）；执行者已停止，等待技术总监证据确认。未开始 S3/阶段收尾，不自行宣布阶段 PASS。
