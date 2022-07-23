#ifndef _MATRICES_H
#define _MATRICES_H 1

#include "objects.h"

#ifndef _MATH_H
    #include <math.h>
#endif

#define ZNear                     0.01
#define ZFar                      1000.00 
#define FovRadius                 ( 1 / tanf(fov * 0.5 / 180.0 * 3.14159) )

/* 3D graphics Matrices and computations. */
Mesh meshxm(Mesh *c, const Mat4x4 m);
const Mat4x4 projection_mat(const float fov, const float aspectratio);
const Mat4x4 rotate_xmat(const float angle);
const Mat4x4 rotate_ymat(const float angle);
const Mat4x4 rotate_zmat(const float angle);

#endif /* _MATRICES_H */

