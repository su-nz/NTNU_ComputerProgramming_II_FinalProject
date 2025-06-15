#!/bin/bash

set -e

echo "📦 安裝必要套件..."
sudo apt update
sudo apt install -y gcc make cmake git \
  libgl1-mesa-dev libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxss-dev \
  libasound2-dev libpulse-dev libaudio-dev \
  libraylib-dev

echo "📁 建立 external 資料夾..."
mkdir -p external
cd external

if [ ! -d SDL ]; then
  echo "⬇️ 下載 SDL2 (v2.26.5)..."
  git clone --depth=1 --branch release-2.26.5 https://github.com/libsdl-org/SDL.git
fi

echo "🔨 編譯 SDL2..."
cd SDL
mkdir -p build && cd build
cmake .. -DBUILD_SHARED_LIBS=OFF -DSDL_STATIC=ON
make -j$(nproc)
cd ../../

if [ ! -d SDL_mixer ]; then
  echo "⬇️ 下載 SDL2_mixer (v2.6.3)..."
  git clone https://github.com/libsdl-org/SDL_mixer.git
fi

echo "🔨 編譯 SDL2_mixer..."
cd SDL_mixer
git checkout release-2.6.3
mkdir -p build && cd build
cmake .. -DBUILD_SHARED_LIBS=OFF \
  -DSDL2MIXER_OPUS=OFF -DSDL2MIXER_MOD=OFF -DSDL2MIXER_MP3=OFF -DSDL2MIXER_FLAC=OFF
make -j$(nproc)
cd ../../

echo "🎮 SDL2 & SDL2_mixer 編譯完成！"

echo "🧩 開始編譯你的專案..."
cd ..
make

echo "✅ 完成！你可以執行 ./TwistedFables 來玩遊戲囉"
