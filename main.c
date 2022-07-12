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
// World Cube
typedef struct {
    Triangle tri[LastTriangle];
} Cube;
// Screen Cube
typedef struct {
    SCTriangle sctri[LastTriangle];
} SCCube;
// 1st frame Initialization matrix
typedef struct {
    float m[4][4];
} Mat4x4;

#define WIDTH                     800
#define HEIGHT                    800
#define ZNear                     -0.001
#define ZFar                      1000.0
#define FieldOfView               90.0
#define AspectRatio               ( ((float)wa.width / (float)wa.height) )
#define FovRad                    ( 1 / tan(FieldOfView * 0.5 / 180.0 * 3.14159) )
#define FTheta                    ( 1 * 0.2 )
#define XWorldToScreen            ( (1 + c.tri[i].vector[j].x) * (wa.width / 2.00) )
#define YWorldToScreen            ( (1 + c.tri[i].vector[j].y) * (wa.height / 2.00) )

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

Vector camera = { 0.0, 0.0, -1.0 };
Vector LightSC = {
    -1.0, -1.0, 1.0, 1.0
};
Vector el;

#define cube_back     0.5
#define cube_front    0.0
#define cube_size     0.5
Cube cube = {
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
SCCube sccube = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;

// initialize the knot object to be transfered because we can't transfer vectorers to vectorers through shared memory.
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);
static void multiply_matrices(Mat4x4 *m);
// static void perspective_dividation(Cube *c);
static void project_mat(void);
static void move_left(Cube *c);
static void move_right(Cube *c);
static void move_up(Cube *c);
static void move_down(Cube *c);
static void move_forward(Cube *c);
static void move_backward(Cube *c);
static void rotate_xmat(void);
static void rotate_ymat(void);
static void rotate_zmat(void);
static Vector cross_product(const Triangle t);
static float dot_product(const Vector v, const Vector nm);
static void paint_mesh(SCCube sc);
static void norm_mesh(const Cube c);
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
        project_mat();
        if (!MAPCOUNT)
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

    XDrawLine(displ, win, gc, 0, wa.height / 2, wa.width, wa.height / 2);
    XDrawLine(displ, win, gc, wa.width / 2, 0, wa.width / 2, wa.height);

    XFreeGC(displ, gc);

    pixmapupdate();

    norm_mesh(cube);
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

        case 119 : move_forward(&cube); // w
            break;
        case 115 : move_backward(&cube); // s
            break;
        case 65361 : move_left(&cube); // left arrow
            break;
        case 65363 : move_right(&cube); // right arrow
            break;
        case 65362 : move_up(&cube); // up arror
            break;
        case 65364 : move_down(&cube); // down arrow
            break;
        case 120 : rotate_xmat(); // x
            break;
        case 121 : rotate_ymat(); // y
            break;
        case 122 : rotate_zmat(); // z
            break;
        case 101 : /* rotate Yaxis Backwards */
            break;
        case 65293 : /* ZOOM *= 0.10 */; // Enter
            break;
        default :
            return;
    }
    
    pixmapdisplay();
    project_mat();
    norm_mesh(cube);
}
static void multiply_matrices(Mat4x4 *m) {

    Cube cache = cube;
    printf("\x1b[H\x1b[J");
    for (int i = 0; i < sizeof(cube.tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < sizeof(cube.tri->vector) / sizeof(Vector); j++) {

            cache.tri[i].vector[j].x = cube.tri[i].vector[j].x * m->m[0][0] + cube.tri[i].vector[j].y * m->m[1][0] + cube.tri[i].vector[j].z * m->m[2][0] + cube.tri[i].vector[j].w * m->m[3][0];
            cache.tri[i].vector[j].y = cube.tri[i].vector[j].x * m->m[0][1] + cube.tri[i].vector[j].y * m->m[1][1] + cube.tri[i].vector[j].z * m->m[2][1] + cube.tri[i].vector[j].w * m->m[3][1];
            cache.tri[i].vector[j].z = cube.tri[i].vector[j].x * m->m[0][2] + cube.tri[i].vector[j].y * m->m[1][2] + cube.tri[i].vector[j].z * m->m[2][2] + cube.tri[i].vector[j].w * m->m[3][2];
            cache.tri[i].vector[j].w = cube.tri[i].vector[j].x * m->m[0][3] + cube.tri[i].vector[j].y * m->m[1][3] + cube.tri[i].vector[j].z * m->m[2][3] + cube.tri[i].vector[j].w * m->m[3][3];
            
            // if (cache.tri[i].vector[j].w != 0) {
            //     cache.tri[i].vector[j].x /= cache.tri[i].vector[j].w;
            //     cache.tri[i].vector[j].y /= cache.tri[i].vector[j].w;
            //     cache.tri[i].vector[j].z /= cache.tri[i].vector[j].w;
            // }
            if (i == 0) {
                printf("X[%d]: %f\nY: %f\nZ: %f\nW: %f\n", i, cache.tri[i].vector[j].x, cache.tri[i].vector[j].y, cache.tri[i].vector[j].z, cache.tri[i].vector[j].w);
                printf("--------------------------------------------------------\n");
            }
        }
    }
    cube = cache;
}
// static void perspective_dividation(Cube *c) {

//     for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) 
//         for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {
         
