#ifndef _VECTORS_MATH_H
#define _VECTORS_MATH_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif
#ifndef _MATH_H
    #include "math.h"
#endif

/* 3D graphics Vec4 computation functions */
const float depth(const Triangle t);
Mesh sort_triangles(Mesh *c);
const float len_vec(const Vec4 v);
const Vec4 norm_vec(const Vec4 v);
const Vec4 multiply_vec(const Vec4 v1, const float num);
const Vec4 divide_vec(const Vec4 v1, const float num);
const Vec4 add_vecs(const Vec4 v1, const Vec4 v2);
const Vec4 sub_vecs(const Vec4 v1, const Vec4 v2);
const Vec4 cross_product(const Vec4 v1, const Vec4 v2);
const float dot_product(const Vec4 v1, const Vec4 v2);
const Vec4 triangle_cp(const Triangle t);
const float winding3D(const Triangle t);
const float winding2D(const Triangle t);

#endif /* _VECTORS_MATH_H */

