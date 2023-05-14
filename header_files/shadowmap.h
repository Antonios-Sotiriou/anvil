#ifndef _SHADOWMAP_H
#define _SHADOWMAP_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _GENERAL_FUNCTIONS_H
    #include "general_functions.h"
#endif

#ifndef _MATRICES_H
    #include "matrices.h"
#endif

#ifndef _MATH_H
    #include "math.h"
#endif

const void createShadowmap(Mesh c);
const void shadowTriangle(const Triangle t);
const Vector shadowTest( float pixX, const float pixY, const float pixZ, const float pixW);

#endif /* _SHADOWMAP_H */