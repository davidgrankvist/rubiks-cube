#ifndef render_h
#define render_h

#include "common.h"

typedef struct {
    Vector3 top_left;
    Vector3 bottom_left;
    Vector3 bottom_right;
    Vector3 top_right;
    Color color;
    bool is_c;
} Quad;

// direction determined by "is_rev"
void draw_quad(Quad* quad);
// counterclockwise
void draw_quad_cc(Quad* quad);
// clockwise
void draw_quad_c(Quad* quad);

#endif
