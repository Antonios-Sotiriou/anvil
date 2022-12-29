/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>

// signal
#include <signal.h>

/* Project specific headers */
#include "header_files/locale.h"
#include "header_files/objects.h"
#include "header_files/bmp.h"

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
GC gc;
XGCValues gcvalues;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

BMP_Info texture;
Texel **texels;
Pixel **pixels;
float **depth_buffer;

Vector  Camera   =   { 0.0, 0.0, 498.0, 1.0 },
        U        =   { 1.0, 0.0, 0.0, 1.0 },
        V        =   { 0.0, 1.0, 0.0, 1.0 },
        N        =   { 0.0, 0.0, 1.0, 1.0 };

Vector LightSC   =   { 0.0, 0.0, 1.0, 1.0 };

float NPlane = 1.0;
float FPlane = 0.009;
float dplus = 0.0;

/* Magnitude of a Vector in 3d space |V| = √(x2 + y2 + z2) */
/* Magnitude of a Vector with one point at origin (0, 0)  |v| =√(x2 + y2) */
/* Magnitude of a Vector with 2 points |v| =√((x2 - x1)2 + (y2 - y1)2) */
/* float t = (Point0 - X0) / (X1 - X0) */
/* depth = (Point0 * (1 - t)) + (Point1 * t); */
/* depth = z1 + t * (z0 - z1) */

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
void signal_handler(int sig);

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

/* General purposes functions */
static void *create2darray(void **obj, const unsigned long obj_size, const int height, const int width);
static void *resize2darray(void **obj, const unsigned long obj_size, const int height, const int width);
const static void free2darray(void **obj, const int height);
const void swap(void *a, void *b, const unsigned long size);

/* Represantation functions */
static void texture_loader(void);
static void project(Mesh c);
static void ppdiv(Mesh *c);
const static Mesh bfculling(const Mesh c);
const static void viewtoscreen(const Mesh c);
const static void rasterize(const Mesh sc);
const static void fillnorthway(const Triangle t, const float light, const float winding);
const static void fillsouthway(const Triangle t, const float light, const float winding);
const static void fillgeneral(const Triangle t, const float light, const float winding);

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
#include "header_files/draw_functions.h"

/* Testing */
#include "header_files/test_shapes.h"

const static void clientmessage(XEvent *event) {
    printf("Received client message event\n");
    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW\n");

        free(shape.t);
        
        if (texture.Height != 0)
            free2darray((void*)texels, texture.Height);
        printf("Reached step 1\n");
        free2darray((void*)pixels, wa.height);
        printf("Reached step 2\n");
        free2darray((void*)depth_buffer, wa.height);
        printf("Reached step 3\n");

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
        // load_obj(&shape, "objects/scene.obj");
        // cube_create(&shape);
        triangle_create(&shape);

        Mat4x4 sm = scale_mat(1.0);
        Mat4x4 tm = translation_mat(0.0, 0.0, 500.0);
        PosMat = mxm(sm, tm);
        shape = meshxm(shape, PosMat);

        /* The pixels and depth buffer creation. */
        texture_loader();
        pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
        depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);

        MAPCOUNT = 1;
    }
}
const static void expose(XEvent *event) {

    printf("expose event received\n");
    /* Resize pixels and depth buffer to match the screen size. */
    // if (MAPCOUNT) {
        // pixels = resize2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
        // depth_buffer = resize2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
    // } else {
    //     texture_loader();
        // pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
        // depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
    // }
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
    // printf("X: %f\n", ((event->xbutton.x - (WIDTH / 2.00)) / (WIDTH / 2.00)));
    // printf("Y: %f\n", ((event->xbutton.y - (HEIGHT / 2.00)) / (HEIGHT / 2.00)));
    printf("X: %d\n", event->xbutton.x);
    printf("Y: %d\n", event->xbutton.y);
}

