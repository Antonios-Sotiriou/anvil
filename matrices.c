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
/* Projection Matrix. */
const Mat4x4 projection_mat(const float fov, const float aspectratio) {
    Mat4x4 m = { 0 };
    m.m[0][0] = aspectratio * FovRadius;
    m.m[1][1] = FovRadius;
    m.m[2][2] = (ZFar / (ZFar - ZNear));
    m.m[2][3] = 1.0;
    m.m[3][2] = ((-ZFar * ZNear) / (ZFar - ZNear));
    m.m[3][3] = 1.0;
    return m;
}
/* Multiplies a Mesh *c with the given Matrix and returns a new Mesh, leaving the original unmodified. */
Mesh meshxm(Mesh *c, const Mat4x4 m) {

    Mesh ch = *c;
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < 3; j++) {
            
            ch.tri[i].vec[j].x = c->tri[i].vec[j].x * m.m[0][0] + c->tri[i].vec[j].y * m.m[1][0] + c->tri[i].vec[j].z * m.m[2][0] + c->tri[i].vec[j].w * m.m[3][0];
            ch.tri[i].vec[j].y = c->tri[i].vec[j].x * m.m[0][1] + c->tri[i].vec[j].y * m.m[1][1] + c->tri[i].vec[j].z * m.m[2][1] + c->tri[i].vec[j].w * m.m[3][1];
            ch.tri[i].vec[j].z = c->tri[i].vec[j].x * m.m[0][2] + c->tri[i].vec[j].y * m.m[1][2] + c->tri[i].vec[j].z * m.m[2][2] + c->tri[i].vec[j].w * m.m[3][2];
            ch.tri[i].vec[j].w = c->tri[i].vec[j].x * m.m[0][3] + c->tri[i].vec[j].y * m.m[1][3] + c->tri[i].vec[j].z * m.m[2][3] + c->tri[i].vec[j].w * m.m[3][3];
        }
    }
    return ch;
}

