#ifndef _SCANLINE_H
#define _SCANLINE_H 1

#ifndef _DRAWLINE_H
    #include "drawline.h"
#endif

#ifndef _LIGHTING_H
    #include "lighting.h"
#endif

/* This struct here is usefull for sorting array elements without affecting them and also saving their original array indexes. */
struct Srt {
    float y;
    int index;
};

const void fillTriangle(Triangle t);
const static void fillGeneral(const Triangle t, const struct Srt srt[]);

const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width);
const static void texGeneral(const Triangle t, const struct Srt srt[], Pixel **texels, const int tex_height, const int tex_width);

#endif /* _SCANLINE_H */


