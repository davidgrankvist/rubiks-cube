#include "raylib.h"
#include "render.h"

void draw_quad(Quad* quad) {
    DrawTriangle3D(quad->top_left, quad->bottom_left, quad->bottom_right, quad->color);
    DrawTriangle3D(quad->bottom_right, quad->top_right, quad->top_left, quad->color);
}

void draw_quad_rev(Quad* quad) {
    DrawTriangle3D(quad->top_left, quad->top_right, quad->bottom_right, quad->color);
    DrawTriangle3D(quad->bottom_right, quad->bottom_left, quad->top_left, quad->color);
}
