#ifndef _OBJECTS_H
#define _OBJECTS_H 1

#ifndef _XLIB_H
    #include <X11/Xlib.h>
#endif

enum { AVector, BVector, CVector, LastVector};

/* Pixels Struct for rgb values 0 - 65535 */
typedef struct {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} Pixel;

/* World Vector */
typedef struct {
    float x, y, z, w;
} Vector;

/* Textures Vector */
typedef struct {
    float u, v, w;
} Textor;

/* World Triangle */
typedef struct {
    int a, b, c;
    Vector v[LastVector];
    Textor tex[LastVector];
    Vector normal;
    Bool clipped;
} Triangle;

/* World Mesh */
typedef struct {
    Triangle *t;
    Vector *v;
    int v_indexes;
    int t_indexes;
    char texture_file[50];
    signed int texture_height;
    signed int texture_width;
    Pixel **texels;
} Mesh;

/* World scene */
typedef struct {
    Mesh *m;
    int indexes;
} Scene;

/* Initialization matrix */
typedef struct {
    float m[4][4];
} Mat4x4;

/* structure for global objets that need their own coordinate system. C here can be used for normalized Color. */
typedef struct {
    Vector Pos, U, V, N, C;
} Global;

/* structure for lighting models. Helps to keep orginized the lighting values that we need to pass arround. */
typedef struct {
    Vector CameraPos;
    Vector lightPos;
    Vector LightColor;
    Vector objColor;
    Vector normal;
    float AmbientStrength;
    Vector Ambient;
    float SpecularStrength;
    Vector Specular;
    int width;
    int halfWidth;
    int height;
    int halfHeight;
    float dot;
    Mat4x4 ModelSpace;
    Mat4x4 LightSpace;
    Mat4x4 ViewSpace;
    float bias;
} Phong;

#endif /* _OBJECTS_H */

