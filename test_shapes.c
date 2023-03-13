#include "header_files/test_shapes.h"

const void cube_create(Mesh *c) {

    int indexes = 12;
    c->t = malloc(sizeof(Triangle) * indexes);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for test Shape struct. cube_create() -- malloc().\n");

    Triangle t[12] = {
            { {{ 0.00, 0.00, shape_front, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }}, /* Front Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ 0.00, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }}, /* Front Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
            { {{ shape_size, 0.00, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }}, /* Back Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ shape_size, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, 0.00, shape_back, 1.0 }}, /* Back Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
            { {{ shape_size, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }}, /* East Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ shape_size,  0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }}, /* East Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }}, /* West Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }}, /* West Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
            { {{ 0.00, -shape_size, shape_front, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }}, /* North Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }}, /* North Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }}, /* South Up */
              {{0.0, 1.0, 1.0} , {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}
            },
            { {{ 0.00, 0.00, shape_back, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }}, /* South Down */
              {{0.0, 1.0, 1.0} , {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}}
            },
    };
    memcpy(c->t, t, sizeof(Triangle) * indexes);
    c->indexes = indexes;
}

void triangle_create(Mesh *c) {

    int indexes = 2;
    c->t = malloc(sizeof(Triangle) * indexes);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for test Shape struct. cube_create() -- malloc().\n");

    Triangle t[2] = {
            { {{ -1.00, 1.00, 0.00, 1.0 }, { -1.00, -1.00, 0.00, 1.0 }, { 1.00, -1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} },  // Textures test
            { {{ -1.00, 1.00, 0.00, 1.0 }, { 1.00, -1.00, 0.00, 1.0 }, { 1.00, 1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}} },  // Textures test
            // { {{ -1.00, 0.00, 0.00, 1.0 }, { 0.00, -1.00, 0.00, 1.0 }, { 0.00, 1.00, 0.00, 1.0 }}, {{ 0.0, 0.5, 1.0 }, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}} }, // general
            // { {{ -0.01, 0.00, 0.00, 1.0 }, { 0.00, -0.01, 0.01, 1.0 }, { 0.01, 0.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} }, // buttom flat
            // { {{ -1.00, 0.00, 0.00, 1.0 }, { 1.00, 0.00, 0.00, 1.0 }, { 0.00, 1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} },    // top flat
            // { {{ -1.00, -0.5, 0.00, 1.0 }, { 0.5, -0.2, 0.00, 1.0 }, { 0.1, 0.6, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} },     // general
            // { {{ -10.00, 0.00, 0.00, 1.0 }, { 10.00, -10.00, 0.00, 1.0 }, { 10.00, 10.00, 0.00, 1.0 }} },
            // { {{ 0.00, 0.00, 1.00, 1.0 }, { 0.00, 0.00, 0.00, 1.0 }, { 0.00, 1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} },  // Camera test
            // { {{ 0.00, 0.00, 1.00, 1.0 }, { 1.00, 0.00, 0.00, 1.0 }, { 0.00, 0.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}} },  // Camera test
    };
    memcpy(c->t, t, sizeof(Triangle) * indexes);
    c->indexes = indexes;
}

