#ifndef _MATRICES_H
#define _MATRICES_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _vectors_mathMATH_H
    #include "vectors_math.h"
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

/* 3D graphics Matrices and computations. */
const Mat4x4 rotate_xmat(const float angle);
const Mat4x4 rotate_ymat(const float angle);
const Mat4x4 rotate_zmat(const float angle);
const Mat4x4 scale_mat(const float scale);
const Mat4x4 translation_mat(const float x, const float y, const float z);
const Mat4x4 perspective_mat(const float fov, const float aspectratio, const float zn, const float zf);
const Mat4x4 reperspective_mat(const float fov, const float aspectratio);
const Mat4x4 orthographic_mat(const float scaleX, const float scaleY, const float transX, const float transY, const float zn, const float zf);
const Mat4x4 reorthographic_mat(const float fov, const float aspectratio, const float zn, const float zf);
const Mesh meshxm(const Mesh c, const Mat4x4 m);
const void normalsxm(const Mesh *c, const Mat4x4 m);
const Vec4 vecxm(const Vec4 v, const Mat4x4 m);
const Mat4x4 pointat(const Vec4 P, const Vec4 T, const Vec4 V);
const Mat4x4 lookat(const Vec4 P, const Vec4 U, const Vec4 V, const Vec4 N);
const Mat4x4 inverse_mat(const Mat4x4 m);
const Mat4x4 transpose_mat(const Mat4x4 m);
const Mat4x4 mxm(const Mat4x4 m1, const Mat4x4 m2);

#endif /* _MATRICES_H */

