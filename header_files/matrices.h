#ifndef _MATRICES_H
#define _MATRICES_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STRING_H
    #include <string.h>
#endif

#ifndef _MATH_H
    #include <math.h>
#endif

#define ZNear                     0.1
#define ZFar                      1000.0 
#define FovRadius                 ( 1 / tanf(fov * 0.5 / 180.0 * 3.14159) )

/* 3D graphics Matrices and computations. */
const Mat4x4 rotate_xmat(const float angle);
const Mat4x4 rotate_ymat(const float angle);
const Mat4x4 rotate_zmat(const float angle);
const Mat4x4 scale_mat(const float scale);
const Mat4x4 translation_mat(const float x, const float y, const float z);
const Mat4x4 projection_mat(const float fov, const float aspectratio);
const Mesh meshxm(const Mesh c, const Mat4x4 m);
const Vector vecxm(const Vector v, const Mat4x4 m);
const Mat4x4 camera_mat(const Vector P, const Vector U, const Vector V, const Vector N);
const Mat4x4 inverse_mat(const Mat4x4 m);
const Mat4x4 mxm(const Mat4x4 m1, const Mat4x4 m2);

#endif /* _MATRICES_H */

