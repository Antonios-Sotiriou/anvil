/* general headers */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

/* signal */
#include <signal.h>
// #include <immintrin.h>

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
#include "header_files/shadowmap.h"
#include "header_files/lighting.h"
#include "header_files/camera.h"
#include "header_files/grfk_pipeline.h"
#include "header_files/world_objects.h"
#include "header_files/kinetics.h"

/* testing */
#include "header_files/test_shapes.h"
#include "header_files/exec_time.h"
#include "header_files/logging.h"

/* ############################################## THREAD POOL ################################################################### */
/* Multithreading, Thread Pool Global variables. */
#include <pthread.h>
#define THREADS 4
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

typedef struct {
    void (*taskFunction)(Vec4, float, float, float, float);
    float arg1, arg2, arg3, arg4;
    Vec4 model;
} Task;

pthread_t threads[THREADS];
Task TaskQueue[10000];
int TASKCOUNT = 0;

void submitTask(Task task);
void printTask(Vec4 normal, float a, float b, float c, float d);
/* ############################################## THREAD POOL ################################################################### */

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
Vec4 camera[N + 1] = {
    { 0.0, 0.0, 498.0, 1.0 },
    { 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0 }
};
Vec4 light[C + 1] = {
    { -56.215076, -47.867058, 670.036438, 1.0 },
    { -0.907780, -0.069064, -0.413726, 0.0 },
    { -0.178108, 0.956481, 0.231131, 0.0 },
    { 0.379759, 0.283504, -0.880576, 0.0 },
    { 1.0, 1.0, 1.0}
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
static int ZNear = 0.01;
static int ZFar = 1000.0;
static float AspectRatio = 0;
static float FOV = 45.0;
static float Angle = 2.0;
static float bias = 0.000120;
static int AdjustShadow = 0;
static int AdjustScene = 0;
// static float Yaw = 0.0;
// static float Pitch = 0.0;
// static float Roll = 0.0;
float NPlane = 1.0;
float FPlane = 0.00001;
static float Scale = 0.03;
int DEBUG = 0;
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

/* Represantation functions */
const static void initBuffers(void);
const static Phong initLightModel(void);
const static void project(Scene s);
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
static void *board(void  *args);
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

        int i = 0;
        for (i = 1; i < THREADS; i++)
            if (pthread_cancel(threads[i]));
                fprintf(stderr, "Thread Cancelation of thead[%d] returned an error.\n", i);

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

            initDependedVariables();
        }

        if (!INIT)
            INIT = 1;
    }
}
const static void buttonpress(XEvent *event) {

    printf("buttonpress event received\n");
    printf("X: %f\n", ((event->xbutton.x - (WIDTH / 2.00)) / (WIDTH / 2.00)));
    printf("Y: %f\n", ((event->xbutton.y - (HEIGHT / 2.00)) / (HEIGHT / 2.00)));
    for (int i = 0; i < 10000; i++) {
        Task task = {
            .taskFunction = &printTask,
            .model = camera[Pos],
            .arg1 = 1.0,
            .arg2 = 2.0,
            .arg3 = 3.0,
            .arg4 = 4.0
        };
        submitTask(task);
    }
}

