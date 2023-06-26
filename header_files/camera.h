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

const void look_left(vec4 *g, const float Angle);
const void look_right(vec4 *g, const float Angle);
const void move_forward(vec4 *g);
const void move_backward(vec4 *g);
const void look_up(vec4 *g, const float Angle);
const void look_down(vec4 *g, const float Angle);
const void move_left(vec4 *g);
const void move_right(vec4 *g);
const void move_up(vec4 *g);
const void move_down(vec4 *g);

#endif /* _CAMERA_H */


