#ifndef _DEBUG_RASTERIZER_H
#define _DEBUG_RASTERIZER_H 1

#ifndef _XLIB_H
    #include <X11/Xlib.h>
#endif

typedef struct {
    /* Importand! XPoint here so we can use the xlib build in function to fill the triangles. */
    XPoint dv[3];
} DTriangle;

/* Screen Mesh */
typedef struct {
    DTriangle *dt;
    int indexes;
} DMesh;

#endif /* _DEBUG_RASTERIZER_H */