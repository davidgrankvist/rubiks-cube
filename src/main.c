#include "raylib.h"
#include "cube.h"


int main() {
    int screen_width = 1200;
    int screen_height = 900;

    InitWindow(screen_width, screen_height, "hello cube");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Cube cube;
    init_cube(&cube);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        //UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

                update_cube(&cube);

                DrawGrid(10, 1.0f);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
