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
    Vector v;
} Quat;

Quat unitQuat(void);
Quat setQuat(const float w, const Vector vec);
void normalizeQuat(Quat *q);
Quat conjugateQuat(const Quat q);
float magnitudeQuat(const Quat q);
Quat rotationQuat(const float angle, const Vector axis);
Quat eulertoQuat(const float roll, const float yaw, const float pitch);
Quat multiplyQuats(const Quat q1, const Quat q2);
Quat addQuats(const Quat q1, const Quat q2);
void printQuat(const Quat q);

#endif /* _QUATERNIONS_H */