//             c->tri[i].vector[j].x /= c->tri[i].vector[j].w;
//             c->tri[i].vector[j].y /= c->tri[i].vector[j].w;
//             c->tri[i].vector[j].z /= c->tri[i].vector[j].w;
//             printf("X: %f\nY: %f\nZ: %f\nW: %f\n", c->tri[i].vector[j].x, c->tri[i].vector[j].y, c->tri[i].vector[j].z, c->tri[i].vector[j].w);
//             printf("--------------------------------------------------------\n");
//         }
// }
static void project_mat(void) {
    Mat4x4 m = { 0 };
    m.m[0][0] = AspectRatio * FovRad;
    m.m[1][1] = FovRad;
    m.m[2][2] = ZFar / (ZFar - ZNear);
    m.m[2][3] = (-ZFar * ZNear) / (ZFar - ZNear);
    m.m[3][2] = 0.0;
    m.m[3][3] = 1.0;

    // init_mesh(&cube);
    multiply_matrices(&m);
    // perspective_dividation(&cube);
}
// static void identity_mat(void) {
//     Mat4x4 m;
//     m.m[0][0] = 1.0;
//     m.m[1][1] = 1.0;
//     m.m[2][2] = 1.0;
//     m.m[3][3] = 1.0;
// }
// static void translation_mat(float x, float y, float z) {
//     Mat4x4 m;
//     m.m[0][0] = 1.0;
//     m.m[1][1] = 1.0;
//     m.m[2][2] = 1.0;
//     m.m[3][3] = 1.0;
//     m.m[3][0] = x;
//     m.m[3][1] = y;
//     m.m[3][2] = z;
// }
static void move_left(Cube *c) {

    for (int i = 0; i < sizeof(cube.tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(cube.tri->vector) / sizeof(Vector); j++) {

            cube.tri[i].vector[j].x -= 0.1;
        }
}
static void move_right(Cube *c) {

    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            c->tri[i].vector[j].x += 0.1;
        }
}
static void move_up(Cube *c) {

    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            c->tri[i].vector[j].y += 0.1;
        }
}
static void move_down(Cube *c) {

    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            c->tri[i].vector[j].y -= 0.1;
        }
}
static void move_forward(Cube *c) {
    
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            c->tri[i].vector[j].z += 0.1;
        }
}
static void move_backward(Cube *c) {

    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c->tri->vector) / sizeof(Vector); j++) {

            c->tri[i].vector[j].z -= 0.1;
        }
}
static void rotate_xmat(void) {
    Mat4x4 m = { 0 };
    m.m[0][0] = 1.0;
    m.m[1][1] = cosf(FTheta);
    m.m[1][2] = -sinf(FTheta);
    m.m[2][1] = sinf(FTheta);
    m.m[2][2] = cosf(FTheta);
    m.m[3][3] = 1.0;

    multiply_matrices(&m);
}
static void rotate_ymat(void) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(FTheta);
    m.m[1][1] = 1.00;
    m.m[0][2] = -sinf(FTheta);
    m.m[2][0] = sinf(FTheta);
    m.m[2][2] = cosf(FTheta);
    m.m[3][3] = 1.0;

    multiply_matrices(&m);
}
static void rotate_zmat(void) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(FTheta);
    m.m[0][1] = sinf(FTheta);
    m.m[1][0] = -sinf(FTheta);
    m.m[1][1] = cosf(FTheta);
    m.m[2][2] = 1.0;
    m.m[3][3] = 1.0;

    multiply_matrices(&m);
}
// static Mat4x4 m_x_m() {
//     Mat4x4 res;
//     for (int i = 0; i < sizeof(res.m) / sizeof(float); i++) 
//         for (int j = 0; j < sizeof(res.m[0]) / sizeof(float); j++) {

//         }
//     return res;
// }
// static float len_vector(const Vector v) {
//     return sqrtf(dot_product(v, v));
// }
// static Vector nor_vector(const Vector v) {
//     float len = len_vector(v);
//     Vector res = { v.x / len, v.y / len, v.z / len };
//     return res;
// }
// static Vector multiply_vectors(const Vector v1, const Vector v2) {
//     Vector res =  { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
//     return res;
// }
// static Vector devide_vectors(const Vector v1, const Vector v2) {
//     Vector res =  { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
//     return res;
// }
// static Vector add_vectors(const Vector v1, const Vector v2) {
//     Vector res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
//     return res;
// }
static Vector sub_vectors(const Vector v1, const Vector v2) {
    Vector res = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return res;
}
static Vector cross_product(const Triangle t) {
    Vector cp, line1, line2;
    line1 = sub_vectors(t.vector[1], t.vector[0]);
    line2 = sub_vectors(t.vector[2], t.vector[0]);

    cp.x = line1.y * line2.z - line1.z * line2.y;
    cp.y = line1.z * line2.x - line1.x * line2.z;
    cp.z = line1.x * line2.y - line1.y * line2.x;

    return cp;
}
static float dot_product(const Vector v1, const Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
static void paint_mesh(SCCube sc) {

    XGCValues gclines, gcfill, gcil;

    gclines.graphics_exposures = False;
    gclines.line_width = 3;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);

    gcfill.graphics_exposures = False;
    gcfill.foreground = 0xab00a6;
    GC gcf = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcfill);

    Vector cp;
    float dp;
    int vecindex = 1;

    for (int i = 0; i < sizeof(sc.sctri) / sizeof(SCTriangle); i++)

        for (int j = 0; j < sizeof(sc.sctri->scvector) / sizeof(XPoint); j++) {
            
            // Here we count the cross product of the world coordinated cube's triangles. S.O.S
            cp = cross_product(cube.tri[i]);

            if (cp.z > 0.0) {

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
            }
        }

    XFreeGC(displ, gcl);
    XFreeGC(displ, gcf);

}
static void norm_mesh(const Cube c) {

    for (int i = 0; i < sizeof(c.tri) / sizeof(Triangle); i++)
        for (int j = 0; j < sizeof(c.tri->vector) / sizeof(Vector); j++) {

            sccube.sctri[i].scvector[j].x = ceil(XWorldToScreen);
            sccube.sctri[i].scvector[j].y = ceil(YWorldToScreen);
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

