# WP-03 证据包：Godot AI MCP 空场验证（补证修订 1 · ADR-006 处置后重提交）

- 合同：`docs/sol/施工合同.md` v1.2（§6 WP-03、§11 负责人补充决定、§12 技术总监裁定）；worker-order `docs/sol/worker-order-s1-clean.md`
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2
- 阶段：`S1-CLEAN-GODOT-BASELINE`；WP-01、WP-02 证据已确认
- 执行者运行时身份：DeepSeek（deepseek-v4-flash，DSH harness）
- 环境：macOS Darwin 25.5.0 arm64；Godot 4.6.2-stable (custom_build)（pid 53275）；复核重提交时间 2026-09-02T22:57:00+0800
- 状态：**待证据确认**。本包为 WP-03 补证修订 1，按技术总监 ADR-006 处置 2026-09-02 22:46 完整性复核发现的基线漂移后重提交（详见 §7）。

## 1. 会话与运行时身份（MCP）

- 会话 `s1@7164`（S1，is_active）：project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`（精确新路径，非旧工程）；Godot `4.6.2-stable (custom_build)`；插件与服务器版本 `3.2.4`；project_name “新建游戏项目”；play_state stopped；editor_pid 53275；readiness ready。
- 复核动作（本修订经 MCP 重取）：`editor_state` 返回 readiness=ready、current_scene=`res://mcp_verify.tscn`、is_playing=false；project 设置 `application/run/main_scene` = 空（main scene 未设置）；`editor_screenshot(source="viewport_2d")` 返回 613×640（原始 1799×1877）真实有效尺寸，绑定会话 s1@7164 与上述项目绝对路径。

## 2. hierarchy（MCP）

- `mcp_verify.tscn` 经 MCP 打开（非 main scene，仅验证夹具）；hierarchy `/Main`(Node3D) + `/Main/MainCamera`(Camera3D)，共 2 节点，无旧/游戏内容。与 ADR-005/合同 §11 决定 3 一致：夹具原样保留，不代表产品架构。

## 3. filesystem / 范围（MCP）

- PackedScene 全工程 1 个（`res://mcp_verify.tscn`）；GDScript 全工程 132 个，路径全部位于 `addons/godot_ai/` 下；旧目录/类名（core、deal、data、game_controller 等）搜索 0 命中；main scene 设置为空。
- 顶层仅：6 个 Godot 默认源文件 + `project.godot` + `addons/` + `docs/` + `.godot/`；无旧 Solitaire 目录。

## 4. logs / diagnostics（MCP）

- editor log：0 行；plugin log：无 error/warning；无 plugin/project 解析或运行错误（Godot 4.6.2 实际编辑器，3 级系统验证口径）。

## 5. 截图证据（补证修订 1 标准）

- 文件：`docs/sol/evidence/wp03_viewport_2d_screenshot.png`，PNG 613×640（sips 复核 pixelWidth 613 / pixelHeight 640），SHA-256 `c98c458ca380799883d69670676c6ad2e9ec6bcefac4c1c5628ed11deb38bab8`；空白 2D 视口，非 2×2 占位、非占位尺寸，MCP 返回绑定会话 s1@7164 与项目绝对路径。符合合同 §11/§12 截图标准。

## 6. 完整性复核与 ADR-006 处置（2026-09-02 22:46 复核发现 → 处置后重提交）

