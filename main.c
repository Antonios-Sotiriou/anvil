// general headers
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>

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
    Vector vec[LastVector];
} Triangle;
// Screen Triangle
typedef struct {
    // Importand! XPoint here so we can use the xlib build in function to fill the triangles.
    XPoint scvec[LastVector];
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

typedef struct {
    Triangle *tri;
    int indexes;
} BF;

#define WIDTH                     800
#define HEIGHT                    800
#define ZNear                     0.01
#define ZFar                      1000.00 
// #define FieldOfView               90.0
#define AspectRatio               ( ((float)wa.width / (float)wa.height) )
#define FovRadius                 ( 1 / tanf(fov * 0.5 / 180.0 * 3.14159) )
#define XWorldToScreen            ( (1 + c.tri[i].vec[j].x) * (wa.width / 2.00) )
#define YWorldToScreen            ( (1 + c.tri[i].vec[j].y) * (wa.height / 2.00) )
#define TranslateX                ( v.x )
#define TranslateY                ( v.y )
#define TranslateZ                ( v.z )

// #define TranslateX                ( c->tri[i].vector[j].x )
// #define TranslateY                ( c->tri[i].vector[j].y )
// #define TranslateZ                ( c->tri[i].vector[j].z )

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

#define cube_back     0.5f
#define cube_front    0.0
#define cube_size     0.5

Mesh cube = {
    {
        { {{ 0.00, 0.00, cube_front, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }} },    // Front Up
        { {{ 0.00, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },      // Front Down

        { {{ cube_size, 0.00, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }} },    // Back Up
        { {{ cube_size, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, 0.00, cube_back, 1.0 }} },     // Back Down

        { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },     // West Up
        { {{ cube_size,  0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} },       // East Down

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }} },    // East Up
        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }} },     // East Down

        { {{ 0.00, -cube_size, cube_front, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },   // North Up
        { {{ 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}} ,   // North Down

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },       // South Up
        { {{ 0.00, 0.00, cube_back, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} }      // South Down
    }
};
SCMesh sccube = { 0 };
Mesh cache = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
static float ANGLE = 0.05;
static float FOV = 120.0;

// Event handling functions.
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);

// 3D graphics Matrices and computations between.
static Mesh meshxm(Mesh *c, const Mat4x4 m);
static Mat4x4 projection_mat(const float fov);
static Mat4x4 rotate_xmat(const float angle);
static Mat4x4 rotate_ymat(const float angle);
static Mat4x4 rotate_zmat(const float angle);

// 3D graphics Vector computation functions
static float len_vec(const Vector v);
static Vector norm_vec(const Vector v);
static Vector multiply_vecs(const Vector v1, const float num);
static Vector divide_vecs(const Vector v1, const float num);
static Vector add_vecs(const Vector v1, const Vector v2);
static Vector sub_vecs(const Vector v1, const Vector v2);
static Vector cross_product(const Vector v1, const Vector v2);
static float dot_product(const Vector v, const Vector nm);

// Represantation functions
static void project(Mesh c);
static void paint_mesh(SCMesh sc);
static void norm_mesh(const BF c);

// Xlib relative functions and event dispatcher.
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

