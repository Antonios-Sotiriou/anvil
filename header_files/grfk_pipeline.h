#ifndef _GRFK_PIPELINE_H
#define _GRFK_PIPELINE_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _MATRICES_H
    #include "matrices.h"
#endif

#ifndef _CLIPPING_H
    #include "clipping.h"
#endif

#ifndef _DRAW_FUNCTIONS_H
    #include "draw_functions.h"
#endif

const void shadowPipeline(Scene s);
const void grfkPipeLine(Scene s);
const static void ppdiv(Mesh *c);
const static Mesh shadowcull(const Mesh c);
const static Mesh bfculling(const Mesh c);
const static Mesh viewtoscreen(const Mesh c);
const static void rasterize(const Mesh sc);

#endif /* _GRFK_PIPELINE_H */