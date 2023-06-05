#ifndef _CAMERA_H
#define _CAMERA_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

#ifndef _QUATERNIONS_H
    #include "quaternions.h"
#endif

const void look_left(Global *g, const float Angle);
const void look_right(Global *g, const float Angle);
const void move_forward(Global *g);
const void move_backward(Global *g);
const void look_up(Global *g, const float Angle);
const void look_down(Global *g, const float Angle);
const void move_left(Global *g);
const void move_right(Global *g);
const void move_up(Global *g);
const void move_down(Global *g);

#endif /* _CAMERA_H */