#ifndef _DRAW_FUNCTIONS_H
#define _DRAW_FUNCTIONS_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _MATH_H
    #include "math.h"
#endif

const void draw_line(Pixel **buffer, float x1, float y1, float x2, float y2, const int red, const int green, const int blue);

#endif /* _DRAW_FUNCTIONS_H */

