#ifndef _DRAW_FUNCTIONS_H
#define _DRAW_FUNCTIONS_H 1

#ifndef _LIGHTING_H
    #include "lighting.h"
#endif

const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue);

const void fillTriangle(Triangle t);
const void fillGeneral(const Triangle t, const int minX, const int maxX, const int minY, const int maxY);

const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width);
const void texGeneral(const Triangle t, Pixel **texels, const int tex_height, const int tex_width, int minX, int maxX, int minY, int maxY);

#endif /* _DRAW_FUNCTIONS_H */

