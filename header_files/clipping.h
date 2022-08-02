#ifndef _CLIPPING_H
#define _CLIPPING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

void clipp(BackFace *bf);
Vector plane_intersect(Vector plane_n, Vector plane_p, Vector line_start, Vector line_end);
float dist(Vector plane_p, Vector plane_n, Vector v);
int clipp_triangle(Vector plane_p, Vector plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2);

#endif /* _CLIPPING_H */

