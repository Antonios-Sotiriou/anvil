#ifndef _VECTORS_MATH_H
#define _VECTORS_MATH_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif
#ifndef _MATH_H
    #include "math.h"
#endif

/* 3D graphics vec4 computation functions */
const float depth(const Triangle t);
Mesh sort_triangles(Mesh *c);
const float len_vec(const vec4 v);
const vec4 norm_vec(const vec4 v);
const vec4 multiply_vec(const vec4 v1, const float num);
const vec4 divide_vec(const vec4 v1, const float num);
const vec4 add_vecs(const vec4 v1, const vec4 v2);
const vec4 sub_vecs(const vec4 v1, const vec4 v2);
const vec4 cross_product(const vec4 v1, const vec4 v2);
const float dot_product(const vec4 v1, const vec4 v2);
const vec4 triangle_cp(const Triangle t);
const float winding3D(const Triangle t);
const float winding2D(const Triangle t);

#endif /* _VECTORS_MATH_H */


