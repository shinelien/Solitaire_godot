# S1 干净 Godot 工程与 MCP 基线施工合同

- 合同版本：1.2（WP-03 补证修订 1 · 基线漂移处置裁定）
- 规则基线：SOL 4.5.2 + 通用执行者连续执行合同 3.2
- 当前阶段：`S1-CLEAN-GODOT-BASELINE`
- 合同状态：已发布，施工中
- 技术总监：Sol 5.6
- 执行者：DeepSeek（负责人已决定；模型不改变权限或验收标准）
- 目标路径：`/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1`

## 1. 阶段成立与用户可观察结果

负责人授权建立一个全新的、没有旧 Solitaire 实现残留的 Godot 4 工程，并要求后续执行者通过 Godot AI MCP 工作。

阶段整体可观察结果：目标路径可由 Godot 4.6.2 正常打开；Godot AI 3.2.4 插件连接成功；工程没有 Main Scene、游戏脚本、场景、牌库、美术或旧测试；除 MCP 基础设施和 SOL 治理文档外没有旧项目内容；冻结一份可供后续 Solitaire 重写使用的干净基线。

该目标具有独立环境与交付物边界，可单独关闭。后续 Solitaire Core、美术、牌库导入与玩法实现均未授权，保持锁定。

## 2. 权威基线

- 目标目录已存在，创建时间基线：2026-09-02T12:18:58+08:00。
- 默认源文件基线排除 `.godot/**` 与 `docs/**` 后共有 6 个文件，聚合 SHA-256 `b18db22eb06e1a27c1777ee1e198c5887b3b7543ce5d1be6357b74d26057bf0a`。
- 6 个文件：`.editorconfig`、`.gitattributes`、`.gitignore`、`icon.svg`、`icon.svg.import`、`project.godot`。
- `project.godot` SHA-256 `3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819`。
- 当前 `project.godot` 无 main scene、无 autoload、无 editor plugin；项目名为“新建游戏项目”，Godot feature 为 4.6 + GL Compatibility。
- 当前 `.godot/**` 有 11 个可再生缓存文件，不属于冻结源码基线。
- `docs/.DS_Store` 是 macOS 在治理文档目录生成的本地元数据，不属于默认源文件或旧工程残留；WP-04 必须在最终 manifest 中单独披露，且不得计入冻结源码基线。
- 目标目录无符号链接。
- 父 Git：`/Volumes/Mac studio pro/solitaire/godot`，`main@6d5eaf3c6ae6f602044f5519e62f0700dae14fd1`；`solitaire2/**` 当前整体未跟踪。
- MCP 复用源必须来自父 Git 固定提交的 Git 对象：`solitaire/addons/godot_ai/**`、`solitaire/mcp_verify.tscn`，不得从旧工作树直接复制。
- Godot AI 固定版本：3.2.4，权威文件 `solitaire/addons/godot_ai/plugin.cfg`。
- 旧工程 `/Volumes/Mac studio pro/solitaire/godot/solitaire` 和 Cocos 工程均为禁止写入、禁止复制普通实现的外部参考；本阶段不需要读取 Cocos。

## 3. 方案依据与复用决定

### 当前项目事实

- 新目标工程已经由 Godot 4.6 建立，内容最小且不存在旧 Solitaire 路径。
- 新工程缺少 Godot AI addon，因此执行者无法在第一次动作前使用 MCP。
- 父 Git 固定提交包含已验证、Git-clean 的 Godot AI 3.2.4 addon、autoload 配置与 `mcp_verify.tscn`。

### 一级与成熟依据

- Godot 官方 Installing plugins：编辑器插件应位于项目 `addons/` 下，通过 `plugin.cfg` 识别，并在 Project Settings > Plugins 中启用。
  - https://docs.godotengine.org/en/stable/tutorials/plugins/editor/installing_plugins.html
- Godot 官方 Project Manager：含 `project.godot` 的目录可作为既有项目导入并打开。
  - https://docs.godotengine.org/en/stable/tutorials/editor/project_manager.html
- 成熟复用源：父 Git `6d5eaf3...` 中 Godot AI 3.2.4 addon 的 267 个受跟踪文件，已在旧空基线中运行过；另有 1 个 `mcp_verify.tscn`。本阶段复用其基础设施，不重新发明 MCP 集成。

### 决定

1. 保留当前 6 个 Godot 默认文件，不从旧 Solitaire 工程复制实现。
2. 只从固定 Git 对象确定性导出 `addons/godot_ai/**` 与 `mcp_verify.tscn`。
3. MCP 未安装前，允许执行者进行一次最小 bootstrap：导出固定 Git blob、为 `project.godot` 增加 `_mcp_game_helper` autoload 和 Godot AI editor plugin 配置、打开目标工程。此后所有 Godot 操作必须走 MCP。
4. 不设置 main scene、窗口分辨率、输入、牌桌或任何产品配置；这些属于后续重写合同。
5. `.godot/**` 仅作为可再生缓存，不进入冻结源码清单。

