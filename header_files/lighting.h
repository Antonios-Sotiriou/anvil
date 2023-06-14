#ifndef _LIGHTING_H
#define _LIGHTING_H 1

#ifndef _STRING_H
    #include <string.h>
#endif

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _MATRICES_H
    #include "matrices.h"
#endif

#ifndef _SHADOWMAP_H
    #include "shadowmap.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

const float phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW);

#endif /* _LIGHTING_H */

