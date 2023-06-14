#ifndef _CLIPPING_H
#define _CLIPPING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _vectors_mathMATH_H
    #include "vectors_math.h"
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

const Mesh clipp(const Mesh c, Vec4 plane_n, Vec4 plane_p);
const Vec4 plane_intersect(Vec4 plane_n, Vec4 plane_p, Vec4 line_start, Vec4 line_end, float *t);
float dist(Vec4 plane_p, Vec4 plane_n, Vec4 v);
int clipp_triangle(Vec4 plane_p, Vec4 plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2);

#endif /* _CLIPPING_H */

