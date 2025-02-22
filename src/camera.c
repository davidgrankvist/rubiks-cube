#include "camera.h"

float distance = 10.f;
float rotation_speed = 1.0f;

float absolute_pitch = 0.0f;

void init_camera(Camera3D* camera) {
    camera->position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera->fovy = 45.0f;
    camera->projection = CAMERA_PERSPECTIVE;

    Vector3 forward = Vector3Subtract(camera->target, camera->position);
    float pitch = atan2f(forward.y, sqrtf(forward.x * forward.x + forward.z * forward.z));
    absolute_pitch = RAD2DEG * -pitch;
}

void update_camera(Camera3D* camera) {
    float yaw = 0.0f;
    float pitch = 0.0f;
    if (IsKeyDown(KEY_LEFT)) {
        yaw += rotation_speed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        yaw += -rotation_speed;
    }
    if (IsKeyDown(KEY_UP) && absolute_pitch + rotation_speed < 90) {
        pitch += rotation_speed;
        absolute_pitch += pitch;
    }
    if (IsKeyDown(KEY_DOWN) && absolute_pitch - rotation_speed > -90) {
        pitch += -rotation_speed;
        absolute_pitch += pitch;
    }
    if (fabs(yaw) > 0 || fabs(pitch) > 0) {
        // yaw rotation
        Vector3 pos = camera->position; 
        Matrix yaw_rot = MatrixRotateY(DEG2RAD * -yaw);
        Vector3 pos_yaw_rot = Vector3Transform(pos, yaw_rot);

        // pitch rotation
        Vector3 forward = Vector3Normalize(Vector3Subtract(camera->target, camera->position));
        Vector3 up = (Vector3){0.0f, 1.0f, 0.0f};
        Vector3 local_x = Vector3Normalize(Vector3CrossProduct(up, forward));
        Matrix pitch_rot = MatrixRotate(local_x, DEG2RAD * pitch);
Vector3 pos_pitch_rot = Vector3Transform(pos_yaw_rot, pitch_rot);
        
        camera->position = pos_pitch_rot;

    }
}
