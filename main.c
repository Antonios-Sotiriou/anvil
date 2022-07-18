// general headers
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

// Project specific headers
#include "header_files/locale.h"

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};
enum { AVector, BVector, CVector, LastVector};
enum { FrontUp, FrontDown, BackUp, BackDown, WestUp, WestDown, EastUp, EastDown, NorthUp, NorthDown, SouthUp, SouthDown, LastTriangle};

// World Vector
typedef struct {
    float x, y, z, w;
} Vector;
// World Triangle
typedef struct {
    Vector vector[LastVector];
} Triangle;
// Screen Triangle
typedef struct {
    // Importand! XPoint here so we can use the xlib build in function to fill the triangles.
    XPoint scvector[LastVector];
} SCTriangle;
// World Mesh
typedef struct {
    Triangle tri[LastTriangle];
} Mesh;
// Screen Mesh
typedef struct {
    SCTriangle sctri[LastTriangle];
} SCMesh;
// 1st frame Initialization matrix
typedef struct {
    float m[4][4];
} Mat4x4;

#define WIDTH                     800
#define HEIGHT                    800
#define ZNear                     0.01
#define ZFar                      1000.0
// #define FieldOfView               90.0
#define AspectRatio               ( ((float)wa.width / (float)wa.height) )
#define FovRadius                 ( 1 / tanf(fov * 0.5 / (180.0 * 3.14159)) )
#define FTheta                    ( 1 * 0.2 )
#define XWorldToScreen            ( (1 + c.tri[i].vector[j].x) * (wa.width / 2.00) )
#define YWorldToScreen            ( (1 + c.tri[i].vector[j].y) * (wa.height / 2.00) )

// #define range                     ( ((num / other) - 0.5) * 2.00 )

// #define NormalizeWorldX           ( (c.tri[i].vector[j].x + (wa.width / 2.00)) / wa.width )
// #define NormalizeWorldY           ( (c.tri[i].vector[j].y + (wa.height / 2.00)) / wa.height )
// #define XWorldToScreen            ( normalized.tri[i].vector[j].x * wa.width )
// #define YWorldToScreen            ( normalized.tri[i].vector[j].y * wa.height )

#define POINTERMASKS              ( ButtonPressMask )
#define KEYBOARDMASKS             ( KeyPressMask )
#define EXPOSEMASKS               ( StructureNotifyMask | ExposureMask )

// Some Global Variables
Display *displ;
Window win;
Pixmap pixmap;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

Vector Camera = { 0.0, 0.0, -1.0, 1.0 }, Up = { 0.0, -1.0, 0.0, 1.0 }, LookDir = { 0.0, 0.0, 1.0, 1.0 }, Target = { 0.0, 0.0, 1.0, 1.0 };
Vector LightSC = {
    -1.0, -1.0, 1.0, 1.0
};
Vector el;

#define cube_back     5.5
#define cube_front    5.0
#define cube_size     0.2