- 复核发现（22:46，触发原 §9 停止）：① `project.godot` on-disk hash 由冻结基线 `518630d4…` 变为 `ef9dfc63…`——Godot 编辑器于 22:25:34（工程打开时刻）规范化重写（段序重排），键值/段集合排序比较完全一致（语义等价，同 753B，仍无 main scene/display/input）；② `addons/godot_ai/.DS_Store` 再次由 macOS 生成 → addon 目录原始 268 文件；③ `.godot` 11→14（可再生）；④ 证据截图被编辑器 import 生成 `.png.import` 与 `.godot/imported/…` 缓存。
- 技术总监 ADR-006（合同 §12）裁定：接受 `ef9dfc63…` 为 project.godot 权威字节基线（不重写/重排）；`.DS_Store` 为可再生元数据——不删除、披露、不计入 267 完整性计数；权威 addon 规则不变（267 固定 Git 对象路径逐字节一致、禁止非元数据意外文件）；`.godot/**` 与证据图 `.import` 侧车披露为可再生副产物。本修订据此重提交，漂移项全部已处置，不再处于未决漂移状态。

## 7. 逐项完整性复核结果（CLI 只读，排除仅 .DS_Store）

- addon 固定对象：固定提交 `6d5eaf3c…:solitaire/addons/godot_ai/**` 共 267 路径，与目标 `addons/godot_ai/` 逐字节 sha256 比较 **mismatches=0（267/267 一致）**；目标 addon 目录仅多出披露的 `.DS_Store`（非元数据意外文件 = 0）。
- `mcp_verify.tscn`：目标 SHA-256 `56a31e49b2312581b4f753529e6fa9b90ba9db2a000acdc69ef7b10f90bbc67f` = 固定 Git 对象（一致）。
- 排除 `.DS_Store` 后 WP-01 口径聚合：`4d3cb4f927453fdc328d59206660ee0a2d05a780532aeae5379fa814b7245ae9`（= WP-02 确认值）；含披露 .DS_Store 的原始聚合 `c170a5486d597f12c82056fd7bfb77a098c3a43991b85cf7ec2d44076efadb84`（披露值）。
- `project.godot`：SHA-256 `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9`（ADR-006 权威基线）；内容复核：`[autoload] _mcp_game_helper`、`[editor_plugins] enabled=PackedStringArray("res://addons/godot_ai/plugin.cfg")` 各 1 项；无 `[display]`、无 `[input]`、无 `application/run/main_scene`。
- `.godot/**`：14 个可再生缓存文件（含 `imported/icon.svg…`、`imported/wp03_viewport_2d_screenshot.png-….ctex/.md5`），披露、不计入冻结源码。
- 符号链接：0；`.DS_Store` 存在两处（`addons/godot_ai/`、`docs/`），均为披露的 macOS 可再生元数据，未删除。
- 固定 Git 对象源提交 `6d5eaf3c…` 在父仓库中仍存在（为仓库当前 HEAD `2ec2d06…` 的祖先）；旧工程零变化；全程无 Git/网络/凭证/删除副作用。

## 8. 验收结果

- §8 矩阵相关项：addon 267 固定对象逐项 = 固定 commit、零本地修改（mcp_verify.tscn 另计 1）✓；project.godot 为 ADR-006 权威基线 `ef9dfc63…`，仅含 MCP autoload/editor plugin、无 main scene/display/input ✓；Godot 4.6.2 实际编辑器 MCP 返回 S1 精确路径、无 plugin/project 错误 ✓；hierarchy/filesystem 无旧实现 ✓；mcp_verify.tscn 由 MCP 打开并截图、非 main scene ✓；可再生元数据（.DS_Store、.godot、.png.import 侧车）全部披露 ✓；旧工程零变化、无外部副作用 ✓。
- 负路径：基线漂移已按 ADR-006 处置（非删除、非回写，属裁定接受 + 元数据排除），不再处于未决漂移；无 Git 对象缺失、无 addon 非元数据不一致、无旧目录混入。

## 9. 未验证/限制

- viewport_2d 截图为空白 2D 视口（S1 空工程无 2D 内容，符合修订标准）；未运行游戏（main scene 空）；`.godot/imported` 缓存数量为编辑器运行态可再生值，已按“可再生副产物”披露口径记录而非冻结断言。

## 10. 依赖

- WP-04（干净基线冻结与终局交接）依赖本证据包被技术总监确认；证据确认前不启动 WP-04。
