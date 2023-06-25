/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

#define EDGEFUNC 0
#define SCANLINE 1

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
#include "header_files/general_functions.h"
#include "header_files/quaternions.h"
#include "header_files/shadowmap.h"
#include "header_files/lighting.h"
#include "header_files/camera.h"

#ifdef EDGEFUNC
    #include "header_files/edgefunc.h"
#elif SCANLINE
    #include "header_files/scanline.h"
#endif

/* testing */
#include "header_files/test_shapes.h"
#include "header_files/exec_time.h"
#include "header_files/logging.h"

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};
enum { Pos, U, V, N, C};

#define WIDTH                     800
#define HEIGHT                    800
#define POINTERMASKS              ( ButtonPressMask )
#define KEYBOARDMASKS             ( KeyPressMask )
#define EXPOSEMASKS               ( StructureNotifyMask )

/* X Global Structures. */
Display *displ;
Window win;
Pixmap pixmap;
GC gc;
XGCValues gcvalues;
XWindowAttributes wa;
XSetWindowAttributes sa;
Atom wmatom[Atom_Last];

/* Project Global Buffers. */
Pixel **pixels;
char *frame_buffer;
float **depth_buffer;
float **shadow_buffer;

/* Project Global Structures. */
Global camera = {
    .Pos = { 0.0, 0.0, 498.0, 1.0 },
    .U   = { 1.0, 0.0, 0.0, 0.0 },
    .V   = { 0.0, 1.0, 0.0, 0.0 },
    .N   = { 0.0, 0.0, 1.0, 0.0 }
};
Global light = {
    .Pos = { -56.215076, -47.867058, 670.036438, 1.0 },
    .U   = { -0.907780, -0.069064, -0.413726, 0.0 },
    .V   = { -0.178108, 0.956481, 0.231131, 0.0 },
    .N   = { 0.379759, 0.283504, -0.880576, 0.0 },
    .C   = { 1.0, 1.0, 1.0}
};

Scene scene = { 0 };
Mat4x4 WorldMat = { 0 }, LookAt = { 0 }, ViewMat = { 0 }, PerspMat = { 0 }, rePerspMat = { 0 }, OrthoMat = { 0 }, LightMat = { 0 };
Phong model = { 0 };

/* Project Global Variables. */
static int INIT = 0;
static int RUNNING = 1;
int HALFW = 0; // Half width of the screen; This variable is initialized in configurenotify function.Help us decrease the number of divisions.
int HALFH = 0; // Half height of the screen; This variable is initialized in configurenotify function.Help us decrease the number of divisions.
static int EYEPOINT = 0;
static int PROJECTIONVIEW = 0;
static int PROJECTBUFFER = 1;
static float AspectRatio = 0;
static float FOV = 45.0;
static float Angle = 2.0;
static float bias = 0.000120;
static int AdjustShadow = 0;
static int AdjustScene = 0;
// static float Yaw = 0.0;
// static float Pitch = 0.0;
// static float Roll = 0.0;
static float NPlane = 1.0;
static float FPlane = 0.00001;
static float Scale = 0.03;
static int DEBUG = 0;
float			        TimeCounter, LastFrameTimeCounter, DeltaTime, prevTime = 0.0, FPS;
struct timeval		    tv, tv0;
int			            Frame = 1, FramesPerFPS;

/* Event handling functions. */
const static void clientmessage(XEvent *event);
const static void reparentnotify(XEvent *event);
const static void mapnotify(XEvent *event);
const static void resizerequest(XEvent *event);
const static void configurenotify(XEvent *event);
const static void buttonpress(XEvent *event);
const static void keypress(XEvent *event);

/* Objects Rotation functions */
const static void rotate_x(Mesh *c, const float angle);
const static void rotate_y(Mesh *c, const float angle);
const static void rotate_z(Mesh *c, const float angle);
const static void rotate_origin(Mesh *obj, const float angle, float x, float y, float z);
const static void rotate_light(Global g, const float angle, float x, float y, float z);