const static void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    // printf("Key Pressed: %ld\n", keysym);
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
        case 120 : rotate_x(&shape, ANGLE);       /* x */
            break;
        case 121 : rotate_y(&shape, ANGLE);       /* y */
            break;
        case 122 : rotate_z(&shape, ANGLE);       /* z */
            break;
        case 65451 : FPlane += 0.001;             /* + */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65453 : FPlane -= 0.001;             /* - */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65450 : dplus += 0.01;             /* * */
            printf("NPlane.z: %f\n", dplus);
            break;
        case 65455 : dplus -= 0.01;             /* / */
            printf("NPlane.z: %f\n", dplus);
            break;
        case 112 : LightSC.z += 10.0;                   /* Dot product increase */
            break;
        case 246 : LightSC.z -= 10.0;                   /* Dot product decrease */
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
/* Creates an obj 2d array of height and width with obj_size of each entry. */
static void *create2darray(void **obj, const unsigned long obj_size, const int height, const int width) {
    obj = malloc(sizeof(obj) * height);
    if (obj == NULL)
        fprintf(stderr, "Could not allocate texels height memory! create2darray() -- malloc().\n");

    for (int y = 0; y < height; y++) {
        obj[y] = malloc(obj_size * width);
        if (obj[y] == NULL)
            fprintf(stderr, "Could not allocate texels width memory! create2darray() -- malloc().\n");
    }
    return obj;
}
/* Resizes an obj 2d array of height and width with obj_size of each entry. */
static void *resize2darray(void **obj, const unsigned long obj_size, const int height, const int width) {
    obj = realloc(obj, sizeof(obj) * height);
    if (obj == NULL)
        fprintf(stderr, "Could not reallocate texels height memory! resize2darray() -- malloc().\n");

    for (int y = 0; y < height; y++) {
        obj[y] = realloc(obj[y], obj_size * width);
        if (obj[y] == NULL)
            fprintf(stderr, "Could not reallocate texels width memory! resize2darray() -- malloc().\n");
    }
    return obj;
}
/* Frees all resources of an obj 2d array of height. */
const static void free2darray(void **obj, const int height) {
    for (int y = 0; y < height; y++)
        free(obj[y]);
    free(obj);
}
/* Swaping two variables a and b of any type with size. */
const void swap(void *a, void *b, unsigned long size) {
    void *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}
