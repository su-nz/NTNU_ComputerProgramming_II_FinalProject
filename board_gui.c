#include "raylib.h"
#include "TwistedFables.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int pos1 = -1, pos2 = -1;
static int char1 = -1, char2 = -1;
static pthread_t render_thread;
static player player1, player2;

void update_coordinates(int p1, int p2) {
    pos1 = p1;
    pos2 = p2;
}

void update_characters(int c1, int c2) {
    char1 = c1;
    char2 = c2;
}

void update_characters_info(player p1, player p2){
    player1 = p1;
    player2 = p2;
}

void* board_gui_loop(void* _) {
    const int baseWidth = 1280;
    const int baseHeight = 720;
    const float aspectRatio = 16.0f / 9.0f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(baseWidth, baseHeight, "Twisted Fables - Board");
    SetTargetFPS(60);

    Texture2D portraits[10];
    for (int i = 0; i < 10; i++) {
        char path[128];
        snprintf(path, sizeof(path), "assets/images/character/%d.png", i);
        portraits[i] = LoadTexture(path);
    }

    while (!WindowShouldClose()) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        float currentRatio = (float)screenWidth / screenHeight;
        if (currentRatio > aspectRatio) {
            screenWidth = screenHeight * aspectRatio;
        } else {
            screenHeight = screenWidth / aspectRatio;
        }

        float cellWidth = screenWidth / 9.0f;
        float boardHeight = screenHeight * 0.35f;
        float coordHeight = screenHeight * 0.15f;
	float infoY1 = screenHeight * 0.0f;
        float infoY2 = screenHeight * 0.1f;
        float boardTop = (screenHeight - boardHeight - coordHeight) / 2.0f;

        BeginDrawing();
        ClearBackground(GRAY);

        // 玩家1資訊列
        const char* labels[] = {"Player1", "HP: %d", "Armor: %d", "Power: %d", "Hand: %d", "MaxHP: %d", "MaxArmor: %d", "Ult: %d"};
        for (int i = 0; i < 8; i++) {
            float x = i * cellWidth;
            int fontSize = coordHeight * 0.2f;
            if (i == 0) {
                DrawText(labels[0], x + cellWidth / 2 - MeasureText(labels[0], fontSize) / 2, infoY1 + coordHeight / 2 - fontSize / 2, fontSize, WHITE);
            } else {
                int value = ((int[]){player1.hp, player1.armor, player1.power, player1.hands, player1.Maxhp, player1.Maxarmor, player1.Ult_threshold})[i - 1];
                const char* label = labels[i];
                char buf[64];
                snprintf(buf, sizeof(buf), label, value);
                DrawText(buf, x + cellWidth / 2 - MeasureText(buf, fontSize) / 2, infoY1 + coordHeight / 2 - fontSize / 2, fontSize, WHITE);
            }
        }

        // 玩家2資訊列
        const char* labels2[] = {"Player2", "HP: %d", "Armor: %d", "Power: %d", "Hand: %d", "MaxHP: %d", "MaxArmor: %d", "Ult: %d"};
        for (int i = 0; i < 8; i++) {
            float x = i * cellWidth;
            int fontSize = coordHeight * 0.2f;
            if (i == 0) {
                DrawText(labels2[0], x + cellWidth / 2 - MeasureText(labels2[0], fontSize) / 2, infoY2 + coordHeight / 2 - fontSize / 2, fontSize, WHITE);
            } else {
                int value = ((int[]){player2.hp, player2.armor, player2.power, player2.hands, player2.Maxhp, player2.Maxarmor, player2.Ult_threshold})[i - 1];
                const char* label = labels2[i];
                char buf[64];
                snprintf(buf, sizeof(buf), label, value);
                DrawText(buf, x + cellWidth / 2 - MeasureText(buf, fontSize) / 2, infoY2 + coordHeight / 2 - fontSize / 2, fontSize, WHITE);
            }
        }

        // 上排：Board 格子
        for (int i = 0; i < 9; i++) {
            float x = i * cellWidth;
            Rectangle cell = {x, boardTop, cellWidth, boardHeight};

            Color squareColor = ((i % 2) == 0) ? (Color){160, 82, 45, 255} : (Color){210, 105, 30, 255};
            DrawRectangleRec(cell, squareColor);
            DrawRectangleLinesEx(cell, 2, DARKGRAY);

            if (pos1 == i + 1 && char1 >= 0 && char1 < 10) {
                Rectangle src = {0, 0, portraits[char1].width, portraits[char1].height};
                Rectangle dest = {x + 5, boardTop + 5, cellWidth - 10, boardHeight - 10};
                DrawTexturePro(portraits[char1], src, dest, (Vector2){0}, 0.0f, WHITE);
            } else if (pos2 == i + 1 && char2 >= 0 && char2 < 10) {
                Rectangle src = {0, 0, portraits[char2].width, portraits[char2].height};
                Rectangle dest = {x + 5, boardTop + 5, cellWidth - 10, boardHeight - 10};
                DrawTexturePro(portraits[char2], src, dest, (Vector2){0}, 0.0f, WHITE);
            }
        }

        // 下排：Coordinate 座標格子
        for (int i = 0; i < 9; i++) {
            float x = i * cellWidth;
            Rectangle cell = {x, boardTop + boardHeight, cellWidth, coordHeight};
            DrawRectangleLinesEx(cell, 1, WHITE);

            int fontSize = coordHeight * 0.5f;
            DrawText(TextFormat("%d", i + 1), x + cellWidth / 2 - MeasureText(TextFormat("%d", i + 1), fontSize) / 2,
                     boardTop + boardHeight + coordHeight / 2 - fontSize / 2, fontSize, LIGHTGRAY);
        }

        EndDrawing();
    }

    for (int i = 0; i < 10; i++) {
        UnloadTexture(portraits[i]);
    }

    CloseWindow();
    return NULL;
}

void start_board_gui() {
    pthread_create(&render_thread, NULL, board_gui_loop, NULL);
}

