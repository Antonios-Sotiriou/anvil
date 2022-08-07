#ifndef _TEST_CUBE_H
#define _TEST_CUBE_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#define cube_back    0.25
#define cube_front   0.0
#define cube_size    0.25

typedef struct {
    Triangle t[12];
    int indexes;
} Shape;

void cube_create(Mesh *c);

#endif /* _TEST_CUBE_H */