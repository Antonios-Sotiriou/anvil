#ifndef _CAMERA_H
#define _CAMERA_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _vectors_mathMATH_H
    #include "vectors_math.h"
#endif

#ifndef _QUATERNIONS_H
    #include "quaternions.h"
#endif

const void look_left(Vec4 *g, const float Angle);
const void look_right(Vec4 *g, const float Angle);
const void move_forward(Vec4 *g);
const void move_backward(Vec4 *g);
const void look_up(Vec4 *g, const float Angle);
const void look_down(Vec4 *g, const float Angle);
const void move_left(Vec4 *g);
const void move_right(Vec4 *g);
const void move_up(Vec4 *g);
const void move_down(Vec4 *g);

#endif /* _CAMERA_H */