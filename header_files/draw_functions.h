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

#ifndef _MATH_H
    #include <math.h>
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

const void drawline(Pixel **buffer, float x1, float y1, float x2, float y2, const int red, const int green, const int blue);

const void filltriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const Global light, const Global camera, const float red, const float green, const float blue);
const void fillnorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const Global light, const Global camera, const float winding, const Vector obj_color);
const void fillsouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const Global light, const Global camera, const float winding, const Vector obj_color);
const void fillgeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const Global light, const Global camera, const float winding, const Vector color);

const void textriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const float light, Pixel **texels, const BMP_Info texture);
const void texnorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const void texsouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);
const void texgeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width);

#endif /* _DRAW_FUNCTIONS_H */

