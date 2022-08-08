#include "header_files/test_shape.h"

void shape_create(Mesh *c) {

    c->t = malloc(sizeof(Triangle) * 12);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for test Shape struct. shape_create() -- malloc().\n");

    Shape shape = {
        { 
            { {{ 0.00, 0.00, shape_front, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }}, .color = 0xda29f3 },    /* Front Up */
            { {{ 0.00, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }}, .color = 0xda29f3 },      /* Front Down */

            { {{ shape_size, 0.00, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }}, .color = 0xda29f3 },    /* Back Up */
            { {{ shape_size, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, 0.00, shape_back, 1.0 }}, .color = 0xda29f3 },     /* Back Down */

            { {{ shape_size, 0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }}, .color = 0xda29f3 },     /* West Up */
            { {{ shape_size,  0.00, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }}, .color = 0xda29f3 },       /* East Down */

            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }}, .color = 0xda29f3 },    /* East Up */
            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, -shape_size, shape_front, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }}, .color = 0xda29f3 },     /* East Down */

            { {{ 0.00, -shape_size, shape_front, 1.0 }, { 0.00, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }}, .color = 0xda29f3 },   /* North Up */
            { {{ 0.00, -shape_size, shape_front, 1.0 }, { shape_size, -shape_size, shape_back, 1.0 }, { shape_size, -shape_size, shape_front, 1.0 }}, .color = 0xda29f3 } ,   /* North Down */

            { {{ 0.00, 0.00, shape_back, 1.0 }, { 0.00, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }}, .color = 0xda29f3 },       /* South Up */
            { {{ 0.00, 0.00, shape_back, 1.0 }, { shape_size, 0.00, shape_front, 1.0 }, { shape_size, 0.00, shape_back, 1.0 }}, .color = 0xda29f3 },     /* South Down */
        },
        .indexes = 12
    };

    for (int i = 0; i < shape.indexes; i++) {
        c->t[i] = shape.t[i];
    }
    c->indexes = shape.indexes;
}