// Mesh unity = { 
//     {
//         { {{-0.05, 0.00, 0.00, 1.0}, {0.00, 0.00, 0.05, 1.0}, {0.05, 0.00, 0.00, 1.0}} },
//         { {{0.00, -0.05, 0.00, 1.0}, {0.00, 0.00, 0.05, 1.0}, {0.00, 0.05, 0.00, 1.0}} },
//         { {{0.00, 0.00, -0.05, 1.0}, {0.00, 0.00, 0.00, 1.0}, {0.00, 0.00, 0.05, 1.0}} },
//     }
// };
Mesh cube = {
    {
        // { {{ -cube_size, cube_size, cube_front, 1.0 }, { -cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }} },    // Front Up
        // { {{ -cube_size, cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, cube_size, cube_front, 1.0 }} },      // Front Down

        // { {{ cube_size, cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { -cube_size, -cube_size, cube_back, 1.0 }} },    // Back Up
        // { {{ cube_size, cube_size, cube_back, 1.0 }, { -cube_size, -cube_size, cube_back, 1.0 }, { -cube_size, cube_size, cube_back, 1.0 }} },     // Back Down

        // { {{ -cube_size, cube_size, cube_back, 1.0 }, { -cube_size, -cube_size, cube_back, 1.0 }, { -cube_size, -cube_size, cube_front, 1.0 }} },     // West Up
        // { {{ -cube_size, cube_size, cube_back, 1.0 }, { -cube_size, -cube_size, cube_front, 1.0 }, { -cube_size, cube_size, cube_front, 1.0 }} },       // East Down

        // { {{ cube_size, cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },    // East Up
        // { {{ cube_size, cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, cube_size, cube_back, 1.0 }} },     // East Down    

        // { {{ -cube_size, -cube_size, cube_front, 1.0 }, { -cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },   // North Up
        // { {{ -cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}} ,   // North Down

        // { {{ -cube_size, cube_size, cube_back, 1.0 }, { -cube_size, cube_size, cube_front, 1.0 }, { cube_size, cube_size, cube_front, 1.0 }} },       // South Up
        // { {{ -cube_size, cube_size, cube_back, 1.0 }, { cube_size, cube_size, cube_front, 1.0 }, { cube_size, cube_size, cube_back, 1.0 }} }      // South Down
                      // #######################################################################
        { {{ 0.00, 0.00, cube_front, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }} },    // Front Up
        { {{ 0.00, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },      // Front Down

        { {{ cube_size, 0.00, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }} },    // Back Up
        { {{ cube_size, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, 0.00, cube_back, 1.0 }} },     // Back Down

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }} },     // West Up
        { {{ 0.00,  0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }} },       // East Down

        { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },    // East Up
        { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} },     // East Down

        { {{ 0.00, -cube_size, cube_front, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },   // North Up
        { {{ 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}} ,   // North Down

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },       // South Up
        { {{ 0.00, 0.00, cube_back, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} }      // South Down
    }
};
SCMesh sccube = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
static float FieldOfView = 90.0;
static float FYaw;

// initialize the knot object to be transfered because we can't transfer vectorers to vectorers through shared memory.
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);

static void meshxm(Mesh *c, const Mat4x4 m);
static Mat4x4 mxm(const Mat4x4 m1, const Mat4x4 m2);
static void vecxm(Vector *v, const Mat4x4 m);
static void projection_mat(const float fov);
static void rotate_xmat(const float angle);
static void rotate_ymat(const float angle);
static void rotate_zmat(const float angle);

static void move_left(Vector *vcam);
static void move_right(Vector *vcam);
static void move_up(Vector *vcam);
static void move_down(Vector *vcam);
static void look_left(float num);
static void look_right(float num);
static void move_forward(void);
static void move_backward(void);

static float len_vector(const Vector v);
static Vector norm_vector(const Vector v);
static Vector multiply_vectors(const Vector v1, const float num);
static Vector divide_vectors(const Vector v1, const float num);
static Vector add_vectors(const Vector v1, const Vector v2);
static Vector sub_vectors(const Vector v1, const Vector v2);

static Vector cross_product(const Vector v1, const Vector v2);
static float dot_product(const Vector v, const Vector nm);
static void adjust_camera(const Vector vcam);
static void paint_mesh(SCMesh sc);
static void norm_mesh(const Mesh c);

static KeySym get_keysym(XEvent *event);
static const void pixmapupdate(void);
static const void pixmapdisplay(void);
static const void atomsinit(void);
static const int board(void);
static void (*handler[LASTEvent]) (XEvent *event) = {
    [ClientMessage] = clientmessage,
    [ReparentNotify] = reparentnotify,
    [MapNotify] = mapnotify,
    [Expose] = expose,
    [ResizeRequest] = resizerequest,
    [ConfigureNotify] = configurenotify,
    [ButtonPress] = buttonpress,
    [KeyPress] = keypress,
};

