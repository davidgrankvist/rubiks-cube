#ifndef cube_h
#define cube_h

#include "common.h"
#include "render.h"

/*
 * Folded out sides for reference.
 *
 *        white
 * green  red     blue  orange
 *        yellow
 */

#define SINGLE_BIT(b) (1 << b)
#define HAS_BIT(n, b) (n & SINGLE_BIT(b))
#define BIT_AT(n, b) !!(n & SINGLE_BIT(b))
#define SET_SINGLE_BIT(v, b) (v << b)

#define SIDE_WHITE 0
#define SIDE_GREEN 1
#define SIDE_RED 2
#define SIDE_BLUE 3
#define SIDE_ORANGE 4
#define SIDE_YELLOW 5

#define IS_WHITE(n) HAS_BIT(n, SIDE_WHITE)
#define IS_GREEN(n) HAS_BIT(n, SIDE_GREEN)
#define IS_RED(n) HAS_BIT(n, SIDE_RED)
#define IS_BLUE(n) HAS_BIT(n, SIDE_BLUE)
#define IS_ORANGE(n) HAS_BIT(n, SIDE_ORANGE)
#define IS_YELLOW(n) HAS_BIT(n, SIDE_YELLOW)

#define BIT_WHITE SINGLE_BIT(SIDE_WHITE)
#define BIT_GREEN SINGLE_BIT(SIDE_GREEN)
#define BIT_RED SINGLE_BIT(SIDE_RED)
#define BIT_BLUE SINGLE_BIT(SIDE_BLUE)
#define BIT_ORANGE SINGLE_BIT(SIDE_ORANGE)
#define BIT_YELLOW SINGLE_BIT(SIDE_YELLOW)

// use similar bits for current orientation
#define SIDE_TOP 0
#define SIDE_LEFT 1
#define SIDE_FRONT 2
#define SIDE_RIGHT 3
#define SIDE_BACK 4
#define SIDE_BOTTOM 5
#define SIDE_NONE 6

#define IS_TOP(n) HAS_BIT(n, SIDE_WHITE)
#define IS_LEFT(n) HAS_BIT(n, SIDE_GREEN)
#define IS_FRONT(n) HAS_BIT(n, SIDE_RED)
#define IS_RIGHT(n) HAS_BIT(n, SIDE_BLUE)
#define IS_BACK(n) HAS_BIT(n, SIDE_ORANGE)
#define IS_BOTTOM(n) HAS_BIT(n, SIDE_YELLOW)

#define BIT_TOP SINGLE_BIT(SIDE_WHITE)
#define BIT_LEFT SINGLE_BIT(SIDE_GREEN)
#define BIT_FRONT SINGLE_BIT(SIDE_RED)
#define BIT_RIGHT SINGLE_BIT(SIDE_BLUE)
#define BIT_BACK SINGLE_BIT(SIDE_ORANGE)
#define BIT_BOTTOM SINGLE_BIT(SIDE_YELLOW)

// actually 26, but 3x3x3 makes looping easier
#define NUM_CUBIES 27
#define NUM_SIDES 6
#define MAX_NUM_QUADS 3

typedef struct {
    // logical state
    uint8_t sides;
    uint8_t color[NUM_SIDES];

    // rendering state
    Vector3 center;
    uint8_t num_quads;
    Quad quads[MAX_NUM_QUADS];
} Cubie;

typedef struct {
    Vector3 normal;
} Side;

#define ROTATION_SPEED 2

typedef struct {
    Cubie cubies[NUM_CUBIES];
    Side sides[NUM_SIDES];

    // render state for rotation
    float angle;
    float angle_target;
    float angle_sign;
    Matrix rotation;
    uint8_t rotation_target;
    bool is_rotating;
} Cube;

void init_cube(Cube* cube);
void update_cube(Cube* cube);

#endif
