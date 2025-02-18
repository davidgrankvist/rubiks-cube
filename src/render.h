#ifndef render_h
#define render_h

#include "cube.h"

typedef struct {
    Vector3 top_left;
    Vector3 bottom_left;
    Vector3 bottom_right;
    Vector3 top_right;
    Color color;
} Quad;

// counterclockwise
void draw_quad(Quad* quad);
// clockwise
void draw_quad_rev(Quad* quad);

#endif
