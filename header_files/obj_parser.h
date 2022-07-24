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

Mesh load_obj(const char path[]);

#endif /* _OBJ_PARSER_H */
