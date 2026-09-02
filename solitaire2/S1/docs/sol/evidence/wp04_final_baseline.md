# WP-04 证据包：干净基线冻结与终局交接

- 合同：`docs/sol/施工合同.md` v1.2（§6 WP-04、§8 验收矩阵、§9/§12 停止与交接、ADR-006 裁定）；worker-order `docs/sol/worker-order-s1-clean.md`
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2
- 阶段：`S1-CLEAN-GODOT-BASELINE`；WP-01、WP-02、WP-03 证据已确认（技术总监 WP-04 授权返回 WP-03“证据确认”，工作包证据确认，非阶段最终验收）
- 执行者运行时身份：DeepSeek（deepseek-v4-flash，DSH harness）
- 环境：macOS Darwin 25.5.0 arm64（macOS 26.5.1）；Godot 4.6.2-stable (custom_build)（editor_pid 53275）；时间 2026-09-02T23:05:00+0800
- 状态：WP-04 证据 + 阶段终局报告已提交并经第 1 轮独立验收返回 **工程 PASS**（非阻塞治理文档缺陷 2 处已修正并独立抽检复核）；技术总监正式阶段裁决 = **`S1-CLEAN-GODOT-BASELINE 通过`（THROUGH/PASS）**，**S1 阶段已通过并关闭**（关闭时间 2026-09-02T23:20:00+0800）

## 1. project.godot 权威字节基线（验收 #3）

- on-disk SHA-256 `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9` = ADR-006 权威值，**未改写**（753B）。
- 内容复核：`[autoload] _mcp_game_helper` 1 项、`[editor_plugins] enabled=…godot_ai/plugin.cfg` 1 项；**无 `application/run/main_scene`、无 `[display]`、无 `[input]`**（MCP `settings_get application/run/main_scene` = 空；文件全文核对无 display/input 段）。

## 2. MCP 固定源 267 + mcp_verify.tscn 逐字节（验收 #4）

- 固定 Git 对象：父仓库提交 `6d5eaf3c6ae6f602044f5519e62f0700dae14fd1` 的 `solitaire/addons/godot_ai/**` 共 **267** 路径（ls-tree 全为 100644 blob，无 gitlink/符号链接；mcp_verify.tscn 另计 1）。
- 逐项比较命令（CLI 只读）：对 267 路径逐一 `git show <commit>:<path> | sha256sum` 与目标实际文件 sha256 比较：**checked=267 mismatches=0（267/267 一致）**。
- 目标 addon 目录实际 268 文件 = 267 固定对象 + 1 披露 `.DS_Store`（6148B）；**非元数据意外文件 = 0**。
- `mcp_verify.tscn`：目标 SHA-256 `56a31e49b2312581b4f753529e6fa9b90ba9db2a000acdc69ef7b10f90bbc67f` = 固定 Git 对象（一致）。
- 排除规则聚合（./ 相对路径、LC_ALL=C、排除 .DS_Store）：`find ./addons/godot_ai ./mcp_verify.tscn -type f ! -name ".DS_Store" | LC_ALL=C sort | xargs sha256sum | sha256sum` = **`4d3cb4f927453fdc328d59206660ee0a2d05a780532aeae5379fa814b7245ae9`**（= WP-01/02/03 确认值，未漂移）。含披露 .DS_Store 的原始聚合 `c170a5486d597f12c82056fd7bfb77a098c3a43991b85cf7ec2d44076efadb84`（披露值）。

## 3. 最终 manifest（验收 #2）

- 文件：`docs/sol/evidence/wp04_final_manifest.txt`（确定性文本清单，./ 相对路径 + sha256 逐行；本清单不内嵌自身 sha256，避免自引用，确定性以“重生成 diff=空”验证）。
- 分类与显式规则：
  - 类别 1 原始/默认工程文件（6）：`.editorconfig`、`.gitattributes`、`.gitignore`、`icon.svg`、`icon.svg.import`、`project.godot`；不含 `.godot/**` 与 `docs/**`。
  - 类别 2 MCP 固定源（267 + 1）：`addons/godot_ai/**` 267 固定对象 + `mcp_verify.tscn`；规则 = 排除披露 `.DS_Store`，267 路径须逐字节 = 固定 Git 对象，禁止非元数据意外文件。
  - 类别 3 SOL 治理/证据：`docs/sol/**`（治理 6 + worker-order + 证据 md/png）；规则 = 排除 `.DS_Store` 与 Godot 生成的 `.png.import` 侧车。
  - 类别 4 可再生/编辑器元数据：全部 `.DS_Store`、Godot 证据图 `.png.import` 侧车、`.godot/**` 可再生缓存；规则 = 披露、不删除、不计入冻结源码/完整性计数。
  - 默认 6 文件聚合（排除 .godot/docs 口径，含 ADR-006 后 project.godot 现状）= **`17385f551e5209c22edc6c4b69327dd522b5008310c2cfd6c7987f91a9fc6b88`**（命令：`printf '%s\n' ./.editorconfig ./.gitattributes ./.gitignore ./icon.svg ./icon.svg.import ./project.godot | LC_ALL=C sort | xargs sha256sum | sha256sum`）。与 WP-01 开工值 `b18db22e…` 的差异仅因 project.godot 经 ADR-006 由 `3f041c32…`/`518630d4…` 演进为 `ef9dfc63…`。
  - 注（第 1 轮独立验收纠正）：`0ffee779c386f667b87b045754ceaf7e303b2a092f5945e5025db0a203f525d1` 实为 **7 个顶层文件**（6 默认文件 + `mcp_verify.tscn`）的聚合（命令：`find . -maxdepth 1 -type f | LC_ALL=C sort | xargs sha256sum | sha256sum`），**并非**默认 6 文件聚合；此处以无歧义标签单独披露，不再与 6 文件口径混用。

