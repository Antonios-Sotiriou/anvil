/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
#include <unistd.h>

/* signal */
#include <signal.h>

/* Project specific headers */
#include "header_files/locale.h"
#include "header_files/objects.h"
#include "header_files/bmp.h"
#include "header_files/matrices.h"
#include "header_files/vectors_math.h"
#include "header_files/obj_parser.h"
#include "header_files/clipping.h"
#include "header_files/draw_functions.h"
#include "header_files/general_functions.h"
#include "header_files/quaternions.h"

/* cubeing */
#include "header_files/test_shapes.h"
#include "header_files/exec_time.h"

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};
enum { Pos, U, V, N, C};

#define WIDTH                     800
#define HEIGHT                    800
#define XWorldToScreen            ( (1 + c.t[i].v[j].x) * HALFW )
#define YWorldToScreen            ( (1 + c.t[i].v[j].y) * HALFH )

#define POINTERMASKS              ( ButtonPressMask )
#define KEYBOARDMASKS             ( KeyPressMask )
#define EXPOSEMASKS               ( StructureNotifyMask | ResizeRedirectMask )

/* X Global Structures. */
Display *displ;
Window win;
Pixmap pixmap;
GC gc;
XGCValues gcvalues;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

/* Project Global Structures. */
Pixel **pixels;
float **depth_buffer;
float **shadow_buffer;

Global camera = {
    .Pos = { 0.0, 0.0, 498.0, 1.0 },
    .U   = { 1.0, 0.0, 0.0, 1.0 },
    .V   = { 0.0, 1.0, 0.0, 1.0 },
    .N   = { 0.0, 0.0, 1.0, 1.0 }
};

Global light = {
    .Pos = { -17.003309, -17.200029, 530.918640, 1.0 },
    .U   = { -0.883297, -0.006683, -0.468767, 1.0 },
    .V   = { -0.182024, 0.926344, 0.329780, 1.0 },
    .N   = { 0.432035, 0.376621, -0.819453, 1.0 },
    .C   = { 1.0, 1.0, 1.0}
};

Scene scene = { 0 };
Mesh terrain = { 0 }, earth = { 0 }, cube = { 0 };
Mat4x4 WorldMat = { 0 }, PosMat = { 0 }, LookAt = { 0 };

/* Magnitude of a Vector in 3d space |V| = √(x2 + y2 + z2) */
/* Magnitude of a Vector with one point at origin (0, 0)  |v| =√(x2 + y2) */
/* Magnitude of a Vector with 2 points |v| =√((x2 - x1)2 + (y2 - y1)2) */
/* float t = (Point0 - X0) / (X1 - X0) */
/* depth = (Point0 * (1 - t)) + (Point1 * t); */
/* depth = z1 + t * (z1 - z0) */

/* Project Global Variables. */
static int MAPCOUNT = 0;
static int RUNNING = 1;
static int HALFW = 0; // Half width of the screen; This variable is initialized in configurenotify function.Help us decrease the number of divisions.
static int HALFH = 0; // Half height of the screen; This variable is initialized in configurenotify function.Help us decrease the number of divisions.
static int EYEPOINT = 0;
static float AspectRatio = 0;
static float FOV = 45.0;
static float Angle = 0.05;
static float Yaw = 0.0;
static float Pitch = 0.0;
// static float Roll = 0.0;
static float NPlane = 1.0;
static float FPlane = 0.0001;
static float dplus = 0.0;
static int DEBUG = 0;
static float cvar = 0.01;

/* Event handling functions. */
const static void clientmessage(XEvent *event);
const static void reparentnotify(XEvent *event);
const static void mapnotify(XEvent *event);
const static void resizerequest(XEvent *event);
const static void configurenotify(XEvent *event);
const static void buttonpress(XEvent *event);
const static void keypress(XEvent *event);
const static void signal_handler(const int sig);

