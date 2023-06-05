#include "header_files/draw_functions.h"
#include "header_files/exec_time.h"
#include "header_files/logging.h"
#include "immintrin.h"

extern XWindowAttributes wa;
extern Pixel **pixels;
extern float **depth_buffer;
extern Phong model;

typedef int i32x4 __attribute__((vector_size(16)));
typedef union {
    __m128i mm;
    i32x4 i32;
} v128i;
typedef float f32x4 __attribute__((vector_size(16)));
typedef union {
    __m128 mm;
    f32x4 f32;
} v128f;
// __mmask32

// #include <pthread.h>
// extern pthread_mutex_t mutexQueue;
// extern pthread_cond_t condQueue;
// extern Task TaskQueue[256];
// extern int TASKCOUNT;
// extern void submitTask(Task task);

const int checkQuad(int xa, int xb, int xc, int *y10, int *y21, int *y02) {
    v128i edge1, edge2, edge3, edge4, step_y, or1, or2, or3, allout;
    step_y.mm = _mm_setr_epi32(*y10, *y21, *y02, 0);
    edge1.mm = _mm_setr_epi32(xa, xb, xc, 0);
    edge2.mm = _mm_add_epi32(edge1.mm, step_y.mm);
    edge3.mm = _mm_add_epi32(edge2.mm, step_y.mm);
    edge4.mm = _mm_add_epi32(edge3.mm, step_y.mm);

    // or1.mm = _mm_or_si128(edge1.mm, edge2.mm);
    // or2.mm = _mm_or_si128(edge3.mm, edge4.mm);
    // or3.mm = _mm_or_si128(or1.mm, or2.mm);

    int mask1 = (edge1.i32[0] | edge1.i32[1] | edge1.i32[2]) < 0 ? -1 : 1;
    int mask2 = (edge2.i32[0] | edge2.i32[1] | edge2.i32[2]) < 0 ? -1 : 1;
    int mask3 = (edge3.i32[0] | edge3.i32[1] | edge3.i32[2]) < 0 ? -1 : 1;
    int mask4 = (edge4.i32[0] | edge4.i32[1] | edge4.i32[2]) < 0 ? -1 : 1;

    if ( (mask1 | mask2 | mask3 | mask4) >= 0 )
        return 1;
    else if ( mask1 < 0 && mask2 < 0 && mask3 < 0 && mask4 < 0 )
        return -1;
    else
        return 1;
}

