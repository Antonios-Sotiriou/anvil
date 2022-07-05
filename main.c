// general headers
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

// Project specific headers
#include "header_files/locale.h"

typedef struct {
    float x, y, z;
} Point;

typedef struct {
    int x, y;
} CPoint;

typedef struct {
    Point point[3];
} Triangle;

typedef struct {
    CPoint cpoint[3];
} CTriangle;

typedef struct {
    Triangle el[2];
} Block;

typedef struct {
    Block block[6];
} Cube;

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};
enum { UnderEl, UperEl, LastEl};
enum { FrontBlock, BackBlock, WestBlock, EastBlock, NorthBlock, SouthBlock, LastBlock};

#define WIDTH                     800
#define HEIGHT                    800
// #define HORIZONTAL                2.00
// #define VERTICAL                  2.00
// #define ZOOM                      4.00
#define AspectRatio               ( wa.width / wa.height )
#define FieldOfView               ( AspectRatio * (1 / tan(wa.width / 2)) * event->xbutton.x )
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
Point el;
Triangle tri = {
    {{ 0.0, -1.0, 1.005 }, { -1.0, 0.0, 1.005 }, { 1.0, 0.0, 1.005 }}
};
CTriangle ctri = { 0 };

static int MAPCOUNT = 0;
static int RUNNING = 1;
static float HORIZONTAL = 2.00;
static float VERTICAL = 2.00;
static float ZOOM = 4.00;

// initialize the knot object to be transfered because we can't transfer pointers to pointers through shared memory.
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);
static void init_tri(Triangle *tri);
static void paint_triangle(CTriangle *ctri);
static void nor_triangle(Triangle *tri);
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
    // XGetWindowAttributes(displ, win, &wa);
}
static const void mapnotify(XEvent *event) {

    printf("mapnotify event received\n");
    
    if (MAPCOUNT) {
        pixmapdisplay();
    } else {
        init_tri(&tri);
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
    nor_triangle(&tri);
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
        el.x = (event->xbutton.x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        el.y = (event->xbutton.y - (wa.height / VERTICAL)) / (wa.height / ZOOM);
    } else {
        el.x = (event->xbutton.x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        el.y = (event->xbutton.y - (wa.height / VERTICAL)) / (wa.height / ZOOM);
    }

    printf("X : %f\nY : %f\n", el.x, el.y);
    printf("FOV : %F\n", ((wa.width / wa.height) / 2.00) / tan(wa.width / 2.00) * 3.14 / 180.00);//((wa.width / wa.height) * (1 / tan(wa.width / 2.00)) * el.x) / ZOOM);
    printf("FOV : %F\n", ((wa.width / wa.height) / 4.00) / tan(800 / 2.00));
    // if (event->xkey.keycode == 1) {
    //     el.zoom *= 0.50;
    // } else if (event->xkey.keycode == 3) {
    //     el.zoom /= 0.50;
    // }
}
static int compare_float(float f1, float f2, int precision) {

    
    if ( ((int)(f1 * precision) - (int)(f2 * precision)) != 0) {
        return 1;
    } else {
        return 0;
    }
}
static void init_tri(Triangle *tri) {

    for (int i = 0; i <= 2; i++) {
        tri->point[i].x = tri->point[i].x / tri->point[i].z;
        tri->point[i].y = tri->point[i].y / tri->point[i].z;
        printf("Point x: %f\nPoint y: %f\n", tri->point[i].x, tri->point[i].y);
    }
}
static void move_left(void) {

    for (int i = 0; i <= 2; i++) {
        ctri.cpoint[i].x -= 1;
        tri.point[i].x = (ctri.cpoint[i].x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        tri.point[i].y = (ctri.cpoint[i].y - (wa.height / VERTICAL)) / (wa.width / ZOOM);
    }
}
static void move_right(void) {

    for (int i = 0; i <= 2; i++) {
        ctri.cpoint[i].x += 1;
        tri.point[i].x = (ctri.cpoint[i].x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        tri.point[i].y = (ctri.cpoint[i].y - (wa.height / VERTICAL)) / (wa.width / ZOOM);
    }
}
static void move_up(void) {

    for (int i = 0; i <= 2; i++) {
        ctri.cpoint[i].y -= 1;
        tri.point[i].x = (ctri.cpoint[i].x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        tri.point[i].y = (ctri.cpoint[i].y - (wa.height / VERTICAL)) / (wa.width / ZOOM);
    }
}
static void move_down(void) {

    for (int i = 0; i <= 2; i++) {
        ctri.cpoint[i].y += 1;
        tri.point[i].x = (ctri.cpoint[i].x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM);
        tri.point[i].y = (ctri.cpoint[i].y - (wa.height / VERTICAL)) / (wa.width / ZOOM);
    }
}
static void move_forward(void) {
    
    for (int i = 0; i <= 2; i++) {
        tri.point[i].z += 0.005;
    }
    init_tri(&tri);
}
static void move_backward(void) {

    for (int i = 0; i <= 2; i++) {
        tri.point[i].z -= 0.005;
    }
    init_tri(&tri);
}
static const void keypress(XEvent *event) {

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
    printf("Pressed key: %lu.\n", keysym);
    printf("The Button that was pressed is %s.\n", buffer);
    switch (keysym) {

        case 119 : move_forward();
            break;
        case 115 : move_backward();
            break;
        case 65361 : move_left();
            break;
        case 65363 : move_right();
            break;
        case 65362 : move_up();
            break;
        case 65364 : move_down();
            break;
        case 65293 : ZOOM *= 0.10;
            break;
        default :
            return;
    }
    
    pixmapdisplay();
    nor_triangle(&tri);
    // paint_triangle(&ctri);

    // event->type = ButtonPress;
    // XSendEvent(displ, win, False, StructureNotifyMask, event);
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
static void paint_triangle(CTriangle *ctri) {

    XGCValues gcv;
    gcv.graphics_exposures = False;
    gcv.line_width = 3;
    gcv.foreground = 0xffffff;
    GC gc = XCreateGC(displ, win, GCGraphicsExposures | GCForeground | GCLineWidth, &gcv);

    XDrawLine(displ, win, gc, ctri->cpoint[2].x, ctri->cpoint[2].y, ctri->cpoint[1].x, ctri->cpoint[1].y);
    XDrawLine(displ, win, gc, ctri->cpoint[1].x, ctri->cpoint[1].y, ctri->cpoint[0].x, ctri->cpoint[0].y);
    XDrawLine(displ, win, gc, ctri->cpoint[0].x, ctri->cpoint[0].y, ctri->cpoint[2].x, ctri->cpoint[2].y);

    XFreeGC(displ, gc);
}
static void nor_triangle(Triangle *tri) {

    int x = 0, y = 0;
    for (int i = 0; i <= wa.width * wa.height; i++) {
        // printf("X %d ---> x : %f i : %d\n", x, (x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM), i);
        for (int v = 0; v <= sizeof(&tri->point) / sizeof(float); v++) {
            if (!compare_float(tri->point[v].x, (x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM), 1000) &&
                !compare_float(tri->point[v].y, (y - (wa.height / VERTICAL)) / (wa.width / ZOOM), 1000)) {

                ctri.cpoint[v].x = x;
                ctri.cpoint[v].y = y;
                printf("Vectors identified: %d\n", v);
            }
        }   
        x++;
        if (x == wa.width) {
            y++;
            x = 0;
        }
    }
    paint_triangle(&ctri);
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

