#include "header_files/quaternions.h"

/* Quaternions library for C. */
/* Quaternion definition: q = w + xi + yj + zk */
/* Quaternion type: i = j = k = sqrt(-1) */

Quat unitQuat(void) {
    Quat q = {
        .w = 1.0,
        .v = { 0.0, 0.0, 0.0 }
    };
    return q;
}

Quat setQuat(const float w, const Vec4 vec) {
    Quat q = {
        .w = w,
        .v = { vec.x, vec.y, vec.z }
    };
    return q;
}

void normalizeQuat(Quat *q) {
    if (((q->w * q->w) + (q->v.x * q->v.x) + (q->v.y * q->v.y) + (q->v.z * q->v.z)) > 1.000010) {
        float magnitude = magnitudeQuat(*q);
        q->w /= magnitude;
        q->v.x /= magnitude;
        q->v.y /= magnitude;
        q->v.z /= magnitude;
    }
}

Quat conjugateQuat(const Quat q) {
    Quat res = {
        .w = q.w,
        .v = {
            .x = -q.v.x,
            .y = -q.v.y,
            .z = -q.v.z,
        }
    };
    return res;
}

float magnitudeQuat(const Quat q) {
    return sqrtf((q.w * q.w) + (q.v.x * q.v.x) + (q.v.y * q.v.y) + (q.v.z * q.v.z));
}

Quat rotationQuat(const float angle, const Vec4 axis) {
    float radius = angle * (3.14159 / 180.0);
    float c = sinf(radius / 2.00);
    Quat res = {
        .w = cosf(radius / 2.00),
        .v = {
            .x = axis.x * c,
            .y = axis.y * c,
            .z = axis.z * c,
        }
    };
    return res;
}

Quat eulertoQuat(const float roll, const float yaw, const float pitch) {
    float cr, sr, cy, sy, cp, sp, cpcy, spsy;
    cr = cosf(roll / 2.00);
    sr = sinf(roll / 2.00);
    cy = cosf(yaw / 2.00);
    sy = sinf(yaw / 2.00);
    cp = cosf(pitch / 2.00);
    sp = sinf(pitch / 2.00);
    cpcy = cp * cy;
    spsy = sp * sy;

    Quat res = {
        .w = cr * cpcy + sr * spsy,
        .v = {
            .x = sr * cpcy - cr * spsy,
            .y = cr * sp * cy + sr * cp * sy,
            .z = cr * cp * sy - sr * sp * cy,
        }
    };
    return res;
}

Quat multiplyQuats(const Quat q1, const Quat q2) {
    Quat res = {
        .w = (q1.w * q2.w) - (q1.v.x * q2.v.x) - (q1.v.y * q2.v.y) - (q1.v.z * q2.v.z),
        .v = {
            .x = (q1.w * q2.v.x)  +  (q1.v.x * q2.w)    +  (q1.v.y * q2.v.z)  -  (q1.v.z * q2.v.y),
            .y = (q1.w * q2.v.y)  -  (q1.v.x * q2.v.z)  +  (q1.v.y * q2.w)    +  (q1.v.z * q2.v.x),
            .z = (q1.w * q2.v.z)  +  (q1.v.x * q2.v.y)  -  (q1.v.y * q2.v.x)  +  (q1.v.z * q2.w),
        }
    };
    return res;
}

Quat addQuats(const Quat q1, const Quat q2) {
    Quat res = {
        .w = q1.w + q2.w,
        .v = {
            .x = q1.v.x + q2.v.x,
            .y = q1.v.y + q2.v.y,
            .z = q1.v.z + q2.v.z,
        }
    };
    return res;
}

Mat4x4 MatfromQuat(const Quat q, const Vec4 v) {
    Mat4x4 m = { 0 };

    m.m[0][0] = 2.0 * ( (q.w * q.w) + (q.v.x * q.v.x) ) - 1.0;
    m.m[0][1] = 2.0 * ( (q.v.x * q.v.y) - (q.w * q.v.z) );
    m.m[0][2] = 2.0 * ( (q.v.x * q.v.z) + (q.w * q.v.y) );
    m.m[0][3] = 0.0;

    m.m[1][0] = 2.0 * ( (q.v.x * q.v.y) + (q.w * q.v.z) );
    m.m[1][1] = 2.0 * ( (q.w * q.w) + (q.v.y * q.v.y) ) - 1.0;
    m.m[1][2] = 2.0 * ( (q.v.y * q.v.z) - (q.w * q.v.x) );
    m.m[1][3] = 0.0;

    m.m[2][0] = 2.0 * ( (q.v.x * q.v.z) - (q.w * q.v.y) );
    m.m[2][1] = 2.0 * ( (q.v.y * q.v.z) + (q.w * q.v.x) );
    m.m[2][2] = 2.0 * ( (q.w * q.w) + (q.v.z * q.v.z) ) - 1.0;
    m.m[2][3] = 0.0;

    if (m.m[2][0] != 0.0)
        m.m[3][0] = v.x - v.x * m.m[0][0] - v.y * m.m[1][0] - v.z * m.m[2][0];
    if (m.m[2][1] != 0.0)
        m.m[3][1] = v.y - v.x * m.m[0][1] - v.y * m.m[1][1] - v.z * m.m[2][1];
    if (m.m[2][2] != 0.0)
        m.m[3][2] = v.z - v.x * m.m[0][2] - v.y * m.m[1][2] - v.z * m.m[2][2];
    m.m[3][3] = 1.0;

    return m;
}

