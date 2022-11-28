/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>

/* Project specific headers */
#include "header_files/locale.h"
#include "header_files/objects.h"
// #include "header_files/rasterizer.h"

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

#define NearPlane                 ( 0b00000001 )
#define FarPlane                  ( 0b00000010 )
#define RightPlane                ( 0b00000011 )
#define LeftPlane                 ( 0b00000100 )
#define UpPlane                   ( 0b00000101 )
#define DownPlane                 ( 0b00000110 )
#define Flags                     ( NearPlane | FarPlane | RightPlane | LeftPlane | UpPlane | DownPlane )


/* Some Global Variables */
Display *displ;
Window win;
Pixmap pixmap;
GC gc;
XGCValues gcvalues;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

Pixel pixels[HEIGHT][WIDTH];
float depth_buffer[HEIGHT][WIDTH];

Vector  Camera   =   { 0.0, 0.0, 498.0, 1.0 },
        U        =   { 1.0, 0.0, 0.0, 1.0 },
        V        =   { 0.0, 1.0, 0.0, 1.0 },
        N        =   { 0.0, 0.0, 1.0, 1.0 };

Vector LightSC   =   { -500.0, -500.0, 1500.0, 1.0 };

float NPlane = 1.0;
float FPlane = 1.0;
float dplus = 0.00;

/* Magnitude of a Vector in 3d space |V| = √(x2 + y2 + z2) */
/* Magnitude of a Vector with one point at origin (0, 0)  |v| =√(x2 + y2) */
/* Magnitude of a Vector with 2 points |v| =√((x2 - x1)2 + (y2 - y1)2) */
/* depth = (Point0 * (1 - t)) + (Point1 * t); */

Mesh shape;
Mat4x4 WorldMat = { 0 };
Mat4x4 PosMat = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
float AspectRatio = WIDTH / HEIGHT;
float FOV = 75.0;
static float ANGLE = 0.05;
static float FYaw = 0.1;

int DEBUG = 0;

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
const static void viewtoscreen(const Mesh c);
const static void rasterize(const SCMesh sc);
const static void debug_rasterize(const SCMesh sc);
const static void debug_draw(const SCMesh sc);
const static void fillnorthway(const SCTriangle sct, const float light);
const static void fillsouthway(const SCTriangle sct, const float light);
const static void fillgeneral(const SCTriangle sct, const float light);

/* Xlib relative functions and event dispatcher. */
static KeySym get_keysym(XEvent *event);
const static void pixmapcreate(void);
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
#include "header_files/test_shapes.h"

const static void clientmessage(XEvent *event) {

    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW");

        free(shape.t);
        
        XFree(gc);
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
        // load_obj(&shape, "objects/bigterrain.obj");
        // load_obj(&shape, "objects/middleterrain.obj");
        // load_obj(&shape, "objects/smallterrain.obj");
        // load_obj(&shape, "objects/mountains.obj");
        // load_obj(&shape, "objects/axis.obj");
        // load_obj(&shape, "objects/teapot.obj");
        // load_obj(&shape, "objects/spaceship.obj");
        // load_obj(&shape, "objects/city.obj");
        // load_obj(&shape, "objects/planet.obj");
        load_obj(&shape, "objects/scene.obj");
        // cube_create(&shape);
        // triangle_create(&shape);

        Mat4x4 sm = scale_mat(100.0);
        Mat4x4 tm = translation_mat(0.0, 0.0, 500.0);
        PosMat = mxm(sm, tm);
        shape = meshxm(shape, PosMat);

        MAPCOUNT = 1;
    }
}
const static void expose(XEvent *event) {

    printf("expose event received\n");
    pixmapcreate();
    project(shape);
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
    printf("X: %f\n", ((event->xbutton.x - (WIDTH / 2.00)) / (WIDTH / 2.00)));
    printf("Y: %f\n", ((event->xbutton.y - (HEIGHT / 2.00)) / (HEIGHT / 2.00)));
}

