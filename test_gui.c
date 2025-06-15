#include "raylib.h"

int main() {
    InitWindow(800, 600, "WSL Test");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib + WSL", 200, 200, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
