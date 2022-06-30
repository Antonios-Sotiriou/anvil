// general headers
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

// Project specific headers
#include "header_files/locale.h"
typedef struct {
    float x, y;
} Point;

typedef struct {
    Point point[3];
} Element;

typedef struct {
    Element el[2];
} Block;

typedef struct {
    Block block[6];
} Cube;

enum { Win_Close, Win_Name, Atom_Type, Atom_Last};
enum { UnderEl, UperEl, LastEl};
enum { FrontBlock, BackBlock, WestBlock, EastBlock, NorthBlock, SouthBlock, LastBlock};

#define WIDTH                     800
#define HEIGHT                    800
#define HORIZONTAL                2.00
#define VERTICAL                  2.00
#define ZOOM                      4.00
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
// Element el;
Point el;

static int MAPCOUNT = 0;
static int RUNNING = 1;

// initialize the knot object to be transfered because we can't transfer pointers to pointers through shared memory.
static const void clientmessage(XEvent *event);
static const void reparentnotify(XEvent *event);
static const void mapnotify(XEvent *event);
static const void expose(XEvent *event);
static const void resizerequest(XEvent *event);
static const void configurenotify(XEvent *event);
static const void buttonpress(XEvent *event);
static const void keypress(XEvent *event);
static const void paint_triangle(Element tri);
// static const void pixmapupdate(void);
// static const void pixmapdisplay(void);
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

        // XFreePixmap(displ, pixmap);
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
        // pixmapdisplay();
    } else {
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
}
static const void resizerequest(XEvent *event) {

    printf("resizerequest event received\n");
}
static const void configurenotify(XEvent *event) {

    printf("configurenotify event received\n");
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

    printf("X : %f --------- Y : %f\n", el.x, el.y);

    Element tri;
    tri.point[0].x = 0.0;
    tri.point[0].y = -1.0;
    tri.point[1].x = 1.0;
    tri.point[1].y = 0.0;
    tri.point[2].x = -1.0;
    tri.point[2].y = 0.0;

    paint_triangle(tri);


    // if (event->xkey.keycode == 1) {
    //     el.zoom *= 0.50;
    // } else if (event->xkey.keycode == 3) {
    //     el.zoom /= 0.50;
    // }
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

    int count = 0;
    KeySym keysym = 0;
    char buffer[32];
    Status status = 0;
    count = Xutf8LookupString(xic, &event->xkey, buffer, 32, &keysym, &status);
    printf("Button pressed.\n");
    printf("Count %d.\n", count);
    if (status == XBufferOverflow) {
        printf("Buffer Overflow...\n");
    }
    if (count) {
        printf("The Button that was pressed is %s.\n", buffer);
    }
    if (status == XLookupKeySym || status == XLookupBoth) {
        printf("Status: %d\n", status);
    }
    printf("Pressed key: %lu.\n", keysym);
    // if (keysym == 65361) {
    //     obj.horiz += 0.01;
    // } else if (keysym == 65363) {
    //     obj.horiz -= 0.01;
    // } else if (keysym == 65362) {
    //     obj.vert += 0.01;
    // } else if (keysym == 65364) {
    //     obj.vert -= 0.01;
    // } else if (keysym == 65293) {
    //     obj.zoom *= 0.50;
    // } else {
    //     return;
    // }
}
// static const void pixmapupdate(void) {

//     XGCValues gc_vals;
//     gc_vals.graphics_exposures = False;
//     GC pix = XCreateGC(displ, app, GCGraphicsExposures, &gc_vals);

//     pixmap = XCreatePixmap(displ, app, stat_app.width, stat_app.height, stat_app.depth);
//     XCopyArea(displ, app, pixmap, pix, 0, 0, stat_app.width, stat_app.height, 0, 0);
//     XFreeGC(displ, pix);
// }
// static const void pixmapdisplay(void) {

//     XGCValues gc_vals;
//     gc_vals.graphics_exposures = False;
//     GC pix = XCreateGC(displ, app, GCGraphicsExposures, &gc_vals);

//     XCopyArea(displ, pixmap, app, pix, 0, 0, stat_app.width, stat_app.height, 0, 0);
//     XFreeGC(displ, pix);
// }
static const void paint_triangle(Element tri) {

    XGCValues gcv;
    gcv.graphics_exposures = False;
    gcv.foreground = 0xffffff;
    GC gc = XCreateGC(displ, win, GCGraphicsExposures | GCForeground, &gcv);

    int x = 0, y = 0;
    for (int i = 0; i <= wa.width * wa.height; i++) {
        if ((x - (wa.width / HORIZONTAL)) / (wa.width / ZOOM) == tri.point[0].x) {
            printf("Found x coordinate\n");
            if ((y - (wa.height / VERTICAL)) / (wa.height / ZOOM) == tri.point[0].y)
                XDrawLine(displ, win, gc, x, y, wa.width, wa.height);
        }
        if (x == wa.width) {
            y++;
            x = 0;
        }
        x++;
    }
    printf("Value of X: %d --- Value of Y: %d\n", x, y);
    XFreeGC(displ, gc);
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

