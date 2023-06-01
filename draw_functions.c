#include "header_files/draw_functions.h"
#include "header_files/exec_time.h"
#include "header_files/logging.h"

extern XWindowAttributes wa;
extern Pixel **pixels;
extern float **depth_buffer;
extern Phong model;

const Pixel antialliasing(const Pixel a, const Pixel b) {
    Pixel r = { 0 };
    r.Red = (a.Red + b.Red) * 0.5;
    r.Green = (a.Green + b.Green) * 0.5;
    r.Blue = (a.Blue + b.Blue) * 0.5;
    return r;
}

const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue) {
    Pixel pix = { blue, green, red }, s1, s2;
    Pixel test1 = { 255, 255, 255 };
    Pixel test2 = { 255, 0, 0 };
    float delta_y = y2 - y1;
    float delta_x = x2 - x1;

    float fabsdy = fabs(delta_y);
    float fabsdx = fabs(delta_x);

    int start_y = y1 + 0.5;
    int end_y = y2 + 0.5;
    int start_x = x1 + 0.5;
    int end_x = x2 + 0.5;

    int step_y, step_x;
    int step_cache = start_y;
    if ( (delta_x == 0) && (delta_y == 0) ) {
        memcpy(&pixels[start_y][start_x], &pix, sizeof(Pixel));
    } else if ( fabsdx >= fabsdy ) {
        float slope = delta_y / delta_x;

        if (delta_x < 0) {

            for (int x = start_x; x > end_x; x--) {
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[step_y][x], &pix, sizeof(Pixel));
                if ( step_cache != step_y) {
                    s1 = antialliasing(pixels[step_y][x], pixels[step_cache][x]);
                    s2 = antialliasing(pixels[step_y][x], pixels[step_y][x + 1]);
                    memcpy(&pixels[step_cache][x], &test1, sizeof(Pixel));
                    memcpy(&pixels[step_y][x + 1], &test2, sizeof(Pixel));
                }
                step_cache = step_y;
            }
        } else {
            int step_cache;
            for (int x = start_x; x < end_x; x++) {
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[step_y][x], &pix, sizeof(Pixel));
                step_cache = step_y;
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (int y = start_y; y > end_y; y--) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[y][step_x], &pix, sizeof(Pixel));
            }
        } else {

            for (int y = start_y; y < end_y; y++) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[y][step_x], &pix, sizeof(Pixel));
            }
        }
    } else {
        fprintf(stderr, "An Error has occured! draw_line().");
        exit(EXIT_FAILURE);
    }
}
const void fillTriangle(const Triangle t) {
    /* Creating 2Arrays for X and Y values to sort them. */
    float Ys[3] = { t.v[0].y, t.v[1].y, t.v[2].y };
    float Xs[3] = { t.v[0].x, t.v[1].x, t.v[2].x };
    /* Sorting the values from smaller to larger. Those values are the triangle bounding box. */
    float temp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (Ys[i] < Ys[j]) {

                temp = Ys[j];
                Ys[j] = Ys[i];
                Ys[i] = temp;
            }
            if (Xs[i] < Xs[j]) {

                temp = Xs[j];
                Xs[j] = Xs[i];
                Xs[i] = temp;
            }
        }

    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    fillGeneral(t, Xs[0] + 0.5, Xs[2] + 0.5, Ys[0] + 0.5, Ys[2] + 0.5);
}
const void fillGeneral(const Triangle t, int minX, int maxX, int minY, int maxY) {
    const int maxHeight = wa.height - 1;
    const int maxWidth = wa.width - 1;
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    const int x10 = x0 - x1,    x20 = x2 - x0,    x02 = x2 - x0,    x21 = x1 - x2;
    const int y10 = y0 - y1,    y20 = y2 - y0,    y02 = y2 - y0,    y21 = y1 - y2;

    const int tpA = ((y10 == 0) && (t.v[2].y > t.v[1].y)) || (y10 < 0) ? 1 : 0;
    const int tpB = ((y21 == 0) && (t.v[0].y > t.v[2].y)) || (y21 < 0) ? 1 : 0;
    const int tpC = ((y02 == 0) && (t.v[1].y > t.v[0].y)) || (y02 < 0) ? 1 : 0;

    minY = minY < 0 ? 0 : minY;
    maxY = maxY > maxHeight ? maxHeight : maxY;
    minX = minX < 0 ? 0 : minX;
    maxX = maxX > maxWidth ? maxWidth : maxX;

    const int area = ((x0 - x1) * y21) - ((y0 - y1) * x21);
    int ya = ((minX - x0) * y10) - ((minY - y0) * x10);
    int yb = ((minX - x1) * y21) - ((minY - y1) * x21);
    int yc = ((minX - x2) * y02) - ((minY - y2) * x02);

    for (int y = minY; y <= maxY; y++) {
        int xa = ya;
        int xb = yb;
        int xc = yc;
        int xflag = 0;
        for (int x = minX; x <= maxX; x++) {

            xa = ( (!xa) && (tpA) ) ? -1 : xa;
            xb = ( (!xb) && (tpB) ) ? -1 : xb;
            xc = ( (!xc) && (tpC) ) ? -1 : xc;

            if ( (xa | xb | xc) >= 0 ) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;

                const float depthZ = a * z2 + b * z0 + c * z1;
                const float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[y][x]) {
                    depth_buffer[y][x] = depthW;
                    model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                    model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                    model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                    phong(model, x, y, depthZ, depthW);
                    // pixels[y][x].Red = depthW * 10 * 255;
                    // pixels[y][x].Green = depthW * 10 * 255;
                    // pixels[y][x].Blue = depthW * 10 * 255;
                }
                xflag++;
            } else if (xflag) break;
            xa += y10,    xb += y21,    xc += y02;
        }
        ya += -x10,    yb += -x21,    yc += -x02;
    }
}
const void texTriangle(const Triangle t, Pixel **texture, const int tex_height, const int tex_width) {
    /* Creating 2Arrays for X and Y values to sort them. */
    float Ys[3] = { t.v[0].y, t.v[1].y, t.v[2].y };
    float Xs[3] = { t.v[0].x, t.v[1].x, t.v[2].x };
    /* Sorting the values from smaller to larger. Those values are the triangle bounding box. */
    float temp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (Ys[i] < Ys[j]) {

                temp = Ys[j];
                Ys[j] = Ys[i];
                Ys[i] = temp;
            }
            if (Xs[i] < Xs[j]) {

                temp = Xs[j];
                Xs[j] = Xs[i];
                Xs[i] = temp;
            }
        }

    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    texGeneral(t, texture, tex_height, tex_width, Xs[0] + 0.5, Xs[2] + 0.5, Ys[0] + 0.5, Ys[2] + 0.5);
}
const void texGeneral(const Triangle t, Pixel **texels, const int tex_height, const int tex_width, int minX, int maxX, int minY, int maxY) {
    Pixel pix = { 0 };
    const int maxHeight = wa.height - 1;
    const int maxWidth = wa.width - 1;
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    const int x10 = x0 - x1,    x20 = x2 - x0,    x02 = x2 - x0,    x21 = x1 - x2;
    const int y10 = y0 - y1,    y20 = y2 - y0,    y02 = y2 - y0,    y21 = y1 - y2;
    const float tu0 = t.vt[0].u,  tu1 = t.vt[1].u,  tu2 = t.vt[2].u;
    const float tv0 = t.vt[0].v,  tv1 = t.vt[1].v,  tv2 = t.vt[2].v;
    const float tw0 = t.vt[0].w,  tw1 = t.vt[1].w,  tw2 = t.vt[2].w;

    const int tpA = ((y10 == 0) && (t.v[2].y > t.v[1].y)) || (y10 < 0) ? 1 : 0;
    const int tpB = ((y21 == 0) && (t.v[0].y > t.v[2].y)) || (y21 < 0) ? 1 : 0;
    const int tpC = ((y02 == 0) && (t.v[1].y > t.v[0].y)) || (y02 < 0) ? 1 : 0;

    minY = minY < 0 ? 0 : minY;
    maxY = maxY > maxHeight ? maxHeight : maxY;
    minX = minX < 0 ? 0 : minX;
    maxX = maxX > maxWidth ? maxWidth : maxX;

    const float area = ((x0 - x1) * y21) - ((y0 - y1) * x21);
    int ya = ((minX - x0) * y10) - ((minY - y0) * x10);
    int yb = ((minX - x1) * y21) - ((minY - y1) * x21);
    int yc = ((minX - x2) * y02) - ((minY - y2) * x02);

    for (int y = minY; y <= maxY; y++) {
        int xa = ya;
        int xb = yb;
        int xc = yc;
        int xflag = 0;
        for (int x = minX; x <= maxX; x++) {

            xa = ( (!xa) && (tpA) ) ? -1 : xa;
            xb = ( (!xb) && (tpB) ) ? -1 : xb;
            xc = ( (!xc) && (tpC) ) ? -1 : xc;

            if ( (xa | xb | xc) >= 0 ) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;

                float depthZ = a * z2 + b * z0 + c * z1;
                float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[y][x]) {
                    depth_buffer[y][x] = depthW;

                    float tex_w = a * tw2 + b * tw0 + c * tw1;
                    int tex_u = ((a * tu2 + b * tu0 + c * tu1) * tex_width) / tex_w;
                    int tex_v = ((a * tv2 + b * tv0 + c * tv1) * tex_height) / tex_w;

                    model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                    model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                    model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                    memcpy(&model.objColor, &texels[tex_v][tex_u], sizeof(Pixel));
                    phong(model, x, y, depthZ, depthW);
                }
                xflag++;
            } else if (xflag) break;
            xa += y10,    xb += y21,    xc += y02;
        }
        ya += -x10,    yb += -x21,    yc += -x02;
    }
}