/* Represantation functions */
const static void initBuffers(void);
const static void initMeshes(Scene *s);
const static void loadTexture(Mesh *c);
const static void createScene(Scene *s);
const static void releaseScene(Scene *s);
const static void project(Scene s);
static void *applyShadows(Scene s);
static void *pipeLine(Scene s);
const static void ppdiv(Mesh *c);
const static Mesh shadowcull(const Mesh c);
const static Mesh bfculling(const Mesh c);
const static Mesh viewtoscreen(const Mesh c);
const static void rasterize(const Mesh sc);
const static Phong initLightModel(void);
const static void displayScene(void);
const static void clearBuffers(const int height, const int width);
const void exportScene(void);

/* Xlib relative functions and event dispatcher. */
const static KeySym getKeysym(XEvent *event);
const static void initMainWindow();
const static void initGlobalGC();
const static void initDependedVariables(void);
const static void pixmapcreate(void);
const static void pixmapdisplay(void);
const static void atomsinit(void);
const static void sigsegv_handler(const int sig);
const static int registerSig(const int signal);
static int board(void);
static void (*handler[LASTEvent]) (XEvent *event) = {
    [ClientMessage] = clientmessage,
    [ReparentNotify] = reparentnotify,
    [MapNotify] = mapnotify,
    [ResizeRequest] = resizerequest,
    [ConfigureNotify] = configurenotify,
    [ButtonPress] = buttonpress,
    [KeyPress] = keypress,
};
const static Global rerasterize(const Global l);

const static void clientmessage(XEvent *event) {
    printf("Received client message event\n");
    if (event->xclient.data.l[0] == wmatom[Win_Close]) {
        printf("WM_DELETE_WINDOW\n");

        releaseScene(&scene);

        printf("Reached step 1\n");
        free2darray((void*)pixels, wa.height);
        printf("Reached step 2\n");
        free2darray((void*)depth_buffer, wa.height);
        printf("Reached step 3\n");
        free2darray((void*)shadow_buffer, wa.height);
        printf("Reached step 4\n");
        free(frame_buffer);
        printf("Reached step 5\n");
        XFreeGC(displ, gc);
        printf("Reached step 6\n");
        XFreePixmap(displ, pixmap);
        printf("Reached step 7\n");
        XDestroyWindow(displ, win);
        printf("Reached step 8\n");

        RUNNING = 0;
    }
}
const static void reparentnotify(XEvent *event) {

    printf("reparentnotify event received\n");
}
const static void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");
}
const static void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
const static void configurenotify(XEvent *event) {

    if (!event->xconfigure.send_event) {
        printf("configurenotify event received\n");
        int old_height = wa.height;
        XGetWindowAttributes(displ, win, &wa);

        if (INIT) {
            free2darray((void*)pixels, old_height);
            free2darray((void*)depth_buffer, old_height);
            free2darray((void*)shadow_buffer, old_height);
            free(frame_buffer);

            pixmapcreate();
            initBuffers();
        }
        initDependedVariables();

        if (!INIT)
            INIT = 1;
    }
}
const static void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
    printf("X: %f\n", ((event->xbutton.x - (WIDTH / 2.00)) / (WIDTH / 2.00)));
    printf("Y: %f\n", ((event->xbutton.y - (HEIGHT / 2.00)) / (HEIGHT / 2.00)));
}

