#ifndef _LOGGING_H
#define _LOGGING_H 1

#ifndef _OBJECTS_H
    #include "objects.h"
#endif

#ifndef _QUATERNIONS_H
    #include "quaternions.h"
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

const void logEvent(const XEvent e);
const void logGlobal(const Global g);
const void logVector(const Vector v);
const void logPixel(const Pixel p);
const void logTriangle(const Triangle t, const int vec, const int tex, const int norm);
const void logMatrix(const Mat4x4 m);
const void logQuat(const Quat q);

#endif /* _LOGGING_H */