#include "cube.h"
#include "render.h"

#define CUBE_SIDE 3
// cube half side
#define CHS 1.5f
#define CUBIE_SIDE 1
#define CUBIE_HALF_SIDE 0.5f
#define CUIHS CUBIE_HALF_SIDE

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

static uint8_t get_side_colors(int x, int y, int z) {
    uint8_t sides = 0;

    // front / back
    if (z == 0) {
        sides |= BIT_ORANGE; 
    } else if (z == 2) {
        sides |= BIT_RED;
    }

    // top / bottom
    if (y == 0) {
        sides |= BIT_YELLOW;
    } else if (y == 2) {
        sides |= BIT_WHITE; 
    }

    // left / right
    if (x == 0) {
        sides |= BIT_GREEN;     
    } else if (x == 2) {
        sides |= BIT_BLUE;
    }

    return sides;
}

void init_cube(Cube* cube) {
    int icubie = 0;
    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                Cubie cubie;
                cubie.center = displace_cubie(x, y, z);
                cubie.sides = get_side_colors(x, y, z);

                cube->cubies[icubie++] = cubie;
            }
        }
    }
}

static void draw_cubie(Cubie* cubie) {
    Quad quad;

    float x = cubie->center.x;
    float y = cubie->center.y;
    float z = cubie->center.z;

    if (IS_RED(cubie->sides)) {
        // red = front
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };

        quad.color = RED;
        draw_quad(&quad);
    }

    if (IS_ORANGE(cubie->sides)) {
        // orange = back
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.color = ORANGE;
        draw_quad_rev(&quad);
    }

    if (IS_WHITE(cubie->sides)) {
        // white = top
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.color = WHITE;
        draw_quad(&quad);
    }

    if (IS_YELLOW(cubie->sides)) {
        // white = bottom
        quad.top_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };

        quad.color = YELLOW;
        draw_quad_rev(&quad);
    }

    if (IS_GREEN(cubie->sides)) {
        // green = left
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };

        quad.color = GREEN;
        draw_quad_rev(&quad);
    }

    if (IS_BLUE(cubie->sides)) {
        // blue = right
        quad.top_left = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.color = BLUE;
        draw_quad(&quad);
    }

    //DrawCube(cubie->center, 0.1, 0.1, 0.1, BLACK);
}

void update_cube(Cube* cube) {
    //DrawCube(corner_front_top_left, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_front_top_right, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_front_bottom_left, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_front_bottom_right, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_back_top_left, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_back_top_right, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_back_bottom_left, 0.1, 0.1, 0.1, BLUE);
    //DrawCube(corner_back_bottom_right, 0.1, 0.1, 0.1, BLUE);

    for (int i = 0; i < NUM_CUBIES; i++) {
        draw_cubie(&cube->cubies[i]);
    }
}
