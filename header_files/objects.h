#ifndef _OBJECTS_H
#define _OBJECTS_H 1

#ifndef _XLIB_H
    #include <X11/Xlib.h>
#endif

/* Pixels Struct for rgb values 0 - 65535 */
typedef struct {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} Pixel;

/* World vec4 */
typedef struct {
    float x, y, z, w;
} vec4;

/* Textures vec4 */
typedef struct {
    float u, v, w;
} Textor;

/* World Triangle */
typedef struct {
    int va, vb, vc;
    vec4 v[3];
    Textor vt[3];
    vec4 vn[3];
    vec4 fn;
} Triangle;

/* World Mesh */
typedef struct {
    Triangle *t;
    vec4 *v;
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
    vec4 Pos, U, V, N, C;
} Global;

/* structure for lighting models. Helps to keep orginized the lighting values that we need to pass arround. */
typedef struct {
    vec4 lightPos;
    vec4 LightColor;
    Pixel objColor;
    vec4 normal;
    float AmbientStrength;
    vec4 Ambient;
    float SpecularStrength;
    vec4 Specular;
    float bias;
} Phong;

// typedef struct {
//     void (*taskFunction)(Phong, float, float, float, float);
//     float arg1, arg2, arg3, arg4;
//     Phong model;
// } Task;

#endif /* _OBJECTS_H */


