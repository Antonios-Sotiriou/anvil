#ifndef _WORLD_OBJECTS_H
#define _WORLD_OBJECTS_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _MATRICES_H
    #include "matrices.h"
#endif

#ifndef _BMP_H
    #include "bmp.h"
#endif

#ifndef _OBJ_PARSER_H
    #include "obj_parser.h"
#endif

#ifndef _GENERAL_FUNCTIONS_H
    #include "general_functions.h"
#endif

#ifndef _KINETICS_H
    #include "kinetics.h"
#endif

const void initMeshes(Scene *s);
const void createScene(Scene *s);
const void releaseScene(Scene *s);
const static void loadTexture(Mesh *c);

#endif /* _WORLD_OBJECTS_H */


