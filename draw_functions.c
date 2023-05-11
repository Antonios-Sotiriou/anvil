#include "header_files/draw_functions.h"
#include "header_files/exec_time.h"

extern Pixel **pixels;
extern float **depth_buffer;
extern float **shadow_buffer;
extern Phong model;

const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue) {
    Pixel pix = { blue, green, red };
    float delta_y = y2 - y1;
    float delta_x = x2 - x1;

    float fabsdy = fabs(delta_y);
    float fabsdx = fabs(delta_x);

    float start_y = ceilf(y1 - 0.5);
    float end_y = ceilf(y2 - 0.5);
    float start_x = ceilf(x1 - 0.5);
    float end_x = ceilf(x2 - 0.5);

    float step_y, step_x;

    if ( (delta_x == 0) && (delta_y == 0) ) {
        memcpy(&pixels[(int)start_y][(int)start_x], &pix, sizeof(Pixel));
    } else if ( fabsdx >= fabsdy ) {
        float slope = delta_y / delta_x;

        if (delta_x < 0) {

            for (float x = start_x; x > end_x; x -= 1.0) {
                step_y = ceilf(((slope * (x - start_x)) + y1) - 0.5);
                memcpy(&pixels[(int)step_y][(int)x], &pix, sizeof(Pixel));
            }
        } else {

            for (float x = start_x; x < end_x; x += 1.0) {
                step_y = ceilf(((slope * (x - start_x)) + y1) - 0.5);
                memcpy(&pixels[(int)step_y][(int)x], &pix, sizeof(Pixel));
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (float y = start_y; y > end_y; y -= 1.0) {
                step_x = ceilf(((slope * (y - start_y)) + x1) - 0.5);
                memcpy(&pixels[(int)y][(int)step_x], &pix, sizeof(Pixel));
            }
        } else {

            for (float y = start_y; y < end_y; y += 1.0) {
                step_x = ceilf(((slope * (y - start_y)) + x1) - 0.5);
                memcpy(&pixels[(int)y][(int)step_x], &pix, sizeof(Pixel));
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

    fillGeneral(t, roundf(Xs[0]), roundf(Xs[2]), roundf(Ys[0]), roundf(Ys[2]));
}
const float edjeFunction(Vector p, Vector a, Vector b) {
    return ( (p.x - a.x) * (b.y - a.y)) - ((p.y - a.y) * (b.x - a.x) );
}
const void fillGeneral(Triangle t, float minX, float maxX, float minY, float maxY) {
    Pixel pix = t.color;
    model.normal = t.normal;
    model.objColor = t.color;
    Vector R = { 1, 0, 0 };
    Vector G = { 0, 1, 0 };
    Vector B = { 0, 0, 1 };

    const float x10 = t.v[1].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x,    x02 = t.v[0].x - t.v[2].x;
    const float y10 = t.v[1].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y,    y02 = t.v[0].y - t.v[2].y;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;

    const float start_y = minY + 0.4, start_x = minX + 0.4;

    const float area = ((t.v[0].x - t.v[1].x) * y21) - ((t.v[0].y - t.v[1].y) * x21);
    float ya = ((start_x - t.v[0].x) * y10) - ((start_y - t.v[0].y) * x10);
    float yb = ((start_x - t.v[1].x) * y21) - ((start_y - t.v[1].y) * x21);
    float yc = ((start_x - t.v[2].x) * y02) - ((start_y - t.v[2].y) * x02);

    for (int y = minY; y <= maxY; y++) {
        float xa = ya;
        float xb = yb;
        float xc = yc;

        for (int x = minX; x <= maxX; x++) {

            // if ( ((y10 == 0) && (t.v[2].y > t.v[1].y)) || (y10 < 0) )
            //     if (xa >= 0 && xa <= 500)
                //    if (xa == 0)
            //         // xa = 1;
            //         // drawLine(x, y, x, y, 255, 0, 0);
            // if ( ((y21 == 0) && (t.v[0].y > t.v[2].y)) || (y21 < 0) )
            //     if (xb >= 0 && xb <= 500)
                //    if (xb == 0)
            //         // xb = 1;
            //         // drawLine(x, y, x, y, 255, 0, 0);
            // if ( ((y02 == 0) && (t.v[1].y > t.v[0].y)) || (y02 < 0) )
            //     if (xc >= 0 && xc <= 500)
                //    if (xc == 0)
            //         // xc = 1;
            //         // drawLine(x, y, x, y, 255, 0, 0);

            if ( xa <= 0 && xb <= 0 && xc <= 0 ) {
                const float a = xa / area;
                const float b = xb / area;
                const float c = xc / area;

                const float depthZ = a * z2 + b * z0 + c * z1;
                const float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[y][x]) {

                    // Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    // if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                    //     pix = phong(model, x, y, depthZ, depthW, 0.0);
                    // } else {
                    //     pix = phong(model, x, y, depthZ, depthW, 1.0);
                    // }

                    // float r = a * R.x + b * G.x + c * B.x;
                    // float g = a * R.y + b * G.y + c * B.y;
                    // float b = a * R.z + b * G.z + c * B.z;
                    // pixels[y][x].Red = r * 255;
                    // pixels[y][x].Green = g * 255;
                    // pixels[y][x].Blue = b * 255;
                    pixels[y][x].Red = depthW * 10 * 255;
                    pixels[y][x].Green = depthW * 10 * 255;
                    pixels[y][x].Blue = depthW * 10 * 255;

                    // memcpy(&pixels[y][x], &pix, sizeof(Pixel));
                    depth_buffer[y][x] = depthW;
                } else if (depthW == depth_buffer[y][x]) {
                    pixels[y][x].Red = 255;
                    pixels[y][x].Green = 0;
                    pixels[y][x].Blue = 0;
                    depth_buffer[y][x] = depthW;
                }
            } 
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

    texGeneral(t, texture, tex_height, tex_width, roundf(Xs[0]), roundf(Xs[2]), roundf(Ys[0]), roundf(Ys[2]));
}
const void texGeneral(const Triangle t, Pixel **texels, const int tex_height, const int tex_width, const float minX, const float maxX, const float minY, const float maxY) {
    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x,    x02 = t.v[0].x - t.v[2].x;
    const float y10 = t.v[1].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y,    y02 = t.v[0].y - t.v[2].y;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    const float tu0 = t.tex[0].u,  tu1 = t.tex[1].u,  tu2 = t.tex[2].u;
    const float tv0 = t.tex[0].v,  tv1 = t.tex[1].v,  tv2 = t.tex[2].v;
    const float tw0 = t.tex[0].w,  tw1 = t.tex[1].w,  tw2 = t.tex[2].w;

    const float area = ((t.v[0].x - t.v[1].x) * y21) - ((t.v[0].y - t.v[1].y) * x21);
    float ya = ((minX + 0.5 - t.v[0].x) * y10) - ((minY + 0.5 - t.v[0].y) * x10);
    float yb = ((minX + 0.5 - t.v[1].x) * y21) - ((minY + 0.5 - t.v[1].y) * x21);
    float yc = ((minX + 0.5 - t.v[2].x) * y02) - ((minY + 0.5 - t.v[2].y) * x02);

    for (int y = minY; y <= maxY; y++) {
        float xa = ya;
        float xb = yb;
        float xc = yc;

        for (int x = minX; x <= maxX; x++) {

            if ( xa <= 0 && xb <= 0 && xc <= 0 ) {
                const float a = xa / area;
                const float b = xb / area;
                const float c = xc / area;

                float tex_w = a * tw2 + b * tw0 + c * tw1;
                int tex_u = ((a * tu2 + b * tu0 + c * tu1) * tex_width) / tex_w;
                int tex_v = ((a * tv2 + b * tv0 + c * tv1) * tex_height) / tex_w;

                float depthZ = a * z2 + b * z0 + c * z1;
                float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[y][x]) {

                    memcpy(&model.objColor, &texels[tex_v][tex_u], sizeof(Pixel));
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z < (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }

                    memcpy(&pixels[y][x], &pix, sizeof(Pixel));
                    depth_buffer[y][x] = depthW;
                }
            }
            xa += y10,    xb += y21,    xc += y02;
        }
        ya += -x10,    yb += -x21,    yc += -x02;
    }
}