/* Moving functions */
const static void look_left(Global *g, const float Angle);
const static void look_right(Global *g, const float Angle);
const static void move_forward(Global *g);
const static void move_backward(Global *g);
const static void look_up(Global *g, const float Angle);
const static void look_down(Global *g, const float Angle);
const static void move_left(Global *g);
const static void move_right(Global *g);
const static void move_up(Global *g);
const static void move_down(Global *g);
const static void rotate_x(Mesh *c, const float angle);
const static void rotate_y(Mesh *c, const float angle);
const static void rotate_z(Mesh *c, const float angle);
const static void rotate_origin(Mesh *obj, const float angle);
const static void submeshxm(const Mesh *c, const Mat4x4 m);

/* Represantation functions */
const static void init_meshes(void);
static void load_texture(Mesh *c);
const static void create_scene(Scene *s);
const static void release_scene(Scene *s);
const static void project(Scene s);
const static void ppdiv(Mesh *c);
const static Mesh bfculling(const Mesh c);
const static void viewtoscreen(const Mesh c);
const static Global adjust_light(const Global l);
const static void rasterize(const Mesh sc);
const static void display_scene(void);
const static void clear_buffers(const int height, const int width);

/* Xlib relative functions and event dispatcher. */
const void export_scene(void);
const static KeySym get_keysym(XEvent *event);
const static void pixmapcreate(void);
const static void pixmapdisplay(void);
const static void atomsinit(void);
const static int board(void);
static void (*handler[LASTEvent]) (XEvent *event) = {
    [ClientMessage] = clientmessage,
    [ReparentNotify] = reparentnotify,
    [MapNotify] = mapnotify,
    [ResizeRequest] = resizerequest,
    [ConfigureNotify] = configurenotify,
    [ButtonPress] = buttonpress,
    [KeyPress] = keypress,
};

const static void clientmessage(XEvent *event) {
    printf("Received client message event\n");
    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW\n");

        release_scene(&scene);

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
    // XGetWindowAttributes(displ, win, &wa);
    // AspectRatio = ((float)wa.width / (float)wa.height);
    // pixmapcreate();
    /* The pixels and depth buffer creation. */
    // pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
    // depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
}
const static void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");

    if (MAPCOUNT) {
        pixmapdisplay();
    } else {
        init_meshes();
        create_scene(&scene);
        MAPCOUNT = 1;
    }
}
const static void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
const static void configurenotify(XEvent *event) {

    if (!event->xconfigure.send_event) {
        printf("configurenotify event received\n");
        XGetWindowAttributes(displ, win, &wa);
        AspectRatio = ((float)wa.width / (float)wa.height);
        HALFW = wa.width / 2.00;
        HALFH = wa.height / 2.00;

        /* Resize pixels and depth buffer to match the screen size. */
        // if (MAPCOUNT) {
        //     pixels = resize2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
        //     depth_buffer = resize2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
        // } else {
        //     load_texture();
            // pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
            // depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
        // }
    }
}
const static void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
    printf("X: %f\n", ((event->xbutton.x - (WIDTH / 2.00)) / (WIDTH / 2.00)));
    printf("Y: %f\n", ((event->xbutton.y - (HEIGHT / 2.00)) / (HEIGHT / 2.00)));
}

