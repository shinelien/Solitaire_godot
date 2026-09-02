# WP-02 证据包：MCP 最小 Bootstrap（补证修订 3）

- 合同：`docs/sol/施工合同.md` v1.1（§6 WP-02、§3 决定 3、§4 不可破坏约束）；worker-order `docs/sol/worker-order-s1-clean.md`
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2
- 阶段：`S1-CLEAN-GODOT-BASELINE`；WP-01 证据已确认（合同 v1.1 / ADR-004：addon 267 + mcp_verify.tscn 另计 1）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash，DSH harness）
- 环境：macOS Darwin 25.5.0 arm64；git 2.50.1；时间 2026-09-02T21:35:43+0800
- 动作类型：pre-MCP 最小 bootstrap（合同 §3 决定 3 唯一授权动作）；未连接 MCP、未打开编辑器（属 WP-03）
- 修订记录：技术总监 2026-09-02 两轮“需修复或补证”已处理（第 1 轮 3 项见 §7 第 1-3 项、第 2 轮 2 项见 §7 第 4-5 项）。补证修订 3 = 基线漂移处置（负责人专项授权删除 macOS 生成的 addons/godot_ai/.DS_Store），见 §9。实现与 bootstrap 未改动（删除对象为本地元数据，不在固定 Git 对象内）。

## 1. 源与导出

- 父 Git：`/Volumes/Mac studio pro/solitaire/godot`，固定提交 `main@6d5eaf3c6ae6f602044f5519e62f0700dae14fd1`。
- 导出方式：`git archive` 读取固定提交 Git 对象（`solitaire/addons/godot_ai/**` 267 文件 + `solitaire/mcp_verify.tscn` 1 文件），经 /tmp 临时暂存后复制进目标 `addons/godot_ai/` 与 `mcp_verify.tscn`；未从旧工作树复制、无网络。
- 路径无空格/特殊字符；导出文件全部 mode 100644（git 侧无 gitlink/子模块）。

## 2. 逐项一致性（全量定点，技术总监已独立复核）

- 268 个路径逐项比较 `git show <commit>:<path> | sha256sum`（预期）与目标实际文件 sha256（实际）：**diff 为空（TARGET_MANIFEST_MATCH）**。技术总监独立确认“268 个文件逐项完全匹配固定 Git 对象”。
- 抽查：`mcp_verify.tscn` sha256 `56a31e49b2312581b4f753529e6fa9b90ba9db2a000acdc69ef7b10f90bbc67f` = git 对象；`plugin.cfg` sha256 `021f54ebeda694bf583254af7cdcab0019b22adaea3425caa7253823c97a5ea7` = git 对象，`version="3.2.4"`。
- 目标 addon 文件数：267；符号链接：0。

## 3. 聚合 SHA-256（WP-01 相同口径，修正值）

- 口径：与 WP-01（BASE-001 b18db22e…）同一约定——在项目根下以 `./` 相对路径、按 C locale 字节序排序的 `sha256sum` 输出行整体再哈希。
- 复算命令（在目标根 `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1` 执行）：
  `find ./addons/godot_ai ./mcp_verify.tscn -type f | LC_ALL=C sort | xargs sha256sum | sha256sum`
- 结果：**`4d3cb4f927453fdc328d59206660ee0a2d05a780532aeae5379fa814b7245ae9`**（与技术总监复算一致）。
- 更正说明：初版证据包报告的 `d5a109a807f1fa17ef21c42f86752e53fe865321f3f9c440ac7c5b108e56fc92` 是对“`hash  solitaire/addons/…`（仓库相对路径文本）”清单行整体哈希的结果，路径文本基准偏离 WP-01 约定，予以废弃；逐项一致性与导出正确性不受影响（268 文件逐项 diff 为空）。另注意会话 locale（zh_CN.UTF-8）非 C 排序，复算须显式 `LC_ALL=C`。

## 4. project.godot 最小配置

- 变更前 hash `3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819`（WP-01 复核一致）；变更后 hash `518630d4314c8c7bc15e5f8fe48b8e6eb2bab627f99ad5b1adebe94fa4d4976b`。
- 重建 pre 内容（重建 hash 精确等于 pre-hash）与实际文件 diff：仅追加 8 行，无其他任何变更。
- 追加内容（逐字取自固定提交旧空基线 `solitaire/project.godot`，非执行者发明）：
  `[autoload] _mcp_game_helper="*res://addons/godot_ai/runtime/game_helper.gd"`；
  `[editor_plugins] enabled=PackedStringArray("res://addons/godot_ai/plugin.cfg")`
- 幂等：重跑追加逻辑不产生重复（autoload=1、plugin.cfg=1）。技术总监独立确认最小差异正确且幂等。
- 无 main scene、无 [display]、无 [input]。

## 5. 范围清单（无其他文件进入工程）

