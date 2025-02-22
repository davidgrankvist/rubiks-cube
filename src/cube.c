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

    // red = front
    Quad qr;
    qr.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
    qr.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
    qr.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
    qr.top_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };

    qr.is_c = false;
    qr.color = IS_RED(cubie->sides) ? RED : BLACK;

    cubie->quads[iquad++] = qr;

    // orange = back
    Quad qo;
    qo.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
    qo.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
    qo.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
    qo.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

    qo.is_c = true;
    qo.color = IS_ORANGE(cubie->sides) ? ORANGE : BLACK;

    cubie->quads[iquad++] = qo;

    // white = top
    Quad qw;
    qw.top_left = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };
    qw.bottom_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
    qw.bottom_right = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
    qw.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

    qw.is_c = false;
    qw.color = IS_WHITE(cubie->sides) ? WHITE : BLACK;

    cubie->quads[iquad++] = qw;

    // yellow = bottom
    Quad qy;
    qy.top_left = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
    qy.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
    qy.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
    qy.top_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };

    qy.is_c = true;
    qy.color = IS_YELLOW(cubie->sides) ? YELLOW : BLACK;

    cubie->quads[iquad++] = qy;

    // green = left
    Quad qg;
    qg.top_left = (Vector3){ x - CUIHS, y + CUIHS, z + CUIHS };
    qg.bottom_left = (Vector3){ x - CUIHS, y - CUIHS, z + CUIHS };
    qg.bottom_right = (Vector3){ x - CUIHS, y - CUIHS, z - CUIHS };
    qg.top_right = (Vector3){ x - CUIHS, y + CUIHS, z - CUIHS };

    qg.is_c = true;
    qg.color = IS_GREEN(cubie->sides) ? GREEN : BLACK;

    cubie->quads[iquad++] = qg;

    // blue = right
    Quad qb;
    qb.top_left = (Vector3){ x + CUIHS, y + CUIHS, z + CUIHS };
    qb.bottom_left = (Vector3){ x + CUIHS, y - CUIHS, z + CUIHS };
    qb.bottom_right = (Vector3){ x + CUIHS, y - CUIHS, z - CUIHS };
    qb.top_right = (Vector3){ x + CUIHS, y + CUIHS, z - CUIHS };

    qb.is_c = false;
    qb.color = IS_BLUE(cubie->sides) ? BLUE : BLACK;

    cubie->quads[iquad++] = qb;

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
    cube->sides[SIDE_LEFT].normal = (Vector3) { -1.0f, 0.0f, 0.0f }; 
    cube->sides[SIDE_FRONT].normal = (Vector3) { 0.0f, 0.0f, 1.0f }; 
    cube->sides[SIDE_RIGHT].normal = (Vector3) { 1.0f, 0.0f, 0.0f }; 
    cube->sides[SIDE_BACK].normal = (Vector3) { 0.0f, 0.0f, -1.0f }; 
    cube->sides[SIDE_BOTTOM].normal = (Vector3) { 0.0f, -1.0f, 0.0f }; 
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
    return fabs(cube->angle - cube->angle_target) < 0.1f;
}

