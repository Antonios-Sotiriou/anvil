#include "header_files/scanline.h"

extern Pixel **pixels;
extern float **depth_buffer;
extern float **shadow_buffer;
extern Phong model;

const void fillTriangle(Triangle t) {
    /* Creating a struct to be able to sort vertices without affecting their order. */
    struct Srt srt[3] = {
        { .y =  t.v[0].y, .index = 0},
        { .y =  t.v[1].y, .index = 1},
        { .y =  t.v[2].y, .index = 2}
    };

    /* Sorting the values from smaller to larger y. */
    struct Srt temp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (srt[i].y < srt[j].y) {
                temp = srt[j];
                srt[j] = srt[i];
                srt[i] = temp;
            }

    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    fillGeneral(t, srt);
}
const static void fillGeneral(const Triangle t, const struct Srt srt[]) {
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const int x01 = x0 - x1,    x12 = x1 - x2,    x20 = x2 - x0;
    const int y01 = y0 - y1,    y12 = y1 - y2,    y20 = y2 - y0;

    const int tx0 = t.v[srt[0].index].x + 0.5,    tx1 = t.v[srt[1].index].x + 0.5,    tx2 = t.v[srt[2].index].x + 0.5;
    const int ty0 = t.v[srt[0].index].y + 0.5,    ty1 = t.v[srt[1].index].y + 0.5,    ty2 = t.v[srt[2].index].y + 0.5;
    const int tx10 = tx1 - tx0,    tx21 = tx2 - tx1,    tx02 = tx0 - tx2;
    const int ty10 = ty1 - ty0,    ty21 = ty2 - ty1,    ty02 = ty0 - ty2;

    const int tpA = ((y01 == 0) && (t.v[2].y < t.v[1].y)) || (y01 < 0) ? 1 : 0;
    const int tpB = ((y12 == 0) && (t.v[0].y < t.v[2].y)) || (y12 < 0) ? 1 : 0;
    const int tpC = ((y20 == 0) && (t.v[1].y < t.v[0].y)) || (y20 < 0) ? 1 : 0;

    const int orient = (tx10 * ty02) - (ty10 * tx02);
    float ma = (float)tx10 / ty10;
    float mb = (float)tx02 / ty02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    const int y_start = ty0;
    const int y_end1 = ty1;
    const int y_end2 = ty2;

    const int area = (x01 * y12) - (y01 * x12);
    int ya = -(y_start - y0) * x01;
    int yb = -(y_start - y1) * x12;
    int yc = -(y_start - y2) * x20;

    int yA = 0;
    if (ty10 != 0)
        for (int y = y_start; y < y_end1; y++) {

            int x_start = (ma * yA) + tx0;
            int x_end = (mb * yA) + tx0;

            int xa = ((x_start - x0) * y01) + ya;
            int xb = ((x_start - x1) * y12) + yb;
            int xc = ((x_start - x2) * y20) + yc;

            for (int x = x_start; x <= x_end; x++) {

                xa = ( (!xa) && (tpA) ) ? -1 : xa;
                xb = ( (!xb) && (tpB) ) ? -1 : xb;
                xc = ( (!xc) && (tpC) ) ? -1 : xc;
                if ( (xa | xb | xc) > 0 ) {
                    const float a = (float)xa / area;
                    const float b = (float)xb / area;
                    const float c = (float)xc / area;

                    const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
                    const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

                    if ( depthW > depth_buffer[y][x] ) {

                        model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                        model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                        model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                        depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                    } else if (depthW == depth_buffer[y][x]) {
                        pixels[y][x].Red = 255;
                        pixels[y][x].Green = 0;
                        pixels[y][x].Blue = 0;
                        depth_buffer[y][x] = depthW;
                    }
                }
                xa += y01, xb += y12, xc += y20;
            }
            ya += -x01, yb += -x12, yc += -x20;
            yA++;
        }

    if (ty21 == 0)
        return;

    ma = (float)tx21 / ty21;
    mb = (float)tx02 / ty02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    int yB = -ty21;
    for (int y = y_end1; y < y_end2; y++) {

        int x_start = (ma * yB) + tx2;
        int x_end = (mb * yB) + tx2;

        int xa = ((x_start - x0) * y01) + ya;
        int xb = ((x_start - x1) * y12) + yb;
        int xc = ((x_start - x2) * y20) + yc;

        for (int x = x_start; x <= x_end; x++) {

            xa = ( (!xa) && (tpA) ) ? -1 : xa;
            xb = ( (!xb) && (tpB) ) ? -1 : xb;
            xc = ( (!xc) && (tpC) ) ? -1 : xc;
            if ( (xa | xb | xc) > 0 ) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;

                const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
                const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

                if ( depthW > depth_buffer[y][x] ) {

                    model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                    model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                    model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                    depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                } else if (depthW == depth_buffer[y][x]) {
                    pixels[y][x].Red = 255;
                    pixels[y][x].Green = 0;
                    pixels[y][x].Blue = 0;
                    depth_buffer[y][x] = depthW;
                }
            }
            xa += y01, xb += y12, xc += y20;
        }
        ya += -x01, yb += -x12, yc += -x20;
        yB++;
    }
}
const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width) {
    /* Creating a struct to be able to sort vertices without affecting their order. */
    struct Srt srt[3] = {
        { .y =  t.v[0].y, .index = 0},
        { .y =  t.v[1].y, .index = 1},
        { .y =  t.v[2].y, .index = 2}
    };

    /* Sorting the values from smaller to larger y. */
    struct Srt temp;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (srt[i].y < srt[j].y) {
                temp = srt[j];
                srt[j] = srt[i];
                srt[i] = temp;
            }

    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    texGeneral(t, srt, texels, tex_height, tex_width);
}
const static void texGeneral(const Triangle t, const struct Srt srt[], Pixel **texels, const int tex_height, const int tex_width) {
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const int x01 = x0 - x1,    x12 = x1 - x2,    x20 = x2 - x0;
    const int y01 = y0 - y1,    y12 = y1 - y2,    y20 = y2 - y0;

    const int tx0 = t.v[srt[0].index].x + 0.5,    tx1 = t.v[srt[1].index].x + 0.5,    tx2 = t.v[srt[2].index].x + 0.5;
    const int ty0 = t.v[srt[0].index].y + 0.5,    ty1 = t.v[srt[1].index].y + 0.5,    ty2 = t.v[srt[2].index].y + 0.5;
    const int tx10 = tx1 - tx0,    tx21 = tx2 - tx1,    tx02 = tx0 - tx2;
    const int ty10 = ty1 - ty0,    ty21 = ty2 - ty1,    ty02 = ty0 - ty2;

    const int tpA = ((y01 == 0) && (t.v[2].y < t.v[1].y)) || (y01 < 0) ? 1 : 0;
    const int tpB = ((y12 == 0) && (t.v[0].y < t.v[2].y)) || (y12 < 0) ? 1 : 0;
    const int tpC = ((y20 == 0) && (t.v[1].y < t.v[0].y)) || (y20 < 0) ? 1 : 0;

    const int orient = (tx10 * ty02) - (ty10 * tx02);
    float ma = (float)tx10 / ty10;
    float mb = (float)tx02 / ty02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    const int y_start = ty0;
    const int y_end1 = ty1;
    const int y_end2 = ty2;

    const int area = (x01 * y12) - (y01 * x12);
    int ya = -(y_start - y0) * x01;
    int yb = -(y_start - y1) * x12;
    int yc = -(y_start - y2) * x20;

    int yA = 0;
    if (ty10 != 0)
        for (int y = y_start; y < y_end1; y++) {

            int x_start = (ma * yA) + tx0;
            int x_end = (mb * yA) + tx0;

            int xa = ((x_start - x0) * y01) + ya;
            int xb = ((x_start - x1) * y12) + yb;
            int xc = ((x_start - x2) * y20) + yc;

            for (int x = x_start; x <= x_end; x++) {

                xa = ( (!xa) && (tpA) ) ? -1 : xa;
                xb = ( (!xb) && (tpB) ) ? -1 : xb;
                xc = ( (!xc) && (tpC) ) ? -1 : xc;
                if ( (xa | xb | xc) > 0 ) {
                    const float a = (float)xa / area;
                    const float b = (float)xb / area;
                    const float c = (float)xc / area;

                    const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
                    const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

                    if ( depthW > depth_buffer[y][x] ) {

                        const float tex_w = a * t.vt[2].w + b * t.vt[0].w + c * t.vt[1].w;
                        const int tex_u = ((a * t.vt[2].u + b * t.vt[0].u + c * t.vt[1].u) / tex_w) * tex_width;
                        const int tex_v = ((a * t.vt[2].v + b * t.vt[0].v + c * t.vt[1].v) / tex_w) * tex_height;

                        model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                        model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                        model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                        memcpy(&model.objColor, &texels[tex_v][tex_u], sizeof(Pixel));
                        depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                    }
                }
                xa += y01, xb += y12, xc += y20;
            }
            ya += -x01, yb += -x12, yc += -x20;
            yA++;
        }

    if (ty21 == 0)
        return;

    ma = (float)tx21 / ty21;
    mb = (float)tx02 / ty02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    int yB = -ty21;
    for (int y = y_end1; y < y_end2; y++) {

        int x_start = (ma * yB) + tx2;
        int x_end = (mb * yB) + tx2;

        int xa = ((x_start - x0) * y01) + ya;
        int xb = ((x_start - x1) * y12) + yb;
        int xc = ((x_start - x2) * y20) + yc;

        for (int x = x_start; x <= x_end; x++) {

            xa = ( (!xa) && (tpA) ) ? -1 : xa;
            xb = ( (!xb) && (tpB) ) ? -1 : xb;
            xc = ( (!xc) && (tpC) ) ? -1 : xc;
            if ( (xa | xb | xc) > 0 ) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;

                const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
                const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

                if ( depthW > depth_buffer[y][x] ) {

                    const float tex_w = a * t.vt[2].w + b * t.vt[0].w + c * t.vt[1].w;
                    const int tex_u = ((a * t.vt[2].u + b * t.vt[0].u + c * t.vt[1].u) / tex_w) * tex_width;
                    const int tex_v = ((a * t.vt[2].v + b * t.vt[0].v + c * t.vt[1].v) / tex_w) * tex_height;

                    model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                    model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                    model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                    memcpy(&model.objColor, &texels[tex_v][tex_u], sizeof(Pixel));
                    depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                }
            }
            xa += y01, xb += y12, xc += y20;
        }
        ya += -x01, yb += -x12, yc += -x20;
        yB++;
    }
}