- 目标顶层新增：`addons/godot_ai/**`（267）、`mcp_verify.tscn`（1）；`project.godot` 仅 §4 追加。
- 其余不变：除 `project.godot` 已发生授权的 MCP 最小变更（§4）外，其余 5 个默认源文件（`.editorconfig`、`.gitattributes`、`.gitignore`、`icon.svg`、`icon.svg.import`）hash 均与 WP-01 一致；`.godot/**` 仍 11 个可再生缓存（未运行编辑器）；`docs/.DS_Store` 为 macOS 本地元数据（非冻结源码基线，WP-04 单独披露，未删除）。
- 表述更正（对应技术总监补证第 3 项及第 2 轮第 1 项）：本 WP 期间写入的 `docs/sol/**` 文件仅为协议要求的证据包与状态文件——`evidence/wp02_mcp_bootstrap.md`、`项目状态.md`、`当前任务.md`、`证据索引.md`（共 4 个治理文件，现场时间戳核验一致）；除此类授权的 SOL 状态/证据文件外，无其他文件进入工程。
- 父仓库 status 仍 10 行（` M solitaire/project.godot` + 8 个 untracked + `?? solitaire2/`），HEAD 不变；旧 Cocos 工程 status 仍 5 行；全程零 Git/网络/凭证/外部副作用。

## 6. 验收结果

- §8 矩阵相关项：addon 267 个跟踪文件逐项来自固定 commit、零本地修改，mcp_verify.tscn 另计 1 ✓；project.godot 只新增 MCP autoload/editor plugin、不含 main scene/display/input ✓；无其他文件进入工程 ✓（范围表述已更正）；旧工程零变化 ✓；无 commit/push/下载/凭证 ✓。
- 负路径：无基线漂移、无 Git 对象缺失、无 addon 不一致、无旧目录混入。
- 未验证/限制：Godot 4.6.2 编辑器打开与 MCP 插件连接属 WP-03（本 WP 未运行编辑器，符合顺序）；CLI 未冒充 3 级系统验证。

## 7. 补证修订记录（技术总监 2026-09-02）

第 1 轮（3 项，已于补证修订 1 处理）：
1. 聚合 hash 口径：按 WP-01 约定复算修正为 `4d3cb4f9…`，命令与说明见 §3；初版 `d5a109…` 已废弃并说明原因。
2. `当前任务.md` 过时（仍写“无活动任务/下一步 WP-01”）：已更新为 WP-02 补证修订后待确认、下一步 WP-03（依赖确认）。
3. “docs/** 未改”表述不准确：已更正为“除授权的 SOL 状态/证据文件外无其他文件进入工程”（§5）。

第 2 轮（2 项文档表述，本修订处理）：
4. §5 SOL 写入清单漏 `当前任务.md`：已补全为 4 个治理文件（`evidence/wp02_mcp_bootstrap.md`、`项目状态.md`、`当前任务.md`、`证据索引.md`），现场时间戳核验一致。
5. “6 个默认源文件 hash 均与 WP-01 一致”不成立（project.godot 已授权变更）：已改为“其余 5 个默认文件不变；project.godot 仅发生授权的 MCP 最小变更”（§5）。

## 8. 依赖

- WP-03（Godot AI MCP 空场验证）依赖本补证修订后的证据包被技术总监确认。

## 9. 基线漂移记录与处置（补证修订 3，2026-09-02）

- 事件：2026-09-02T21:37 macOS 在 `addons/godot_ai/` 生成 `.DS_Store`（6148B，Finder/编辑器浏览目录产生；addons/ 下仅此一个同类文件）。该文件不在固定 Git 对象内（`git ls-tree` 复核无 ds_store 项），不属于 267 个导出文件。
- 漂移影响：addon 目录文件数变为 268（267 + .DS_Store）；WP-01 口径聚合 hash 漂移为 `858bcedcdc790418b26ac1a0613540cd829780f26af9227e650225437753c706`（≠ 确认值 `4d3cb4f9…`）；与固定 Git 对象逐项清单比对出现 1 个多余文件。
- 处置（负责人专项授权，仅此单一动作）：删除 `addons/godot_ai/.DS_Store`；未删除其他文件、未修改 bootstrap、未进入 WP-03。
- 复核结果（删除后）：addon 文件数恢复 267；268 路径（267+1）逐项与固定 Git 对象 diff 为空（MANIFEST_MATCH）；聚合 hash 恢复 `4d3cb4f927453fdc328d59206660ee0a2d05a780532aeae5379fa814b7245ae9`（与确认值一致）；`mcp_verify.tscn` `56a31e49…`、`project.godot` `518630d4…`、`.godot` 11、父仓库 status 10 行、旧 Cocos 5 行均未变。
- 结论：基线漂移已消除，WP-02 证据结论不变（267+1 逐项 = 固定 Git 对象；聚合 `4d3cb4f9…`）。
