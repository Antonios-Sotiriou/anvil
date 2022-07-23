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
#define XWorldToScreen            ( (1 + c.tri[i].vec[j].x) * (wa.width / 2.00) )
#define YWorldToScreen            ( (1 + c.tri[i].vec[j].y) * (wa.height / 2.00) )
#define TranslateX                ( v.x )
#define TranslateY                ( v.y )
#define TranslateZ                ( v.z )

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

Vector Camera = { 0.0, 0.0, -1.0, 1.0 }, Up = { 0.0, -1.0, 0.0, 1.0 }, LookDir = { 0.0, 0.0, 1.0, 1.0 }, Target = { 0.0, 0.0, 1.0, 1.0 };
Vector LightSC = {
    -1.0, -1.0, 1.0, 1.0
};

#define cube_back     0.5
#define cube_front    0.0
#define cube_size     0.5
Mesh cube = {
    {
        { {{ 0.00, 0.00, cube_front, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }} },    /* Front Up */
        { {{ 0.00, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },      /* Front Down */

        { {{ cube_size, 0.00, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }} },    /* Back Up */
        { {{ cube_size, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, 0.00, cube_back, 1.0 }} },     /* Back Down */

        { {{ cube_size, 0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },     /* West Up */
        { {{ cube_size,  0.00, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} },       /* East Down */

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }} },    /* East Up */
        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, -cube_size, cube_front, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }} },     /* East Down */

        { {{ 0.00, -cube_size, cube_front, 1.0 }, { 0.00, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }} },   /* North Up */
        { {{ 0.00, -cube_size, cube_front, 1.0 }, { cube_size, -cube_size, cube_back, 1.0 }, { cube_size, -cube_size, cube_front, 1.0 }}} ,   /* North Down */

        { {{ 0.00, 0.00, cube_back, 1.0 }, { 0.00, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }} },       /* South Up */
        { {{ 0.00, 0.00, cube_back, 1.0 }, { cube_size, 0.00, cube_front, 1.0 }, { cube_size, 0.00, cube_back, 1.0 }} }      /* South Down */
    }
};
Mesh cache = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
float AspectRatio = 0;
float FOV = 120.0;
static float ANGLE = 0.05;

/* Event handling functions. */
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);

/* Moving functions */
void rotate_x(Mesh *c, const float angle);
void rotate_y(Mesh *c, const float angle);
void rotate_z(Mesh *c, const float angle);

/* Represantation functions */
static void project(Mesh c);
static void ppdiv(Mesh *c);
const static BackFace bfculling(const Mesh c);
const static void draw(const SCMesh sc, const BackFace c);
const static void rasterize(const BackFace c);

/* Xlib relative functions and event dispatcher. */
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

/* Project specific inludes. */
#include "header_files/matrices.h"
#include "header_files/vectors_math.h"

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
    AspectRatio = ((float)wa.width / (float)wa.height);
}
static const void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");

    if (MAPCOUNT) {
        pixmapdisplay();
    } else {
        cache = cube;  /* Importand spot. */
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

    if (!event->xconfigure.send_event) {
        printf("configurenotify event received\n");
        XGetWindowAttributes(displ, win, &wa);
        AspectRatio = ((float)wa.width / (float)wa.height);
    }
}
static const void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
}
static const void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    
    switch (keysym) {

        case 120 : rotate_x(&cache, ANGLE); /* x */
            break;
        case 121 : rotate_y(&cache, ANGLE); /* y */
            break;
        case 122 : rotate_z(&cache, ANGLE); /* z */
            break;
        default :
            return;
    }
    cube = cache;  /* Importand spot. */

    pixmapdisplay();
    project(cache);
}
/* Rotates object according to World X axis. */
void rotate_x(Mesh *c, const float angle) {
    Mat4x4 m = rotate_xmat(angle);
    *c = meshxm(&cube, m);
}
/* Rotates object according to World Y axis. */
void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(angle);
    *c = meshxm(&cube, m);
}
/* Rotates object according to World Z axis. */
void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(angle);
    *c = meshxm(&cube, m);
}
/* Starts the Projection Pipeline. */
static void project(Mesh c) {
    Mat4x4 m = projection_mat(FOV, AspectRatio);
    c = meshxm(&cube, m);
    /* Applying perspective division. */
    ppdiv(&c);
    /* Triangles must be checked for cross product. */
    BackFace bf = bfculling(c);
    /* Triangles must possibly be sorted according to z value and then be passed to rasterizer. */
    /* res = sort_vectors(&res); */
    /* Sending to translation to Screen Coordinates. */
    rasterize(bf);
    
    free(bf.tri);
}
/* Perspective division. */
static void ppdiv(Mesh *c) {
    for (int i = 0; i < sizeof(c->tri) / sizeof(Triangle); i++) {
        for (int j = 0; j < 3; j++) {

            if (c->tri[i].vec[j].w != 0) {
                c->tri[i].vec[j].x /= c->tri[i].vec[j].w;
                c->tri[i].vec[j].y /= c->tri[i].vec[j].w;
                c->tri[i].vec[j].z /= c->tri[i].vec[j].w;
            }
        }
    }
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic BackFace stucture Triangles array. */
const static BackFace bfculling(const Mesh c) {
    BackFace res = { 0 };
    Vector cp;
    int counter = 1;
    int index = 0;
    res.tri = malloc(sizeof(Triangle));
    if (!res.tri)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < sizeof(c.tri) / sizeof(Triangle); i++) {

        cp = triangle_cp(c.tri[i]);
        if (dot_product(cp, Camera) < 0.00) {
            res.tri = realloc(res.tri, sizeof(Triangle) * counter);

            if (!res.tri)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            res.tri[index] = c.tri[i];
            counter++;
            index++;
        }
    }
    res.indexes = index;
    return res;
}
/* Draws the Mesh's Triangles on screen in 2D coordinates. */
const static void draw(const SCMesh sc, const BackFace c) {

    XGCValues gclines, gcil;
    gclines.graphics_exposures = False;
    gclines.line_width = 3;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);

    Vector cp;
    float dp;
    int vecindex = 1;

    for (int i = 0; i < sc.indexes; i++) {

        for (int j = 0; j < 3; j++) {
            /* Attention here.We compute the cross product of the world coordinates mesh not the screen. */
            cp = triangle_cp(c.tri[i]);
            dp = dot_product(cp, LightSC);
            gcil.graphics_exposures = False;
            
            if (dp > 0.00) {
                gcil.foreground = 0xbb09b8;
            } else 
                gcil.foreground = 0xff00fb;

            GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
            XFillPolygon(displ, win, gci, sc.sctri[i].scvec, 3, Convex, CoordModeOrigin);

            if (j == 2)
                vecindex = 0;
            XDrawLine(displ, win, gcl, sc.sctri[i].scvec[j].x, sc.sctri[i].scvec[j].y, sc.sctri[i].scvec[vecindex].x, sc.sctri[i].scvec[vecindex].y);
            vecindex++;
            XFreeGC(displ, gci);
        }
    }
    XFreeGC(displ, gcl);
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void rasterize(const BackFace c) {

    SCMesh scmesh;
    scmesh.sctri = calloc(c.indexes, sizeof(SCTriangle));

    if (!scmesh.sctri)
        fprintf(stderr, "Could not allocate memory - rasterize() - calloc\n");

    scmesh.indexes = c.indexes;

    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            scmesh.sctri[i].scvec[j].x = XWorldToScreen;
            scmesh.sctri[i].scvec[j].y = YWorldToScreen;
        }
    }
    draw(scmesh, c);
    free(scmesh.sctri);
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
/* General initialization and event handling. */
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

