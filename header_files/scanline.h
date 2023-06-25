#ifndef _SCANLINE_H
#define _SCANLINE_H 1

#ifndef _LIGHTING_H
    #include "lighting.h"
#endif

const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue);

const void fillTriangle(Triangle t);
const static void fillGeneral(const Triangle t);

const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width);
const static void texGeneral(const Triangle t, const float winding, Pixel **texels, const int tex_height, const int tex_width);

#endif /* _SCANLINE_H */

