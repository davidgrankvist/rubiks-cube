#include "cube.h"
#include "render.h"

#define CUBE_SIDE 3
// cube half side
#define CHS 1.5f
#define CUBIE_SIDE 1
#define CUBIE_HALF_SIDE 0.5f

Vector3 center = { 0.0f, 0.0f, 0.0f };

// red side
Vector3 corner_front_top_left = { -CHS, CHS, CHS };
Vector3 corner_front_top_right = { CHS, CHS, CHS };
Vector3 corner_front_bottom_left = { -CHS, -CHS, CHS };
Vector3 corner_front_bottom_right = { CHS, -CHS, CHS };

// orange side
Vector3 corner_back_top_left = { -CHS, CHS, -CHS};
Vector3 corner_back_top_right = { CHS, CHS, -CHS };
Vector3 corner_back_bottom_left = { -CHS, -CHS, -CHS };
Vector3 corner_back_bottom_right = { CHS, -CHS, -CHS };

/*
 * Pass in indices (0, 0, 0) to (2, 2, 2) and displace
 * to get actual cubie centers.
 */
static Vector3 displace_cubie(int x, int y, int z) {
    Vector3 pos;
    pos.x = x + corner_front_top_left.x + CUBIE_HALF_SIDE;
    pos.y = y - corner_front_top_left.y + CUBIE_HALF_SIDE;
    pos.z = z - corner_front_top_left.z + CUBIE_HALF_SIDE;
    return pos;
}

void init_cube(Cube* cube) {
    int icubie = 0;
    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                Cubie cubie;
                cubie.center = displace_cubie(x, y, z);
                cubie.sides = BIT_RED;

                cube->cubies[icubie++] = cubie;
            }
        }
    }
}

void update_cube(Cube* cube) {
    // reference corners
    DrawCube(corner_front_top_left, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_front_top_right, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_front_bottom_left, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_front_bottom_right, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_back_top_left, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_back_top_right, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_back_bottom_left, 0.1, 0.1, 0.1, BLUE);
    DrawCube(corner_back_bottom_right, 0.1, 0.1, 0.1, BLUE);

    for (int i = 0; i < NUM_CUBIES; i++) {
        DrawCube(cube->cubies[i].center, 0.1, 0.1, 0.1, GREEN);
    }
}
