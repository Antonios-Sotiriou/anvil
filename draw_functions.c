#include "header_files/draw_functions.h"
#include "header_files/exec_time.h"

const void drawLine(Pixel **pixels, float x1, float y1, float x2, float y2, const float red, const float green, const float blue) {
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
#include "header_files/draw_functions.h"

const void fillTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle t, Phong model) {
    /* Creating 2Arrays for X and Y values to sort them. */
    float Ys[3] = { ceilf(t.v[0].y), ceilf(t.v[1].y), ceilf(t.v[2].y) };
    float Xs[3] = { ceilf(t.v[0].x), ceilf(t.v[1].x), ceilf(t.v[2].x) };
    /* Sorting the values from smaller to larger. Those values are the triangle bounding box. */
    int temp;
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

    fillGeneral(pixels, depth_buffer, shadow_buffer, t, model, Xs[0], Xs[2], Ys[0], Ys[2]);
}
const float edjeFunction(Vector p, Vector a, Vector b) {
    return ( (p.x - a.x) * (b.y - a.y)) - ((p.y - a.y) * (b.x - a.x) );
}
const void fillGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle t, Phong model, const float minX, const float maxX, const float minY, const float maxY) {
    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x,    x02 = t.v[0].x - t.v[2].x;
    const float y10 = t.v[1].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y,    y02 = t.v[0].y - t.v[2].y;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    // Vector R = { 1, 0, 0 };
    // Vector G = { 0, 1, 0 };
    // Vector B = { 0, 0, 1 };

    const float area = edjeFunction(t.v[0], t.v[1], t.v[2]);

    for (float y = minY; y < maxY; y += 1.0) {
        float ya = (y - t.v[0].y) * x10;
        float yb = (y - t.v[1].y) * x21;
        float yc = (y - t.v[2].y) * x02;
        for (float x = minX; x < maxX; x += 1.0) {

            float a = ((x - t.v[0].x) * y10) - ya;
            float b = ((x - t.v[1].x) * y21) - yb;
            float c = ((x - t.v[2].x) * y02) - yc;
            // printf("a_step: %f,    b_step: %f,    c_step: %f\n", ((x - t.v[0].x) * y10), ((x - t.v[1].x) * y21), ((x - t.v[2].x) * y02));
            if ( a <= 0 && b <= 0 && c <= 0 ) {
                a /= area;
                b /= area;
                c /= area;

                const float depthZ = a * z2 + b * z0 + c * z1;
                const float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[(int)y][(int)x]) {

                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);

                    if ( shadow.z < (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }

                    // float r = a * R.x + b * G.x + c * B.x;
                    // float g = a * R.y + b * G.y + c * B.y;
                    // float b = a * R.z + b * G.z + c * B.z;
                    // pixels[(int)y][(int)x].Red = r * 255;
                    // pixels[(int)y][(int)x].Green = g * 255;
                    // pixels[(int)y][(int)x].Blue = b * 255;

                    memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                    depth_buffer[(int)y][(int)x] = depthW;
                }
            }
        }
    }
}
const void texTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle t, Phong model, Pixel **texture, const int tex_height, const int tex_width) {
    /* Creating 2Arrays for X and Y values to sort them. */
    float Ys[3] = { ceilf(t.v[0].y), ceilf(t.v[1].y), ceilf(t.v[2].y) };
    float Xs[3] = { ceilf(t.v[0].x), ceilf(t.v[1].x), ceilf(t.v[2].x) };

    /* Sorting the values from smaller to larger. Those values are the triangle bounding box. */
    int temp;
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

    texGeneral(pixels, depth_buffer, shadow_buffer, t, model, texture, tex_height, tex_width, Xs[0], Xs[2], Ys[0], Ys[2]);
}
const void texGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, Pixel **texels, const int tex_height, const int tex_width, const float minX, const float maxX, const float minY, const float maxY) {
    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x,    x02 = t.v[0].x - t.v[2].x;
    const float y10 = t.v[1].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y,    y02 = t.v[0].y - t.v[2].y;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    const float tu0 = t.tex[0].u,  tu1 = t.tex[1].u,  tu2 = t.tex[2].u;
    const float tv0 = t.tex[0].v,  tv1 = t.tex[1].v,  tv2 = t.tex[2].v;
    const float tw0 = t.tex[0].w,  tw1 = t.tex[1].w,  tw2 = t.tex[2].w;

    float area = edjeFunction(t.v[0], t.v[1], t.v[2]);

    for (float y = minY; y < maxY; y += 1.0) {
        float ya = -(y - t.v[0].y) * x10;
        float yb = -(y - t.v[1].y) * x21;
        float yc = -(y - t.v[2].y) * x02;
        for (float x = minX; x < maxX; x += 1.0) {

            float a = ((x - t.v[0].x) * y10) + ya;
            float b = ((x - t.v[1].x) * y21) + yb;
            float c = ((x - t.v[2].x) * y02) + yc;

            if ( a <= 0 && b <= 0 && c <= 0 ) {
                a /= area;
                b /= area;
                c /= area;

                float tex_w = a * tw2 + b * tw0 + c * tw1;
                int tex_u = ((a * tu2 + b * tu0 + c * tu1) * tex_width) / tex_w;
                int tex_v = ((a * tv2 + b * tv0 + c * tv1) * tex_height) / tex_w;

                float depthZ = a * z2 + b * z0 + c * z1;
                float depthW = a * w2 + b * w0 + c * w1;

                if (depthW > depth_buffer[(int)y][(int)x]) {

                    memcpy(&model.objColor, &texels[(int)tex_v][(int)tex_u], sizeof(Pixel));
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z < (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }

                    memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                    depth_buffer[(int)y][(int)x] = depthW;
                }
            }
        }
    }
}

