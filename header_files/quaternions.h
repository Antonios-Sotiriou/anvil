#ifndef _QUATERNIONS_H
#define _QUATERNIONS_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _MATH_H
    #include <math.h>
#endif

typedef struct {
    float w;
    Vec4 v;
} Quat;

Quat unitQuat(void);
Quat setQuat(const float w, const Vec4 vec);
void normalizeQuat(Quat *q);
Quat conjugateQuat(const Quat q);
float magnitudeQuat(const Quat q);
Quat rotationQuat(const float angle, const Vec4 axis);
Quat eulertoQuat(const float roll, const float yaw, const float pitch);
Quat multiplyQuats(const Quat q1, const Quat q2);
Quat addQuats(const Quat q1, const Quat q2);
Mat4x4 MatfromQuat(const Quat q, const Vec4 v);

#endif /* _QUATERNIONS_H */