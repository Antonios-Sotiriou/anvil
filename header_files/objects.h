#ifndef _OBJECTS_H
#define _OBJECTS_H 1

#ifndef _XLIB_H
    #include <X11/Xlib.h>
#endif

enum { AVector, BVector, CVector, LastVector};

/* World Vector */
typedef struct {
    float x, y, z, w;
} Vector;

/* World Triangle */
typedef struct {
    Vector v[LastVector];
    Vector n;                  /* The normal Vector */
    unsigned int color;
} Triangle;

/* Screen Triangle */
typedef struct {
    /* Importand! XPoint here so we can use the xlib build in function to fill the triangles. */
    XPoint scv[LastVector];
} SCTriangle;

/* World Mesh */
typedef struct {
    Triangle *t;
    int indexes;
} Mesh;

/* Screen Mesh */
typedef struct {
    SCTriangle *sct;
    int indexes;
} SCMesh;

/* Initialization matrix */
typedef struct {
    float m[4][4];
} Mat4x4;

#endif /* _OBJECTS_H */

