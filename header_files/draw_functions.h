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

const void drawLine(Pixel **buffer, float x1, float y1, float x2, float y2, const float red, const float green, const float blue);

const void fillTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle *t, Phong model);
const void fillNorthway(Pixel **pixels, float **depth_buffer, const Triangle t, Phong model, const float winding);
const void fillSouthway(Pixel **pixels, float **depth_buffer, const Triangle t, Phong model, const float winding);
const void fillGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding);

const void texTriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const float light, Pixel **texels, const int tex_height, const int tex_width);
const void texNorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const void texSouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const void texGeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);

#endif /* _DRAW_FUNCTIONS_H */