const static void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    // printf("Key Pressed: %ld\n", keysym);
    // printf("\x1b[H\x1b[J");
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
        case 120 : rotate_x(&shape, ANGLE);       /* x */
            break;
        case 121 : rotate_y(&shape, ANGLE);       /* y */
            break;
        case 122 : rotate_z(&shape, ANGLE);       /* z */
            break;
        case 65451 : FPlane += 0.00001;             /* + */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65453 : FPlane -= 0.00001;             /* - */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65450 : NPlane += 0.005;             /* * */
            printf("NPlane.z: %f\n", NPlane);
            break;
        case 65455 : NPlane -= 0.005;             /* / */
            printf("NPlane.z: %f\n", NPlane);
            break;
        case 112 : LightSC.z += 10.01;                   /* Dot product increase */
            break;
        case 246 : LightSC.z -= 10.01;                   /* Dot product decrease */
            break;
        default :
            return;
    }
    project(shape);
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
    *c = meshxm(shape, m);
}
/* Rotates object according to World Y axis. */
static void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(angle);
    *c = meshxm(shape, m);
}
/* Rotates object according to World Z axis. */
static void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(angle);
    *c = meshxm(shape, m);
}
/* Starts the Projection Pipeline. */
static void project(Mesh c) {

    Mat4x4 matCamera = camera_mat(Camera, U, V, N);

    // Make view matrix from camera
    Mat4x4 reView = inverse_mat(matCamera);
    
    Mat4x4 m = projection_mat(FOV, AspectRatio);

    WorldMat = mxm(reView, m);

    Mesh cache = meshxm(c, WorldMat);
    // printf("VIEW: X: %f  Y: %f  Z: %f  W: %f\n", cache.t[0].v[0].x, cache.t[0].v[0].y, cache.t[0].v[0].z, cache.t[0].v[0].w);
    // printf("VIEW: X: %f  Y: %f  Z: %f  W: %f\n", cache.t[0].v[1].x, cache.t[0].v[1].y, cache.t[0].v[1].z, cache.t[0].v[1].w);
    // printf("VIEW: X: %f  Y: %f  Z: %f  W: %f\n", cache.t[0].v[2].x, cache.t[0].v[2].y, cache.t[0].v[2].z, cache.t[0].v[2].w);
    /* At this Point triangles must be clipped against near plane. */
    Vector plane_near_p = { 0.0, 0.0, NPlane },
           plane_near_n = { 0.0, 0.0, 1.0 };
    Mesh nf = clipp(cache, plane_near_p, plane_near_n);
    free(cache.t);

    /* Applying perspective division. */
    if (nf.indexes) {
        ppdiv(&nf);
    }
    // printf("NDC: X: %f  Y: %f  Z: %f  W: %f\n", nf.t[0].v[0].x, nf.t[0].v[0].y, nf.t[0].v[0].z, nf.t[0].v[0].w);
    // printf("NDC: X: %f  Y: %f  Z: %f  W: %f\n", nf.t[0].v[1].x, nf.t[0].v[1].y, nf.t[0].v[1].z, nf.t[0].v[1].w);
    // printf("NDC: X: %f  Y: %f  Z: %f  W: %f\n", nf.t[0].v[2].x, nf.t[0].v[2].y, nf.t[0].v[2].z, nf.t[0].v[2].w);

    /* Applying Backface culling before we proceed to full frustum clipping. */
    Mesh bf = bfculling(nf);
    free(nf.t);

    /* Far Plane clipping and side clipping. */
    Vector plane_far_p = { 0.0, 0.0, FPlane },
           plane_far_n = { 0.0, 0.0, 1.0 };
    Mesh ff = clipp(bf, plane_far_p, plane_far_n);
    free(bf.t);

    Vector plane_right_p = { 1.0, 0.0, 0.0 },
           plane_right_n = { -1.0, 0.0, 0.0 };
    Mesh rf = clipp(ff, plane_right_p, plane_right_n);
    free(ff.t);

    Vector plane_down_p = { 0.0, 1.0, 0.0 },
           plane_down_n = { 0.0, -1.0, 0.0 };
    Mesh df = clipp(rf, plane_down_p, plane_down_n);
    free(rf.t);

    Vector plane_left_p = { -1.0, 0.0, 0.0 },
           plane_left_n = { 1.0, 0.0, 0.0 };
    Mesh lf = clipp(df, plane_left_p, plane_left_n);
    free(df.t);

    Vector plane_up_p = { 0.0, -1.0, 0.0 },
           plane_up_n = { 0.0, 1.0, 0.0 };
    Mesh uf = clipp(lf, plane_up_p, plane_up_n);
    free(lf.t);

    /* Triangles must possibly be sorted according to z value and then be passed to rasterizer. */
    // uf = sort_triangles(&uf);

    /* Sending to translation to Screen Coordinates. */
    viewtoscreen(uf);
    
    free(uf.t);
}
/* Perspective division. */
static void ppdiv(Mesh *c) {
    for (int i = 0; i < c->indexes; i++) {
        for (int j = 0; j < 3; j++) {

            if ( c->t[i].v[j].w > 0.00 ) {
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
    float dpc;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.indexes; i++) {
        cp = triangle_cp(c.t[i]);
        dpc = dot_product(norm_vec(Camera), norm_vec(cp));

        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];
            r.t[index].normal = norm_vec(cp);

            counter++;
            index++;
        }
    }
    r.indexes = index;
    return r;
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void viewtoscreen(const Mesh c) {

    SCMesh sc;
    sc.sct = calloc(c.indexes, sizeof(SCTriangle));

    if (!sc.sct)
        fprintf(stderr, "Could not allocate memory - rasterize() - calloc\n");

    sc.indexes = c.indexes;

    for (int i = 0; i < sc.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            sc.sct[i].scv[j].x = XWorldToScreen;
            sc.sct[i].scv[j].y = YWorldToScreen;
            sc.sct[i].scv[j].z = 1 / c.t[i].v[j].w;
            sc.sct[i].normal = c.t[i].normal;
        }
    }
    if (DEBUG)
        debug_rasterize(sc);
    else
        rasterize(sc);
    free(sc.sct);
}
/* Rasterize given Mesh by sorting the triangles by Y, then by X and finally, passing them to the appropriate functions according to their charakteristics. */
const static void rasterize(const SCMesh sc) {

    char image_data[wa.width * wa.height * 4];
    /* Initializing the frame buffer to depth of 1. */
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            depth_buffer[i][j] = 0.0;
    memset(pixels, 0, (wa.height * wa.width * sizeof(Pixel)));

    SCVector temp;
    Vector lightsc = vecxm(LightSC, WorldMat);
    // if (lightsc.w > 0.00) {
        lightsc.x /= lightsc.w;
        lightsc.y /= lightsc.w;
        lightsc.z /= lightsc.w;
    // }
    // printf("Light: X: %f  Y: %f  Z: %f  W: %f\n", lightsc.x, lightsc.y, lightsc.z, lightsc.w);

    /* Sorting Vectors from smaller to larger y. */
    float dpl;
    for (int m = 0; m < sc.indexes; m++) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (sc.sct[m].scv[i].y <= sc.sct[m].scv[j].y) {
                    temp = sc.sct[m].scv[i];
                    sc.sct[m].scv[i] = sc.sct[m].scv[j];
                    sc.sct[m].scv[j] = temp;
                }

        dpl = dot_product(norm_vec(lightsc), sc.sct[m].normal);
        // if (dpl <= 0)
        //     dpl *= -1;
        // printf("dpl: %f\n", dpl);

        if ( (sc.sct[m].scv[1].y - sc.sct[m].scv[2].y) == 0 )
            fillnorthway(sc.sct[m], dpl);
        else if ( (sc.sct[m].scv[0].y - sc.sct[m].scv[1].y) == 0 )
            fillsouthway(sc.sct[m], dpl);
        else
            fillgeneral(sc.sct[m], dpl);
    }

    int height_inc = 0;
    int width_inc = 0;
    for (int i = 0; i < sizeof(image_data) / sizeof(char); i++) {

        image_data[i] = pixels[height_inc][width_inc].Blue;
        image_data[i + 1] = pixels[height_inc][width_inc].Green;
        image_data[i + 2] = pixels[height_inc][width_inc].Red;
        i += 3;
        width_inc++;
        if (width_inc == wa.width) {
            height_inc += 1;
            width_inc = 0;
        }
    }

    XImage *image = XCreateImage(displ, wa.visual, wa.depth, ZPixmap, 0, image_data, wa.width, wa.height, 32, (wa.width * 4));
    XPutImage(displ, pixmap, gc, image, 0, 0, 0, 0, wa.width, wa.height);
    XFree(image);

    pixmapdisplay();
    int point_a = (1 + lightsc.x) * (wa.width / 2);
    int point_b = (1 + lightsc.y) * (wa.height / 2);
    XDrawPoint(displ, win, gc, point_a, point_b);
}
const static void fillnorthway(const SCTriangle sct, const float light) {
    float ma, mb, za, zb, depth;
    ma = (float)(sct.scv[1].x - sct.scv[0].x) / (float)(sct.scv[1].y - sct.scv[0].y);
    mb = (float)(sct.scv[2].x - sct.scv[0].x) / (float)(sct.scv[2].y - sct.scv[0].y);

    za = (float)(sct.scv[1].z - sct.scv[0].z) / (float)(sct.scv[1].y - sct.scv[0].y);
    zb = (float)(sct.scv[2].z - sct.scv[0].z) / (float)(sct.scv[2].y - sct.scv[0].y);

    int y_start = (int)ceil(sct.scv[0].y - 0.5);
    int y_end = (int)ceil(sct.scv[1].y - 0.5);

    for (int y = y_start; y < y_end; y++) {
        int x_start, x_end;
        float p0 = (ma * (y - sct.scv[0].y)) + sct.scv[0].x;
        float p1 = (mb * (y - sct.scv[0].y)) + sct.scv[0].x;

        float z0 = (za * (y - sct.scv[0].y)) + sct.scv[0].z;
        float z1 = (zb * (y - sct.scv[0].y)) + sct.scv[0].z;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 - 0.5);
            x_end = (int)ceil(p1 - 0.5);
        } else {
            x_start = (int)ceil(p1 - 0.5);
            x_end = (int)ceil(p0 - 0.5);
        }
        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = z0 * (1 - barycentric) + (z1 * barycentric);
            // printf("Y: %d  X: %d  depth: %f\n", y, x, depth);

            if (depth > depth_buffer[y][x] + dplus) {
                pixels[y][x].Red = 33 * light;
                pixels[y][x].Green = 122 * light;
                pixels[y][x].Blue = 157 * light;
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const static void fillsouthway(const SCTriangle sct, const float light) {
    float mb, mc, zb, zc, depth;
    mb = (float)(sct.scv[2].x - sct.scv[0].x) / (float)(sct.scv[2].y - sct.scv[0].y);
    mc = (float)(sct.scv[2].x - sct.scv[1].x) / (float)(sct.scv[2].y - sct.scv[1].y);

    zb = (float)(sct.scv[2].z - sct.scv[0].z) / (float)(sct.scv[2].y - sct.scv[0].y);
    zc = (float)(sct.scv[2].z - sct.scv[1].z) / (float)(sct.scv[2].y - sct.scv[1].y);

    int y_start = (int)ceil(sct.scv[1].y - 0.5);
    int y_end = (int)ceil(sct.scv[2].y - 0.5);

    for (int y = y_start; y <= y_end; y++) {
        int x_start, x_end;
        float p0 = (mb * (y - sct.scv[0].y)) + sct.scv[0].x;
        float p1 = (mc * (y - sct.scv[1].y)) + sct.scv[1].x;

        float z1 = (zb * (y - sct.scv[0].y)) + sct.scv[0].z;
        float z2 = (zc * (y - sct.scv[1].y)) + sct.scv[1].z;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 - 0.5);
            x_end = (int)ceil(p1 - 0.5);
        } else {
            x_start = (int)ceil(p1 - 0.5);
            x_end = (int)ceil(p0 - 0.5);
        }
        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = z2 * (1 - barycentric) + (z1 * barycentric);
            // printf("Y: %d  X: %d  depth: %f\n", y, x, depth);

            if (depth > depth_buffer[y][x] + dplus) {
                pixels[y][x].Red = 33 * light;
                pixels[y][x].Green = 122 * light;
                pixels[y][x].Blue = 157 * light;
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const static void fillgeneral(const SCTriangle sct, const float light) {
    float ma, mb, mc, za, zb, zc, depth;
    ma = (float)(sct.scv[1].x - sct.scv[0].x) / (float)(sct.scv[1].y - sct.scv[0].y);
    mb = (float)(sct.scv[2].x - sct.scv[0].x) / (float)(sct.scv[2].y - sct.scv[0].y);
    mc = (float)(sct.scv[2].x - sct.scv[1].x) / (float)(sct.scv[2].y - sct.scv[1].y);

    za = (float)(sct.scv[1].z - sct.scv[0].z) / (float)(sct.scv[1].y - sct.scv[0].y);
    zb = (float)(sct.scv[2].z - sct.scv[0].z) / (float)(sct.scv[2].y - sct.scv[0].y);
    zc = (float)(sct.scv[2].z - sct.scv[1].z) / (float)(sct.scv[2].y - sct.scv[1].y);

    int y_start = (int)ceil(sct.scv[0].y - 0.5);
    int y_end1 = (int)ceil(sct.scv[1].y - 0.5);
    int y_end2 = (int)ceil(sct.scv[2].y - 0.5);

    for (int y = y_start; y <= y_end1; y++) {
        int x_start, x_end;
        float p0 = (ma * (y - sct.scv[0].y)) + sct.scv[0].x;
        float p1 = (mb * (y - sct.scv[0].y)) + sct.scv[0].x;

        float z0 = (za * (y - sct.scv[0].y)) + sct.scv[0].z;
        float z1 = (zb * (y - sct.scv[0].y)) + sct.scv[0].z;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 - 0.5);
            x_end = (int)ceil(p1 - 0.5);
        } else {
            x_start = (int)ceil(p1 - 0.5);
            x_end = (int)ceil(p0 - 0.5);
        }
        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = z0 * (1 - barycentric) + (z1 * barycentric);
            // printf("Y: %d  X: %d  depth: %f\n", y, x, depth);

            if (depth > depth_buffer[y][x] + dplus) {
                pixels[y][x].Red = 33 * light;
                pixels[y][x].Green = 122 * light;
                pixels[y][x].Blue = 157 * light;
                depth_buffer[y][x] = depth;
            }
        }
        if (y == y_end1)
            for (int y = y_end1 + 1; y <= y_end2; y++) {

                int x_start, x_end;
                float p0 = (mb * (y - sct.scv[0].y)) + sct.scv[0].x;
                float p1 = (mc * (y - sct.scv[1].y)) + sct.scv[1].x;

                float z1 = (zb * (y - sct.scv[0].y)) + sct.scv[0].z;
                float z2 = (zc * (y - sct.scv[1].y)) + sct.scv[1].z;

                if (p0 <= p1) {
                    x_start = (int)ceil(p0 - 0.5);
                    x_end = (int)ceil(p1 - 0.5);
                } else {
                    x_start = (int)ceil(p1 - 0.5);
                    x_end = (int)ceil(p0 - 0.5);
                }
                for (int x = x_start; x < x_end; x++) {

                    float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
                    depth = z2 * (1 - barycentric) + (z1 * barycentric);
                    // printf("Y: %d  X: %d  depth: %f\n", y, x, depth);

                    if (depth > depth_buffer[y][x] + dplus) {
                        pixels[y][x].Red = 33 * light;
                        pixels[y][x].Green = 122 * light;
                        pixels[y][x].Blue = 157 * light;
                        depth_buffer[y][x] = depth;
                    }
                }
            }

    }
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void debug_rasterize(const SCMesh sc) {
    debug_draw(sc);
}
/* Draws the Mesh's Triangles on screen in 2D coordinates. */
const static void debug_draw(const SCMesh sc) {
    
    XClearWindow(displ, win);
    if (DEBUG == 2) {
        #include "header_files/debug_rasterizer.h"
        DMesh dm;
        dm.dt = calloc(sc.indexes, sizeof(SCTriangle));
        gcvalues.foreground = 0xcb3ecf;
        XChangeGC(displ, gc, GCForeground, &gcvalues);

        if (!dm.dt)
            fprintf(stderr, "Could not allocate memory - rasterize() - calloc\n");

        dm.indexes = sc.indexes;

        for (int i = 0; i < sc.indexes; i++) {
            for (int j = 0; j < 3; j++) {

                dm.dt[i].dv[j].x = sc.sct[i].scv[j].x;
                dm.dt[i].dv[j].y = sc.sct[i].scv[j].y;
            }
            XFillPolygon(displ, win, gc, dm.dt[i].dv, 3, Convex, CoordModeOrigin);
        }
        free(dm.dt);
    }

    int vindex = 1;
    gcvalues.foreground = 0xffffff;
    XChangeGC(displ, gc, GCForeground, &gcvalues);
    for (int i = 0; i < sc.indexes; i++) {

        for (int j = 0; j < 3; j++) {

            if (j == 2)
                vindex = 0;
            XDrawLine(displ, win, gc, sc.sct[i].scv[j].x, sc.sct[i].scv[j].y, sc.sct[i].scv[vindex].x, sc.sct[i].scv[vindex].y);
            vindex++;
        }
    }
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
    XFree(xim);
    return keysym;
}
const static void pixmapcreate(void) {
    pixmap = XCreatePixmap(displ, win, wa.width, wa.height, wa.depth);
}
const static void pixmapdisplay(void) {
    XCopyArea(displ, pixmap, win, gc, 0, 0, wa.width, wa.height, 0, 0);
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

    gcvalues.foreground = 0xffffff;
    gcvalues.background = 0x000000;
    gcvalues.graphics_exposures = False;
    gc = XCreateGC(displ, win, GCBackground | GCForeground | GCGraphicsExposures, &gcvalues);

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

    if (argc > 1) {
        printf("argc: %d\n", argc);
        if (strcasecmp(argv[1], "Debug") == 0) {
            if (strcasecmp(argv[2], "1") == 0) {
                fprintf(stderr, "INFO : ENABLED DEBUG Level 1\n");
                DEBUG = 1;
            } else if (strcasecmp(argv[2], "2") == 0) {
                fprintf(stderr, "INFO : ENABLED DEBUG Level 2\n");
                DEBUG = 2;
            }
        }
    }

    if (board())
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