风险：错误复制旧工作树可能带入残留；错误项目路径可能连接到旧工程；插件连接可用不代表新工程干净。验证必须同时覆盖固定 Git 对象 hash、MCP editor path、scene hierarchy、filesystem 和完整路径清单。

## 4. 不可破坏约束

1. 禁止修改或删除 `/Volumes/Mac studio pro/solitaire/godot/solitaire/**` 与 `/Volumes/Mac studio pro/solitaire/WTF-Solitaire/**`。
2. 禁止把旧 `core/data/deal/application/presentation/scenes/tests/assets/docs` 复制到新工程。
3. 禁止创建 main scene、游戏脚本、Solitaire 目录、牌库、美术或测试。
4. 禁止修改从固定 Git 对象导出的 `addons/godot_ai/**` 内容。
5. 禁止 commit、push、分支切换、发布、部署、网络下载、凭证或外部副作用。
6. 唯一允许的 pre-MCP 文件动作是合同 §3 的最小 bootstrap；MCP 连接后禁止用 CLI/文件系统替代 Godot 编辑器验证。
7. 只有负责人发布本合同后执行者才能开工；技术总监不代发、不启动执行会话。

## 5. 目标验收级别

**3 级：系统验证完成。** 必须在本机 Godot 4.6.2 实际编辑器中，通过 Godot AI MCP 验证正确项目、插件连接和空工程状态。只看文件或 CLI 不足以通过。

## 6. 有序工作包

### WP-01 新目标基线复核

- 依赖：无。
- 工作指标：核对目标路径、6 个源文件、11 个缓存文件、0 个符号链接、父 Git commit 与完整 status。
- 验收指标：与合同 §2 一致；无旧 Solitaire 顶层目录；两个旧工程前后状态不变。
- 证据：路径清单、hash、Git status、执行者运行时身份与时间。

### WP-02 MCP 最小 Bootstrap

- 依赖：WP-01 证据确认。
- 工作指标：从固定 Git 对象导出 Godot AI 3.2.4 addon 的 267 个跟踪文件和 1 个 `mcp_verify.tscn`；对目标既有 `project.godot` 只增加 1 个 autoload 和 1 个 editor plugin 配置。
- 验收指标：导出文件逐项与固定 Git 对象一致；`project.godot` 无 main scene/display/input；无其他文件进入工程。
- 证据：源 commit/blob、文件数、聚合 hash、定点 diff、范围清单。

### WP-03 Godot AI MCP 空场验证

- 依赖：WP-02 证据确认。
- 工作指标：通过 MCP 取得 editor state、正确 project path、scene hierarchy/filesystem、diagnostics、logs、editor screenshot；打开 `mcp_verify.tscn` 仅作插件验证，不设 main scene。
- 验收指标：MCP 会话连接目标精确为新路径；无旧类/脚本/场景；diagnostics 无 plugin/project error；截图可见新工程。
- 证据：MCP 会话标识、关键返回、日志和截图路径。

### WP-04 干净基线冻结与终局交接

- 依赖：WP-03 证据确认。
- 工作指标：输出排除 `.godot/**` 后完整文件 manifest/hash；分类 baseline/MCP/SOL/cache；更新唯一状态看板和证据索引。
- 验收指标：除 6 个默认文件、MCP addon、mcp_verify 和 SOL 文档外无其他内容；无 main scene；旧工程零变化；报告无未验证项冒充通过。
- 证据：最终 manifest、pre/post status/hash、MCP 结果、阶段终局报告。

依赖某 WP 的后续工作仅在技术总监返回“证据确认”后继续；这不是阶段 Gate 或最终裁决。

## 7. 范围与授权

范围内：目标路径的 `addons/godot_ai/**`、`mcp_verify.tscn`、`project.godot` 最小 MCP 配置、`docs/sol/**`、`.godot/**` 可再生缓存。

范围外/禁止：全部 Solitaire 产品代码/数据/资产；旧 Godot/Cocos 工程；任何依赖安装、网络下载、Git 提交或发布。

默认授权：负责人发布后，可创建目标范围文件、从固定本地 Git 对象导出、打开本地 Godot Editor、使用 MCP 只读检查和生成证据。

负责人专属：删除/覆盖既有文件、修改固定目标路径、从网络安装新插件、commit/push/发布。当前均未授权且不需要。

## 8. 验收矩阵与负路径

1. 新路径精确、无符号链接、无旧 Solitaire 实现目录。
2. 默认 6 文件开工 hash 与记录一致或任何漂移被停止上报。
3. MCP addon 267 个跟踪文件逐项来自固定 Git commit，零本地修改；`mcp_verify.tscn` 另计 1 个。
4. `project.godot` 只新增 MCP autoload/editor plugin，不含 main scene/display/input。
5. Godot 4.6.2 打开目标工程且插件无解析/运行错误。
6. MCP editor state 返回新路径，scene/filesystem 不含旧实现。
7. `mcp_verify.tscn` 可由 MCP 打开并截图，但不设为 main scene。
8. 旧 Godot 与 Cocos 工程 pre/post status 一致。
9. 最终 manifest 无未披露文件；`.godot/**` 明确标记可再生。
10. 无 commit、push、下载、凭证、外部副作用。