## 4. MCP 只读状态绑定（验收 #5）

- 会话 `s1@7164`（S1，is_active）：project_path = `/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1/`（精确新路径）；Godot `4.6.2-stable (custom_build)`；插件与服务器版本 `3.2.4`；play_state/game_status = stopped；readiness ready；current_scene = `res://mcp_verify.tscn`（未设 main scene）。
- hierarchy：`/Main`(Node3D) + `/Main/MainCamera`(Camera3D) 共 2 节点，无旧/游戏内容；`/Main` script = null。
- filesystem：PackedScene 全工程 1（`res://mcp_verify.tscn`）；GDScript 132 个全部位于 `addons/godot_ai/`；`game_controller` 等旧名搜索 0 命中。
- logs：editor log 0 行；plugin log 正常（plugin loaded/connected、无 error/warning）。
- 截图证据：WP-03 `wp03_viewport_2d_screenshot.png`（613×640，SHA-256 `c98c458c…`）**保留未变**；本 WP 未新建场景、未运行游戏。
- 上述均经 Godot AI MCP（3 级系统验证口径）；CLI 仅用于 hash/manifest/Git 只读。

## 5. 父仓库与旧工程状态（验收 #6）

- 父仓库 `/Volumes/Mac studio pro/solitaire/godot`：HEAD = `2ec2d060ba17253ca9083eb5398e3ce4af29e6b4`（2026-09-02T22:31:12+0800，负责人提交“MCP和项目迁移”），固定源提交 `6d5eaf3c6ae6f602044f5519e62f0700dae14fd1` 为其祖先（merge-base --is-ancestor 通过）；HEAD 现已跟踪 solitaire2/S1 快照（含 267 addon、project.godot、部分 docs），与施工源无关、未影响本 WP 结论。
- pre/post 父仓库 status 逐字比对（本 WP 生成 `wp04_parent_status_pre.txt`）：仅 docs/sol 治理/证据文件为本 WP 写入项（WP-03 evidence 的 3 个文件为 WP-03 遗留 + 本 WP 新增/更新治理与证据）；**无其他工作树变化**。
- 旧 Godot `/Volumes/Mac studio pro/solitaire/godot/solitaire`：位于父仓库内，pre/post 均无本 WP 触碰。
- 旧 Cocos `/Volumes/Mac studio pro/solitaire/WTF-Solitaire`：独立仓库，HEAD `515710ad2ff06bb405f5ee539904f6c837cb2983`，status 5 行（proj.ios_mac 未跟踪项），pre/post 一致（未触碰）。
- 全程无 commit/push/checkout/网络/凭证/删除；未覆盖无关用户变更。

## 6. 可再生元数据披露（验收 #7/合同 §8.9）

- `.DS_Store`：`addons/godot_ai/.DS_Store`（6148B，22:15 复发，ADR-006 归为披露可再生态，不删除）+ `docs/.DS_Store`（6148B）。
- `.godot/**`：可再生缓存，披露、不计入冻结源码。WP-04 冻结快照 14 个；S1 关闭修订时编辑器仍在运行，`editor_script_doc_cache.res` 重新生成，manifest 类别 4c 当前快照 = **15** 个（editor/、imported/icon.svg、imported/wp03_viewport_2d_screenshot.png 的 .ctex/.md5、uid_cache 等；数量为编辑器运行态可再生值，随运行变动）。
- Godot 证据图侧车：`docs/sol/evidence/wp03_viewport_2d_screenshot.png.import` + `.godot/imported/wp03_viewport_2d_screenshot.png-…`。
- 符号链接：0。

## 7. 验收结果

