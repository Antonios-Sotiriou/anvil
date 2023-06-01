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
const void shadowTriangle(const Triangle t, const int minX, const int maxX, const int minY, const int maxY);
const Vector shadowTest(Vector pix);

#endif /* _SHADOWMAP_H */