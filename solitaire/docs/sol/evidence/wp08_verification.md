# WP-08 运行验证与证据

- 阶段: S1-GODOT-CORE-LOOP
- 执行者: DeepSeek v4 Worker
- 环境: Godot 4.6.2.stable.custom_build.001aa128b（/Applications/Godot.app/Contents/MacOS/Godot）, headless
- 时间: 2026-09-02
- 基线: 项目根 /Volumes/Mac studio pro/solitaire/godot/solitaire

## 命令与退出码（全部真实引擎，非自写解析器）

### 1. 项目导入/解析
命令: `/Applications/Godot.app/.../Godot --headless --path . --import`
结果: 退出码 0；日志 rg `SCRIPT ERROR|Parse Error|ERROR` 计数 0。
备注: 最终导入前先 `rm -rf .godot` 全量重建，确保无陈旧缓存污染。

### 2. 完整自动化测试套件
命令: `Godot --headless --script res://tests/run_all.gd --path .`
结果: 退出码 0；10 suites, 52/52 passed, 0 failed。
套件覆盖：
- test_legacy_deal.gd（两牌库数量 32,084/4,999、字节、SHA-256、全量记录严格解码）
- test_decoder_negative.gd（长度错误/越界字节/重复/缺牌失败关闭）
- test_golden.gd（50 静态 Golden，tableau+stock 52/52 逐一比对）
- test_rules.gd（降序异色、空列仅 K、同花 A→K、非法回移、非法移动零变化）
- test_moves.gd（执行器、原子失败、显式 FlipTableau、DRAW/RECYCLE、事务内翻牌）
- test_draw_recycle.gd（Draw-1/Draw-3 顺序、尾组不足 3 张、无限回收、初始抽牌）
- test_undo.gd（快照精确恢复、翻牌/Draw-3/recycle、深拷贝别名隔离、多次 Undo、空 Undo）
- test_hint_auto_replay.gd（Hint 只读合法、Auto Complete 仅 foundation 且安全停滞、Replay 同牌同模式、重复 Replay、New Deal、Draw 切换）
- test_state_invariants.gd（脚本化对局不变量、4×13 WON 判定、非 Foundation 不判胜）
- test_source_boundaries.gd（Core 不继承 Node、Presentation 不改状态、golden 非运行时生成）

### 3. 主场景运行冒烟
命令: `SOLITAIRE_SMOKE=1 Godot --headless --path . --quit-after 300`
结果: 退出码 0；`[smoke] start` / `[smoke] end ok=true moves=1`；无 SCRIPT ERROR / 未处理错误。
冒烟脚本经主场景 _ready 驱动真实 GameController：发牌→抽牌→Undo→Stock 操作→New Deal→Replay→Draw-3→Auto Complete→Hint→状态不变量。

### 4. 工程迭代记录（关键修复）
- `Array[T]()` 构造器在此引擎全量分析下解析失败 → 改为 typed 局部变量初始化。
- 类名 `repository.get()` 与 Object.get 冲突 → 更名 get_record()。
- 循环引用 GameState↔KlondikeRules 导致 headless 解析失败 → GameState.invariant_errors 内联规则副本（与 KlondikeRules 语义一致）。
- 源边界测试与测试数据修正（牌面花色映射、typed array 替换）。

## 结果汇总
- 解析：通过，无 GDScript parse/type error。
- 测试：52/52 通过。
- 冒烟：主场景可启动并存活，无未处理错误。
- 验收级别：3 级系统验证完成（见 docs/sol/阶段结果.md）。