const static void keypress(XEvent *event) {
    
    KeySym keysym = get_keysym(event);
    Global *eye;
    if (EYEPOINT)
        eye = &light;
    else
        eye = &camera;

    printf("Key Pressed: %ld\n", keysym);
    printf("\x1b[H\x1b[J");
    switch (keysym) {

        case 97 : look_left(eye, Angle);       /* a */
            break;
        case 100 : look_right(eye, Angle);     /* d */
            break;
        case 119 : move_forward(eye);         /* w */
            break;
        case 115 : move_backward(eye);        /* s */
            break;
        case 113 : look_up(eye, Angle);       /* q */
            break;
        case 101 : look_down(eye, Angle);     /* e */
            break;
        case 65361 : move_left(eye);          /* left arrow */
            break;
        case 65363 : move_right(eye);         /* right arrow */
            break;
        case 65362 : move_up(eye);            /* up arror */
            break;
        case 65364 : move_down(eye);          /* down arrow */
            break;
        case 120 : rotate_x(&scene.m[0], Angle);       /* x */
            break;
        case 121 : rotate_y(&scene.m[0], Angle);       /* y */
            break;
        case 122 : rotate_z(&scene.m[0], Angle);       /* z */
            break;
        case 112 : camera.Pos.x += cvar;         /* p */
            camera.Pos.y += cvar;
            camera.Pos.z += cvar;
            break;
        case 117 : camera.U.x += cvar;          /* u */
            camera.U.y += cvar;
            camera.U.z += cvar;
            break;
        case 118 : camera.V.x += cvar;          /* v */
            // camera.V.y += cvar;
            camera.V.z += cvar;
            break;
        case 110 : camera.N.x += cvar;          /* n */
            camera.N.y += cvar;
            camera.N.z += cvar;
            break;
        case 65451 : FPlane += 0.0001;             /* + */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65453 : FPlane -= 0.0001;             /* - */
            printf("FPlane.z: %f\n", FPlane);
            break;
        case 65450 : dplus += 0.01;             /* * */
            printf("NPlane.z: %f\n", dplus);
            break;
        case 65455 : dplus -= 0.01;             /* / */
            printf("NPlane.z: %f\n", dplus);
            break;
        case 99 : rotate_origin(&scene.m[2], Angle);        /* c */
            break;
        case 108 :                                    /* l */
            if (EYEPOINT == 0)
                EYEPOINT = 1;
            else
                EYEPOINT = 0;
            break;
        case 65462 : light.Pos.x += 0.01;                   /* Adjust Light Source */
            break;
        case 65460 : light.Pos.x -= 0.01;                   /* Adjust Light Source */
            break;
        case 65458 : light.Pos.y += 0.01;                   /* Adjust Light Source */
            break;
        case 65464 : light.Pos.y -= 0.01;                   /* Adjust Light Source */
            break;
        case 43 : light.Pos.z += 1.0;                     /* + */
            break;
        case 45 : light.Pos.z -= 1.0;                     /* - */
            break;
        case 98 : export_scene();                     /* - */
            break;
        default :
            return;
    }
}
/* Rotates the camera to look left. */
static void look_left(Global *g, const float angle) {
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(-1, g->V);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Rotates the camera to look right. */
const static void look_right(Global *g, const float angle) {
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(1, g->V);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
const static void move_forward(Global *g) {
    g->Pos = add_vecs(g->Pos, multiply_vec(g->N, 0.1));
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
const static void move_backward(Global *g) {
    g->Pos = sub_vecs(g->Pos, multiply_vec(g->N, 0.1));
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Rotates the camera to look Up. */
const static void look_up(Global *g, const float angle) {

    /* A working example with Quaternion rotation. */
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(-1, g->U);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Rotates the camera to look Down. */
const static void look_down(Global *g, const float angle) {

    /* A working example with Quaternion rotation. */
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(1, g->U);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Moves camera position left. */
const static void move_left(Global *g) {
    g->Pos = sub_vecs(g->Pos, multiply_vec(g->U, 0.1));
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Moves camera position right. */
const static void move_right(Global *g) {
    g->Pos = add_vecs(g->Pos, multiply_vec(g->U, 0.1));
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Moves camera position Up. */
const static void move_up(Global *g) {
    // g->Pos = sub_vecs(g->Pos, multiply_vec(g->V, 0.1));
    g->Pos.y -= 0.1;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Moves camera position Down. */
const static void move_down(Global *g) {
    // g->Pos = add_vecs(g->Pos, multiply_vec(g->V, 0.1));
    g->Pos.y += 0.1;
    LookAt = lookat(g->Pos, g->U, g->V, g->N);
}
/* Rotates object according to World X axis. */
const static void rotate_x(Mesh *c, const float angle) {
    Mat4x4 m = rotate_xmat(angle);
    *c = meshxm(*c, m);
}
/* Rotates object according to World Y axis. */
const static void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(angle);
    *c = meshxm(*c, m);
}
/* Rotates object according to World Z axis. */
const static void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(angle);
    *c = meshxm(*c, m);
}
/* Rotates object according to own axis. */
const static void rotate_origin(Mesh *obj, const float angle) {
    Mat4x4 origin = translation_mat(0.0, 0.0, 500.0);
    submeshxm(obj, origin);
    Mat4x4 m = rotate_xmat(angle);
    Mat4x4 tm = translation_mat(0.0, 0.0, 500.0);
    Mat4x4 nm = mxm(m, tm);
    // *obj = meshxm(*obj, m);
    *obj = meshxm(*obj, nm);

}
/* Substracts the Translation from the given mesh. */
const static void submeshxm(const Mesh *c, const Mat4x4 m) {

    for (int i = 0; i < c->indexes; i++) {
        for (int j = 0; j < 3; j++) {
            
            c->t[i].v[j].x -= m.m[3][0];
            c->t[i].v[j].y -= m.m[3][1];
            c->t[i].v[j].z -= m.m[3][2];
        }
    }
}
const static void init_meshes(void) {
    Mat4x4 ScaleMat, TransMat;

    load_obj(&terrain, "objects/terrain.obj");
    memcpy(terrain.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    load_texture(&terrain);
    ScaleMat = scale_mat(1.0);
    TransMat = translation_mat(0.0, 0.5, 500.0);
    PosMat = mxm(ScaleMat, TransMat);
    terrain = meshxm(terrain, PosMat);

    load_obj(&earth, "objects/earth.obj");
    memcpy(earth.texture_file, "textures/Earth.bmp", sizeof(char) * 19);
    load_texture(&earth);
    ScaleMat = scale_mat(1.0);
    TransMat = translation_mat(1.0, 1.0, 510.0);
    PosMat = mxm(ScaleMat, TransMat);
    earth = meshxm(earth, PosMat);

    cube_create(&cube);
    memcpy(cube.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    load_texture(&cube);

    ScaleMat = scale_mat(8.0);
    TransMat = translation_mat(0.0, 0.0, 500.0);
    PosMat = mxm(ScaleMat, TransMat);
    cube = meshxm(cube, PosMat);

    LookAt = lookat(camera.Pos, camera.U, camera.V, camera.N);
}
const static void load_texture(Mesh *c) {

    BMP_Header bmp_header;
    BMP_Info texture;

    FILE *fp;
    fp = fopen(c->texture_file, "rb");
    if (fp == NULL){
        fclose(fp);
        fprintf(stderr, "Could not open file < %s >! load_texture() -- fopen().\n", c->texture_file);
    } else {
        fread(&bmp_header, sizeof(BMP_Header), 1, fp);
        fseek(fp, 14, SEEK_SET);
        fread(&texture, sizeof(BMP_Info), 1, fp);
        fseek(fp, (14 + texture.Size), SEEK_SET);

        c->texture_height = texture.Height;
        c->texture_width = texture.Width;
        c->texels = create2darray((void*)c->texels, sizeof(Pixel), texture.Height, texture.Width);

        for (int y = (texture.Height - 1); y >= 0; y--) {
            for (int x = 0; x < texture.Width; x++) {
                fread(&c->texels[y][x], sizeof(Pixel), 1, fp);
            }
        }
    }
    fclose(fp);
}
/* Unifies all meshes to a mesh array to finally create the scene or frame else spoken. */
const static void create_scene(Scene *s) {
    s->m = malloc(sizeof(Mesh) * 3);
    s->indexes = 3;
    s->m[0] = terrain;
    s->m[1] = earth;
    s->m[2] = cube;
}
const static void release_scene(Scene *s) {
    for (int i = 0; i < s->indexes; i++) {
        free(s->m[i].t);
        free2darray((void*)s->m[i].texels, s->m[i].texture_height);
    }
    free(s->m);
}
const static void clear_buffers(const int height, const int width) {
    /* Initializing the given buffer to depth of 0 and reseting the Pixels. */
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {

            if (pixels[y][x].Red != 0)
                pixels[y][x].Red = 0;
            if (pixels[y][x].Green != 0)
                pixels[y][x].Green = 0;
            if (pixels[y][x].Blue != 0)
                pixels[y][x].Blue = 0;

            if (depth_buffer[y][x] != 0.0)
                depth_buffer[y][x] = 0.0;
        }
}
/* Starts the Projection Pipeline. */
const static void project(Scene s) {

    // LookAt = lookat(camera.Pos, camera.U, camera.V, camera.N);
    // // Make view matrix from LookAt.
    Mat4x4 View = inverse_mat(LookAt);
    
    Mat4x4 Proj = projection_mat(FOV, AspectRatio);

    WorldMat = mxm(View, Proj);

    for (int i = 0; i < s.indexes; i++) {
        Mesh cache = meshxm(s.m[i], WorldMat);

        /* At this Point triangles must be clipped against near plane. */
        Vector plane_near_p = { 0.0, 0.0, NPlane },
            plane_near_n = { 0.0, 0.0, 1.0 };
        Mesh nf = clipp(cache, plane_near_p, plane_near_n);

        /* Applying perspective division. */
        if (nf.indexes) {
            ppdiv(&nf);
        }

        /* Applying Backface culling before we proceed to full frustum clipping. */
        Mesh bf = bfculling(nf);

        /* Sending to translation from NDC to Screen Coordinates. */
        viewtoscreen(bf);
    }
    display_scene();
}
/* Perspective division. */
const static void ppdiv(Mesh *c) {
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
    Mesh r = c;
    Vector cp;
    float dpc;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.indexes; i++) {
        cp = triangle_cp(c.t[i]);
        dpc = dot_product(norm_vec(camera.Pos), norm_vec(cp));

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
    free(c.t);
    return r;
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static void viewtoscreen(const Mesh c) {

    for (int i = 0; i < c.indexes; i++) {
        for (int j = 0; j < 3; j++) {

            c.t[i].v[j].x = XWorldToScreen;
            c.t[i].v[j].y = YWorldToScreen;
            c.t[i].v[j].z = 1 / c.t[i].v[j].w;

            c.t[i].tex[j].u /= c.t[i].v[j].w;
            c.t[i].tex[j].v /= c.t[i].v[j].w;
            c.t[i].tex[j].w = 1 / c.t[i].v[j].w;
        }
    }

    /* Far Plane clipping and side clipping. */
    Vector plane_far_p = { 0.0, 0.0, FPlane },
           plane_far_n = { 0.0, 0.0, 1.0 };
    Mesh ff = clipp(c, plane_far_p, plane_far_n);

    Vector plane_right_p = { (float)wa.width - 1.0, 0.0, 0.0 },
           plane_right_n = { -1.0, 0.0, 0.0 };
    Mesh rf = clipp(ff, plane_right_p, plane_right_n);

    Vector plane_down_p = { 0.0, (float)wa.height - 1.0, 0.0 },
           plane_down_n = { 0.0, -1.0, 0.0 };
    Mesh df = clipp(rf, plane_down_p, plane_down_n);

    Vector plane_left_p = { 0.0, 0.0, 0.0 },
           plane_left_n = { 1.0, 0.0, 0.0 };
    Mesh lf = clipp(df, plane_left_p, plane_left_n);

    Vector plane_up_p = { 0.0, 0.0, 0.0 },
           plane_up_n = { 0.0, 1.0, 0.0 };
    Mesh uf = clipp(lf, plane_up_p, plane_up_n);

    rasterize(uf);
    free(uf.t);
}
const static Global adjust_light(const Global l) {
    Global r = l;
    r.Pos = vecxm(l.Pos, WorldMat);

    if (r.Pos.w <= 0.1)
        r.Pos.w = 0.1;

    if (r.Pos.z <= 0.1)
        r.Pos.z = 0.1;

    r.Pos.x /= r.Pos.w;
    r.Pos.y /= r.Pos.w;
    r.Pos.z /= r.Pos.w;

    return r;
}
/* Rasterize given Mesh by sorting the triangles by Y, then by X and finally, passing them to the appropriate functions according to their charakteristics. */
const static void rasterize(const Mesh c) {
    
    Global dirlight = adjust_light(light);

    for (int i = 0; i < c.indexes; i++) {

        if (DEBUG == 1) {
            drawline(pixels, c.t[i].v[0].x, c.t[i].v[0].y, c.t[i].v[1].x, c.t[i].v[1].y, 255, 0, 0);
            drawline(pixels, c.t[i].v[1].x, c.t[i].v[1].y, c.t[i].v[2].x, c.t[i].v[2].y, 0, 255, 0);
            drawline(pixels, c.t[i].v[2].x, c.t[i].v[2].y, c.t[i].v[0].x, c.t[i].v[0].y, 0, 0, 255);
        } else if (DEBUG == 2) {
            // clock_t start_time = start();
            filltriangle(pixels, depth_buffer, &c.t[i], dirlight,  camera, 33, 122, 157);
            // end(start_time);
        } else {
            textriangle(pixels, depth_buffer, &c.t[i], dirlight.Pos.w, c.texels, (c.texture_height - 1), (c.texture_width - 1));
        }
    }

    dirlight.Pos.x = (1 + dirlight.Pos.x) * HALFW;
    dirlight.Pos.y = (1 + dirlight.Pos.y) * HALFH;
    // printf("lightsc.x: %f, lightsc.y: %f, lightsc.z: %f, lightsc.w: %f\n", dirlight.Pos.x, dirlight.Pos.y, dirlight.Pos.z, dirlight.Pos.w);
    XDrawPoint(displ, win, gc, dirlight.Pos.x, dirlight.Pos.y);

    // drawline(pixels, (1 + camera.Pos.x) * 400, (1 + camera.Pos.y) * 400, (1 + camera.U.x) * 400, (1 + camera.U.y) * 400, 255, 0, 0);
    // drawline(pixels, (1 + camera.Pos.x) * 400, (1 + camera.Pos.y) * 400, (1 + camera.V.x) * 400, (1 + camera.V.y) * 400, 0, 255, 0);
    // drawline(pixels, (1 + camera.Pos.x) * 400, (1 + camera.Pos.y) * 400, (1 + camera.N.x) * 400, (1 + camera.N.y) * 400, 0, 0, 255);
}
/* Writes the final Pixel values on screen. */
const static void display_scene(void) {

    char image_data[wa.width * wa.height * 4];

    int height_inc = 0;
    int width_inc = 0;
    for (int i = 0; i < sizeof(image_data) / sizeof(char); i++) {

        image_data[i] = pixels[height_inc][width_inc].Red;
        image_data[i + 1] = pixels[height_inc][width_inc].Green;
        image_data[i + 2] = pixels[height_inc][width_inc].Blue;

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
    clear_buffers(wa.height, wa.width);
}
const void export_scene(void) {
    BMP_Header header = {
        .Type = 0x4d42,
        .Size = (wa.width * wa.height * 32 ) / 8,
        .OffSet = 54,
    };
    BMP_Info info = {
        .Size = 40,
        .Width = wa.width,
        .Height = wa.height,
        .Planes = 1,
        .BitsPerPixel = 32,
    };
    FILE *fp = fopen("textures/export.bmp", "wb");
    fwrite(&header, sizeof(BMP_Header), 1, fp);
    fseek(fp, 14, SEEK_SET);
    fwrite(&info, sizeof(BMP_Info), 1, fp);
    fseek(fp, (14 + info.Size), SEEK_SET);

    for (int y = wa.height - 1; y >= 0; y--)
        for (int x = 0; x < wa.width; x++)
            fwrite(&pixels[y][x], sizeof(int), 1, fp);

    fclose(fp);
}
const static KeySym get_keysym(XEvent *event) {

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
const static void signal_handler(const int sig) {
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

    XGetWindowAttributes(displ, win, &wa);
    AspectRatio = ((float)wa.width / (float)wa.height);
    pixmapcreate();
    pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
    depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);

    atomsinit();

    /* Signal handling for effectivelly releasing the resources. */
    struct sigaction sig = { 0 };
    sig.sa_handler = &signal_handler;
    int sig_val = sigaction(SIGSEGV, &sig, NULL);
    if (sig_val == -1) {
        fprintf(stderr, "Warning: board() -- sigaction()\n");
        return EXIT_FAILURE;
    }

    while (RUNNING) {

        // clock_t start_time = start();
        project(scene);
        // end(start_time);

        while(XPending(displ)) {

            XNextEvent(displ, &event);

            if (handler[event.type])
                handler[event.type](&event);
        }
        usleep(16661);
    }
    return EXIT_SUCCESS;
}
const int main(int argc, char *argv[]) {

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

