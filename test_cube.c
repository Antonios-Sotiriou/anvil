#include "header_files/test_cube.h"

Mesh cube_create(void) {

    Mesh obj = { 0 };
    obj.t = malloc(sizeof(Triangle) * 12);

    Shape cube = {
        { 
            { {{ 0.00, 0.00, cube_front, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}, .color = 0xf9d905 },    /* Front Up */
            { {{ 0.00, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }}, .color = 0xf9d905 },      /* Front Down */

            { {{ cube_size, 0.00, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }}, .color = 0xf9d905 },    /* Back Up */
            { {{ cube_size, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, 0.00, cube_back, 1.0 }}, .color = 0xf9d905 },     /* Back Down */

            { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }}, .color = 0xf9d905 },     /* West Up */
            { {{ cube_size,  0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }}, .color = 0xf9d905 },       /* East Down */

            { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }}, .color = 0xf9d905 },    /* East Up */
            { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }}, .color = 0xf9d905 },     /* East Down */

            { {{ 0.00, -cube_size, cube_front, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }}, .color = 0xf9d905 },   /* North Up */
            { {{ 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}, .color = 0xf9d905 } ,   /* North Down */

            { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }}, .color = 0xf9d905 },       /* South Up */
            { {{ 0.00, 0.00, cube_back, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }}, .color = 0xf9d905 },     /* South Down */
        },
        .indexes = 12
    };

    for (int i = 0; i < cube.indexes; i++) {
        obj.t[i] = cube.t[i];
    }

    obj.indexes = cube.indexes;

    return obj;
}

