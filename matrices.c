#include "header_files/matrices.h"

/* Rotate Object on X axis according the world origin */
const Mat4x4 rotate_xmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = 1.0;
    m.m[1][1] = cosf(angle);
    m.m[1][2] = -sinf(angle);
    m.m[2][1] = sinf(angle);
    m.m[2][2] = cosf(angle);
    m.m[3][3] = 1.0;
    return m;
}
/* Rotate Object on Y axis according the world origin */
const Mat4x4 rotate_ymat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(angle);
    m.m[1][1] = 1.00;
    m.m[0][2] = -sinf(angle);
    m.m[2][0] = sinf(angle);
    m.m[2][2] = cosf(angle);
    m.m[3][3] = 1.0;
    return m;
}
/* Rotate Object on Z axis according the world origin */
const Mat4x4 rotate_zmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(angle);
    m.m[0][1] = sinf(angle);
    m.m[1][0] = -sinf(angle);
    m.m[1][1] = cosf(angle);
    m.m[2][2] = 1.0;
    m.m[3][3] = 1.0;
    return m;
}
/* Scale Matrix. */
const Mat4x4 scale_mat(const float scale) {
    Mat4x4 m = { 0 };
    m.m[0][0] = scale;
    m.m[1][1] = scale;
    m.m[2][2] = scale;
    m.m[3][3] = 1.0;
    return m;
}
/* Translation Matrix. */
const Mat4x4 translation_mat(const float x, const float y, const float z) {
    Mat4x4 m = { 0 };
    m.m[0][0] = 1.0;
    m.m[1][1] = 1.0;
    m.m[2][2] = 1.0;
    m.m[3][3] = 1.0;
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}
/* Projection Matrix. */
const Mat4x4 projection_mat(const float fov, const float aspectratio) {
    Mat4x4 m = { 0 };
    m.m[0][0] = aspectratio * FovRadius;
    m.m[1][1] = aspectratio * FovRadius;
    m.m[2][2] = (ZFar / (ZFar - ZNear));
    m.m[2][3] = -1.0;
    m.m[3][2] = ((ZFar * ZNear) / (ZFar - ZNear));
    m.m[3][3] = 0.0;
    return m;
}
/* Multiplies a Mesh c with the given Matrix and returns a new Mesh, leaving the original unmodified. */
const Mesh meshxm(const Mesh c, const Mat4x4 m) {

    Mesh r = { 0 };
    
    r.t = malloc(sizeof(Triangle) * c.indexes);
    if (!r.t)
        fprintf(stderr, "Could not allocate memory for Cache Mesh. meshxm() -- malloc().\n");

    if (!memcpy(r.t, c.t, sizeof(Triangle) * c.indexes))
        fprintf(stderr, "Could not copy memory for Cache Mesh. meshxm() -- memcpy().\n");
    
    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {
            
            r.t[i].v[j].x = c.t[i].v[j].x * m.m[0][0] + c.t[i].v[j].y * m.m[1][0] + c.t[i].v[j].z * m.m[2][0] + c.t[i].v[j].w * m.m[3][0];
            r.t[i].v[j].y = c.t[i].v[j].x * m.m[0][1] + c.t[i].v[j].y * m.m[1][1] + c.t[i].v[j].z * m.m[2][1] + c.t[i].v[j].w * m.m[3][1];
            r.t[i].v[j].z = c.t[i].v[j].x * m.m[0][2] + c.t[i].v[j].y * m.m[1][2] + c.t[i].v[j].z * m.m[2][2] + c.t[i].v[j].w * m.m[3][2];
            r.t[i].v[j].w = c.t[i].v[j].x * m.m[0][3] + c.t[i].v[j].y * m.m[1][3] + c.t[i].v[j].z * m.m[2][3] + c.t[i].v[j].w * m.m[3][3];
        }
    }
    r.indexes = c.indexes;
    return r;
}
/* Multiplies a Vector with the given Matrix and returns a new Vector, leaving the original unmodified. */
const Vector vecxm(const Vector v, const Mat4x4 m) {
    
    Vector r = { 0 };
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    r.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];
    return r;
}
/* The Camera Matrix or as used to called the View Matrix.Returns a new 4x4 Matrix representing the camera. */
const Mat4x4 camera_mat(const Vector P, const Vector U, const Vector V, const Vector N) {
    Mat4x4 m = { 0 };
    m.m[0][0] = U.x;    m.m[0][1] = U.y;    m.m[0][2] = U.z;    m.m[0][3] = 0.0;
    m.m[1][0] = V.x;    m.m[1][1] = V.y;    m.m[1][2] = V.z;    m.m[1][3] = 0.0;
    m.m[2][0] = N.x;    m.m[2][1] = N.y;    m.m[2][2] = N.z;    m.m[2][3] = 0.0;
    m.m[3][0] = P.x;    m.m[3][1] = P.y;    m.m[3][2] = P.z;    m.m[3][3] = 1.0;
    return m;
}
/* Inverts the given Matrix m returning a new 4x4 Matrix. */
const Mat4x4 inverse_mat(const Mat4x4 m) {
    Mat4x4 rm = { 0 };
    rm.m[0][0] =   m.m[0][0];    rm.m[0][1] = m.m[1][0];    rm.m[0][2] = m.m[2][0];    rm.m[0][3] = 0.0;
    rm.m[1][0] =   m.m[0][1];    rm.m[1][1] = m.m[1][1];    rm.m[1][2] = m.m[2][1];    rm.m[1][3] = 0.0;
    rm.m[2][0] =   m.m[0][2];    rm.m[2][1] = m.m[1][2];    rm.m[2][2] = m.m[2][2];    rm.m[2][3] = 0.0;
    rm.m[3][0] = -(m.m[3][0] * rm.m[0][0] + m.m[3][1] * rm.m[1][0] + m.m[3][2] * rm.m[2][0]);
    rm.m[3][1] = -(m.m[3][0] * rm.m[0][1] + m.m[3][1] * rm.m[1][1] + m.m[3][2] * rm.m[2][1]);
    rm.m[3][2] = -(m.m[3][0] * rm.m[0][2] + m.m[3][1] * rm.m[1][2] + m.m[3][2] * rm.m[2][2]);
    rm.m[3][3] = 1.0;
    return rm;
}
/* Multiplies two given Matrices m1, m2.Returns a new 4x4 Matrix. */
const Mat4x4 mxm(const Mat4x4 m1, const Mat4x4 m2) {
    Mat4x4 r = { 0 };
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) {
            r.m[j][i] = m1.m[j][0] * m2.m[0][i] + m1.m[j][1] * m2.m[1][i] + m1.m[j][2] * m2.m[2][i] + m1.m[j][3] * m2.m[3][i];
        }
    return r;
}