static void texture_loader(void) {

    char texture_name[28] = "/home/as/Desktop/stones.bmp";
    BMP_Header bmp_header;

    FILE *fp;
    fp = fopen(texture_name, "rb");
    if (fp == NULL){
        fclose(fp);
        fprintf(stderr, "Could not open file < %s >! texture_loader() -- fopen().\n", texture_name);
    } else {
        fread(&bmp_header, sizeof(BMP_Header), 1, fp);
        fseek(fp, 14, SEEK_SET);
        fread(&texture, sizeof(BMP_Info), 1, fp);
        fseek(fp, (14 + texture.Size), SEEK_SET);

        texels = create2darray((void*)texels, sizeof(Texel), texture.Height, texture.Width);
        
        // char image[(texture.Height * texture.Width) * 4];

        for (int y = (texture.Height - 1); y >= 0; y--) {
            for (int x = 0; x < texture.Width; x++) {
                fread(&texels[y][x], sizeof(Texel), 1, fp);
            }
        }

        // int texels_inc = 0;
        // for (int y = 0; y < texture.Height; y++)
        //     for (int x = 0; x < texture.Width; x++) {

        //         image[texels_inc] = texels[y][x].Red;
        //         image[texels_inc + 1] = texels[y][x].Green;
        //         image[texels_inc + 2] = texels[y][x].Blue;
        //         texels_inc += 4;
        //     }

        // XImage *im = XCreateImage(displ, wa.visual, wa.depth, ZPixmap, 0, image, texture.Width, texture.Height, 32, (texture.Width * 4));
        // XPutImage(displ, win, gc, im, 0, 0, 100, 100, texture.Width, texture.Height);
        // XFree(im);
    }
    fclose(fp);
}
/* Starts the Projection Pipeline. */
static void project(Mesh c) {

    Mat4x4 matCamera = camera_mat(Camera, U, V, N);

    // Make view matrix from camera
    Mat4x4 reView = inverse_mat(matCamera);
    
    Mat4x4 m = projection_mat(FOV, AspectRatio);

    WorldMat = mxm(reView, m);

    Mesh cache = meshxm(c, WorldMat);

    /* At this Point triangles must be clipped against near plane. */
    Vector plane_near_p = { 0.0, 0.0, NPlane },
           plane_near_n = { 0.0, 0.0, 1.0 };
    Mesh nf = clipp(cache, plane_near_p, plane_near_n);
    free(cache.t);

    /* Applying perspective division. */
    if (nf.indexes) {
        ppdiv(&nf);
    }

    /* Applying Backface culling before we proceed to full frustum clipping. */
    Mesh bf = bfculling(nf);
    free(nf.t);

    /* Triangles must possibly be sorted according to z value and then be passed to rasterizer. */
    // uf = sort_triangles(&uf);

    /* Sending to translation to Screen Coordinates. */
    viewtoscreen(bf);
    
    // free(bf.t);
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

    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            c.t[i].v[j].x = XWorldToScreen;
            c.t[i].v[j].y = YWorldToScreen;
            c.t[i].v[j].z = 1 / c.t[i].v[j].w;

            // c.t[i].tex[j].u = c.t[i].tex[j].u;
            // c.t[i].tex[j].v = c.t[i].tex[j].v;
            // sc.sct[i].tex[j].w = c.t[i].tex[j].w;
        }
    }


    /* Far Plane clipping and side clipping. */
    Vector plane_far_p = { 0.0, 0.0, FPlane },
           plane_far_n = { 0.0, 0.0, 1.0 };
    Mesh ff = clipp(c, plane_far_p, plane_far_n);
    free(c.t);

    Vector plane_right_p = { (float)wa.width - 1.0, 0.0, 0.0 },
           plane_right_n = { -1.0, 0.0, 0.0 };
    Mesh rf = clipp(ff, plane_right_p, plane_right_n);
    free(ff.t);

    Vector plane_down_p = { 0.0, (float)wa.height - 1.0, 0.0 },
           plane_down_n = { 0.0, -1.0, 0.0 };
    Mesh df = clipp(rf, plane_down_p, plane_down_n);
    free(rf.t);

    Vector plane_left_p = { 0.0, 0.0, 0.0 },
           plane_left_n = { 1.0, 0.0, 0.0 };
    Mesh lf = clipp(df, plane_left_p, plane_left_n);
    free(df.t);

    Vector plane_up_p = { 0.0, 0.0, 0.0 },
           plane_up_n = { 0.0, 1.0, 0.0 };
    Mesh uf = clipp(lf, plane_up_p, plane_up_n);
    free(lf.t);

    rasterize(uf);
    free(uf.t);
}
/* Rasterize given Mesh by sorting the triangles by Y, then by X and finally, passing them to the appropriate functions according to their charakteristics. */
const static void rasterize(const Mesh c) {

    char image_data[wa.width * wa.height * 4];

    /* Initializing the frame buffer to depth of 1 and reseting the Pixels. */
    for (int y = 0; y < wa.height; y++)
        for (int x = 0; x < wa.width; x++) {

            if (pixels[y][x].Red != 0)
                pixels[y][x].Red = 0;
            if (pixels[y][x].Green != 0)
                pixels[y][x].Green = 0;
            if (pixels[y][x].Blue != 0)
                pixels[y][x].Blue = 0;

            if (depth_buffer[y][x] != 0.0)
                depth_buffer[y][x] = 0.0;
        }

    /* Sorting Vectors from smaller to larger y. */
    Vector temp_v;
    Textor temp_t;
    float dpl, winding;
    for (int m = 0; m < c.indexes; m++) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (c.t[m].v[i].y <= c.t[m].v[j].y) {

                    temp_v = c.t[m].v[i];
                    temp_t = c.t[m].tex[i];

                    c.t[m].v[i] = c.t[m].v[j];
                    c.t[m].tex[i] = c.t[m].tex[j];

                    c.t[m].v[j] = temp_v;
                    c.t[m].tex[j] = temp_t;
                }

        dpl = dot_product(LightSC, c.t[m].normal);
        winding = winding3D(c.t[m]);

        if (DEBUG == 1) {
            draw_line(pixels, c.t[m].v[0].x, c.t[m].v[0].y, c.t[m].v[1].x, c.t[m].v[1].y, 255, 0, 0);
            draw_line(pixels, c.t[m].v[1].x, c.t[m].v[1].y, c.t[m].v[2].x, c.t[m].v[2].y, 0, 255, 0);
            draw_line(pixels, c.t[m].v[2].x, c.t[m].v[2].y, c.t[m].v[0].x, c.t[m].v[0].y, 0, 0, 255);
        } else {
            if ( (c.t[m].v[1].y - c.t[m].v[2].y) == 0 )
                fillnorthway(c.t[m], dpl, winding);
            else if ( (c.t[m].v[0].y - c.t[m].v[1].y) == 0 )
                fillsouthway(c.t[m], dpl, winding);
            else
                fillgeneral(c.t[m], dpl, winding);
        }
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
}
const static void fillnorthway(const Triangle t, const float light, const float winding) {
    float ma, mb, za, zb, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);

    int y_start = (int)ceil(t.v[0].y - 0.5);
    int y_end = (int)ceil(t.v[1].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = (ma * (y - y_start)) + ceil(t.v[0].x - 0.5);
        int x_end = (mb * (y - y_start)) + ceil(t.v[0].x - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z0 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = 33 * (light * depth);
                pixels[y][x].Green = 122 * (light * depth);
                pixels[y][x].Blue = 157 * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const static void fillsouthway(const Triangle t, const float light, const float winding) {
    float mb, mc, zb, zc, depth;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[1].y - 0.5);
    int y_end = ceil(t.v[2].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = (mb * (y - y_start)) + ceil(t.v[0].x - 0.5);
        int x_end = (mc * (y - y_start)) + ceil(t.v[1].x - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float z2 = (zc * (y - y_start)) + t.v[1].z;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z2 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = 33 * (light * depth);
                pixels[y][x].Green = 122 * (light * depth);
                pixels[y][x].Blue = 157 * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const static void fillgeneral(Triangle t, const float light, const float winding) {
    // printf("clipped: %s\n", t.clipped ? "True" : "False");
    // printf("Raster space v0.x: %f   v0.y: %f   v0.z: %f\n", t.v[0].x, t.v[0].y, t.v[0].z);
    // printf("Raster space v1.x: %f   v1.y: %f   v1.z: %f\n", t.v[1].x, t.v[1].y, t.v[1].z);
    // printf("Raster space v2.x: %f   v2.y: %f   v2.z: %f\n\n", t.v[2].x, t.v[2].y, t.v[2].z);
    float ma, mb, mc, za, zb, zc, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);
    // printf("Raster space ma: %f   mb: %f   mc: %f\n\n", ma, mb, mc);
    if ( (t.v[1].x < t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    } else if ( (t.v[1].x < t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    }
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[0].y - 0.5);
    int y_end1 = ceil(t.v[1].y - 0.5);
    int y_end2 = ceil(t.v[2].y - 0.5);

    for (int y = y_start; y < y_end1; y++) {

        int x_start = (ma * (y - y_start)) + ceil(t.v[0].x - 0.5);
        int x_end = (mb * (y - y_start)) + ceil(t.v[0].x - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z0 * (1 - barycentric)) + (z1 * barycentric));// - (z0 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = 33 * (light * depth);
                pixels[y][x].Green = 122 * (light * depth);
                pixels[y][x].Blue = 157 * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
    for (int y = y_end1; y < y_end2; y++) {

        int x_start = (mb * (y - y_start)) + ceil(t.v[0].x - 0.5);
        int x_end = (mc * (y - y_end1)) + ceil(t.v[1].x - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z1, z2;
        if (winding < 0) {
            z1 = (zb * (y - y_start)) + t.v[0].z;
            z2 = (zc * (y - y_end1)) + t.v[1].z;
        } else {
            z2 = (za * (y - y_start)) + t.v[0].z;
            z1 = (zc * (y - y_end1)) + t.v[1].z;
        }

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z2 * (1 - barycentric)) + (z1 * barycentric));// - (z2 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = 33 * (light * depth);
                pixels[y][x].Green = 122 * (light * depth);
                pixels[y][x].Blue = 157 * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
    // printf("depth before divide: %f  After: %f\n", depth, 1 / depth);
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
void signal_handler(int sig) {
    printf("Received Signal from OS with ID: %d\n", sig);
    XEvent event = { 0 };
    event.type = ClientMessage;
    event.xclient.data.l[0] = wmatom[Win_Close];
    /* Send the signal to our event dispatcher for further processing. */
    handler[event.type](&event);
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
        fprintf(stderr, "Warning: board() -- XOpenDisplay()\n");
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

    /* Signal handling for effectivelly releasing the resources. */
    struct sigaction sig = { 0 };
    // sig.sa_handler = &signal_handler;
    int sig_val = sigaction(SIGSEGV, &sig, NULL);
    if (sig_val == -1) {
        fprintf(stderr, "Warning: board() -- sigaction()\n");
        return EXIT_FAILURE;
    }

    while (RUNNING) {

        XNextEvent(displ, &event);

        if (handler[event.type])
            handler[event.type](&event);
    }
    return EXIT_SUCCESS;
}
int main(int argc, char *argv[]) {

    if (locale_init())
        fprintf(stderr, "Warning: main() -locale()\n");

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

