#!/bin/bash

echo "🛠 準備編譯 raylib 靜態庫..."
mkdir -p raylib/build
cd raylib/build

# 執行 cmake 與 make
cmake ..
make

echo "✅ 完成：靜態庫已生成於 raylib/build/raylib/libraylib.a"
