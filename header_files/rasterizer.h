#ifndef _RASTERIZER_H
#define _RASTERIZER_H 1

#ifndef OBJECTS_H
    #include "header_files/objects.h"
#endif

const static void rasterize(const SCMesh sc, char *buffer, Pixel *pixels);
const static void fillnorthway(const Triangle t, Pixel *pixels);
const static void fillsouthway(const Triangle t, Pixel *pixels);
const static void fillgeneral(const Triangle t, Pixel *pixels);

#endif /* _RASTERIZER_H */