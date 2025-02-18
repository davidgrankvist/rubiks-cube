#ifndef cube_h
#define cube_h

#include <stdint.h>
#include "raylib.h"

/*
 * Folded out sides for reference.
 *
 *        white
 * green  red     blue  orange
 *        yellow
 */

#define SET_BIT(b) (1 << b)
#define HAS_BIT(n, b) (n & SET_BIT(b))

#define SIDE_WHITE 0
#define SIDE_GREEN 1
#define SIDE_RED 2
#define SIDE_BLUE 3
#define SIDE_ORANGE 4
#define SIDE_YELLOW 5

#define BIT_WHITE SET_BIT(SIDE_WHITE)
#define BIT_GREEN SET_BIT(SIDE_GREEN)
#define BIT_RED SET_BIT(SIDE_RED)
#define BIT_BLUE SET_BIT(SIDE_BLUE)
#define BIT_ORANGE SET_BIT(SIDE_ORANGE)
#define BIT_YELLOW SET_BIT(SIDE_YELLOW)

typedef struct {
    // bit flags to indicate which sides the cubie belongs to
    uint8_t sides;
    // cubie reference position to rotate
    Vector3 center;
} Cubie;

typedef struct {
    // current rotation of the side
    float angle;
    // axis to rotate side about
    Vector3 normal;
} Side;

// actually 26, but 3x3x3 makes looping easier
#define NUM_CUBIES 27
#define NUM_SIDES 6

typedef struct {
    Cubie cubies[NUM_CUBIES];
    Side sides[NUM_SIDES];
} Cube;

void init_cube(Cube* cube);
void update_cube(Cube* cube);

#endif
