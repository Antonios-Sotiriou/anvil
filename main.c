/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>

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

Vector  Camera   =   { 0.0, 0.0, 0.01, 0.0 },
        U        =   { 1.0, 0.0, 0.0, 0.0 },
        V        =   { 0.0, 1.0, 0.0, 0.0 },
        N        =   { 0.0, 0.0, 1.0, 0.0 };

Vector LightSC   =   { -1.0, -1.0, 0.0, 0.0 };

Vector NPlane = { 0.0, 0.0, 1.05 };
Vector FPlane = { 0.0, 0.0, 1.2 };

Mesh cube;
Mat4x4 WorldMat = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
float AspectRatio = 0;
float FOV = 75.0;
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
const static Mesh bfculling(const Mesh c);
const static void draw(const SCMesh sc, const Mesh c);
const static void rasterize(const Mesh c);

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
#include "header_files/clipping.h"

/* Testing */
#include "header_files/test_shape.h"

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
        // load_obj(&cube, "objects/middleterrain.obj");
        shape_create(&cube);

        Mat4x4 sm = scale_mat(1.0);
        Mat4x4 tm = translation_mat(0.0, 0.0, 2.0);
        Mat4x4 WorldMat = mxm(sm, tm);
        cube = meshxm(cube, WorldMat);

        MAPCOUNT = 1;
    }
}
const static void expose(XEvent *event) {

    printf("expose event received\n");
    pixmapupdate();
    project(cube);
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
    printf("Key Pressed: %ld\n", keysym);
    printf("\x1b[H\x1b[J");
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
        case 120 : rotate_x(&cube, ANGLE);       /* x */
            break;
        case 121 : rotate_y(&cube, ANGLE);       /* y */
            break;
        case 122 : rotate_z(&cube, ANGLE);       /* z */
            break;
        case 65451 : FPlane.z += 0.01;       /* + */
            printf("FPlane.z: %f\n\n", FPlane.z);
            break;
        case 65453 : FPlane.z -= 0.01;       /* - */
            printf("FPlane.z: %f\n\n", FPlane.z);
            break;
        case 65450 : NPlane.z += 0.01;       /* * */
            printf("NPlane.z: %f\n\n", NPlane.z);
            break;
        case 65455 : NPlane.z -= 0.01;       /* / */
            printf("NPlane.z: %f\n\n", NPlane.z);
            break;
        default :
            return;
    }

    pixmapdisplay();
    
    project(cube);
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
    Vector tempU = multiply_vec(U, 0.1);
    Camera = sub_vecs(Camera, tempU);
}
/* Moves camera position right. */
static void move_right(Vector *v) {
    Vector tempU = multiply_vec(U, 0.1);
    Camera = add_vecs(Camera, tempU);
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

    Mat4x4 matCamera = camera_mat(Camera, U, V, N);

    // Make view matrix from camera
    Mat4x4 reView = inverse_mat(matCamera);
    
    Mat4x4 m = projection_mat(FOV, AspectRatio);

    Mat4x4 nm = mxm(reView, m);

    Mesh cache = { 0 };
    cache = meshxm(c, nm);

    /* Applying perspective division. */
    ppdiv(&cache);

    /* Triangles must be checked for cross product. */
    Mesh bf = bfculling(cache);
    free(cache.t);

    /* At this Point triangles must be clipped against near plane. */
    Vector plane_near_p = NPlane,
           plane_near_n = { 0.0, 0.0, 1.0 };
    Mesh nf = clipp(bf, plane_near_p, plane_near_n);
    free(bf.t);

    // ppdiv(&nf);

    Vector plane_far_p = FPlane, //{ 0.0, 0.0, 1.2 },
           plane_far_n = { 0.0, 0.0, -1.0 };
    Mesh ff = clipp(nf, plane_far_p, plane_far_n);
    free(nf.t);

    // ppdiv(&ff);
    // Mesh bf = bfculling(ff);
    // free(ff.t);

    Vector plane_right_p = { 1.0, 0.0, 0.0 },
           plane_right_n = { -1.0, 0.0, 0.0 };
    Mesh rf = clipp(ff, plane_right_p, plane_right_n);
    free(ff.t);

    Vector plane_left_p = { -1.0, 0.0, 0.0 },
           plane_left_n = { 1.0, 0.0, 0.0 };
    Mesh lf = clipp(rf, plane_left_p, plane_left_n);
    free(rf.t);

    Vector plane_up_p = { 0.0, -1.0, 0.0 },
           plane_up_n = { 0.0, 1.0, 0.0 };
    Mesh uf = clipp(lf, plane_up_p, plane_up_n);
    free(lf.t);

    Vector plane_down_p = { 0.0, 1.0, 0.0 },
           plane_down_n = { 0.0, -1.0, 0.0 };
    Mesh df = clipp(uf, plane_down_p, plane_down_n);
    free(uf.t);

    /* Triangles must possibly be sorted according to z value and then be passed to rasterizer. */
    df = sort_triangles(&df);

    // printf("\x1b[H\x1b[J");
    printf("Camera X: %f\nCamera Y: %f\nCamera Z: %f\n", Camera.x, Camera.y, Camera.z);

    /* Sending to translation to Screen Coordinates. */
    rasterize(df);
    
    free(df.t);
}
/* Perspective division. */
static void ppdiv(Mesh *c) {
    for (int i = 0; i < c->indexes; i++) {
        for (int j = 0; j < 3; j++) {

            if ( c->t[i].v[j].w > 1.00 ) {
                    c->t[i].v[j].x /= c->t[i].v[j].w;
                    c->t[i].v[j].y /= c->t[i].v[j].w;
                    c->t[i].v[j].z /= c->t[i].v[j].w;
            }
        }
    }
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic Mesh stucture Triangles array. */
const static Mesh bfculling(const Mesh c) {
    Mesh r = { 0 };
    Vector cp;
    float dp;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.indexes; i++) {

        cp = triangle_cp(c.t[i]);
        dp = dot_product(Camera, cp);

        // if (Camera.z < 0.00)
        //     dp *= -1;
        // else if (Camera.z == 0.00)
        //     dp = -0.1;

        if (dp > 0.00) {
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
const static void draw(const SCMesh sc, const Mesh c) {

    XGCValues gclines, gcil;
    gclines.graphics_exposures = False;
    gclines.line_width = 1;
    gclines.foreground = 0xffffff;
    GC gcl = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gclines);

    // Vector cp;
    // float dp;
    int vindex = 1;

    for (int i = 0; i < sc.indexes; i++) {

        for (int j = 0; j < 3; j++) {
            /* Attention here.We compute the cross product of the world coordinates Mesh not the screen. */
            // cp = triangle_cp(c.t[i]);
            // dp = dot_product(LightSC, cp);

            gcil.graphics_exposures = False;

            // if (dp > 0.00) {
            //     gcil.foreground = 0xff00fb;
            // } else {
                gcil.foreground = c.t[i].color;
            // }

            GC gci = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcil);
            XFillPolygon(displ, win, gci, sc.sct[i].scv, 3, Convex, CoordModeOrigin);

            if (i == 0 && j == 2) {
                printf("X: %f\nY: %f\nZ: %f\n W : %f\n", c.t[i].v[j].x, c.t[i].v[j].y, c.t[i].v[j].z, c.t[i].v[j].w);
                printf("---------------------------------------\n");
            }

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
const static void rasterize(const Mesh c) {

    SCMesh scmesh;
    // Mesh normalized = c;
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

