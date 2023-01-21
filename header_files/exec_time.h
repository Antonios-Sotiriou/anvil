#ifndef _EXEC_TIME_H
#define _EXEC_TIME_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _TIME_H
    #include <time.h>
#endif

const clock_t start(void);
const void end(const clock_t start_time);

const void log_global(const Global g);
const void log_vector(const Vector v);

#endif /* _EXEC_TIME_H */