static uint8_t rotate_cubie_sides(uint8_t prev_sides, uint8_t target, bool reverse) {
    uint8_t sides = 0;

    uint8_t right = BIT_AT(prev_sides, SIDE_RIGHT);
    uint8_t bottom = BIT_AT(prev_sides, SIDE_BOTTOM);
    uint8_t left = BIT_AT(prev_sides, SIDE_LEFT);
    uint8_t top = BIT_AT(prev_sides, SIDE_TOP);
    uint8_t front = BIT_AT(prev_sides, SIDE_FRONT);
    uint8_t back = BIT_AT(prev_sides, SIDE_BACK);

    switch(target) {
        case SIDE_TOP: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   front -> right
                 *   left -> front
                 *   back -> left
                 *   right -> back
                 */
                right = BIT_AT(prev_sides, SIDE_FRONT);
                front = BIT_AT(prev_sides, SIDE_LEFT);
                left = BIT_AT(prev_sides, SIDE_BACK);
                back = BIT_AT(prev_sides, SIDE_RIGHT);
            } else {
                /*
                 * Clockwise:
                 *   front -> left
                 *   left -> back
                 *   back -> right
                 *   right -> front
                 */
                left = BIT_AT(prev_sides, SIDE_FRONT);
                back = BIT_AT(prev_sides, SIDE_LEFT);
                right = BIT_AT(prev_sides, SIDE_BACK);
                front = BIT_AT(prev_sides, SIDE_RIGHT);
            }
            
            break;
        }
        case SIDE_LEFT: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   front -> top
                 *   top -> back
                 *   back -> bottom
                 *   bottom -> front
                 */
                top = BIT_AT(prev_sides, SIDE_FRONT);
                back = BIT_AT(prev_sides, SIDE_TOP);
                bottom = BIT_AT(prev_sides, SIDE_BACK);
                front = BIT_AT(prev_sides, SIDE_BOTTOM);
            } else {
                /*
                 * Clockwise:
                 *   front -> bottom
                 *   top -> front
                 *   back -> top
                 *   bottom -> back
                 */
                bottom = BIT_AT(prev_sides, SIDE_FRONT);
                front = BIT_AT(prev_sides, SIDE_TOP);
                top = BIT_AT(prev_sides, SIDE_BACK);
                back = BIT_AT(prev_sides, SIDE_BOTTOM);
            }
            
            break;
        }
        case SIDE_FRONT: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   top -> left
                 *   right -> top
                 *   bottom -> right
                 *   left -> bottom
                 */
                left = BIT_AT(prev_sides, SIDE_TOP);
                top = BIT_AT(prev_sides, SIDE_RIGHT);
                right = BIT_AT(prev_sides, SIDE_BOTTOM);
                bottom = BIT_AT(prev_sides, SIDE_LEFT);
            } else {
                /*
                 * Clockwise:
                 *   top -> right
                 *   right -> bottom
                 *   bottom -> left
                 *   left -> top
                 */
                right = BIT_AT(prev_sides, SIDE_TOP);
                bottom = BIT_AT(prev_sides, SIDE_RIGHT);
                left = BIT_AT(prev_sides, SIDE_BOTTOM);
                top = BIT_AT(prev_sides, SIDE_LEFT);
            }
            
            break;
        }
        case SIDE_RIGHT: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   top -> front
                 *   back -> top
                 *   bottom -> back
                 *   front -> bottom
                 */
                front = BIT_AT(prev_sides, SIDE_TOP);
                top = BIT_AT(prev_sides, SIDE_BACK);
                back = BIT_AT(prev_sides, SIDE_BOTTOM);
                bottom = BIT_AT(prev_sides, SIDE_FRONT);
            } else {
                /*
                 * Clockwise:
                 *   top -> back
                 *   back -> bottom
                 *   bottom -> front
                 *   front -> top
                 */
                back = BIT_AT(prev_sides, SIDE_TOP);
                bottom = BIT_AT(prev_sides, SIDE_BACK);
                front = BIT_AT(prev_sides, SIDE_BOTTOM);
                top = BIT_AT(prev_sides, SIDE_FRONT);
            }
            
            break;
        }
        case SIDE_BACK: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   top -> right
                 *   left -> top
                 *   bottom -> left
                 *   right -> bottom
                 */
                right = BIT_AT(prev_sides, SIDE_TOP);
                top = BIT_AT(prev_sides, SIDE_LEFT);
                left = BIT_AT(prev_sides, SIDE_BOTTOM);
                bottom = BIT_AT(prev_sides, SIDE_RIGHT);
            } else {
                /*
                 * Clockwise:
                 *   top -> left
                 *   left -> bottom
                 *   bottom -> right
                 *   right -> top
                 */
                left = BIT_AT(prev_sides, SIDE_TOP);
                bottom = BIT_AT(prev_sides, SIDE_LEFT);
                right = BIT_AT(prev_sides, SIDE_BOTTOM);
                top = BIT_AT(prev_sides, SIDE_RIGHT);
            }
            
            break;
        }
        case SIDE_BOTTOM: {
            if (reverse) {
                /*
                 * Counter clockwise:
                 *   left -> back
                 *   front -> left
                 *   right -> front
                 *   back -> right
                 */
                back = BIT_AT(prev_sides, SIDE_LEFT);
                left = BIT_AT(prev_sides, SIDE_FRONT);
                front = BIT_AT(prev_sides, SIDE_RIGHT);
                right = BIT_AT(prev_sides, SIDE_BACK);
            } else {
                /*
                 * Clockwise:
                 *   left -> front
                 *   front -> right
                 *   right -> back
                 *   back -> left
                 */
                front = BIT_AT(prev_sides, SIDE_LEFT);
                right = BIT_AT(prev_sides, SIDE_FRONT);
                back = BIT_AT(prev_sides, SIDE_RIGHT);
                left = BIT_AT(prev_sides, SIDE_BACK);
            }
            
            break;
        }
    }

    sides = SET_SINGLE_BIT(right, SIDE_RIGHT)
        | SET_SINGLE_BIT(bottom, SIDE_BOTTOM)
        | SET_SINGLE_BIT(left, SIDE_LEFT)
        | SET_SINGLE_BIT(top, SIDE_TOP)
        | SET_SINGLE_BIT(front, SIDE_FRONT)
        | SET_SINGLE_BIT(back, SIDE_BACK);
            
    return sides;
}

// after the rotation animation has finished, make sure current sides reflect the rotation
static void update_current_sides(Cube* cube) {
    for (int i = 0; i < NUM_CUBIES; i++) {
        Cubie* cubie = &cube->cubies[i];
        if (HAS_BIT(cubie->sides, cube->rotation_target)) {
            uint8_t sides = rotate_cubie_sides(cubie->sides, cube->rotation_target, cube->angle_sign < 0);
            cubie->sides = sides;
        }
    }
}

static void check_rotation(Cube* cube) {
    if (!cube->is_rotating) {
        return;
    }

    if (rotation_is_done(cube)) {
        cube->is_rotating = false;
        update_current_sides(cube);
        cube->rotation_target = SIDE_NONE;
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