const static void keypress(XEvent *event) {
    
    KeySym keysym = getKeysym(event);
    Vec4 *eye;
    if (EYEPOINT)
        eye = &light[Pos];
    else
        eye = &camera[Pos];

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
        case 65462 : light[Pos].x += 10.1;                   /* Adjust Light Source */
            break;
        case 65460 : light[Pos].x -= 10.1;                   /* Adjust Light Source */
            break;
        case 65458 : light[Pos].z -= 10.1;                   /* Adjust Light Source */
            break;
        case 65464 : light[Pos].z += 10.1;                   /* Adjust Light Source */
            break;
        case 65465 : light[Pos].y -= 10.1;                   /* Adjust Light Source */
            break;
        case 65459 : light[Pos].y += 10.1;                   /* Adjust Light Source */
            break;
        case 43 : Scale += 0.01;
            printf("Scale: %f\n", Scale);                    /* + */
            OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0, ZNear, ZFar);
            break;
        case 45 : Scale -= 0.01;                            /* - */
            printf("Scale: %f\n", Scale);
            OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0, ZNear, ZFar);
            break;
        case 65289 : ;                    /* Tab */
            break;
        default :
            return;
    }
    LookAt = lookat(eye[Pos], eye[U], eye[V], eye[N]);
    ViewMat = inverse_mat(LookAt);
    model.lightPos = vecxm(light[Pos], ViewMat);
    AdjustShadow = 1;
    AdjustScene = 1;

    if (!PROJECTIONVIEW)
        WorldMat = mxm(ViewMat, PerspMat);
    else
        WorldMat = mxm(ViewMat, OrthoMat);
    // project(scene);
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
/* Initializing the structure which we pass arround for lighting calculations. This way we keep lighting vvariables more orginized. */
const static Phong initLightModel(void) {
    Phong r = { 0 };

    r.lightPos = vecxm(light[Pos], ViewMat);
    Vec4 LightColor = { 1.0, 1.0, 1.0 };
    Vec4 SpecularColor = { 0.0, 1.0, 0.0 };

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
/* Starts the Projection Pipeline. */ // ########################################################################################################
const static void project(Scene s) {
    if (AdjustShadow) {
        for (int y = 0; y < wa.height; y++) {
            memset(shadow_buffer[y], '@', sizeof(float) * wa.width);
        }
        shadowPipeline(s);
        AdjustShadow = 0;
    }
    // if (AdjustScene) {
    //     clearBuffers(wa.height, wa.width);
        grfkPipeLine(s);
        // displayScene();
        // AdjustScene = 0;
    // }
    displayScene();
    clearBuffers(wa.height, wa.width);
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
    PerspMat = perspective_mat(FOV, AspectRatio, ZNear, ZFar);
    rePerspMat = reperspective_mat(FOV, AspectRatio);
    OrthoMat = orthographic_mat(Scale, Scale, 0.0, 0.0, ZNear, ZFar);

    LookAt = lookat(camera[Pos], camera[U], camera[V], camera[N]);
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
/* ############################################## THREAD POOL ################################################################### */
const void executeTask(Task *task) {
    task->taskFunction(task->model, task->arg1, task->arg2, task->arg3, task->arg4);
}
void *startThread(void *args) {
    Task task;
    while (1) {

        pthread_mutex_lock(&mutexQueue);
        while (TASKCOUNT == 0) {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        task = TaskQueue[0];
        for (int i = 0; i < TASKCOUNT; i++) {
            TaskQueue[i] = TaskQueue[i + 1];
        }
        TASKCOUNT--;

        pthread_mutex_unlock(&mutexQueue);

        executeTask(&task);
    }
}
void submitTask(Task task) {
    pthread_mutex_lock(&mutexQueue);
    TaskQueue[TASKCOUNT] = task;
    TASKCOUNT++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}
void printTask(Vec4 normal, float a, float b, float c, float d) {
    logVec4(normal);
    printf("a: %f,    b: %f,    c: %f,    d: %f\n", a, b, c, d);
}
/* ############################################## THREAD POOL ################################################################### */
/* General initialization and event handling. */
static void *board(void  *args) {

    if (!XInitThreads()) {
        fprintf(stderr, "Warning: board() -- XInitThreads()\n");
        // return EXIT_FAILURE;
    }

    XEvent event;

    displ = XOpenDisplay(NULL);
    if (displ == NULL) {
        fprintf(stderr, "Warning: board() -- XOpenDisplay()\n");
        // return EXIT_FAILURE;
    }

    initMainWindow();
    InitTimeCounter();
    initGlobalGC();
    pixmapcreate();
    atomsinit();
    // registerSig(SIGSEGV);

    initDependedVariables();
    initBuffers();
    createScene(&scene);
    initMeshes(&scene);
    model = initLightModel();

    float end_time = 0.0;
    while (RUNNING) {

        clock_t start_time = start();
        UpdateTimeCounter();
        CalculateFPS();
        project(scene);
        // rotate_origin(&scene.m[2], Angle, 0.0, 0.0, 1.0);
        // rotate_origin(&scene.m[1], 1, 0.0, 1.0, 0.0);
        // rotate_origin(&scene.m[2], Angle, 1.0, 0.0, 0.0);
        end_time = end(start_time);
        displayInfo();

        while(XPending(displ)) {

            XNextEvent(displ, &event);

            if (handler[event.type])
                handler[event.type](&event);
        }
        usleep(0);
    }

    // return EXIT_SUCCESS;
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

    /* ############################################## THREAD POOL ################################################################### */
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&condQueue, NULL);

    for (int i = 0; i < THREADS; i++) {
        if (i == 0)
            if (pthread_create(&threads[i], NULL, &board, NULL) != 0);
        else 
            if (pthread_create(&threads[i], NULL, &startThread, NULL) != 0)
                fprintf(stderr, "Failed to create thread [ %d ]\n", i);
    }

    // for (int i = 0; i < 100; i++) {
    //     Task task = {
    //         .taskFunction = &printTask,
    //         .normal = camera.Pos,
    //         .arg1 = 1.0,
    //         .arg2 = 2.0,
    //         .arg3 = 3.0,
    //         .arg4 = 4.0
    //     };
    //     submitTask(task);
    // }

    for (int i = 0; i < THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Failed to join thread [ %d ]\n", i);
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&condQueue);
    /* ############################################## THREAD POOL ################################################################### */

    // if (board()) {
    //     fprintf(stderr, "ERROR: main() -- board()\n");
    //     return EXIT_FAILURE;
    // }

    XCloseDisplay(displ);
    
    return EXIT_SUCCESS;
}

