#include "header_files/rasterizer.h"

/* Rasterize given Mesh by sorting the triangles by Y, then by X and finally, passing them to the appropriate functions according to their charakteristics. */
const static void rasterize(const SCMesh sc, char *image_data, Pixel *pixels) {

    int height_inc = 0;
    int width_inc = 0;

    /* Sorting Vectors from smaller to larger y. */
    SCVector temp;
    for (int m = 0; m <= sc.indexes; m++)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (sc.sct[m].scv[i].y <= sc.sct[m].scv[j].y) {
                    temp = sc.sct[m].scv[i];
                    sc.sct[m].scv[i] = sc.sct[m].scv[j];
                    sc.sct[m].scv[j] = temp;
                }

    if ( (t.v[0].y == t.v[1].y) && (t.v[1].y == t.v[2].y) )
        return;
    else if ( (t.v[1].y - t.v[2].y) == 0 )
        fillnorthway(t, &pixels);
    else if ( (t.v[0].y - t.v[1].y) == 0 )
        fillsouthway(t, &pixels);
    else
        fillgeneral(t, &pixels);

    for (int i = 0; i <  sizeof(image_data) / sizeof(char); i++) {
        image_data[i] = pixels[height_inc][width_inc].Blue;
        image_data[i + 1] = pixels[height_inc][width_inc].Green;
        image_data[i + 2] = pixels[height_inc][width_inc].Red;
        i += 3;
        width_inc++;

        if (width_inc == WIDTH) {
            height_inc += 1;
            width_inc = 0;
        }
    }

    XImage *image = XCreateImage(displ, wa.visual, wa.depth, ZPixmap, 0, image_data, wa.width, wa.height, 32, 0);
    XPutImage(displ, pixmap, gc, image, 0, 0, 0, 0, wa.width, wa.height);

    pixmapdisplay();
    XFree(image);
}
const static void fillnorthway(const Triangle t) {
    gcvalues.foreground = 0xff0000;
    XChangeGC(displ, gc, GCForeground, &gcvalues);
    float ma, mb;
    ma = (float)(t.v[1].x - t.v[0].x) / (float)(t.v[1].y - t.v[0].y);
    mb = (float)(t.v[2].x - t.v[0].x) / (float)(t.v[2].y - t.v[0].y);
    int y_start = t.v[0].y;
    int y_end = t.v[1].y;

    for (int y = y_start; y <= y_end; y++) {
        int x_start, x_end;
        float p0 = (ma * (y - t.v[0].y)) + t.v[0].x;
        float p1 = (mb * (y - t.v[0].y)) + t.v[0].x;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 + 0.5);
            x_end = (int)ceil(p1 + 0.5);
        } else {
            x_start = (int)ceil(p1 + 0.5);
            x_end = (int)ceil(p0 + 0.5);
        }
        for (int x = x_start; x < x_end; x++) {

            pixels[y][x].Red = 655;
            pixels[y][x].Green = 13265;
            pixels[y][x].Blue = 60000;
        }
    }
}
const static void fillsouthway(const Triangle t) {
    gcvalues.foreground = 0xffe800;
    XChangeGC(displ, gc, GCForeground, &gcvalues);
    float mb, mc;
    mb = (float)(t.v[2].x - t.v[0].x) / (float)(t.v[2].y - t.v[0].y);
    mc = (float)(t.v[2].x - t.v[1].x) / (float)(t.v[2].y - t.v[1].y);

    int y_start = t.v[1].y;
    int y_end = t.v[2].y;

    for (int y = y_start; y <= y_end; y++) {
        int x_start, x_end;
        float p0 = (mc * (y - t.v[1].y)) + t.v[1].x;
        float p1 = (mb * (y - t.v[0].y)) + t.v[0].x;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 + 0.5);
            x_end = (int)ceil(p1 + 0.5);
        } else {
            x_start = (int)ceil(p1 + 0.5);
            x_end = (int)ceil(p0 + 0.5);
        }
        for (int x = x_start; x < x_end; x++) {
            pixels[y][x].Red = 9;
            pixels[y][x].Green = 227;
            pixels[y][x].Blue = 224;
        }
    }
}
const static void fillgeneral(const Triangle t) {
    gcvalues.foreground = 0x005eff;
    XChangeGC(displ, gc, GCForeground, &gcvalues);
    float ma, mb, mc;
    ma = (float)(t.v[1].x - t.v[0].x) / (float)(t.v[1].y - t.v[0].y);
    mb = (float)(t.v[2].x - t.v[0].x) / (float)(t.v[2].y - t.v[0].y);
    mc = (float)(t.v[2].x - t.v[1].x) / (float)(t.v[2].y - t.v[1].y);

    int y_start = t.v[0].y;
    int y_end = t.v[1].y;

    for (int y = y_start; y <= y_end; y++) {
        int x_start, x_end;
        float p0 = (ma * (y - t.v[0].y)) + t.v[0].x;
        float p1 = (mb * (y - t.v[0].y)) + t.v[0].x;

        if (p0 <= p1) {
            x_start = (int)ceil(p0 + 0.5);
            x_end = (int)ceil(p1 + 0.5);
        } else {
            x_start = (int)ceil(p1 + 0.5);
            x_end = (int)ceil(p0 + 0.5);
        }
        for (int x = x_start; x < x_end; x++) {
            pixels[y][x].Red = 65;
            pixels[y][x].Green = 238;
            pixels[y][x].Blue = 3223;
        }
        if (y == y_end)
            for (int y = y_end + 1; y <= t.v[2].y; y++) {

                int x_start, x_end;
                float p0 = (mc * (y - t.v[1].y)) + t.v[1].x;
                float p1 = (mb * (y - t.v[0].y)) + t.v[0].x;

                if (p0 <= p1) {
                    x_start = (int)ceil(p0 + 0.5);
                    x_end = (int)ceil(p1 + 0.5);
                } else {
                    x_start = (int)ceil(p1 + 0.5);
                    x_end = (int)ceil(p0 + 0.5);
                }
                for (int x = x_start; x < x_end; x++) {
                    pixels[y][x].Red = 65;
                    pixels[y][x].Green = 238;
                    pixels[y][x].Blue = 3223;
                }
            }

    }
}

