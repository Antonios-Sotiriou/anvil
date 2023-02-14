#ifndef _LIGHTING_H
#define _LIGHTING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

const Pixel phong(Vector pixpos, const Vector normal, const Global light, const Global camera, const Vector obj_color);

#endif /* _LIGHTING_H */

