#include "raylib.h"

int main() {
    int screen_width = 800;
    int screen_height = 450;

    InitWindow(screen_width, screen_height, "Hello Raylib!");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
