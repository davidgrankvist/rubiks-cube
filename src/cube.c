#include "cube.h"

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

static void init_quads(Cubie* cubie) {
    int iquad = 0;

    float x = cubie->center.x;
    float y = cubie->center.y;
    float z = cubie->center.z;

    if (IS_RED(cubie->sides)) {
        // red = front
        Quad quad;
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };

        quad.is_c = false;
        quad.color = RED;
        
        cubie->quads[iquad++] = quad;
    }

    if (IS_ORANGE(cubie->sides)) {
        // orange = back
        Quad quad;
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.is_c = true;
        quad.color = ORANGE;

        cubie->quads[iquad++] = quad;
    }

    if (IS_WHITE(cubie->sides)) {
        // white = top
        Quad quad;
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.is_c = false;
        quad.color = WHITE;

        cubie->quads[iquad++] = quad;
    }

    if (IS_YELLOW(cubie->sides)) {
        // yellow = bottom
        Quad quad;
        quad.top_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };

        quad.is_c = true;
        quad.color = YELLOW;

        cubie->quads[iquad++] = quad;
    }

    if (IS_GREEN(cubie->sides)) {
        // green = left
        Quad quad;
        quad.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };

        quad.is_c = true;
        quad.color = GREEN;

        cubie->quads[iquad++] = quad;
    }

    if (IS_BLUE(cubie->sides)) {
        // blue = right
        Quad quad;
        quad.top_left = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
        quad.bottom_left = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
        quad.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
        quad.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

        quad.is_c = false;
        quad.color = BLUE;

        cubie->quads[iquad++] = quad;
    }

    cubie->num_quads = iquad;
}

static void init_cubies(Cube* cube) {
    int icubie = 0;
    for (int z = 0; z < 3; z++) {
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                Cubie cubie;
                cubie.center = displace_cubie(x, y, z);
                cubie.sides = get_side_colors(x, y, z);
                init_quads(&cubie);

                cube->cubies[icubie++] = cubie;
            }
        }
    }
}

void init_cube(Cube* cube) {
    init_cubies(cube);
    // init_sides(cube);
}

static void rotate_quad(Quad* quad, Matrix* rotation) {
    quad->top_left = Vector3Transform(quad->top_left, *rotation);
    quad->top_right = Vector3Transform(quad->top_right, *rotation);
    quad->bottom_left = Vector3Transform(quad->bottom_left, *rotation);
    quad->bottom_right = Vector3Transform(quad->bottom_right, *rotation);
}

static void update_cubie(Cubie* cubie, Matrix* rotation) {
    for (int i = 0; i < cubie->num_quads; i++) {
        Quad* quad = &cubie->quads[i];
        if (IS_RED(cubie->sides)) {
            rotate_quad(quad, rotation);
        }
        draw_quad(quad);
    }
}

void update_cube(Cube* cube) {
    Matrix rotation = MatrixRotateZ(DEG2RAD * 1);

    rlBegin(RL_TRIANGLES);
    for (int i = 0; i < NUM_CUBIES; i++) {
        Cubie* cubie = &cube->cubies[i];
        update_cubie(cubie, &rotation);
    }
    rlEnd();
}
