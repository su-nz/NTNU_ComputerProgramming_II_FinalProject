# NTNU_ComputerProgramming_II_FinalProject

### WSL 本身是 CLI 環境，沒內建 GUI，你需要：

✅ 一、安裝 X Server for Windows
- 安裝 VcXsrv 
  - https://sourceforge.net/projects/vcxsrv/


- 安裝後執行 XLaunch：
  - 選「One large window」
  - 勾選「Disable access control」
  - 完成後會有一個 X Server 視窗在跑

- 回到 WSL 終端機，設定環境變數：

    ```
    export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
    ```
- 或直接固定寫入 ~/.bashrc：
    ```
    echo 'export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk "{print \$2}"):0' >> ~/.bashrc
    source ~/.bashrc
    ```
✅ 二、安裝 raylib 開發套件
- 如果你用的是 Ubuntu WSL：

    ```
    sudo apt update
    sudo apt install gcc make libraylib-dev libraylib-dev libraylib-dev libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libpthread-stubs0-dev
    ```

- 你可以直接建一個 minimal 測試程式：
    ```
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

    ```
    gcc test_gui.c -o test_gui -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    ```

- 執行（確保 X Server 有跑）：
    ```
    ./test_gui
    ```

✅ 測試成功後就能跑你的完整程式

```
make
./TwistedFables
```