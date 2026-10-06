#!/bin/zsh
S2_ROOT="${0:A:h}"
S2_GODOT="/Applications/Godot.app/Contents/MacOS/Godot"
if [[ ! -x "$S2_GODOT" ]]; then
  print '没有找到 Godot，请在 Godot 项目管理器中导入此文件夹的 project.godot。'
  read -k 1
  exit 1
fi
exec "$S2_GODOT" --path "$S2_ROOT"