static const void clientmessage(XEvent *event) {

    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW");

        XFreePixmap(displ, pixmap);
        XDestroyWindow(displ, win);
        XCloseDisplay(displ);
        
        RUNNING = 0;
    }
}
static const void reparentnotify(XEvent *event) {

    printf("reparentnotify event received\n");
    XGetWindowAttributes(displ, win, &wa);
}
static const void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");

    if (MAPCOUNT) {
        pixmapdisplay();
    } else {
        projection_mat(FieldOfView);
        MAPCOUNT = 1;
    }
}
static const void expose(XEvent *event) {

    printf("expose event received\n");
    XGCValues gcv;
    gcv.graphics_exposures = False;
    gcv.foreground = 0xffffff;
    GC gc = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcv);

    XGetWindowAttributes(displ, win, &wa);

    // XDrawLine(displ, win, gc, 0, wa.height / 2, wa.width, wa.height / 2);
    // XDrawLine(displ, win, gc, wa.width / 2, 0, wa.width / 2, wa.height);

    XFreeGC(displ, gc);

    pixmapupdate();

    norm_mesh(cube);
    // norm_mesh(unity);
}
static const void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
static const void configurenotify(XEvent *event) {

    //printf("configurenotify event received\n");
}
static const void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
    if (el.x == 0.00 && el.y == 0.00) {
        el.x = (event->xbutton.x - (wa.width / 2.00)) / (wa.width / 2.00);
        el.y = (event->xbutton.y - (wa.height / 2.00)) / (wa.height / 2.00);
    } else {
        el.x = (event->xbutton.x - (wa.width / 2.00)) / (wa.width / 2.00);
        el.y = (event->xbutton.y - (wa.height / 2.00)) / (wa.height / 2.00);
    }
}
static const void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    switch (keysym) {

        case 119 : move_forward(); // w
            break;
        case 97 : look_left(FYaw); // a
            break;
        case 115 : move_backward(); // s
            break;
        case 100 : look_right(FYaw); // d
            break;
        case 65361 : move_left(&Camera); // left arrow
            break;
        case 65363 : move_right(&Camera); // right arrow
            break;
        case 65362 : move_up(&Camera); // up arror
            break;
        case 65364 : move_down(&Camera); // down arrow
            break;
        case 120 : rotate_xmat(FTheta); // x
            break;
        case 121 : rotate_ymat(FTheta); // y
            break;
        case 122 : rotate_zmat(FTheta); // z
            break;
        case 101 : /* rotate Yaxis Backwards */
            break;
        case 65293 : /* ZOOM *= 0.10 */; // Enter
            break;
        default :
            return;
    }
    
    pixmapdisplay();
    projection_mat(FieldOfView);
    norm_mesh(cube);
}
static void meshxm(Mesh *c, const Mat4x4 m) {

    Mesh cache = *c;
    printf("\x1b[H\x1b[J");
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {
            
            cache.tri[i].vector[j].x = c->tri[i].vector[j].x * m.m[0][0] + c->tri[i].vector[j].y * m.m[1][0] + c->tri[i].vector[j].z * m.m[2][0] + c->tri[i].vector[j].w * m.m[3][0];
            cache.tri[i].vector[j].y = c->tri[i].vector[j].x * m.m[0][1] + c->tri[i].vector[j].y * m.m[1][1] + c->tri[i].vector[j].z * m.m[2][1] + c->tri[i].vector[j].w * m.m[3][1];
            cache.tri[i].vector[j].z = c->tri[i].vector[j].x * m.m[0][2] + c->tri[i].vector[j].y * m.m[1][2] + c->tri[i].vector[j].z * m.m[2][2] + c->tri[i].vector[j].w * m.m[3][2];
            cache.tri[i].vector[j].w = c->tri[i].vector[j].x * m.m[0][3] + c->tri[i].vector[j].y * m.m[1][3] + c->tri[i].vector[j].z * m.m[2][3] + c->tri[i].vector[j].w * m.m[3][3];
            if (i == 0 && j == 2) {
                printf("X -----> %f\nY -----> %f\nZ -----> %f\nW -----> %f\n", c->tri[i].vector[j].x, c->tri[i].vector[j].y, c->tri[i].vector[j].z, c->tri[i].vector[j].w);
                printf("----------------------------------------------------\n");
                printf("X -----> %f\nY -----> %f\nZ -----> %f\nW -----> %f\n", cache.tri[i].vector[j].x, cache.tri[i].vector[j].y, cache.tri[i].vector[j].z, cache.tri[i].vector[j].w);
            }
        }
    }
    *c = cache;
}
static void ppdiv(Mesh *c) {
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            if (c->tri[i].vector[j].w != 0 ) {
                // printf("X -----> %f\nY -----> %f\nZ -----> %f\nW -----> %f\n", c->tri[i].vector[j].x, c->tri[i].vector[j].y, c->tri[i].vector[j].z, c->tri[i].vector[j].w);
                c->tri[i].vector[j].x /= c->tri[i].vector[j].w;
                c->tri[i].vector[j].y /= c->tri[i].vector[j].w;
                // c->tri[i].vector[j].z /= c->tri[i].vector[j].w;
            }
        }
    }
}
static Mat4x4 mxm(const Mat4x4 m1, const Mat4x4 m2) {
    Mat4x4 res;
    for (int i = 0; i < sizeof(res.m[0]) / sizeof(float); i++) 
        for (int j = 0; j < sizeof(res.m[0][0]) / sizeof(float); j++) {
            res.m[j][i] = m1.m[j][0] * m2.m[0][i] + m1.m[j][1] * m2.m[1][i] + m1.m[j][2] * m2.m[2][i] + m1.m[j][3] * m2.m[3][i];
        }
    return res;
}
static void vecxm(Vector *v, const Mat4x4 m) {
    
    Vector cache = *v;
    cache.x = v->x * m.m[0][0] + v->y * m.m[1][0] + v->z * m.m[2][0] + v->w * m.m[3][0];
    cache.y = v->x * m.m[0][1] + v->y * m.m[1][1] + v->z * m.m[2][1] + v->w * m.m[3][1];
    cache.z = v->x * m.m[0][2] + v->y * m.m[1][2] + v->z * m.m[2][2] + v->w * m.m[3][2];
    cache.w = v->x * m.m[0][3] + v->y * m.m[1][3] + v->z * m.m[2][3] + v->w * m.m[3][3];
    *v = cache;
}
static Mat4x4 pointat(Vector pos, Vector target, Vector up) {
    // Calculate new Forward direction.
    Vector newForward = sub_vectors(target, pos);
    newForward = norm_vector(newForward);

    // Calculate newUp direction.
    Vector a = multiply_vectors(newForward, dot_product(up, newForward));
    Vector newUp = sub_vectors(up, a);
    newUp = norm_vector(newUp);

    // Calculate new Right direction.
    Vector newRight = cross_product(newUp, newForward);

    Mat4x4 m;
    m.m[0][0] = newRight.x;      m.m[0][1] = newRight.y;      m.m[0][2] = newRight.z;      m.m[0][3] = 0.0;
    m.m[1][0] = newUp.x;         m.m[1][1] = newUp.y;         m.m[1][2] = newUp.z;         m.m[1][3] = 0.0;
    m.m[2][0] = newForward.x;    m.m[2][1] = newForward.y;    m.m[2][2] = newForward.z;    m.m[2][3] = 0.0;
    m.m[3][0] = pos.x;           m.m[3][1] = pos.y;           m.m[3][2] = pos.z;           m.m[3][3] = 1.0;

    return m;
}
static Mat4x4 inverse_mat(Mat4x4 m) {
    Mat4x4 rm;
    rm.m[0][0] = m.m[0][0];    rm.m[0][1] = m.m[1][0];    rm.m[0][2] = m.m[2][0];    rm.m[0][3] = 0.0;
    rm.m[1][0] = m.m[0][1];    rm.m[1][1] = m.m[1][1];    rm.m[1][2] = m.m[2][1];    rm.m[1][3] = 0.0;
    rm.m[2][0] = m.m[0][2];    rm.m[2][1] = m.m[1][2];    rm.m[2][2] = m.m[2][2];    rm.m[2][3] = 0.0;
    rm.m[3][0] = -(m.m[3][0] * rm.m[0][0] + m.m[3][1] * rm.m[1][0] + m.m[3][2] * rm.m[2][0]);
    rm.m[3][1] = -(m.m[3][0] * rm.m[0][1] + m.m[3][1] * rm.m[1][1] + m.m[3][2] * rm.m[2][1]);
    rm.m[3][2] = -(m.m[3][0] * rm.m[0][2] + m.m[3][1] * rm.m[1][2] + m.m[3][2] * rm.m[2][2]);
    rm.m[3][3] = 1.0;

    return rm;
}
static void projection_mat(const float fov) {
    Mat4x4 m = { 0 };
    m.m[0][0] = AspectRatio * FovRadius;
    m.m[1][1] = AspectRatio * FovRadius;
    m.m[2][2] = (ZFar / (ZFar - ZNear));
    m.m[2][3] = 1.0;
    m.m[3][2] = ((-ZFar * ZNear) / (ZFar - ZNear));
    m.m[3][3] = 0.0;

    meshxm(&cube, m);
    ppdiv(&cube);
}
static void rotate_xmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = 1.0;
    m.m[1][1] = cosf(FTheta);
    m.m[1][2] = -sinf(FTheta);
    m.m[2][1] = sinf(FTheta);
    m.m[2][2] = cosf(FTheta);
    m.m[3][3] = 1.0;

    meshxm(&cube, m);
}
static void rotate_ymat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(angle);
    m.m[1][1] = 1.00;
    m.m[0][2] = -sinf(angle);
    m.m[2][0] = sinf(angle);
    m.m[2][2] = cosf(angle);
    m.m[3][3] = 1.0;

    meshxm(&cube, m);
}
static void rotate_zmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(FTheta);
    m.m[0][1] = sinf(FTheta);
    m.m[1][0] = -sinf(FTheta);
    m.m[1][1] = cosf(FTheta);
    m.m[2][2] = 1.0;
    m.m[3][3] = 1.0;

    meshxm(&cube, m);
}
static void move_left(Vector *vcam) {
    vcam->x -= 0.1;
    adjust_camera(*vcam);
}
static void move_right(Vector *vcam) {
    vcam->x += 0.1;
    adjust_camera(*vcam);
}
static void move_up(Vector *vcam) {
    vcam->y -= 0.1;
    adjust_camera(*vcam);
}
static void move_down(Vector *vcam) {
    vcam->y += 0.1;
    adjust_camera(*vcam);
}
static void look_left(float num) {
    num -= 0.2;
    // Mat4x4 matCameraRot = rotate_ymat(num);
    // vecxm(&Target, matCameraRot);
    // LookDir = Target;
    // Target = add_vectors(Camera, LookDir);
    // adjust_camera(Camera);
}
static void look_right(float num) {
    num += 0.2;
    // Mat4x4 matCameraRot = rotate_ymat(num);
    // vecxm(&Target, matCameraRot);
    // LookDir = Target;
    // Target = add_vectors(Camera, LookDir);
    // adjust_camera(Camera);
}
static void move_forward(void) {
    Vector vForward = multiply_vectors(LookDir, 0.1);
    Camera = add_vectors(Camera, vForward);
    adjust_camera(Camera);
}
static void move_backward(void) {
    Vector vForward = multiply_vectors(LookDir, 0.1);
    Camera = sub_vectors(Camera, vForward);
    adjust_camera(Camera);
}
static void adjust_camera(const Vector vcam) {
    // Make camera Matrix.
    Mat4x4 matView = pointat(vcam, Target, Up);
    // Invert Camera matrix.
    Mat4x4 View = inverse_mat(matView);
    meshxm(&cube, View);
}
static float len_vector(const Vector v) {
    return sqrtf(dot_product(v, v));
}
static Vector norm_vector(const Vector v) {
    float len = len_vector(v);
    Vector res = { v.x / len, v.y / len, v.z / len };
    return res;
}
static Vector multiply_vectors(const Vector v1, const float num) {
    Vector res =  { v1.x * num, v1.y * num, v1.z * num };
    return res;
}
static Vector divide_vectors(const Vector v1, const float num) {
    Vector res =  { v1.x / num, v1.y / num, v1.z / num };
    return res;
}
static Vector add_vectors(const Vector v1, const Vector v2) {
    Vector res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return res;
}
static Vector sub_vectors(const Vector v1, const Vector v2) {
    Vector res = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return res;
}
static Vector cross_product(const Vector v1, const Vector v2) {
    Vector cp;
    cp.x = v1.y * v2.z - v1.z * v2.y;
    cp.y = v1.z * v2.x - v1.x * v2.z;
    cp.z = v1.x * v2.y - v1.y * v2.x;
    return cp;
}
static float dot_product(const Vector v1, const Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
static void paint_mesh(SCMesh sc) {

    XGCValues gclines, gcfill, gcil;

    gclines.graphics_exposures = False;
    gclines.line_width = 3;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);

    gcfill.graphics_exposures = False;
    gcfill.foreground = 0xab00a6;
    GC gcf = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcfill);

    Vector cp, line1, line2;
    float dp;
    int vecindex = 1;
    // printf("\x1b[H\x1b[J");
    for (int i = 0; i < sizeof(sc.sctri) / sizeof(SCTriangle); i++)
        
        for (int j = 0; j < sizeof(sc.sctri->scvector) / sizeof(XPoint); j++) {

            line1 = sub_vectors(cube.tri[i].vector[1], cube.tri[i].vector[0]);
            line2 = sub_vectors(cube.tri[i].vector[2], cube.tri[i].vector[0]);
            
            cp = cross_product(line1, line2);

            // if (dot_product(cp, Camera) < 0.0) {

                dp = dot_product(LightSC, cp);
                gcil.graphics_exposures = False;

                if (dp > 0.1 && dp < 0.5) {
                    gcil.foreground = 0xbb09b8;
                } else 
                    gcil.foreground = 0xff00fb;
                GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
                if (i == 0) 
                    // gcil.foreground = 0x0377eb;
                    
                    // GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
                    XFillPolygon(displ, win, gci, sc.sctri[i].scvector, 3, Convex, CoordModeOrigin);

                if (j == 2)
                    vecindex = 0;
                XDrawLine(displ, win, gcl, sc.sctri[i].scvector[j].x, sc.sctri[i].scvector[j].y, sc.sctri[i].scvector[vecindex].x, sc.sctri[i].scvector[vecindex].y);
                vecindex++;
                XFreeGC(displ, gci);
            // }
        }

    XFreeGC(displ, gcl);
    XFreeGC(displ, gcf);

}
static void norm_mesh(const Mesh c) {
    for (int i = 0; i < sizeof(c.tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c.tri->vector) / sizeof(Vector); j++) {

            sccube.sctri[i].scvector[j].x = XWorldToScreen;
            sccube.sctri[i].scvector[j].y = YWorldToScreen;
        }
    paint_mesh(sccube);
}
static KeySym get_keysym(XEvent *event) {

    /* Get user text input */
    XIM xim;
    XIC xic;
    char *failed_arg;
    XIMStyles *styles;

    xim = XOpenIM(displ, NULL, NULL, NULL);
    if (xim == NULL) {
        perror("keypress() - XOpenIM()");
    }
    failed_arg = XGetIMValues(xim, XNQueryInputStyle, &styles, NULL);
    if (failed_arg != NULL) {
        perror("keypress() - XGetIMValues()");
    }
    xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, XNClientWindow, win, NULL);
    if (xic == NULL) {
        perror("keypress() - XreateIC()");
    }
    XSetICFocus(xic);

    KeySym keysym = 0;
    char buffer[32];
    Status status = 0;
    Xutf8LookupString(xic, &event->xkey, buffer, 32, &keysym, &status);
    if (status == XBufferOverflow) {
        perror("Buffer Overflow...\n");
    }
    // printf("Pressed key: %lu.\n", keysym);
    // printf("The Button that was pressed is %s.\n", buffer);

    return keysym;
}
static const void pixmapupdate(void) {

    XGCValues gc_vals;
    gc_vals.graphics_exposures = False;
    GC pix = XCreateGC(displ, win, GCGraphicsExposures, &gc_vals);

    pixmap = XCreatePixmap(displ, win, wa.width, wa.height, wa.depth);
    XCopyArea(displ, win, pixmap, pix, 0, 0, wa.width, wa.height, 0, 0);
    XFreeGC(displ, pix);
}
static const void pixmapdisplay(void) {

    XGCValues gc_vals;
    gc_vals.graphics_exposures = False;
    GC pix = XCreateGC(displ, win, GCGraphicsExposures, &gc_vals);

    XCopyArea(displ, pixmap, win, pix, 0, 0, wa.width, wa.height, 0, 0);
    XFreeGC(displ, pix);
}
static const void atomsinit(void) {

    /* Delete window initializer area */
    wmatom[Win_Close] = XInternAtom(displ, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(displ, win, &wmatom[Win_Close], 1);

    /* Change main window Title */
    wmatom[Win_Name] = XInternAtom(displ, "WM_NAME", False);
    wmatom[Atom_Type] =  XInternAtom(displ, "STRING", False);
    XChangeProperty(displ, win, wmatom[Win_Name], wmatom[Atom_Type], 8, PropModeReplace, (unsigned char*)"Mandelbrot Set", 14);
}
// General initialization and event handling.
const int board(void) {

    XEvent event;

    displ = XOpenDisplay(NULL);
    if (displ == NULL) {
        fprintf(stderr, "Warning: Board - XOpenDisplay()\n");
        return EXIT_FAILURE;
    }
    int screen = XDefaultScreen(displ);

    /*  Root main Window */
    sa.event_mask = EXPOSEMASKS | KEYBOARDMASKS | POINTERMASKS;
    sa.background_pixel = 0x000000;
    win = XCreateWindow(displ, XRootWindow(displ, screen), 0, 0, WIDTH, HEIGHT, 0, CopyFromParent, InputOutput, CopyFromParent, CWBackPixel | CWEventMask, &sa);
    XMapWindow(displ, win);

    atomsinit();

    while (RUNNING) {

        XNextEvent(displ, &event);
        
        if (handler[event.type])
            handler[event.type](&event);
    }
    return EXIT_SUCCESS;
}
int main(int argc, char *argv[]) {

    if (locale_init())
        fprintf(stderr, "Warning: Main -locale()\n");

    if (board())
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

