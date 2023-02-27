#include "header_files/draw_functions.h"

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
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[(int)step_y][(int)x], &pix, sizeof(Pixel));
            }
        } else {

            for (float x = start_x; x < end_x; x += 1.0) {
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[(int)step_y][(int)x], &pix, sizeof(Pixel));
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (float y = start_y; y > end_y; y -= 1.0) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[(int)y][(int)step_x], &pix, sizeof(Pixel));
            }
        } else {

            for (float y = start_y; y < end_y; y += 1.0) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[(int)y][(int)step_x], &pix, sizeof(Pixel));
            }
        }
    } else {
        fprintf(stderr, "An Error has occured! draw_line().");
        exit(EXIT_FAILURE);
    }
}
const void fillTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle *t, Phong model, const int SHADOWS, const int LIGHTS) {
    Vector temp_v;
    Textor temp_t;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t->v[i].y <= t->v[j].y) {

                temp_v = t->v[i];
                temp_t = t->tex[i];

                t->v[i] = t->v[j];
                t->tex[i] = t->tex[j];

                t->v[j] = temp_v;
                t->tex[j] = temp_t;
            }

    // model.dot = dot_product(norm_vec(model.lightPos), t->normal);
    // printf("model.dot: %f\n", model.dot);
    model.normal = t->normal;
    float winding = winding3D(*t);

    // if ( (t->v[1].y - t->v[2].y) == 0 )
    //     fillNorthway(pixels, depth_buffer, *t, model, winding);
    // else if ( (t->v[0].y - t->v[1].y) == 0 )
    //     fillSouthway(pixels, depth_buffer, *t, model, winding);
    // else
        fillGeneral(pixels, depth_buffer, shadow_buffer, *t, model, winding, SHADOWS, LIGHTS);
}
const void fillNorthway(Pixel **pixels, float **depth_buffer, const Triangle t, Phong model, const float winding) {
    float ma, mb, za, zb, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].w - t.v[0].w) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end = ceilf(t.v[1].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * (y - y_start)) + t.v[0].w;
        float z1 = (zb * (y - y_start)) + t.v[0].w;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = (z0 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[(int)y][(int)x]) {
                Pixel pix = phong(model, x, y, 0.0, 0.0, 1.0);
                // model.finalColor.Red = 157 * (model.dot * depth);
                // model.finalColor.Green = 122 * (model.dot * depth);
                // model.finalColor.Blue = 33 * (model.dot * depth);

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depth;
            }
        }
    }
}
const void fillSouthway(Pixel **pixels, float **depth_buffer, const Triangle t, Phong model, const float winding) {
    float mb, mc, zb, zc, depth;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].w - t.v[1].w) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[1].y - 0.5);
    float y_end = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * (y - y_start)) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1 = (zb * (y - y_start)) + t.v[0].w;
        float z2 = (zc * (y - y_start)) + t.v[1].w;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = (z2 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[(int)y][(int)x]) {
                Pixel pix = phong(model, x, y, 0.0, 0.0, 1.0);
                // model.finalColor.Red = 157 * (model.dot * depth);
                // model.finalColor.Green = 122 * (model.dot * depth);
                // model.finalColor.Blue = 33 * (model.dot * depth);

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depth;
            }
        }
    }
}
const void fillGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, const int SHADOWS, const int LIGHTS) {
    Pixel pix = { 0 };
    float ma, mb, mc, za, zb, zc, wa, wb, wc, depthZ, depthW;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    wa = (t.v[1].w - t.v[0].w) / (t.v[1].y - t.v[0].y);
    wb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);
    if (winding > 0) {
        swap(&za, &zb, sizeof(float));
        swap(&wa, &wb, sizeof(float));
    }

    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);
    wc = (t.v[2].w - t.v[1].w) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end1 = ceilf(t.v[1].y - 0.5);
    float y_end2 = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end1; y += 1.0) {

        float x_start = ceilf(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float w0 = (wa * (y - y_start)) + t.v[0].w;
        float w1 = (wb * (y - y_start)) + t.v[0].w;

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = ((z0 * (1 - barycentric)) + (z1 * barycentric));
            depthW = ((w0 * (1 - barycentric)) + (w1 * barycentric));

            if ( depthW > depth_buffer[(int)y][(int)x] ) {
                pix.Blue = model.objColor.x * 255;
                pix.Green = model.objColor.y * 255;
                pix .Red = model.objColor.z * 255;

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix.Blue -= 20;
                        pix.Green -= 20;
                        pix .Red -= 20;
                        
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);

                    } else {

                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);

                    }
                }

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
        }
    }
    for (float y = y_end1; y < y_end2; y += 1.0) {

        float x_start = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * (y - y_end1)) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1, z2, w1, w2;
        if (winding < 0) {
            z1 = (zb * (y - y_start)) + t.v[0].z;
            z2 = (zc * (y - y_end1)) + t.v[1].z;
            w1 = (wb * (y - y_start)) + t.v[0].w;
            w2 = (wc * (y - y_end1)) + t.v[1].w;
        } else {
            z2 = (za * (y - y_start)) + t.v[0].z;
            z1 = (zc * (y - y_end1)) + t.v[1].z;
            w2 = (wa * (y - y_start)) + t.v[0].w;
            w1 = (wc * (y - y_end1)) + t.v[1].w;
        }

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = ((z2 * (1 - barycentric)) + (z1 * barycentric));
            depthW = ((w2 * (1 - barycentric)) + (w1 * barycentric));

            if ( depthW > depth_buffer[(int)y][(int)x] ) {
                
                pix.Blue = model.objColor.x * 255;
                pix.Green = model.objColor.y * 255;
                pix .Red = model.objColor.z * 255;

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix.Blue -= 20;
                        pix.Green -= 20;
                        pix .Red -= 20;
                        
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);

                    } else {

                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);

                    }
                }

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
        }
    }
}
const void texTriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const float light, Pixel **texels, const int tex_height, const int tex_width) {
    Vector temp_v;
    Textor temp_t;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t->v[i].y <= t->v[j].y) {

                temp_v = t->v[i];
                temp_t = t->tex[i];

                t->v[i] = t->v[j];
                t->tex[i] = t->tex[j];

                t->v[j] = temp_v;
                t->tex[j] = temp_t;
            }

    float winding = winding3D(*t);

    if ( (t->v[1].y - t->v[2].y) == 0 )
        texNorthway(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
    else if ( (t->v[0].y - t->v[1].y) == 0 )
        texSouthway(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
    else
        texGeneral(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
}
const void texNorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float ma, mb, za, zb, wa, wb, depthZ, depthW;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    wa = (t.v[1].w - t.v[0].w) / (t.v[1].y - t.v[0].y);
    wb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);

    float tu1 = (t.tex[1].u - t.tex[0].u) / (t.v[1].y - t.v[0].y);
    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);

    float tv1 = (t.tex[1].v - t.tex[0].v) / (t.v[1].y - t.v[0].y);
    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);

    float tw1 = (t.tex[1].w - t.tex[0].w) / (t.v[1].y - t.v[0].y);
    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end = ceilf(t.v[1].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);

        float tex_ys = (tv1 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv2 * (y - y_start)) + t.tex[0].v;

        float tex_xs = (tu1 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu2 * (y - y_start)) + t.tex[0].u;

        float tex_ws = (tw1 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw2 * (y - y_start)) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float w0 = (wa * (y - y_start)) + t.v[0].w;
        float w1 = (wb * (y - y_start)) + t.v[0].w;
        if (winding > 0) {
            swap(&z0, &z1, sizeof(float));
            swap(&w0, &w1, sizeof(float));
        }

        float q_step = 1.0 / (x_end - x_start);
        float q = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            float tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            float tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = (z0 * (1 - barycentric)) + (z1 * barycentric);
            depthW = (w0 * (1 - barycentric)) + (w1 * barycentric);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                memcpy(&pixels[(int)y][(int)x], &texels[(int)tex_y][(int)tex_x], sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            q += q_step;
        }
    }
}
const void texSouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float mb, mc, zb, zc, wb, wc, depthZ, depthW;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);
    wb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);
    wc = (t.v[2].w - t.v[1].w) / (t.v[2].y - t.v[1].y);

    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);
    float tu3 = (t.tex[2].u - t.tex[1].u) / (t.v[2].y - t.v[1].y);

    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);
    float tv3 = (t.tex[2].v - t.tex[1].v) / (t.v[2].y - t.v[1].y);

    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);
    float tw3 = (t.tex[2].w - t.tex[1].w) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[1].y - 0.5);
    float y_end = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * (y - y_start)) + t.v[1].x) - 0.5);

        float tex_ys = (tv2 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv3 * (y - y_start)) + t.tex[1].v;

        float tex_xs = (tu2 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu3 * (y - y_start)) + t.tex[1].u;

        float tex_ws = (tw2 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw3 * (y - y_start)) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float z2 = (zc * (y - y_start)) + t.v[1].z;
        float w1 = (wb * (y - y_start)) + t.v[0].w;
        float w2 = (wc * (y - y_start)) + t.v[1].w;
        if (winding > 0) {
            swap(&z1, &z2, sizeof(float));
            swap(&w1, &w2, sizeof(float));
        }

        float q_step = 1.0 / (x_end - x_start);
        float q = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            float tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            float tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = (z2 * (1 - barycentric)) + (z1 * barycentric);
            depthW = (w2 * (1 - barycentric)) + (w1 * barycentric);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                memcpy(&pixels[(int)y][(int)x], &texels[(int)tex_y][(int)tex_x], sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            q += q_step;
        }
    }
}
const void texGeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float ma, mb, mc, za, zb, zc, wa, wb, wc, depthZ, depthW;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    
    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    wa = (t.v[1].w - t.v[0].w) / (t.v[1].y - t.v[0].y);
    wb = (t.v[2].w - t.v[0].w) / (t.v[2].y - t.v[0].y);

    if (winding > 0) {
        swap(&za, &zb, sizeof(float));
        swap(&wa, &wb, sizeof(float));
    }

    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);
    wc = (t.v[2].w - t.v[1].w) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end1 = ceilf(t.v[1].y - 0.5);
    float y_end2 = ceilf(t.v[2].y - 0.5);

    float tu1 = (t.tex[1].u - t.tex[0].u) / (t.v[1].y - t.v[0].y);
    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);
    float tu3 = (t.tex[2].u - t.tex[1].u) / (t.v[2].y - t.v[1].y);

    float tv1 = (t.tex[1].v - t.tex[0].v) / (t.v[1].y - t.v[0].y);
    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);
    float tv3 = (t.tex[2].v - t.tex[1].v) / (t.v[2].y - t.v[1].y);

    float tw1 = (t.tex[1].w - t.tex[0].w) / (t.v[1].y - t.v[0].y);
    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);
    float tw3 = (t.tex[2].w - t.tex[1].w) / (t.v[2].y - t.v[1].y);


    for (float y = y_start; y < y_end1; y += 1.0) {

        float x_start = ceilf(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);

        float tex_ys = (tv1 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv2 * (y - y_start)) + t.tex[0].v;

        float tex_xs = (tu1 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu2 * (y - y_start)) + t.tex[0].u;

        float tex_ws = (tw1 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw2 * (y - y_start)) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float q_step = 1.0 / (x_end - x_start);
        float q = 0.0;

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float w0 = (wa * (y - y_start)) + t.v[0].w;
        float w1 = (wb * (y - y_start)) + t.v[0].w;

        for (float x = x_start; x < x_end; x += 1.0) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            float tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            float tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = ((z0 * (1 - barycentric)) + (z1 * barycentric));
            depthW = ((w0 * (1 - barycentric)) + (w1 * barycentric));

            if (depthW > depth_buffer[(int)y][(int)x]) {
                memcpy(&pixels[(int)y][(int)x], &texels[(int)tex_y][(int)tex_x], sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            q += q_step;
        }
    }
    for (float y = y_end1; y < y_end2; y += 1.0) {

        float x_start = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * (y - y_end1)) + t.v[1].x) - 0.5);

        float tex_ys = (tv2 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv3 * (y - y_end1)) + t.tex[1].v;

        float tex_xs = (tu2 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu3 * (y - y_end1)) + t.tex[1].u;

        float tex_ws = (tw2 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw3 * (y - y_end1)) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1, z2, w1, w2;
        if (winding < 0) {
            z1 = (zb * (y - y_start)) + t.v[0].z;
            z2 = (zc * (y - y_end1)) + t.v[1].z;
            w1 = (wb * (y - y_start)) + t.v[0].w;
            w2 = (wc * (y - y_end1)) + t.v[1].w;
        } else {
            z2 = (za * (y - y_start)) + t.v[0].z;
            z1 = (zc * (y - y_end1)) + t.v[1].z;
            w2 = (wa * (y - y_start)) + t.v[0].w;
            w1 = (wc * (y - y_end1)) + t.v[1].w;
        }

        float q_step = 1.0 / (x_end - x_start);
        float q = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            float tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            float tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (x - x_start) / (x_end - x_start);
            depthZ = ((z2 * (1 - barycentric)) + (z1 * barycentric));
            depthW = ((w2 * (1 - barycentric)) + (w1 * barycentric));

            if (depthW > depth_buffer[(int)y][(int)x]) {
                memcpy(&pixels[(int)y][(int)x], &texels[(int)tex_y][(int)tex_x], sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            q += q_step;
        }
    }
}

