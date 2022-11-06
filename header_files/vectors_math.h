#ifndef _VECTORS_MATH_H
#define _VECTORS_MATH_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif
#ifndef _MATH_H
    #include "math.h"
#endif

/* 3D graphics Vector computation functions */
const float depth(const Triangle t);
Mesh sort_triangles(Mesh *c);
const float len_vec(const Vector v);
const Vector norm_vec(const Vector v);
const Vector multiply_vec(const Vector v1, const float num);
const Vector divide_vec(const Vector v1, const float num);
const Vector add_vecs(const Vector v1, const Vector v2);
const Vector sub_vecs(const Vector v1, const Vector v2);
const Vector cross_product(const Vector v1, const Vector v2);
const float dot_product(const Vector v1, const Vector v2);
const Vector triangle_cp(const Triangle t);
const int winding(const Triangle t);
const float clippedwinding(const Triangle t);

#endif /* _VECTORS_MATH_H */

