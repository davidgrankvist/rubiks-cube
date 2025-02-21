#include "render.h"

#define rlVertex3fVec(v) rlVertex3f(v.x, v.y, v.z)
#define rlColor3fStruct(s) \
    rlColor3f(s.r / 255.0f, s.g / 255.0f, s.b / 255.0f)

void draw_quad_cc(Quad* quad) {
    rlColor3fStruct(quad->color);

    rlVertex3fVec(quad->top_left);
    rlVertex3fVec(quad->bottom_left);
    rlVertex3fVec(quad->bottom_right);

    rlVertex3fVec(quad->bottom_right);
    rlVertex3fVec(quad->top_right);
    rlVertex3fVec(quad->top_left);
}

void draw_quad_c(Quad* quad) {
    rlColor3fStruct(quad->color);

    rlVertex3fVec(quad->top_left);
    rlVertex3fVec(quad->top_right);
    rlVertex3fVec(quad->bottom_right);

    rlVertex3fVec(quad->bottom_right);
    rlVertex3fVec(quad->bottom_left);
    rlVertex3fVec(quad->top_left);
}

void draw_quad(Quad* quad) {
    if (quad->is_c) {
        draw_quad_c(quad);
    } else {
        draw_quad_cc(quad);
    }
}
