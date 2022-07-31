/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

/* Project specific headers */
#include "header_files/locale.h"
#include "header_files/objects.h"

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};

#define WIDTH                     800
#define HEIGHT                    800
#define XWorldToScreen            ( (1 + c.t[i].v[j].x) * (wa.width / 2.00) )
#define YWorldToScreen            ( (1 + c.t[i].v[j].y) * (wa.height / 2.00) )

// #define NormalizeWorldX           ( (c.t[i].v[j].x + (wa.width / 2.00)) / wa.width )
// #define NormalizeWorldY           ( (c.t[i].v[j].y + (wa.height / 2.00)) / wa.height )
// #define XWorldToScreen            ( normalized.t[i].v[j].x * wa.width )
// #define YWorldToScreen            ( normalized.t[i].v[j].y * wa.height )

#define POINTERMASKS              ( ButtonPressMask )
#define KEYBOARDMASKS             ( KeyPressMask )
#define EXPOSEMASKS               ( StructureNotifyMask | ExposureMask )

/* Some Global Variables */
Display *displ;
Window win;
Pixmap pixmap;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

Vector  Camera   =   { 0.0, 0.0, -1.0, 0.0 }, 
        U        =   { 1.0, 0.0, 0.0, 0.0 },
        V        =   { 0.0, 1.0, 0.0, 0.0 },
        N        =   { 0.0, 0.0, 1.0, 0.0 };

Vector LightSC   = { -1.0, -1.0, 0.0, 0.0 };

// #define cube_back    0.25
// #define cube_front   0.0
// #define cube_size    0.25
// Mesh cube = {
//     {
//         { {{ 0.00, 0.00, cube_front, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }} },    /* Front Up */
//         { {{ 0.00, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },      /* Front Down */

//         { {{ cube_size, 0.00, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }} },    /* Back Up */
//         { {{ cube_size, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, 0.00, cube_back, 1.0 }} },     /* Back Down */

//         { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },     /* West Up */
//         { {{ cube_size,  0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} },       /* East Down */

//         { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }} },    /* East Up */
//         { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }} },     /* East Down */

//         { {{ 0.00, -cube_size, cube_front, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },   /* North Up */
//         { {{ 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}} ,   /* North Down */

//         { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },       /* South Up */
//         { {{ 0.00, 0.00, cube_back, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} },      /* South Down */
//     },
//     .indexes = 12
// };
Mesh cube = { 0 };
Mesh cache = { 0 };
Mat4x4 WorldMat = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
float AspectRatio = 0;
float FOV = 90.0;
static float ANGLE = 0.05;
static float FYaw = 0.1;

/* Event handling functions. */
const static void clientmessage(XEvent *event);
const static void reparentnotify(XEvent *event);
const static void mapnotify(XEvent *event);
const static void expose(XEvent *event);
const static void resizerequest(XEvent *event);
const static void configurenotify(XEvent *event);
const static void buttonpress(XEvent *event);
const static void keypress(XEvent *event);

/* Moving functions */
static void look_left(float fyaw);
static void move_backward(Vector *v);
static void look_right(float fyaw);
static void move_forward(Vector *v);
static void move_left(Vector *v);
static void move_right(Vector *v);
static void move_up(Vector *v);
static void move_down(Vector *v);
static void rotate_x(Mesh *c, const float angle);
static void rotate_y(Mesh *c, const float angle);
static void rotate_z(Mesh *c, const float angle);

/* Represantation functions */
static void project(Mesh c);
static void ppdiv(Mesh *c);
const static BackFace bfculling(const Mesh c);
const static void draw(const SCMesh sc, const BackFace c);
const static void rasterize(const BackFace c);

/* Xlib relative functions and event dispatcher. */
static KeySym get_keysym(XEvent *event);
const static void pixmapupdate(void);
const static void pixmapdisplay(void);
const static void atomsinit(void);
const static int board(void);
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

/* Project specific inludes. */
#include "header_files/matrices.h"
#include "header_files/vectors_math.h"
#include "header_files/obj_parser.h"

