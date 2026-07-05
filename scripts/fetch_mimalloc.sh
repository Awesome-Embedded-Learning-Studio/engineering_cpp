#!/usr/bin/env bash
# ============================================================
# fetch_mimalloc.sh — 拉取 mimalloc 源码,配合本仓 mimalloc 系列学习
# ============================================================
#
# 背景:
#   mimalloc 已从本仓 submodule 移除(教学价值转 anatomy_memory 承接),
#   但 B 站《现代 C++ 工程实践》mimalloc 系列(5 期)+ documentation/tutorial/mimalloc/
#   仍是「读开源项目」的教学资产。本脚本拉取上游 mimalloc 到本地,让教程路径有效。
#
# 用法(从仓根):
#   bash scripts/fetch_mimalloc.sh
#
# 拉取后:
#   - 源码:project/external/mimalloc/
#   - 教程:documentation/tutorial/mimalloc/
#   - 视频:video/mimalloc.md
#
# 注:默认拉取最新 master。B 站视频录制于 2026 年初,若教程引用的代码行
#    与 master 有差异,可 cd project/external/mimalloc && git checkout <tag>
#    切到视频对应版本。

set -euo pipefail

TARGET="project/external/mimalloc"
REPO="https://github.com/microsoft/mimalloc.git"

# 切到仓根(允许从任意目录跑)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(dirname "$SCRIPT_DIR")"
cd "$ROOT"

if [ -d "$TARGET" ]; then
  echo "✓ $TARGET 已存在。如需重新拉取:rm -rf $TARGET 后重跑。"
  exit 0
fi

mkdir -p project/external
echo "→ 克隆 mimalloc 到 $TARGET ..."
git clone --depth 1 "$REPO" "$TARGET"
echo ""
echo "✓ 拉取完成。"
echo "  教程:documentation/tutorial/mimalloc/README.md"
echo "  视频:video/mimalloc.md"
echo ""
echo "注:默认 master 分支。视频录制于 2026 年初,如代码与教程有出入,"
echo "   cd $TARGET && git checkout <tag> 切到视频版本。"
