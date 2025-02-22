#include "cube.h"
#include "camera.h"

int main() {
    int screen_width = 1200;
    int screen_height = 900;

    InitWindow(screen_width, screen_height, "hello cube");

    Camera3D camera = { 0 };
    init_camera(&camera);

    Cube cube;
    init_cube(&cube);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        update_camera(&camera);

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            BeginMode3D(camera);
                update_cube(&cube);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
