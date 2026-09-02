# TD 架构预调查：合同 2.0 视觉与分辨率修订

- 调查者：Sol 5.6（技术总监）
- 日期：2026-09-02
- 性质：只读架构预调查；不是执行者施工证据或最终验收
- Cocos 权威：`origin/InvincibleWarrior@12b33cbed606952e4f90c88d987961a6ef8f50fc`
- Godot 当前工程：`/Volumes/Mac studio pro/solitaire/godot/solitaire`

## 当前实现

- `project.godot`：viewport `1280×800`，无旧版等价 stretch/aspect。
- `presentation/cards/card_view.gd`：`90×126`，用 `_draw()` 生成临时牌面。
- `presentation/board/board_view.gd`：横屏坐标；Foundation X=860，Tableau X=20..620。
- 判断：Core/交互原型可复用；Presentation 不满足负责人新增的视觉与分辨率目标。

## 旧版一手取证

1. `Classes/AppDelegate.cpp`：设计尺寸 `1080×1920`，`ResolutionPolicy::FIXED_WIDTH`。
2. `cocosstudio/ui/GameLayerHD.csd`：根 Layer/Panel `1080×1920`，牌位 `146×220`。
3. `Classes/AppConstant.h`：`POKER_SIZE = 148×220`。
4. `Classes/manager/AtlasManager.cpp`、`Classes/object/CardSprite.cpp`：通过 `car_new_0_1.atlas` region 映射纸牌正面、牌背与花色/点数。
5. `Resources/game/car_new_0_1.png`：`1044×2034`；atlas 牌背 region `142×218`。
6. `Resources/ui.png`：`2019×2047`；`Resources/ui1.png`：`1988×2039`；`GameLayerHD.csd` 引用其核心槽位/按钮。
7. Cocos 工作树检查：仍在 master，仅原有未跟踪 Xcode/Pods 内容；本次调查零写入。

## Godot 官方依据与适用性

- Multiple resolutions（latest）：viewport width/height 是设计尺寸；`canvas_items` 按基准缩放 2D；`keep_width` 保持宽度并对高屏扩展纵向可见区域。适用于复刻 Cocos FIXED_WIDTH。
  - https://docs.godotengine.org/en/latest/tutorials/rendering/multiple_resolutions.html
- Importing images（latest）：PNG 可作为 Texture2D；2D filtering 在 CanvasItem/项目设置；lossless 适合避免额外压缩伪影。适用于旧 PNG 原图。
  - https://docs.godotengine.org/en/latest/tutorials/assets_pipeline/importing_images.html
- Import process（stable）：工程内资源应由 Godot 导入并通过 ResourceLoader 使用，不依赖 `.godot/imported` 内部路径。适用于跨平台导出。
  - https://docs.godotengine.org/en/stable/tutorials/assets_pipeline/import_process.html

## 复用决定

- 复用当前 Core/Deal/Application/测试；复核后只修可证缺陷。
- 固定导入旧版核心闭环所需牌面、牌背、背景/槽位与按钮，不复制商业化无关资源。
- 不引入 Cocos/Spine runtime；从固定 atlas 确定性生成 AtlasTexture/region 数据或无损裁切 PNG。
- Godot 采用 `1080×1920 + canvas_items + keep_width + portrait`。
- 静态视觉与交互闭环本阶段验收；完整旧 Spine 动画后置。

## 风险与验证要求

- 风险：Cocos/Godot Y 轴方向、atlas region/rotate、146/148 尺寸差、宽度固定时高屏安全区、输入坐标变换。
- 验证：52 Card ID 映射检查；1080×1920 与高屏 MCP 截图；实际 stock/drag/double-click 输入；MCP logs/diagnostics；无关资产与 Cocos 工作树 scope audit。
