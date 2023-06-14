#ifndef _LIGHTING_H
#define _LIGHTING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _vectors_mathMATH_H
    #include "vectors_math.h"
#endif

const float phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW);

#endif /* _LIGHTING_H */

