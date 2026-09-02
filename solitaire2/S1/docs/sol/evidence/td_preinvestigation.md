# TD 开工前调查：干净 Godot 与 MCP 基线

- 调查者：Sol 5.6（技术总监）
- 时间：2026-09-02T12:24:41+08:00
- 目标：`/Volumes/Mac studio pro/solitaire/godot/solitaire2/S1`
- 性质：只读调查与合同依据，不是执行者施工证据

## 当前工程事实

- 目标存在，Godot 4.6 新建；除 `.godot/**` 外仅 6 个默认文件。
- 6 文件聚合 SHA-256：`b18db22eb06e1a27c1777ee1e198c5887b3b7543ce5d1be6357b74d26057bf0a`。
- `project.godot` SHA-256：`3f041c32bcc2eb76c96347f839ace629aa8a06df327420e4163ab66bb3a83819`。
- `project.godot` 无 main scene、autoload、editor plugin、display 或 input；项目名“新建游戏项目”。
- `.godot/**` 有 11 个可再生文件；目标中无符号链接。
- 父 Git `/Volumes/Mac studio pro/solitaire/godot`：`main@6d5eaf3c6ae6f602044f5519e62f0700dae14fd1`；目标 `solitaire2/**` 未跟踪。

## MCP 可复用源

- 固定 Git 对象路径：`solitaire/addons/godot_ai/**`、`solitaire/mcp_verify.tscn`。
- `plugin.cfg`：Godot AI 3.2.4，入口 `plugin.gd`。
- 父 Git 固定提交中的旧空基线已有 `_mcp_game_helper` autoload 与 `res://addons/godot_ai/plugin.cfg` editor plugin 配置。
- 决定：从固定 Git 对象导出，不从有残留的旧工作树复制；文件逐项与 commit 核对。

## 官方依据

- Godot stable Installing plugins：插件以 `addons/<plugin>` 和 `plugin.cfg` 安装，并在 Project Settings > Plugins 启用。
  - https://docs.godotengine.org/en/stable/tutorials/plugins/editor/installing_plugins.html
- Godot stable Project Manager：包含 `project.godot` 的目录可作为既有工程导入。
  - https://docs.godotengine.org/en/stable/tutorials/editor/project_manager.html

## 风险与验证

- 风险：复制旧工作树导致残留；MCP 连到旧工程；pre-MCP bootstrap 越界；插件可连接但工程并不干净。
- 验证：固定 commit/file count/hash；project.godot 最小 diff；MCP editor path/hierarchy/filesystem/diagnostics/log/screenshot；最终全文件 manifest；两个旧工程 pre/post 零变化。