const static void keypress(XEvent *event) {
    
    KeySym keysym = getKeysym(event);
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
        case 120 : rotate_x(&scene.m[1], Angle);       /* x */
            break;
        case 121 : rotate_y(&scene.m[1], Angle);       /* y */
            break;
        case 122 : rotate_z(&scene.m[0], Angle);       /* z */
            break;
        case 114 : rotate_light(light, Angle, 0.0, 1.0, 0.0);    /* r */
            break;
        case 99 : rotate_origin(&scene.m[2], Angle, 1.0, 0.0, 0.0);        /* c */
            break;
        case 98 : exportScene();                            /* b */
            break;
        case 112 :
            if (PROJECTBUFFER == 3)
                PROJECTBUFFER = 0;
            PROJECTBUFFER++;
            if (PROJECTBUFFER == 1) {
                fprintf(stderr, "Projecting Pixels -- PROJECTBUFFER: %d\n", PROJECTBUFFER);
            } else if (PROJECTBUFFER == 2) {
                fprintf(stderr, "Projecting Depth buffer -- PROJECTBUFFER: %d\n", PROJECTBUFFER);
            } else if (PROJECTBUFFER == 3) {
                fprintf(stderr, "Projecting Shadow buffer -- PROJECTBUFFER: %d\n", PROJECTBUFFER);
            }
            break;
        case 110 : bias -= 0.00001;               /* n */
            printf("Bias: %f\n", bias);
            break;
        case 117 : bias += 0.00001;              /* u */
            printf("Bias: %f\n", bias);
            break;
        case 118 :
            if (!PROJECTIONVIEW)               /* v */
                PROJECTIONVIEW++;
            else
                PROJECTIONVIEW = 0;
            break;
        case 65451 :FPlane += 0.0001;             /* + */
            printf("FPlane: %f\n",FPlane);
            break;
        case 65453 :FPlane -= 0.0001;             /* - */
            printf("FPlane: %f\n", FPlane);
            break;
        case 65450 : NPlane += 0.01;             /* * */
            printf("NPlane: %f\n", NPlane);
            break;
        case 65455 : NPlane -= 0.01;             /* / */
            printf("NPlane: %f\n", NPlane);
            break;
        case 108 :                                    /* l */
            if (EYEPOINT == 0)
                EYEPOINT = 1;
            else
                EYEPOINT = 0;
            break;
        case 65462 : light.Pos.x += 10.1;                   /* Adjust Light Source */
            break;
        case 65460 : light.Pos.x -= 10.1;                   /* Adjust Light Source */
            break;
        case 65458 : light.Pos.z -= 10.1;                   /* Adjust Light Source */
            break;
        case 65464 : light.Pos.z += 10.1;                   /* Adjust Light Source */
            break;
        case 65465 : light.Pos.y -= 10.1;                   /* Adjust Light Source */
            break;
        case 65459 : light.Pos.y += 10.1;                   /* Adjust Light Source */
            break;
        case 43 : Scale += 0.01;
            printf("Scale: %f\n", Scale);                    /* + */
            OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0);
            break;
        case 45 : Scale -= 0.01;                            /* - */
            printf("Scale: %f\n", Scale);
            OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0);
            break;
        case 65289 : rerasterize(light);                    /* Tab */
            break;
        default :
            return;
    }
    LookAt = lookat(eye->Pos, eye->U, eye->V, eye->N);
    ViewMat = inverse_mat(LookAt);
    model.lightPos = vecxm(light.Pos, ViewMat);
    AdjustShadow = 1;
    AdjustScene = 1;

    if (!PROJECTIONVIEW)
        WorldMat = mxm(ViewMat, PerspMat);
    else
        WorldMat = mxm(ViewMat, OrthoMat);
    project(scene);
}
/* Rotates object according to World X axis. */
const static void rotate_x(Mesh *c, const float angle) {
    Mat4x4 m = rotate_xmat(radians(angle));
    Mesh cache = *c;
    *c = meshxm(cache, m);
    free(cache.t);
    free(cache.v);
}
/* Rotates object according to World Y axis. */
const static void rotate_y(Mesh *c, const float angle) {
    Mat4x4 m = rotate_ymat(radians(angle));
    Mesh cache = *c;
    *c = meshxm(cache, m);
    free(cache.t);
    free(cache.v);
}
/* Rotates object according to World Z axis. */
const static void rotate_z(Mesh *c, const float angle) {
    Mat4x4 m = rotate_zmat(radians(angle));
    Mesh cache = *c;
    *c = meshxm(cache, m);
    free(cache.t);
    free(cache.v);
}
/* Rotates object according to own axis. */
const static void rotate_origin(Mesh *c, const float angle, float x, float y, float z) {
    Vector pos = { 1.0, -1.0, 510.0 };
    Vector axis = { x, y, z };
    Quat n = setQuat(0, pos);

    Quat xrot = rotationQuat(angle, axis);
    Mat4x4 rm = MatfromQuat(xrot, n.v);

    Mesh cache = *c;
    normalsxm(&cache, rm);
    *c = meshxm(cache, rm);
    
    free(cache.t);
    free(cache.v);
}
/* Rotates light arround scene center. */
const static void rotate_light(Global g, const float angle, float x, float y, float z) {
    Vector pos = { 0.0, 0.0, 498.0 };
    Vector axis = { x, y, z };
    Quat n = setQuat(0, pos);

    Quat xrot = rotationQuat(1, axis);
    Mat4x4 rm = MatfromQuat(xrot, n.v);

    light.Pos = vecxm(g.Pos, rm);
    light.U = vecxm(g.U, rm);
    light.V = vecxm(g.V, rm);
    light.N = vecxm(g.N, rm);
    logGlobal(light);
}
/* Creates and Initializes the importand buffers. (frame, depth, shadow). */
const static void initBuffers(void) {
    pixels = create2darray((void*)pixels, sizeof(Pixel), wa.height, wa.width);
    depth_buffer = create2darray((void*)depth_buffer, sizeof(float), wa.height, wa.width);
    shadow_buffer = create2darray((void*)shadow_buffer, sizeof(float), wa.height, wa.width);
    frame_buffer = calloc(wa.width * wa.height * 4, 1);

    for (int y = 0; y < wa.height; y++){
        memset(pixels[y], 0, sizeof(Pixel) * wa.width);
        memset(depth_buffer[y], 0, sizeof(float) * wa.width);
        // for (int x = 0; x < wa.width; x++) {
        //     shadow_buffer[y][x] = 1.0;
        // }
    }
}
/* Initializes the meshes from which the Scene consists. */
const static void initMeshes(Scene *s) {
    Mesh space = { 0 }, terrain = { 0 }, jupiter = { 0 }, earth = { 0 }, sun = { 0 };
    Mat4x4 ScaleMat, TransMat, PosMat;

    // space = load_obj("objects/spacedom.obj");
    // memcpy(space.texture_file, "textures/spacedom_texture.bmp", sizeof(char) * 30);
    // loadTexture(&space);
    // ScaleMat = scale_mat(1000.0);
    // TransMat = translation_mat(0.0, 0.0, 500.0);
    // PosMat = mxm(ScaleMat, TransMat);
    // s->m[4] = meshxm(space, PosMat);
    // free(space.v);
    // free(space.t);

    terrain = load_obj("objects/triangle.obj");
    memcpy(terrain.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    loadTexture(&terrain);
    ScaleMat = scale_mat(1.0);
    rotate_x(&terrain, -90);
    TransMat = translation_mat(0.0, 0.0, 502.0);
    PosMat = mxm(ScaleMat, TransMat);
    s->m[0] = meshxm(terrain, PosMat);
    free(terrain.v);
    free(terrain.t);

    // jupiter = load_obj("objects/earth.obj");
    // memcpy(jupiter.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    // loadTexture(&jupiter);
    // ScaleMat = scale_mat(10.0);
    // TransMat = translation_mat(-10.0, 0.0, 580.0);
    // PosMat = mxm(ScaleMat, TransMat);
    // s->m[1] = meshxm(jupiter, PosMat);
    // free(jupiter.v);
    // free(jupiter.t);

    // earth = load_obj("objects/earth.obj");
    // memcpy(earth.texture_file, "textures/Earth.bmp", sizeof(char) * 19);
    // loadTexture(&earth);
    // ScaleMat = scale_mat(0.5);
    // TransMat = translation_mat(1.0, -1.0, 510.0);
    // PosMat = mxm(ScaleMat, TransMat);
    // // normalsxm(&earth, PosMat);
    // s->m[2] = meshxm(earth, PosMat);
    // free(earth.v);
    // free(earth.t);

    // sun = load_obj("objects/spacedom.obj");
    // memcpy(sun.texture_file, "textures/light.bmp", sizeof(char) * 19);
    // loadTexture(&sun);
    // ScaleMat = scale_mat(0.5);
    // TransMat = translation_mat(light.Pos.x, light.Pos.y, light.Pos.z);
    // PosMat = mxm(ScaleMat, TransMat);
    // s->m[3] = meshxm(sun, PosMat);
    // free(sun.v);
    // free(sun.t);
}
/* Loads the appropriate Textures and importand Texture infos. */
const static void loadTexture(Mesh *c) {

    BMP_Header bmp_header;
    BMP_Info texture;

    FILE *fp;
    fp = fopen(c->texture_file, "rb");
    if (fp == NULL){
        fclose(fp);
        fprintf(stderr, "Could not open file < %s >! loadTexture() -- fopen().\n", c->texture_file);
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
const static void createScene(Scene *s) {
    s->m = malloc(sizeof(Mesh) * 4);
    s->indexes = 4;
}
const static void releaseScene(Scene *s) {
    for (int i = 0; i < s->indexes; i++) {
        free(s->m[i].t);
        free(s->m[i].v);
        free2darray((void*)s->m[i].texels, s->m[i].texture_height);
    }
    free(s->m);
}
/* Starts the Projection Pipeline. */ // ########################################################################################################
const static void project(Scene s) {
    if (AdjustShadow) {
        for (int y = 0; y < wa.height; y++) {
            memset(shadow_buffer[y], '@', sizeof(float) * wa.width);
            // for (int x = 0; x < wa.width; x++) {
            //     // shadow_buffer[y][x] = 1.0;
            //     printf("shadow_buffer[%d][%d]: %f\n", y, x, shadow_buffer[y][x]);
            // }
        }
        applyShadows(s);
        AdjustShadow = 0;
    }
    // if (AdjustScene) {
    //     clearBuffers(wa.height, wa.width);
        pipeLine(s);
        // displayScene();
        // AdjustScene = 0;
    // }
    displayScene();
    clearBuffers(wa.height, wa.width);
}
static void *applyShadows(Scene s) {
    Mat4x4 lm = lookat(light.Pos, light.U, light.V, light.N);
    Mat4x4 Lview = inverse_mat(lm);
    LightMat = mxm(Lview, OrthoMat);

    for (int i = 0; i < s.indexes; i++) {

        Mesh cache = meshxm(s.m[i], LightMat);

        /* At this Point triangles must be clipped against near plane. */
        Vector plane_near_p = { 0.0, 0.0, NPlane },
            plane_near_n = { 0.0, 0.0, 1.0 };
        Mesh nf = clipp(cache, plane_near_p, plane_near_n);

        if (nf.t_indexes) {
            /* Applying Backface culling before we proceed to full frustum clipping. */
            Mesh bf = shadowcull(nf);

            /* Sending to translation from NDC to Screen Coordinates. */
            Mesh uf = viewtoscreen(bf);

            createShadowmap(uf);
            free(uf.t);
            free(uf.v);
        } else {
            free(nf.t);
            free(nf.v);
        }
    }
    return NULL;
}
static void *pipeLine(Scene s) {

    for (int i = 0; i < s.indexes; i++) {

        Mesh cache = meshxm(s.m[i], WorldMat);

        /* Transform normals in View Space before clipping and perspective division. */
        normalsxm(&cache, ViewMat);

        /* At this Point triangles must be clipped against near plane. */
        Vector plane_near_p = { 0.0, 0.0, NPlane },
            plane_near_n = { 0.0, 0.0, 1.0 };
        Mesh nf = clipp(cache, plane_near_p, plane_near_n);

        /* Applying perspective division. */
        if (nf.t_indexes) {
            ppdiv(&nf);

            /* Applying Backface culling before we proceed to full frustum clipping. */
            Mesh bf = bfculling(nf);

            /* Sending to translation from NDC to Screen Coordinates. */
            Mesh uf = viewtoscreen(bf);

            rasterize(uf);
            free(uf.t);
            free(uf.v);
        } else {
            free(nf.t);
            free(nf.v);
        }
    }
    return NULL;
} // ##############################################################################################################################################
/* Perspective division. */
const static void ppdiv(Mesh *c) {

    for (int i = 0; i < c->t_indexes; i++) {
        for (int j = 0; j < 3; j++) {
            // if ( c->t[i].v[j].w > 0.00 ) {
                c->t[i].v[j].x /= c->t[i].v[j].w;
                c->t[i].v[j].y /= c->t[i].v[j].w;
                c->t[i].v[j].z /= c->t[i].v[j].w;
            // }
        }
    }
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic Mesh stucture Triangles array. */
const static Mesh shadowcull(const Mesh c) {
    Mesh r = c;
    Vector cp;
    float dpc;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.t_indexes; i++) {
        dpc = winding3D(c.t[i]);

        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];

            counter++;
            index++;
        }
    }
    r.t_indexes = index;
    free(c.t);
    return r;
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

    for (int i = 0; i < c.t_indexes; i++) {
        dpc = winding3D(c.t[i]);

        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];

            counter++;
            index++;
        }
    }
    r.t_indexes = index;
    free(c.t);
    return r;
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static Mesh viewtoscreen(const Mesh c) {
    float w = 0.0;
    for (int i = 0; i < c.t_indexes; i++) {
        for (int j = 0; j < 3; j++) {
            w = c.t[i].v[j].w;
            c.t[i].v[j].x = (++c.t[i].v[j].x) * HALFW;
            c.t[i].v[j].y = (++c.t[i].v[j].y) * HALFH;
            c.t[i].v[j].z *= 0.5;//( (1 / c.t[i].v[j].z) - (1 / ZNear) ) / ( (1 / ZFar) - (1 / ZNear) );//(c.t[i].v[j].z - ZNear) / (ZFar - ZNear);
            c.t[i].v[j].w = 1 / w;

            c.t[i].vt[j].u /= w;
            c.t[i].vt[j].v /= w;
            c.t[i].vt[j].w = c.t[i].v[j].w;
        }
    }

    /* Far Plane clipping and side clipping. */
    Vector plane_far_p = { 0.0, 0.0, FPlane },
           plane_far_n = { 0.0, 0.0, 1.0 };
    Mesh ff = clipp(c, plane_far_p, plane_far_n);

    // if (DEBUG == 1) {
        Vector plane_right_p = { wa.width - 1.0, 0.0, 0.0 },
            plane_right_n = { -1.0, 0.0, 0.0 };
        Mesh rf = clipp(ff, plane_right_p, plane_right_n);

        Vector plane_down_p = { 0.0, wa.height - 1.0, 0.0 },
            plane_down_n = { 0.0, -1.0, 0.0 };
        Mesh df = clipp(rf, plane_down_p, plane_down_n);

        Vector plane_left_p = { 0.0, 0.0, 0.0 },
            plane_left_n = { 1.0, 0.0, 0.0 };
        Mesh lf = clipp(df, plane_left_p, plane_left_n);

        Vector plane_up_p = { 0.0, 0.0, 0.0 },
            plane_up_n = { 0.0, 1.0, 0.0 };
        Mesh uf = clipp(lf, plane_up_p, plane_up_n);
        return uf;
    // }
    // return ff;
}
/* Rasterize given Mesh by passing them to the appropriate function. */
const static void rasterize(const Mesh c) {
    signed int tex_h = c.texture_height - 1;
    signed int tex_w = c.texture_width - 1;

    for (int i = 0; i < c.t_indexes; i++) {

        if (DEBUG == 1) {
            drawLine(c.t[i].v[0].x, c.t[i].v[0].y, c.t[i].v[1].x, c.t[i].v[1].y, 255, 0, 0);
            drawLine(c.t[i].v[1].x, c.t[i].v[1].y, c.t[i].v[2].x, c.t[i].v[2].y, 255, 0, 0);
            drawLine(c.t[i].v[2].x, c.t[i].v[2].y, c.t[i].v[0].x, c.t[i].v[0].y, 255, 0, 0);
        } else if (DEBUG == 2) {
            // clock_t start_time = start();
            fillTriangle(c.t[i]);
            // end(start_time);
        } else {
            // clock_t start_time = start();
            texTriangle(c.t[i], c.texels, tex_h, tex_w);
            // end(start_time);
        }
    }
}
/* Initializing the structure which we pass arround for lighting calculations. This way we keep lighting vvariables more orginized. */
const static Phong initLightModel(void) {
    Phong r = { 0 };

    r.lightPos = vecxm(light.Pos, ViewMat);
    Vector LightColor = { 1.0, 1.0, 1.0 };
    Vector SpecularColor = { 0.0, 1.0, 0.0 };

    r.LightColor = LightColor;
    r.objColor.Blue = 0.129 * 255;
    r.objColor.Green = 0.478 * 255;
    r.objColor.Red = 0.615 * 255;

    r.AmbientStrength = 0.1;
    r.Ambient = multiply_vec(r.LightColor, r.AmbientStrength);

    r.SpecularStrength = 0.75;
    r.Specular = multiply_vec(SpecularColor, r.SpecularStrength);

    return r;
}
/* Writes the final Pixel values on screen. */
const static void displayScene(void) {

    int size = wa.width * wa.height * 4;

    int height_inc = 0;
    int width_inc = 0;
    for (int i = 0; i < size; i++) {

        if (PROJECTBUFFER <= 1)
            memcpy(&frame_buffer[i], &pixels[height_inc][width_inc], sizeof(Pixel));
        else if (PROJECTBUFFER == 2)
            memcpy(&frame_buffer[i], &depth_buffer[height_inc][width_inc], sizeof(float));
        else if (PROJECTBUFFER == 3)
            memcpy(&frame_buffer[i], &shadow_buffer[height_inc][width_inc], sizeof(float));

        i += 3;
        width_inc++;
        if (width_inc == wa.width) {
            height_inc += 1;
            width_inc = 0;
        }
    }

    XImage *image = XCreateImage(displ, wa.visual, wa.depth, ZPixmap, 0, frame_buffer, wa.width, wa.height, 32, (wa.width * 4));
    XPutImage(displ, pixmap, gc, image, 0, 0, 0, 0, wa.width, wa.height);
    free(image);

    pixmapdisplay();
}
/* Clearing Buffers but setting their value to 0. */
const static void clearBuffers(const int height, const int width) {

    for (int y = 0; y < height; y++) {
        memset(pixels[y], 0, sizeof(Pixel) * width);
        memset(depth_buffer[y], 0, sizeof(float) * width);
    }
}
/* Exports displayed Scene in bmp format. */
const void exportScene(void) {
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
const static KeySym getKeysym(XEvent *event) {

    /* Get Keyboard UTF-8 input */
    XIM xim = { 0 };
    xim = XOpenIM(displ, NULL, NULL, NULL);
    if (xim == NULL) {
        perror("keypress() - XOpenIM()");
    }

    XIC xic = { 0 };
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
const static void initMainWindow(void) {
    sa.event_mask = EXPOSEMASKS | KEYBOARDMASKS | POINTERMASKS;
    sa.background_pixel = 0x000000;
    win = XCreateWindow(displ, XRootWindow(displ, XDefaultScreen(displ)), 0, 0, WIDTH, HEIGHT, 0, CopyFromParent, InputOutput, CopyFromParent, CWBackPixel | CWEventMask, &sa);
    XMapWindow(displ, win);
    XGetWindowAttributes(displ, win, &wa);
}
void InitTimeCounter() {
    gettimeofday(&tv0, NULL);
    FramesPerFPS = 30;
}
void UpdateTimeCounter() {
    LastFrameTimeCounter = TimeCounter;
    gettimeofday(&tv, NULL);
    TimeCounter = (float)(tv.tv_sec - tv0.tv_sec) + 0.000001*((float)(tv.tv_usec - tv0.tv_usec));
    DeltaTime = TimeCounter - LastFrameTimeCounter;
}
void CalculateFPS() {
    Frame ++;

    if((Frame % FramesPerFPS) == 0) {
    FPS = ((float)(FramesPerFPS)) / (TimeCounter-prevTime);
    prevTime = TimeCounter;
    }
}
void displayInfo() {
    char Resolution_string[20], TimeCounter_string[20], FPS_string[20];

    sprintf(Resolution_string, "Resolution: %d x %d\0", wa.width, wa.height);
    sprintf(TimeCounter_string, "Running Time: %4.1f\0", TimeCounter);
    sprintf(FPS_string, "%4.1f fps\0", FPS);

    XDrawString(displ ,win ,gc, 5, 12, Resolution_string, strlen(Resolution_string));
    XDrawString(displ ,win ,gc, 5, 24, TimeCounter_string, strlen(TimeCounter_string));
    XDrawString(displ ,win ,gc, 5, 36, FPS_string, strlen(FPS_string));
}
const static void initGlobalGC(void) {
    gcvalues.foreground = 0xffffff;
    gcvalues.background = 0x000000;
    gcvalues.graphics_exposures = False;
    gc = XCreateGC(displ, win, GCBackground | GCForeground | GCGraphicsExposures, &gcvalues);
}
const static void initDependedVariables(void) {
    AspectRatio = ((float)wa.width / (float)wa.height);
    HALFW = wa.width >> 1;
    HALFH = wa.height >> 1;
    PerspMat = perspective_mat(FOV, AspectRatio);
    rePerspMat = reperspective_mat(FOV, AspectRatio);
    OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0);

    LookAt = lookat(camera.Pos, camera.U, camera.V, camera.N);
    ViewMat = inverse_mat(LookAt);
    WorldMat = mxm(ViewMat, PerspMat);

    AdjustShadow = 1;
    AdjustScene = 1;
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
/* Signal handler to clean memory before exit, after receiving a given signal. */
const static void sigsegv_handler(const int sig) {
    printf("Received Signal from OS with ID: %d\n", sig);
    XEvent event = { 0 };
    event.type = ClientMessage;
    event.xclient.data.l[0] = wmatom[Win_Close];
    /* Send the signal to our event dispatcher for further processing. */
    if(RUNNING)
        handler[event.type](&event);
}
/* Registers the given Signal. */
const static int registerSig(const int signal) {
    /* Signal handling for effectivelly releasing the resources. */
    struct sigaction sig = { 0 };
    sig.sa_handler = &sigsegv_handler;
    int sig_val = sigaction(signal, &sig, NULL);
    if (sig_val == -1) {
        fprintf(stderr, "Warning: board() -- sigaction()\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/* General initialization and event handling. */
static int board(void) {

    if (!XInitThreads()) {
        fprintf(stderr, "Warning: board() -- XInitThreads()\n");
        return EXIT_FAILURE;
    }

    XEvent event;

    displ = XOpenDisplay(NULL);
    if (displ == NULL) {
        fprintf(stderr, "Warning: board() -- XOpenDisplay()\n");
        return EXIT_FAILURE;
    }

    initMainWindow();
    InitTimeCounter();
    initGlobalGC();
    pixmapcreate();
    atomsinit();
    registerSig(SIGSEGV);

    initDependedVariables();
    initBuffers();
    createScene(&scene);
    initMeshes(&scene);
    model = initLightModel();

    float end_time = 0.0;
    while (RUNNING) {

        // clock_t start_time = start();
        UpdateTimeCounter();
        CalculateFPS();
        // project(scene);
        // rotate_origin(&scene.m[2], Angle, 0.0, 0.0, 1.0);
        // rotate_origin(&scene.m[1], 1, 0.0, 1.0, 0.0);
        // rotate_origin(&scene.m[2], Angle, 1.0, 0.0, 0.0);
        // end_time = end(start_time);
        displayInfo();

        while(XPending(displ)) {

            XNextEvent(displ, &event);

            if (handler[event.type])
                handler[event.type](&event);
        }
        usleep(0);
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

    if (board()) {
        fprintf(stderr, "ERROR: main() -- board()\n");
        return EXIT_FAILURE;
    }

    XCloseDisplay(displ);
    
    return EXIT_SUCCESS;
}
/* From World Coordinate System to Screen space and back again to World Coordinate System. Testing Purposes only. */
const static Global rerasterize(const Global l) {
    Global r = l;
    printf("World Space:  r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    Mat4x4 View = inverse_mat(LookAt);
    r.Pos = vecxm(r.Pos, View);
    printf("Camera Space: r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    // Mat4x4 Proj = orthographic_mat(Scale, Scale, 0.0, 0.0);
    // r.Pos = vecxm(r.Pos, Proj);
    // printf("Orthogr Homogin Space: r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    Mat4x4 Proj = perspective_mat(FOV, AspectRatio);
    r.Pos = vecxm(r.Pos, Proj);
    printf("Perspec Clipp Space: r.x: %f,   r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    if (r.Pos.w > 0.0) {
        r.Pos.x /= r.Pos.w;
        r.Pos.y /= r.Pos.w;
        r.Pos.z /= r.Pos.w;
    }
    printf("NDC Space:    r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    r.Pos.x = (1.0 + r.Pos.x) * HALFW;
    r.Pos.y = (1.0 + r.Pos.y) * HALFH;
    printf("Screen Space: r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    r.Pos.x = (r.Pos.x / HALFW) - 1.0;
    r.Pos.y = (r.Pos.y / HALFH) - 1.0;
    printf("To NDC:       r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    if (r.Pos.w > 0.0) {
        r.Pos.x *= r.Pos.w;
        r.Pos.y *= r.Pos.w;
        r.Pos.z *= r.Pos.w;
    }
    printf("To Clipp:    r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    // Mat4x4 reProj = reperspective_mat(FOV, AspectRatio);
    Mat4x4 reProj = reperspective_mat(FOV, AspectRatio);
    r.Pos = vecxm(r.Pos, reProj);
    r.Pos.w = 1.0;
    printf("To Camera:   r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    r.Pos = vecxm(r.Pos, LookAt);
    printf("To World:   r.x: %f,    r.y: %f,    r.z: %f,    r.w: %f\n", r.Pos.x, r.Pos.y, r.Pos.z, r.Pos.w);

    return r;
}

