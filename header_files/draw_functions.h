#ifndef _DRAW_FUNCTIONS_H
#define _DRAW_FUNCTIONS_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _BMP_H
    #include "bmp.h"
#endif

#ifndef _VECTORS_MATH_H
    #include "vectors_math.h"
#endif

#ifndef _GENERAL_FUNCTIONS_H
    #include "general_functions.h"
#endif

#ifndef _SHADOWMAP_H
    #include "shadowmap.h"
#endif

#ifndef _LIGHTING_H
    #include "lighting.h"
#endif

#ifndef _MATRICES_H
    #include "matrices.h"
#endif

#ifndef _MATH_H
    #include <math.h>
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue);

const void fillTriangle(Triangle t);
const static void fillNorthway(const Triangle t, const float winding);
const static void fillSouthway(const Triangle t, const float winding);
const static void fillGeneral(const Triangle t, const float winding);
// const void fillGeneral(Triangle t, int minX, int maxX, int minY, int maxY);

const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width);
const static void texNorthway(const Triangle t, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const static void texSouthway(const Triangle t, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const static void texGeneral(const Triangle t, const float winding, Pixel **texels, const int tex_height, const int tex_width);

#endif /* _DRAW_FUNCTIONS_H */

