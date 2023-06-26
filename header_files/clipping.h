#ifndef _CLIPPING_H
#define _CLIPPING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

const Mesh clipp(const Mesh c, vec4 plane_n, vec4 plane_p);
const vec4 plane_intersect(vec4 plane_n, vec4 plane_p, vec4 line_start, vec4 line_end, float *t);
float dist(vec4 plane_p, vec4 plane_n, vec4 v);
int clipp_triangle(vec4 plane_p, vec4 plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2);

#endif /* _CLIPPING_H */