// Project specific inludes.
#include "header_files/moves.h" 

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
        cache = cube;  // Importand spot.
        MAPCOUNT = 1;
    }
}
static const void expose(XEvent *event) {

    printf("expose event received\n");
    pixmapupdate();
    project(cache);
}
static const void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
static const void configurenotify(XEvent *event) {

    //printf("configurenotify event received\n");
}
static const void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
}
static const void keypress(XEvent *event) {

    KeySym keysym = get_keysym(event);
    
    switch (keysym) {

        case 120 : rotate_x(&cache, ANGLE); // x
            break;
        case 121 : rotate_y(&cache, ANGLE); // y
            break;
        case 122 : rotate_z(&cache, ANGLE); // z
            break;
        default :
            return;
    }
    cube = cache;  // Importand spot.

    pixmapdisplay();
    project(cache);
}
static Mesh meshxm(Mesh *c, const Mat4x4 m) {

    Mesh ch = *c;
    // printf("\x1b[H\x1b[J");
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < sizeof(c->tri->vec) / sizeof(Vector); j++) {
            
            ch.tri[i].vec[j].x = c->tri[i].vec[j].x * m.m[0][0] + c->tri[i].vec[j].y * m.m[1][0] + c->tri[i].vec[j].z * m.m[2][0] + c->tri[i].vec[j].w * m.m[3][0];
            ch.tri[i].vec[j].y = c->tri[i].vec[j].x * m.m[0][1] + c->tri[i].vec[j].y * m.m[1][1] + c->tri[i].vec[j].z * m.m[2][1] + c->tri[i].vec[j].w * m.m[3][1];
            ch.tri[i].vec[j].z = c->tri[i].vec[j].x * m.m[0][2] + c->tri[i].vec[j].y * m.m[1][2] + c->tri[i].vec[j].z * m.m[2][2] + c->tri[i].vec[j].w * m.m[3][2];
            ch.tri[i].vec[j].w = c->tri[i].vec[j].x * m.m[0][3] + c->tri[i].vec[j].y * m.m[1][3] + c->tri[i].vec[j].z * m.m[2][3] + c->tri[i].vec[j].w * m.m[3][3];
        }
    }
    return ch;
}
static void ppdiv(BF *c) {
    for (int i = 0; i < c->indexes; i++) {
        for (int j = 0; j < 3; j++) {

            if (c->tri[i].vec[j].w != 0 ) {
                c->tri[i].vec[j].x /= c->tri[i].vec[j].w;
                c->tri[i].vec[j].y /= c->tri[i].vec[j].w;
                c->tri[i].vec[j].z /= c->tri[i].vec[j].w;
            }
        }
    }
}
static BF bfculling(const Mesh c) {
    BF res = { 0 };
    Vector cp, line1, line2;
    int counter = 1;
    int index = 0;
    res.tri = malloc(sizeof(Triangle));

    for (int i = 0; i < sizeof(c.tri) / sizeof(Triangle); i++) {
        line1 = sub_vecs(c.tri[i].vec[1], c.tri[i].vec[0]);
        line2 = sub_vecs(c.tri[i].vec[2], c.tri[i].vec[0]);

        cp = cross_product(line1, line2);
        if (dot_product(cp, Camera) < 0.00) {
            res.tri = realloc(res.tri, sizeof(Triangle) * counter);
            res.tri[index] = c.tri[i];
            counter++;
            index++;
        }
    }
    res.indexes = index;
    return res;
}
float depth(Triangle t) {
    float res = 0;
    int count = 0;
    for (int i = 0; i < sizeof(t) / sizeof(Vector); i++) {
        res += t.vec[i].z;
        count++;
    }
    return res / count;
}
static BF sort_vectors(BF *c) {

    Triangle value = { 0 };
    int pos = 0;

    for (int i = 0; i < c->indexes; i++) {
        
        for (int j = pos; j < c->indexes; j++) {

            if (depth(c->tri[i]) > depth(c->tri[j])) {
                value = c->tri[i];
                c->tri[i] = c->tri[j];
                c->tri[j] = value;
            }
        }
        pos++;
    }
    return *c;
}
static void project(Mesh c) {
    Mat4x4 m = projection_mat(FOV);
    c = meshxm(&cube, m);

    // Triangles must be checked for cross product.
    BF res = bfculling(c);
    // Applying perspective division.
    ppdiv(&res);
    // Triangles must possibly be sorted according to z value and then be passed to rasterizer.
    res = sort_vectors(&res);
    // Sending to translation to Screen Coordinates.
    norm_mesh(res);
    
    free(res.tri);
}
static Mat4x4 projection_mat(const float fov) {
    Mat4x4 m = { 0 };
    m.m[0][0] = AspectRatio * FovRadius;
    m.m[1][1] = FovRadius;
    m.m[2][2] = (ZFar / (ZFar - ZNear));
    m.m[2][3] = 1.0;
    m.m[3][2] = ((-ZFar * ZNear) / (ZFar - ZNear));
    m.m[3][3] = 1.0;
    return m;
}
void rotate_x(Mesh *c, const float angle) {
    Mat4x4 m = rotate_xmat(angle);
    *c = meshxm(&cube, m);
}
static Mat4x4 rotate_xmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = 1.0;
    m.m[1][1] = cosf(angle);
    m.m[1][2] = -sinf(angle);
    m.m[2][1] = sinf(angle);
    m.m[2][2] = cosf(angle);
    m.m[3][3] = 1.0;
    return m;
}
void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(angle);
    *c = meshxm(&cube, m);
}
static Mat4x4 rotate_ymat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(angle);
    m.m[1][1] = 1.00;
    m.m[0][2] = -sinf(angle);
    m.m[2][0] = sinf(angle);
    m.m[2][2] = cosf(angle);
    m.m[3][3] = 1.0;
    return m;
}
void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(angle);
    *c = meshxm(&cube, m);
}
static Mat4x4 rotate_zmat(const float angle) {
    Mat4x4 m = { 0 };
    m.m[0][0] = cosf(angle);
    m.m[0][1] = sinf(angle);
    m.m[1][0] = -sinf(angle);
    m.m[1][1] = cosf(angle);
    m.m[2][2] = 1.0;
    m.m[3][3] = 1.0;
    return m;
}
static float len_vec(const Vector v) {
    return sqrtf(dot_product(v, v));
}
static Vector norm_vec(const Vector v) {
    float len = len_vec(v);
    Vector res = { v.x / len, v.y / len, v.z / len };
    return res;
}
static Vector multiply_vecs(const Vector v1, const float num) {
    Vector res =  { v1.x * num, v1.y * num, v1.z * num };
    return res;
}
static Vector divide_vecs(const Vector v1, const float num) {
    Vector res =  { v1.x / num, v1.y / num, v1.z / num };
    return res;
}
static Vector add_vecs(const Vector v1, const Vector v2) {
    Vector res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return res;
}
static Vector sub_vecs(const Vector v1, const Vector v2) {
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

    for (int i = 0; i < sizeof(sc.sctri) / sizeof(SCTriangle); i++)
        
        for (int j = 0; j < sizeof(sc.sctri->scvec) / sizeof(XPoint); j++) {

            line1 = sub_vecs(cache.tri[i].vec[1], cache.tri[i].vec[0]);
            line2 = sub_vecs(cache.tri[i].vec[2], cache.tri[i].vec[0]);
            
            cp = cross_product(line1, line2);

            dp = dot_product(LightSC, cp);
            gcil.graphics_exposures = False;

            if (dp > 0.1 && dp < 0.5) {
                gcil.foreground = 0xbb09b8;
            } else 
                gcil.foreground = 0xff00fb;
            GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
            if (i == 0) {
                // gcil.foreground = 0x0377eb;
                // GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
                XFillPolygon(displ, win, gci, sc.sctri[i].scvec, 3, Convex, CoordModeOrigin);
            }

            if (j == 2)
                vecindex = 0;
            XDrawLine(displ, win, gcl, sc.sctri[i].scvec[j].x, sc.sctri[i].scvec[j].y, sc.sctri[i].scvec[vecindex].x, sc.sctri[i].scvec[vecindex].y);
            vecindex++;
            XFreeGC(displ, gci);
        }

    XFreeGC(displ, gcl);
    XFreeGC(displ, gcf);

}
static void norm_mesh(const BF c) {
    for (int i = 0; i < c.indexes; i++)
        for (int j = 0; j < 3; j++) {

            sccube.sctri[i].scvec[j].x = XWorldToScreen;
            sccube.sctri[i].scvec[j].y = YWorldToScreen;
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

    wmatom[Win_Close] = XInternAtom(displ, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(displ, win, &wmatom[Win_Close], 1);

    wmatom[Win_Name] = XInternAtom(displ, "WM_NAME", False);
    wmatom[Atom_Type] =  XInternAtom(displ, "STRING", False);
    XChangeProperty(displ, win, wmatom[Win_Name], wmatom[Atom_Type], 8, PropModeReplace, (unsigned char*)"Anvil", 5);
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