负路径：目标基线漂移、Git 对象缺失、插件断连、MCP 连到旧路径、addon 文件不一致、旧目录混入、main scene 被意外设置。任一发生时失败关闭，不用 CLI-only 冒充 3 级验证。

并发/幂等：bootstrap 重跑必须不产生重复 autoload/plugin 项；并发编辑器会话连接到不同项目时必须停止。持久化/账户/网络/真实设备不适用。

## 9. 证据、停止与交接

- 证据写入 `docs/sol/evidence/**`，摘要登记 `证据索引.md`；每项含基线、环境、运行时身份、时间、动作、预期/实际、结果和限制。
- 执行者只输出：负责人授权请求、架构停止、WP 证据包、阶段终局报告。
- 基线漂移、旧内容混入、需修改旧工程、插件版本/来源冲突或 MCP 连错路径：立即架构停止。
- 普通导入/连接问题在当前 WP 内修复；不得扩大范围。
- WP-04 完成后提交不超过 40 行的阶段终局报告并严格停工，等待技术总监独立验收。
- 下一阶段 Solitaire 重写保持锁定，必须由负责人另行授权。

## 10. 执行难度与负责人决定

执行难度：低；建议：DeepSeek；理由：工作边界明确，主要是固定 Git 对象导出、MCP bootstrap 和空工程证据；备选：Luna。

负责人决定：使用 DeepSeek，且所有 bootstrap 后的 Godot 工作必须通过 Godot AI MCP。
## 11. 负责人补充决定（2026-09-02，WP-03 补证修订 1 授权）

- 记录人：执行者 DeepSeek（按负责人明确指示记录）；决定人：负责人；时间 2026-09-02。
- 决定 1（产品架构）：正式 Solitaire 产品采用 **Godot 纯 2D 架构**，以 `Control / TextureRect / CanvasItem` 为主要表现层，不使用 Node3D 开发游戏。
- 决定 2（旧工程参考）：旧 Cocos 工程仅作为规则、行为、素材、分辨率和产品体验的**只读参考**，不复制其代码结构。
- 决定 3（验证夹具）：`mcp_verify.tscn` 的 Node3D 仅为既有 MCP 验证夹具，保留原样，**不代表产品架构**，不得修改或转换。
- 授权修订（WP-03 截图标准）：WP-03 截图标准修订为 MCP `editor_screenshot(source="viewport_2d")`；空白 2D 视口允许，但必须是有效尺寸、不是 2×2 占位图，并绑定正确的 S1 会话和项目绝对路径。
- 影响：上述为产品架构与验证口径决定，不改变 S1-CLEAN-GODOT-BASELINE 阶段的范围/授权/验收级别；Solitaire 产品开发仍锁定，由负责人另行授权。

## 12. 技术总监基线漂移处置裁定（2026-09-02，合同 v1.2，WP-03 补证修订 1 重提交依据）

- 裁定人：技术总监 Sol 5.6（负责人已决定）；执行者据裁定完成治理/证据修订并重提交，未获得任何工程文件改动授权。
- 裁定 1（project.godot 字节基线）：接受 Godot 编辑器 22:25:34 规范化重写的 on-disk `project.godot` 为**新的字节基线**，SHA-256 `ef9dfc63fdcbe8273eb9edceff9216f7e592bcdcd95f011603b494c2fcf9e4c9`；其语义设置与先前的 `518630d4…` 冻结基线等价（键值/段集合一致，753B），仍无 main scene/display/input。执行者**不得重写或重排**该文件；后续校验以 ef9dfc63 为权威字节。
- 裁定 2（可再生元数据排除规则，通用而持久）：`addons/godot_ai/.DS_Store`（及工程内所有 `.DS_Store`）为 macOS 可再生元数据，**不得删除**，分类为可再生元数据：从源码/addon 完整性计数与聚合哈希中排除，但在清单与证据中显式披露。**权威 addon 完整性规则不变且不被削弱**：固定 Git 对象中全部 267 个路径必须存在且逐字节一致；禁止任何**非元数据**意外文件。因披露的元数据文件，addon 目录原始计数可为 268。
- 裁定 3（编辑器可再生副产物）：`.godot/**` 与 Godot 生成的证据图片 `.import` 侧车（如 `docs/sol/evidence/wp03_viewport_2d_screenshot.png.import` 及其 `.godot/imported/…` 缓存）为可再生/编辑器元数据，须在清单与证据中披露，不作为产品源码或完整性计数对象。
- 裁定 4（架构与截图标准延续）：产品架构决定不变——未来 Solitaire 为纯 2D；旧 Cocos 只读参考；`mcp_verify.tscn` 为原样保留的基础设施夹具。WP-03 截图标准 = MCP `editor_screenshot(source="viewport_2d")` 真实返回、非占位尺寸、绑定 S1 会话与项目绝对路径。
- 授权边界：本裁定只授权治理/证据文件修订与只读验证；未授权任何 project.godot/addon/场景/产品文件改动、删除或 WP-04。