- §8 矩阵：新路径精确、无旧顶层目录 ✓；默认 6 文件聚合 hash 一致 `17385f55…`（project.godot 按 ADR-006 `ef9dfc63…`；7 顶层文件聚合 `0ffee779…` 已另行无歧义披露）✓；addon 267 逐项 = 固定 Git commit、零本地修改，mcp_verify.tscn 另计 1 ✓；project.godot 仅含 MCP autoload/editor plugin、无 main scene/display/input ✓；Godot 4.6.2 MCP 返回 S1 精确路径、无 plugin/project 错误 ✓；hierarchy/filesystem 无旧实现 ✓；mcp_verify.tscn 仅验证夹具、非 main scene ✓；旧工程 pre/post 一致 ✓；最终 manifest 无未披露文件、.godot 明确可再生 ✓；无 commit/push/下载/凭证 ✓。
- 第 1 轮独立验收（2026-09-02）：工程验收 **PASS**，建议 PASS；非阻塞治理文档缺陷 2 处——① `阶段结果.md` 施工/验收状态滞后（本修订已更正为“实现候补完成、独立验收 PASS”）；② 本节“默认 6 文件聚合”标签/值不符（`0ffee779…` 实为含 `mcp_verify.tscn` 的 7 顶层文件聚合；6 文件聚合已更正为 `17385f55…`，`0ffee779…` 以无歧义标签披露）。修正候补已重报，本包 manifest 已重生成并逐项复核与磁盘一致；2 处修正经独立抽检复核通过。
- 技术总监正式裁决（2026-09-02，关闭 S1）：正式 S1 阶段裁决 = **`S1-CLEAN-GODOT-BASELINE 通过`（THROUGH/PASS）**；采纳第 1 轮独立验收工程 PASS，无任何残留未通过验收准则；**S1 阶段已通过并关闭**（关闭时间 2026-09-02T23:20:00+0800）。S1 关闭与后续产品阶段授权/开工相互独立；负责人最新授权允许后续推进至 WP-08，但下一动作须为新阶段预调查/阶段合同，本关闭令不含任何 WP-05+ 施工。
- 负路径：无基线漂移、无 addon 非元数据不一致、无旧目录混入、无 main scene、未连错路径。
- 状态口径：本报告为 WP-04 证据 + 阶段终局报告（修正重报 + 关闭修订）。第 1 轮独立验收工程 PASS → 技术总监正式裁决 `S1-CLEAN-GODOT-BASELINE 通过` → **S1 已关闭**。

## 8. 未验证/限制

- 父仓库 HEAD 已由负责人推进至 `2ec2d06…`（含 solitaire2/S1 快照跟踪），本 WP 仅如实记录、不参与、不提交；与固定源 `6d5eaf3…` 的区分已在 §5 与清单中载明。
- `.godot/imported` 缓存数量为编辑器运行态可再生值，按披露口径记录而非冻结断言。
- 阶段终局报告全文见本包 §10 输出约定（≤40 行；**原提交时**状态“通过候选/待独立验收与 TD 最终裁决”，第 1 轮独立验收后为“独立验收 PASS / TD 正式裁决待裁决”，关闭修订后当前 = **独立验收 PASS / TD 正式裁决 `S1-CLEAN-GODOT-BASELINE 通过` / S1 已关闭**）。
- viewport_2d 截图沿用 WP-03 已确认证据；本 WP 未新增截图（合同要求保留既有证据、不建新场景）。

## 9. 依赖

- 无 WP-05 或后续依赖工作施工；S1 已通过技术总监正式裁决并关闭。负责人最新授权允许后续推进至 WP-08，但下一动作须为新阶段预调查/阶段合同（未启动）；Solitaire 产品重写与 S1 关闭相互独立，仍以负责人授权/开工令为准。

## 10. 变更文件

- docs/sol/evidence/wp04_final_baseline.md（本包，新增）；docs/sol/evidence/wp04_final_manifest.txt（确定性最终清单，新增）；docs/sol/项目状态.md、docs/sol/当前任务.md、docs/sol/证据索引.md（治理更新）。未改动任何工程/固定源/元数据文件。

## 11. 修订记录

### 修订 1（第 1 轮独立验收修正重报，2026-09-02T23:17:00+0800）

- 范围：仅 docs/sol/** 治理/证据文件；未触碰 project.godot/addon/mcp_verify.tscn/.godot/.DS_Store 等任何工程/固定源/元数据文件；无 commit/push/网络/删除。
- 修正 A：`docs/sol/阶段结果.md` 状态更正（第 1 轮验收、实现候补完成、独立验收 PASS、TD 正式裁决待裁决、下一阶段锁定）。
- 修正 B：本节默认 6 文件聚合更正为 `17385f551e5209c22edc6c4b69327dd522b5008310c2cfd6c7987f91a9fc6b88`；`0ffee779…` 另以“7 顶层文件（6 默认 + mcp_verify.tscn）聚合”标签披露。
- 同步：`项目状态.md`/`当前任务.md`/`证据索引.md` 记录“独立验收 PASS、TD 正式裁决待裁决”；`wp04_final_manifest.txt` 按当前磁盘重生成并逐项复核。

### 修订 2（S1 关闭修订，2026-09-02T23:20:00+0800）

- 范围：仅 docs/sol/** 治理/证据文件；未触碰 project.godot/addon/mcp_verify.tscn/.godot/.DS_Store 等任何工程/固定源/元数据文件；无 commit/push/网络/删除；未开始任何 WP-05+ 工作。
- 关闭：技术总监正式裁决 = **`S1-CLEAN-GODOT-BASELINE 通过`（THROUGH/PASS）**；无任何残留未通过验收准则；S1 阶段关闭。`阶段结果.md`/`项目状态.md`/`当前任务.md`/`证据索引.md` 与本节状态口径同步为“S1 已通过并关闭、下一动作 = 新阶段预调查/阶段合同（未启动）”；`wp04_final_manifest.txt` 按当前磁盘重生成并逐项复核。
