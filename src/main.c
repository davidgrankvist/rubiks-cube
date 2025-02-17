#include "raylib.h"
#include "cube.h"

void draw_quad(Quad* quad) {
    DrawTriangle3D(quad->top_left, quad->bottom_left, quad->bottom_right, quad->color);
    DrawTriangle3D(quad->bottom_right, quad->top_right, quad->top_left, quad->color);
}

int main() {
    int screen_width = 1200;
    int screen_height = 900;

    InitWindow(screen_width, screen_height, "Hello Raylib!");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Quad quad;
    quad.top_left = (Vector3){ -2.0f, 2.0f, 0.0f };
    quad.bottom_left = (Vector3){ -2.0f, 0.0f, 0.0f };
    quad.bottom_right = (Vector3){ 0.0f, 0.0f, 0.0f };
    quad.top_right = (Vector3){ 0.0f, 2.0f, 0.0f };
    quad.color = RED;

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        //UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                draw_quad(&quad);

                DrawGrid(10, 1.0f);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
