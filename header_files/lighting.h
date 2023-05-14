#ifndef _LIGHTING_H
#define _LIGHTING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const int shadow);

#endif /* _LIGHTING_H */

