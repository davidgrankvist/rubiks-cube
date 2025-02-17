#ifndef cube_h
#define cube_h

#include <stdint.h>

typedef struct {
    Vector3 top_left;
    Vector3 bottom_left;
    Vector3 bottom_right;
    Vector3 top_right;
    Color color;
} Quad;

#endif
