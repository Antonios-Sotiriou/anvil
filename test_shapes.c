#include "header_files/test_shapes.h"

void cube_create(Mesh *c) {

    c->t = malloc(sizeof(Triangle) * 12);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for test Shape struct. cube_create() -- malloc().\n");

    Shape shape = {
        { 
            { {{ 0.00, 0.00, shape_front, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }} },    /* Front Up */
            { {{ 0.00, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }} },      /* Front Down */

            { {{ shape_size, 0.00, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }} },    /* Back Up */
            { {{ shape_size, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, 0.00, shape_back, 1.0 }} },     /* Back Down */

            { {{ shape_size, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }} },     /* East Up */
            { {{ shape_size,  0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }} },       /* East Down */

            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }} },    /* West Up */
            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }} },     /* West Down */

            { {{ 0.00, -shape_size, shape_front, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }} },   /* North Up */
            { {{ 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }} } ,   /* North Down */

            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }} },       /* South Up */
            { {{ 0.00, 0.00, shape_back, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }} },     /* South Down */
        },
        .indexes = 12
    };

    for (int i = 0; i < shape.indexes; i++) {
        c->t[i] = shape.t[i];
    }
    c->indexes = shape.indexes;
}

void triangle_create(Mesh *c) {

    c->t = malloc(sizeof(Triangle) * 1);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for test Shape struct. cube_create() -- malloc().\n");

    Shape shape = {
        {    
            // { {{ -1.00, 1.00, 0.00, 1.0 }, { -1.00, -1.00, 0.00, 1.0 }, { 1.00, -1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}} },  // Textures test
            // { {{ -1.00, 1.00, 0.00, 1.0 }, { 1.00, -1.00, 0.00, 1.0 }, { 1.00, 1.00, 0.00, 1.0 }}, {{ 0.0, 1.0, 1.0 }, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}} },  // Textures test
            { {{ -1.00, 0.00, 0.00, 1.0 }, { 0.00, -1.00, 0.00, 1.0 }, { 0.00, 1.00, 0.00, 1.0 }} }, // general
            // { {{ -1.00, 0.00, 0.00, 1.0 }, { 0.00, -1.00, 0.00, 1.0 }, { 1.00, 0.00, 0.00, 1.0 }} }, // buttom flat
            // { {{ -1.00, 0.00, 0.00, 1.0 }, { 1.00, 0.00, 0.00, 1.0 }, { 0.00, 1.00, 0.00, 1.0 }} },    // top flat
            // { {{ -1.00, -0.5, 0.00, 1.0 }, { 0.5, -0.2, 0.00, 1.0 }, { 0.1, 0.6, 0.00, 1.0 }} },     // general
            // { {{ -10.00, 0.00, 0.00, 1.0 }, { 10.00, -10.00, 0.00, 1.0 }, { 10.00, 10.00, 0.00, 1.0 }} },
        },
        .indexes = 1
    };

    for (int i = 0; i < shape.indexes; i++) {
        c->t[i] = shape.t[i];
    }
    c->indexes = shape.indexes;
}

