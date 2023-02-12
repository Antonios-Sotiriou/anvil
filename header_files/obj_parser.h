#ifndef _OBJ_PARSER_H
#define _OBJ_PARSER_H 1

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

/* Usefull struct to parse the obj file Faces */
typedef struct {
    int va, vb, vc;
    int ta, tb, tc;
    int na, nb, nc;
} Face;

const Mesh load_obj(const char path[]);

#endif /* _OBJ_PARSER_H */