const static void clientmessage(XEvent *event) {

    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW");

        free(cube.t);

        XFreePixmap(displ, pixmap);
        XDestroyWindow(displ, win);
        XCloseDisplay(displ);
        
        RUNNING = 0;
    }
}
const static void reparentnotify(XEvent *event) {

    printf("reparentnotify event received\n");
    XGetWindowAttributes(displ, win, &wa);
    AspectRatio = ((float)wa.width / (float)wa.height);
}
const static void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");

    if (MAPCOUNT) {
        pixmapdisplay();
    } else {
        cube = load_obj("/home/as/Desktop/spaceship.obj");
        
        cache = cube;  /* Importand spot. */

        Mat4x4 sm = scale_mat(1.5);
        Mat4x4 tm = translation_mat(0.0, 0.0, 1.0);
        Mat4x4 WorldMat = mxm(sm, tm);
        cache = meshxm(cube, WorldMat);
        MAPCOUNT = 1;
    }
}
const static void expose(XEvent *event) {

    printf("expose event received\n");
    pixmapupdate();
    project(cache);
}
const static void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
const static void configurenotify(XEvent *event) {

    if (!event->xconfigure.send_event) {
        printf("configurenotify event received\n");
        XGetWindowAttributes(displ, win, &wa);
        AspectRatio = ((float)wa.width / (float)wa.height);
    }
}
const static void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
}
const static void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    
    switch (keysym) {

        case 119 : move_forward(&Camera);         /* w */
            break;
        case 97 : look_left(FYaw);                /* a */
            break;
        case 115 : move_backward(&Camera);        /* s */
            break;
        case 100 : look_right(FYaw);              /* d */
            break;
        case 65361 : move_left(&Camera);          /* left arrow */
            break;
        case 65363 : move_right(&Camera);         /* right arrow */
            break;
        case 65362 : move_up(&Camera);            /* up arror */
            break;
        case 65364 : move_down(&Camera);          /* down arrow */
            break;
        case 120 : rotate_x(&cache, ANGLE);       /* x */
            break;
        case 121 : rotate_y(&cache, ANGLE);       /* y */
            break;
        case 122 : rotate_z(&cache, ANGLE);       /* z */
            break;
        default :
            return;
    }
    cube = cache;  /* Importand spot. */

    pixmapdisplay();

    project(cache);
}
/* Rotates the camera to look left. */
static void look_left(float fyaw) {
    fyaw = -FYaw;
    fyaw += 0.05;
    Mat4x4 m = rotate_ymat(fyaw);
    U = vecxm(U, m);
    N = vecxm(N, m);
}
static void move_backward(Vector *v) {
    Vector tempN = multiply_vec(N, 0.1);
    Camera = sub_vecs(Camera, tempN);
}
/* Rotates the camera to look right. */
static void look_right(float fyaw) {
    fyaw -= 0.05;
    Mat4x4 m = rotate_ymat(fyaw);
    U = vecxm(U, m);
    N = vecxm(N, m);
}
static void move_forward(Vector *v) {
    Vector tempN = multiply_vec(N, 0.1);
    Camera = add_vecs(Camera, tempN);
}
/* Moves camera position left. */
static void move_left(Vector *v) {
    v->x -= 0.1;
}
/* Moves camera position right. */
static void move_right(Vector *v) {
    v->x += 0.1;
}
/* Moves camera position Up. */
static void move_up(Vector *v) {
    v->y -= 0.1;
}
/* Moves camera position Down. */
static void move_down(Vector *v) {
    v->y += 0.1;
}
/* Rotates object according to World X axis. */
static void rotate_x(Mesh *c, const float angle) {
    Mat4x4 m = rotate_xmat(angle);
    *c = meshxm(cube, m);
}
/* Rotates object according to World Y axis. */
static void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(angle);
    *c = meshxm(cube, m);
}
/* Rotates object according to World Z axis. */
static void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(angle);
    *c = meshxm(cube, m);
}
/* Starts the Projection Pipeline. */
static void project(Mesh c) {

    /* Translation Matrix doesn't working without ppdiv. */
    // Mat4x4 sm = scale_mat(0.2);
    // Mat4x4 tm = translation_mat(0.0, 0.0, 1.0);
    // Mat4x4 lm = mxm(sm, tm);

    Mat4x4 matCamera = camera_mat(Camera, U, V, N);

    // Make view matrix from camera
    Mat4x4 reView = inverse_mat(matCamera);
    

    Mat4x4 m = projection_mat(FOV, AspectRatio);

    Mat4x4 nm = mxm(reView, m);

    c = meshxm(cube, nm);
    /* Applying perspective division. */
    ppdiv(&c);
    /* Triangles must be checked for cross product. */
    BackFace bf = bfculling(c);

    /* Triangles must possibly be sorted according to z value and then be passed to rasterizer. */
    bf = sort_triangles(&bf);

    /* Sending to translation to Screen Coordinates. */
    rasterize(bf);
    
    free(bf.t);
}
/* Perspective division. */
static void ppdiv(Mesh *c) {
    for (int i = 0; i < c->indexes; i++) {
        for (int j = 0; j < 3; j++) {

            if (c->t[i].v[j].w != 0) {
                c->t[i].v[j].x /= c->t[i].v[j].w;
                c->t[i].v[j].y /= c->t[i].v[j].w;
                c->t[i].v[j].z /= c->t[i].v[j].w;
            }
        }
    }
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic BackFace stucture Triangles array. */
const static BackFace bfculling(const Mesh c) {
    BackFace r = { 0 };
    Vector cp;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.indexes; i++) {

        cp = triangle_cp(c.t[i]);
        if (dot_product(cp, Camera) < 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];
            counter++;
            index++;
        }
    }
    r.indexes = index;
    return r;
}
/* Draws the Mesh's Triangles on screen in 2D coordinates. */
const static void draw(const SCMesh sc, const BackFace c) {

    XGCValues gclines, gcil;
    gclines.graphics_exposures = False;
    gclines.line_width = 1;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);

    Vector cp;
    float dp;
    int vindex = 1;

    for (int i = 0; i < sc.indexes; i++) {

        for (int j = 0; j < 3; j++) {
            /* Attention here.We compute the cross product of the world coordinates BackFace not the screen. */
            cp = triangle_cp(c.t[i]);
            dp = dot_product(cp, LightSC);
            gcil.graphics_exposures = False;

            if (dp > 0.00) {
                gcil.foreground = 0xbb09b8;
            } else 
                gcil.foreground = 0xff00fb;

            GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
            XFillPolygon(displ, win, gci, sc.sct[i].scv, 3, Convex, CoordModeOrigin);

            if (j == 2)
                vindex = 0;
            XDrawLine(displ, win, gcl, sc.sct[i].scv[j].x, sc.sct[i].scv[j].y, sc.sct[i].scv[vindex].x, sc.sct[i].scv[vindex].y);
            vindex++;
            XFreeGC(displ, gci);
        }
    }
    XFreeGC(displ, gcl);
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void rasterize(const BackFace c) {

    SCMesh scmesh;
    // BackFace normalized = c;
    scmesh.sct = calloc(c.indexes, sizeof(SCTriangle));

    if (!scmesh.sct)
        fprintf(stderr, "Could not allocate memory - rasterize() - calloc\n");

    scmesh.indexes = c.indexes;

    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            // normalized.t[i].v[j].x = NormalizeWorldX;
            // normalized.t[i].v[j].y = NormalizeWorldY;           

            scmesh.sct[i].scv[j].x = XWorldToScreen;
            scmesh.sct[i].scv[j].y = YWorldToScreen;
        }
    }
    draw(scmesh, c);
    free(scmesh.sct);
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
const static void pixmapupdate(void) {

    XGCValues gc_vals;
    gc_vals.graphics_exposures = False;
    GC pix = XCreateGC(displ, win, GCGraphicsExposures, &gc_vals);

    pixmap = XCreatePixmap(displ, win, wa.width, wa.height, wa.depth);
    XCopyArea(displ, win, pixmap, pix, 0, 0, wa.width, wa.height, 0, 0);
    XFreeGC(displ, pix);
}
const static void pixmapdisplay(void) {

    XGCValues gc_vals;
    gc_vals.graphics_exposures = False;
    GC pix = XCreateGC(displ, win, GCGraphicsExposures, &gc_vals);

    XCopyArea(displ, pixmap, win, pix, 0, 0, wa.width, wa.height, 0, 0);
    XFreeGC(displ, pix);
}
const static void atomsinit(void) {

    wmatom[Win_Close] = XInternAtom(displ, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(displ, win, &wmatom[Win_Close], 1);

    wmatom[Win_Name] = XInternAtom(displ, "WM_NAME", False);
    wmatom[Atom_Type] =  XInternAtom(displ, "STRING", False);
    XChangeProperty(displ, win, wmatom[Win_Name], wmatom[Atom_Type], 8, PropModeReplace, (unsigned char*)"Anvil", 5);
}
/* General initialization and event handling. */
const static int board(void) {

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

