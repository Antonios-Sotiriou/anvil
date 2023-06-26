#ifndef _TEST_SHAPE_H
#define _TEST_SHAPE_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STRING_H
    #include <string.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#define shape_back    0.25
#define shape_front   0.0
#define shape_size    0.25

const void cube_create(Mesh *c);
void triangle_create(Mesh *c);

#endif /* _TEST_SHAPE_H */


