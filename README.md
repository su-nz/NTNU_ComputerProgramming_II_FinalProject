# 🧠 NTNU Computer Programming II Final Project — Twisted Fables GUI Edition

本專案為 NTNU《程式設計（二）》期末專題，以 C 語言與 [raylib](https://www.raylib.com/) 實作 GUI 介面版的卡牌遊戲《Twisted Fables》。

---

## 📦 環境需求

### ✅WSL 環境

#### 1. 安裝 X Server for Windows
- 推薦使用 [VcXsrv](https://sourceforge.net/projects/vcxsrv/)
- 安裝後執行 `XLaunch`，選擇：
  - ✅ `One large window`
  - ✅ `Disable access control`
- 執行後會常駐一個 X Server 視窗。

#### 2. 設定 DISPLAY 環境變數（WSL 端）

**暫時設定**（每次開機需重新輸入）：
```bash
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
```

**永久設定**（建議寫入 `~/.bashrc`）：
```bash
echo 'export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk "{print \$2}"):0' >> ~/.bashrc
source ~/.bashrc
```

#### 3.安裝套件 
```bash
sudo apt update
sudo apt install -y gcc make libraylib-dev libgl1-mesa-dev libx11-dev libpthread-stubs0-dev
```

### ✅Ubuntu 環境

```bash
sudo apt update
sudo apt install -y gcc make libraylib-dev libgl1-mesa-dev libx11-dev libpthread-stubs0-dev
```

---

## 🔧 編譯與執行說明

### Makefile 設定（已內建）

```make
CC = gcc
CFLAGS = -std=c99 -w
CFLAGS += -Iinclude

SRC = TwistedFables.c Function.c Skill.c Card.c vector.c board_gui.c
OBJ = $(SRC:.c=.o)
TARGET = TwistedFables

LIBS = \
  ./libraylib.a \
  ./libSDL2.a \
  ./libSDL2_mixer.a \
  -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
```

---

## 🚀 快速開始
### ✅WSL 環境
1. **啟動 VcXsrv（XLaunch）**
2. **開啟 WSL 終端機**
3. **設定好 DISPLAY 環境變數**
4. **編譯並執行：**

```bash
make run
```
### ✅Ubuntu 環境
1. **編譯並執行：**
```bash
make run
```

---

## 🧪 測試 GUI（選擇性）

你可以先用這段程式碼確認 GUI 是否可用：

```c
// test_gui.c
#include "raylib.h"

int main() {
    InitWindow(800, 600, "Raylib Test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello from WSL with raylib!", 100, 100, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

編譯指令：

```bash
gcc test_gui.c -o test_gui -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./test_gui
```

---

## 📂 專案結構

```
TwistedFables/
├── include/               # 放置 .h 標頭檔
├── raylib/                # raylib 原始碼（可選）
├── build_raylib.sh        # raylib 建構腳本
├── TwistedFables.c        # 主程式
├── Skill.c / Function.c   # 功能模組
├── vector.c / Card.c      # 輔助模組
├── board_gui.c            # GUI 顯示模組
├── Makefile
└── README.md
└── ...
```