const int DrawQuad(int xa, int xb, int xc, int *y10, int *y21, int *y02, float area, float z0, float z1, float z2, float w0, float w1, float w2, int x, int y, int modulo) {
    v128f edge1, edge2, edge3, edge4, step_y, ar, zdepth, wdepth, az1, az2, az3, az4, aw1, aw2, aw3, aw4;
    ar.mm = _mm_set1_ps(area);
    step_y.mm = _mm_setr_ps((float)*y10, (float)*y21, (float)*y02, 0);
    edge1.mm = _mm_setr_ps((float)xa, (float)xb, (float)xc, 0.0);
    edge2.mm = _mm_add_ps(edge1.mm, step_y.mm);
    edge3.mm = _mm_add_ps(edge2.mm, step_y.mm);
    edge4.mm = _mm_add_ps(edge3.mm, step_y.mm);

    edge1.mm = _mm_div_ps(edge1.mm, ar.mm);
    edge2.mm = _mm_div_ps(edge2.mm, ar.mm);
    edge3.mm = _mm_div_ps(edge3.mm, ar.mm);
    edge4.mm = _mm_div_ps(edge4.mm, ar.mm);

    // xa = ( (!xa) && (tpA) ) ? -1 : xa;
    // xb = ( (!xb) && (tpB) ) ? -1 : xb;
    // xc = ( (!xc) && (tpC) ) ? -1 : xc;

    // const float a = (float)xa / area;
    // const float b = (float)xb / area;
    // const float c = (float)xc / area;

    zdepth.mm = _mm_setr_ps(z2, z0, z1, 0.0);
    wdepth.mm = _mm_setr_ps(w2, w0, w1, 0.0);

    az1.mm = _mm_mul_ps(edge1.mm, zdepth.mm);
    az2.mm = _mm_mul_ps(edge2.mm, zdepth.mm);
    az3.mm = _mm_mul_ps(edge3.mm, zdepth.mm);
    az4.mm = _mm_mul_ps(edge4.mm, zdepth.mm);

    aw1.mm = _mm_mul_ps(edge1.mm, wdepth.mm);
    aw2.mm = _mm_mul_ps(edge2.mm, wdepth.mm);
    aw3.mm = _mm_mul_ps(edge3.mm, wdepth.mm);
    aw4.mm = _mm_mul_ps(edge4.mm, wdepth.mm);

    const float depthZ1 = az1.f32[0] + az1.f32[1] + az1.f32[2];
    const float depthZ2 = az2.f32[0] + az2.f32[1] + az2.f32[2];
    const float depthZ3 = az3.f32[0] + az3.f32[1] + az3.f32[2];
    const float depthZ4 = az4.f32[0] + az4.f32[1] + az4.f32[2];

    const float depthW1 = aw1.f32[0] + aw1.f32[1] + aw1.f32[2];
    const float depthW2 = aw2.f32[0] + aw2.f32[1] + aw2.f32[2];
    const float depthW3 = aw3.f32[0] + aw3.f32[1] + aw3.f32[2];
    const float depthW4 = aw4.f32[0] + aw4.f32[1] + aw4.f32[2];

    // const float depthZ = a * z2 + b * z0 + c * z1;
    // const float depthW = a * w2 + b * w0 + c * w1;

    depth_buffer[y][x] = depthW1 > depth_buffer[y][x] ? phong(model, x, y, depthZ1, depthW1) : depth_buffer[y][x];
    depth_buffer[y][x + 1] = depthW2 > depth_buffer[y][x + 1] ? phong(model, x + 1, y, depthZ2, depthW2) : depth_buffer[y][x + 1];
    depth_buffer[y][x + 2] = depthW3 > depth_buffer[y][x + 2] ? phong(model, x + 2, y, depthZ3, depthW3) : depth_buffer[y][x + 2];
    depth_buffer[y][x + 3] = depthW4 > depth_buffer[y][x + 3] ? phong(model, x + 3, y, depthZ4, depthW4) : depth_buffer[y][x + 3];

    // if (depthW > depth_buffer[y][x]) {
    //     depth_buffer[y][x] = depthW;
    // }
    // *y10 << 2, *y21 << 2, *y02 << 2;
}

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
    int x10 = x0 - x1,    x20 = x2 - x0,    x02 = x2 - x0,    x21 = x1 - x2;
    int y10 = y0 - y1,    y20 = y2 - y0,    y02 = y2 - y0,    y21 = y1 - y2;

    const int tpA = ((y10 == 0) && (t.v[2].y > t.v[1].y)) || (y10 < 0) ? 1 : 0;
    const int tpB = ((y21 == 0) && (t.v[0].y > t.v[2].y)) || (y21 < 0) ? 1 : 0;
    const int tpC = ((y02 == 0) && (t.v[1].y > t.v[0].y)) || (y02 < 0) ? 1 : 0;

    // minY = minY < 0 ? 0 : minY;
    // maxY = maxY > maxHeight ? maxHeight : maxY;
    // minX = minX < 0 ? 0 : minX;
    // maxX = maxX > maxWidth ? maxWidth : maxX;

    const int area = ((x0 - x1) * y21) - ((y0 - y1) * x21);
    int ya = ((minX - x0) * y10) - ((minY - y0) * x10);
    int yb = ((minX - x1) * y21) - ((minY - y1) * x21);
    int yc = ((minX - x2) * y02) - ((minY - y2) * x02);

    const int modulo = maxX % 4;
    const int limit = maxX - modulo;
    for (int y = minY; y <= maxY; y++) {
        int xa = ya;
        int xb = yb;
        int xc = yc;
        int xflag = 0;
        for (int x = minX; x <= maxX; x += 4) {

            if (checkQuad(xa, xb, xc, &y10, &y21, &y02) > 0) {
                DrawQuad(xa, xb, xc, &y10, &y21, &y02, area, z0, z1, z2, w0, w1, w2, x, y, modulo);
                // x += 4;
                // xa += y10 << 2,    xb += y21 << 2,    xc += y02 << 2;
                // break;
            }

            // xa = ( (!xa) && (tpA) ) ? -1 : xa;
            // xb = ( (!xb) && (tpB) ) ? -1 : xb;
            // xc = ( (!xc) && (tpC) ) ? -1 : xc;
            
            

            // if ( (xa | xb | xc) > 0 ) {
            //     const float a = (float)xa / area;
            //     const float b = (float)xb / area;
            //     const float c = (float)xc / area;

            //     const float depthZ = a * z2 + b * z0 + c * z1;
            //     const float depthW = a * w2 + b * w0 + c * w1;

            //     if (depthW > depth_buffer[y][x]) {
            //         depth_buffer[y][x] = depthW;
            //         model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
            //         model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
            //         model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

            //         // Task task = {
            //         //     .taskFunction = &phong,
            //         //     .model = model,
            //         //     .arg1 = x,
            //         //     .arg2 = y,
            //         //     .arg3 = depthZ,
            //         //     .arg4 = depthW
            //         // };
            //         // submitTask(task);

            //         phong(model, x, y, depthZ, depthW);
            //         // pixels[y][x].Red = depthW * 10 * 255;
            //         // pixels[y][x].Green = depthW * 10 * 255;
            //         // pixels[y][x].Blue = depthW * 10 * 255;
            //     } else if (depthW == depth_buffer[y][x]) {
            //         pixels[y][x].Red = 255;
            //         pixels[y][x].Green = 0;
            //         pixels[y][x].Blue = 0;
            //         depth_buffer[y][x] = depthW;
            //     }
            //     xflag++;
            // } else if (xflag) break;
            // xa += y10,    xb += y21,    xc += y02;
            xa += y10 << 2,    xb += y21 << 2,    xc += y02 << 2;
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

            if ( (xa | xb | xc) > 0 ) {
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

