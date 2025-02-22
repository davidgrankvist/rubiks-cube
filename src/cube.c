#include "cube.h"
#include "math.h"

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
                // before any rotation is applied, front = red and so on
                cubie.sides = get_side_colors(x, y, z);
                init_quads(&cubie);

                cube->cubies[icubie++] = cubie;
            }
        }
    }
}

static void init_sides(Cube* cube) {
    cube->sides[SIDE_TOP].normal = (Vector3) { 0.0f, 1.0f, 0.0f }; 
    cube->sides[SIDE_LEFT].normal = (Vector3) { 1.0f, 0.0f, 0.0f }; 
    cube->sides[SIDE_FRONT].normal = (Vector3) { 0.0f, 0.0f, 1.0f }; 
    cube->sides[SIDE_RIGHT].normal = (Vector3) { 1.0f, 0.0f, 0.0f }; 
    cube->sides[SIDE_BACK].normal = (Vector3) { 0.0f, 0.0f, 1.0f }; 
    cube->sides[SIDE_BOTTOM].normal = (Vector3) { 0.0f, 1.0f, 0.0f }; 
}

void init_cube(Cube* cube) {
    init_cubies(cube);
    init_sides(cube);
}

static void rotate_quad(Quad* quad, Matrix* rotation) {
    quad->top_left = Vector3Transform(quad->top_left, *rotation);
    quad->top_right = Vector3Transform(quad->top_right, *rotation);
    quad->bottom_left = Vector3Transform(quad->bottom_left, *rotation);
    quad->bottom_right = Vector3Transform(quad->bottom_right, *rotation);
}

static void update_cubie(Cubie* cubie, Matrix* rotation, uint8_t rotation_target) {
    for (int i = 0; i < cubie->num_quads; i++) {
        Quad* quad = &cubie->quads[i];
        if (HAS_BIT(cubie->sides, rotation_target)) {
            rotate_quad(quad, rotation);
        }
        draw_quad(quad);
    }
}

typedef struct {
    uint8_t target; 
    float sign;
    bool did_start;
} SideRotation;

static void setup_side_rotation(SideRotation* side_rotation, uint8_t target, bool reverse) {
    side_rotation->did_start = true;
    side_rotation->target = target;
    side_rotation->sign = 1.0f;

    if (reverse) {
        side_rotation->sign *= -1;
    }
}

// map input to a rotation operation
static void check_input(Cube* cube, SideRotation* side_rotation) {
    // wait for animation to finish before rotating again
    if (cube->is_rotating) {
        return;
    }

    side_rotation->did_start = false;
    bool reverse = IsKeyDown(KEY_LEFT_SHIFT);

    if (IsKeyPressed(KEY_W)) {
        setup_side_rotation(side_rotation, SIDE_TOP, reverse);
    }
    if (IsKeyPressed(KEY_A)) {
        setup_side_rotation(side_rotation, SIDE_LEFT, reverse);
    }
    if (IsKeyPressed(KEY_S)) {
        setup_side_rotation(side_rotation, SIDE_FRONT, reverse);
    }
    if (IsKeyPressed(KEY_D)) {
        setup_side_rotation(side_rotation, SIDE_RIGHT, reverse);
    }
    if (IsKeyPressed(KEY_Q)) {
        setup_side_rotation(side_rotation, SIDE_BACK, reverse);
    }
    if (IsKeyPressed(KEY_E)) {
        setup_side_rotation(side_rotation, SIDE_BOTTOM, reverse);
    }
}

static void start_rotation(Cube* cube, SideRotation* side_rotation) {
    if (cube->is_rotating || !side_rotation->did_start) {
        return; 
    }

    cube->is_rotating = true;
    cube->angle = 0;
    cube->angle_sign = side_rotation->sign; 
    cube->angle_target = 90.0f * side_rotation->sign;
    cube->rotation_target = side_rotation->target;
}

static bool rotation_is_done(Cube* cube) {
    return abs(cube->angle - cube->angle_target) < 0.1f;     
}

static void check_rotation(Cube* cube) {
    if (!cube->is_rotating) {
        return;
    }

    if (rotation_is_done(cube)) {
        cube->is_rotating = false;
        cube->rotation_target = SIDE_NONE;
        // TODO: also update current sides of rotated cubies
        return;
    }

    Vector3 normal = cube->sides[cube->rotation_target].normal; 
    cube->rotation = MatrixRotate(normal, DEG2RAD * ROTATION_SPEED * cube->angle_sign * -1);
    cube->angle += (cube->angle_sign) * ROTATION_SPEED;
}

void update_cube(Cube* cube) {
    SideRotation side_rotation;
    check_input(cube, &side_rotation);
    start_rotation(cube, &side_rotation);
    check_rotation(cube);

    Matrix* rotation = &cube->rotation;
    uint8_t rotation_target = cube->rotation_target;

    rlBegin(RL_TRIANGLES);
    for (int i = 0; i < NUM_CUBIES; i++) {
        Cubie* cubie = &cube->cubies[i];
        update_cubie(cubie, rotation, rotation_target);
    }
    rlEnd();
}
