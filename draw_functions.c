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
const void fillTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle t, Phong model, const int SHADOWS, const int LIGHTS) {
    // t->normal = vecxm(t->normal, model.ViewSpace);
    // t->normal = vecxm(t->normal, model.ModelSpace);
    // t->normal = vecxm(t->normal, model.LightSpace);
    // #include "header_files/logging.h"
    // model.dot = dot_product(norm_vec(model.lightPos), t->normal);
    // logVector(model.CameraPos);
    // if (model.dot > 0) {
    //     model.objColor.x = 0.5;
    //     model.objColor.y = 0.5;
    //     model.objColor.z = 0.5;
    // }

    Vector temp_v;
    Textor temp_t;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {

                temp_v = t.v[i];
                temp_t = t.tex[i];

                t.v[i] = t.v[j];
                t.tex[i] = t.tex[j];

                t.v[j] = temp_v;
                t.tex[j] = temp_t;
            }

    model.normal = t.normal;
    float winding = winding3D(t);

    if ( (t.v[1].y - t.v[2].y) == 0 )
        fillNorthway(pixels, depth_buffer, shadow_buffer, t, model, winding, SHADOWS, LIGHTS);
    else if ( (t.v[0].y - t.v[1].y) == 0 )
        fillSouthway(pixels, depth_buffer, shadow_buffer, t, model, winding, SHADOWS, LIGHTS);
    else
        fillGeneral(pixels, depth_buffer, shadow_buffer, t, model, winding, SHADOWS, LIGHTS);
}
const void fillNorthway(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, const int SHADOWS, const int LIGHTS) {
    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z;
    const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w;
    const float ma = x10 / y10,    mb = x20 / y20;
    const float za = z10 / y10,    zb = z20 / y20;
    const float wa = w10 / y10,    wb = w20 / y20;

    const float y_start = ceilf(t.v[0].y - 0.5);
    const float y_end = ceilf(t.v[1].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((ma * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yys) + t.v[0].x) - 0.5);
        // printf("x_start1: %f, x_end1: %f,    y_start1: %f, y_end1: %f\n", x_start, x_end, y_start, y_end);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * yys) + t.v[0].z;
        float z1 = (zb * yys) + t.v[0].z;
        float w0 = (wa * yys) + t.v[0].w;
        float w1 = (wb * yys) + t.v[0].w;
        if (winding > 0) {
            swap(&z0, &z1, sizeof(float));
            swap(&w0, &w1, sizeof(float));
        }

        const float xexs = x_end - x_start;
        const float z1z0 = z1 - z0, w1w0 = w1 - w0;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depthZ = z0 + (barycentric * z1z0);
            const float depthW = w0 + (barycentric * w1w0);

            if (depthW > depth_buffer[(int)y][(int)x]) {

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }
                }
                // pixels[(int)y][(int)x].Red = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Green = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Blue = depthW * 70 * 255;

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0;
        }
        yys += 1.0;
    }
}
const void fillSouthway(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, const int SHADOWS, const int LIGHTS) {
    Pixel pix = { 0 };
    const float x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    const float mb = x20 / y20,    mc = x21 / y21;
    const float zb = z20 / y20,    zc = z21 / y21;
    const float wb = w20 / y20,    wc = w21 / y21;

    const float y_start = ceilf(t.v[1].y - 0.5);
    const float y_end = ceilf(t.v[2].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((mb * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yys) + t.v[1].x) - 0.5);
        // printf("x_start2: %f, x_end2: %f,    y_start2: %f, y_end2: %f\n", x_start, x_end, y_start, y_end);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1 = (zb * yys) + t.v[0].z;
        float z2 = (zc * yys) + t.v[1].z;
        float w1 = (wb * yys) + t.v[0].w;
        float w2 = (wc * yys) + t.v[1].w;
        if (winding > 0) {
            swap(&z1, &z2, sizeof(float));
            swap(&w1, &w2, sizeof(float));
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2, w1w2 = w1 - w2;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depthZ = z2 + (barycentric * z1z2);
            const float depthW = w2 + (barycentric * w1w2);

            if (depthW > depth_buffer[(int)y][(int)x]) {

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }
                }
                // pixels[(int)y][(int)x].Red = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Green = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Blue = depthW * 70 * 255;

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0;
        }
        yys += 1.0;
    }
}
const void fillGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, const int SHADOWS, const int LIGHTS) {
    // const float y_start = t.v[0].y;
    // const float y_end1 = t.v[1].y;
    // const float y_end2 = t.v[2].y;

    // const float barycentric = (t.v[1].y - y_start) / (y_end2 - y_start);
    // Vector newVec = {
    //     .x = t.v[0].x + (barycentric * (t.v[2].x - t.v[0].x)),
    //     .y = t.v[1].y,
    //     .z = t.v[0].z + (barycentric * (t.v[2].z - t.v[0].z)),
    //     .w = t.v[0].w + (barycentric * (t.v[2].w - t.v[0].w))
    // };
    // Triangle up = {
    //     .v[0] = t.v[0],
    //     .v[1] = newVec,
    //     .v[2] = t.v[1],
    // };
    // Triangle down = {
    //     .v[0] = t.v[1],
    //     .v[1] = newVec,
    //     .v[2] = t.v[2],
    // };

    // fillNorthway(pixels, depth_buffer, shadow_buffer, up, model, winding3D(up), 1, 1);
    // fillSouthway(pixels, depth_buffer, shadow_buffer, down, model, winding3D(down), 1, 1);


    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    const float ma = x10 / y10,    mb = x20 / y20,    mc = x21 / y21;
    float za = z10 / y10,    zb = z20 / y20,    zc = z21 / y21;
    float wa = w10 / y10,    wb = w20 / y20,    wc = w21 / y21;

    if (winding > 0) {
        swap(&za, &zb, sizeof(float));
        swap(&wa, &wb, sizeof(float));
    }

    const float y_start = ceilf(t.v[0].y - 0.5);
    const float y_end1 = ceilf(t.v[1].y - 0.5);
    const float y_end2 = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end1; y += 1.0) {
        const float yA = y - y_start;

        float x_start = ceilf(((ma * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * yA) + t.v[0].z;
        float z1 = (zb * yA) + t.v[0].z;
        float w0 = (wa * yA) + t.v[0].w;
        float w1 = (wb * yA) + t.v[0].w;

        const float xexs = x_end - x_start;
        const float z1z0 = z1 - z0,    w1w0 = w1 - w0;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depthZ = z0 + (barycentric * z1z0);
            const float depthW = w0 + (barycentric * w1w0);
            if ( depthW > depth_buffer[(int)y][(int)x] ) {

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }
                }
                // pixels[(int)y][(int)x].Red = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Green = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Blue = depthW * 70 * 255;

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0;
        }
    }

    for (float y = y_end1; y < y_end2; y += 1.0) {
        const float yA = y - y_start;
        const float yB = y - y_end1;

        float x_start = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yB) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1, z2, w1, w2;
        if (winding < 0) {
            z1 = (zb * yA) + t.v[0].z;
            z2 = (zc * yB) + t.v[1].z;
            w1 = (wb * yA) + t.v[0].w;
            w2 = (wc * yB) + t.v[1].w;
        } else {
            z2 = (za * yA) + t.v[0].z;
            z1 = (zc * yB) + t.v[1].z;
            w2 = (wa * yA) + t.v[0].w;
            w1 = (wc * yB) + t.v[1].w;
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2,    w1w2 = w1 - w2;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depthZ = z2 + (barycentric * z1z2);
            const float depthW = w2 + (barycentric * w1w2);
            if ( depthW > depth_buffer[(int)y][(int)x] ) {

                if (SHADOWS) {
                    Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                    if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 0.0);
                    } else {
                        if (LIGHTS)
                            pix = phong(model, x, y, depthZ, depthW, 1.0);
                    }
                }
                // pixels[(int)y][(int)x].Red = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Green = depthW * 70 * 255;
                // pixels[(int)y][(int)x].Blue = depthW * 70 * 255;

                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0;
        }
    }
}
const void texTriangle(Pixel **pixels, float **depth_buffer, float **shadow_buffer, Triangle t, Phong model, Pixel **texels, const int tex_height, const int tex_width) {
    Vector temp_v;
    Textor temp_t;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {

                temp_v = t.v[i];
                temp_t = t.tex[i];

                t.v[i] = t.v[j];
                t.tex[i] = t.tex[j];

                t.v[j] = temp_v;
                t.tex[j] = temp_t;
            }

    model.normal = t.normal;
    float winding = winding3D(t);

    if ( (t.v[1].y - t.v[2].y) == 0 )
        texNorthway(pixels, depth_buffer, shadow_buffer, t, model, winding, texels, tex_height, tex_width);
    else if ( (t.v[0].y - t.v[1].y) == 0 )
        texSouthway(pixels, depth_buffer, shadow_buffer, t, model, winding, texels, tex_height, tex_width);
    else
        texGeneral(pixels, depth_buffer, shadow_buffer, t, model, winding, texels, tex_height, tex_width);
}
const void texNorthway(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z;
    const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w;
    const float ma = x10 / y10,    mb = x20 / y20;
    const float za = z10 / y10,    zb = z20 / y20;
    const float wa = w10 / y10,    wb = w20 / y20;

    const float tu0 = (t.tex[1].u - t.tex[0].u) / y10,    tu1 = (t.tex[2].u - t.tex[0].u) / y20;
    const float tv0 = (t.tex[1].v - t.tex[0].v) / y10,    tv1 = (t.tex[2].v - t.tex[0].v) / y20;
    const float tw0 = (t.tex[1].w - t.tex[0].w) / y10,    tw1 = (t.tex[2].w - t.tex[0].w) / y20;

    const float y_start = ceilf(t.v[0].y - 0.5);
    const float y_end = ceilf(t.v[1].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((ma * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yys) + t.v[0].x) - 0.5);

        float tex_ys = (tv0 * yys) + t.tex[0].v;
        float tex_ye = (tv1 * yys) + t.tex[0].v;

        float tex_xs = (tu0 * yys) + t.tex[0].u;
        float tex_xe = (tu1 * yys) + t.tex[0].u;

        float tex_ws = (tw0 * yys) + t.tex[0].w;
        float tex_we = (tw1 * yys) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z0 = (za * yys) + t.v[0].z;
        float z1 = (zb * yys) + t.v[0].z;
        float w0 = (wa * yys) + t.v[0].w;
        float w1 = (wb * yys) + t.v[0].w;
        if (winding > 0) {
            swap(&z0, &z1, sizeof(float));
            swap(&w0, &w1, sizeof(float));
        }

        const float xexs = x_end - x_start;
        const float z1z0 = z1 - z0,    w1w0 = w1 - w0;
        const float twews = tex_we - tex_ws,    tyeys = tex_ye - tex_ys,    txexs = tex_xe - tex_xs;
        const float q_step = 1.0 / xexs;
        float q = 0.0, xxs = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) {
            const float tex_w = tex_ws + (q * twews);
            const float tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
            const float tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

            const float barycentric = xxs / xexs;
            const float depthZ = z0 + (barycentric * z1z0);
            const float depthW = w0 + (barycentric * w1w0);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                model.objColor.x = texels[(int)tex_y][(int)tex_x].Blue;
                model.objColor.y = texels[(int)tex_y][(int)tex_x].Green;
                model.objColor.z = texels[(int)tex_y][(int)tex_x].Red;
                Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                }
                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0,    q += q_step;
        }
        yys += 1.0;
    }
}
const void texSouthway(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    Pixel pix = { 0 };
    const float x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    const float mb = x20 / y20,    mc = x21 / y21;
    const float zb = z20 / y20,    zc = z21 / y21;
    const float wb = w20 / y20,    wc = w21 / y21;

    const float tu1 = (t.tex[2].u - t.tex[0].u) / y20,    tu2 = (t.tex[2].u - t.tex[1].u) / y21;
    const float tv1 = (t.tex[2].v - t.tex[0].v) / y20,    tv2 = (t.tex[2].v - t.tex[1].v) / y21;
    const float tw1 = (t.tex[2].w - t.tex[0].w) / y20,    tw2 = (t.tex[2].w - t.tex[1].w) / y21;

    const float y_start = ceilf(t.v[1].y - 0.5);
    const float y_end = ceilf(t.v[2].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((mb * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yys) + t.v[1].x) - 0.5);

        float tex_ys = (tv1 * yys) + t.tex[0].v;
        float tex_ye = (tv2 * yys) + t.tex[1].v;

        float tex_xs = (tu1 * yys) + t.tex[0].u;
        float tex_xe = (tu2 * yys) + t.tex[1].u;

        float tex_ws = (tw1 * yys) + t.tex[0].w;
        float tex_we = (tw2 * yys) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1 = (zb * yys) + t.v[0].z;
        float z2 = (zc * yys) + t.v[1].z;
        float w1 = (wb * yys) + t.v[0].w;
        float w2 = (wc * yys) + t.v[1].w;
        if (winding > 0) {
            swap(&z1, &z2, sizeof(float));
            swap(&w1, &w2, sizeof(float));
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2,    w1w2 = w1 - w2;
        const float twews = tex_we - tex_ws,    tyeys = tex_ye - tex_ys,    txexs = tex_xe - tex_xs;
        const float q_step = 1.0 / xexs;
        float q = 0.0, xxs = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) {
            const float tex_w = tex_ws + (q * twews);
            const float tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
            const float tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

            const float barycentric = xxs / xexs;
            const float depthZ = z2 + (barycentric * z1z2);
            const float depthW = w2 + (barycentric * w1w2);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                model.objColor.x = texels[(int)tex_y][(int)tex_x].Blue;
                model.objColor.y = texels[(int)tex_y][(int)tex_x].Green;
                model.objColor.z = texels[(int)tex_y][(int)tex_x].Red;
                Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                }
                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0,    q += q_step;
        }
        yys += 1.0;
    }
}
const void texGeneral(Pixel **pixels, float **depth_buffer, float **shadow_buffer, const Triangle t, Phong model, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    // const float y_start = t.v[0].y;
    // const float y_end1 = t.v[1].y;
    // const float y_end2 = t.v[2].y;

    // const float barycentric = (t.v[1].y - y_start) / (y_end2 - y_start);
    // Vector newVec = {
    //     .x = t.v[0].x + (barycentric * (t.v[2].x - t.v[0].x)),
    //     .y = t.v[1].y,
    //     .z = t.v[0].z + (barycentric * (t.v[2].z - t.v[0].z)),
    //     .w = t.v[0].w + (barycentric * (t.v[2].w - t.v[0].w))
    // };
    // Textor newTex = {
    //     .u = t.tex[0].u + (barycentric * (t.tex[2].u - t.tex[0].u)),
    //     .v = t.tex[0].v + (barycentric * (t.tex[2].v - t.tex[0].v)),
    //     .w = t.tex[0].w + (barycentric * (t.tex[2].w - t.tex[0].w))
    // };
    // Triangle up = t;
    // up.v[0] = t.v[0];
    // up.tex[0] = t.tex[0];
    // up.v[1] = newVec;
    // up.tex[1] = newTex;
    // up.v[2] = t.v[1];
    // up.tex[2] = t.tex[1];

    // Triangle down = t;
    // down.v[0] = t.v[1];
    // down.tex[0] = t.tex[1];
    // down.v[1] = newVec;
    // down.tex[1] = newTex;
    // down.v[2] = t.v[2];
    // down.tex[2] = t.tex[2];

    // texNorthway(pixels, depth_buffer, shadow_buffer, up, model, winding3D(up), texels, tex_height, tex_width);
    // texSouthway(pixels, depth_buffer, shadow_buffer, down, model, winding3D(down), texels, tex_height, tex_width);


    Pixel pix = { 0 };
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    const float ma = x10 / y10,    mb = x20 / y20,    mc = x21 / y21;
    float za = z10 / y10,    zb = z20 / y20,    zc = z21 / y21;
    float wa = w10 / y10,    wb = w20 / y20,    wc = w21 / y21;

    if (winding > 0) {
        swap(&za, &zb, sizeof(float));
        swap(&wa, &wb, sizeof(float));
    }

    const float y_start = ceilf(t.v[0].y - 0.5);
    const float y_end1 = ceilf(t.v[1].y - 0.5);
    const float y_end2 = ceilf(t.v[2].y - 0.5);

    const float tu0 = (t.tex[1].u - t.tex[0].u) / y10,    tu1 = (t.tex[2].u - t.tex[0].u) / y20,    tu2 = (t.tex[2].u - t.tex[1].u) / y21;
    const float tv0 = (t.tex[1].v - t.tex[0].v) / y10,    tv1 = (t.tex[2].v - t.tex[0].v) / y20,    tv2 = (t.tex[2].v - t.tex[1].v) / y21;
    const float tw0 = (t.tex[1].w - t.tex[0].w) / y10,    tw1 = (t.tex[2].w - t.tex[0].w) / y20,    tw2 = (t.tex[2].w - t.tex[1].w) / y21;

    for (float y = y_start; y < y_end1; y += 1.0) {
        const float yA = y - y_start;

        float x_start = ceilf(((ma * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yA) + t.v[0].x) - 0.5);

        float tex_ys = (tv0 * yA) + t.tex[0].v;
        float tex_ye = (tv1 * yA) + t.tex[0].v;

        float tex_xs = (tu0 * yA) + t.tex[0].u;
        float tex_xe = (tu1 * yA) + t.tex[0].u;

        float tex_ws = (tw0 * yA) + t.tex[0].w;
        float tex_we = (tw1 * yA) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        const float z0 = (za * yA) + t.v[0].z;
        const float z1 = (zb * yA) + t.v[0].z;
        const float w0 = (wa * yA) + t.v[0].w;
        const float w1 = (wb * yA) + t.v[0].w;

        const float xexs = x_end - x_start;
        const float z1z0 = z1 - z0,    w1w0 = w1 - w0;
        const float twews = tex_we - tex_ws,    tyeys = tex_ye - tex_ys,    txexs = tex_xe - tex_xs;
        const float q_step = 1.0 / xexs;
        float q = 0.0, xxs = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) { 
            const float tex_w = tex_ws + (q * twews);
            const float tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
            const float tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

            const float barycentric = xxs / xexs;
            const float depthZ = z0 + (barycentric * z1z0);
            const float depthW = w0 + (barycentric * w1w0);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                model.objColor.x = texels[(int)tex_y][(int)tex_x].Blue;
                model.objColor.y = texels[(int)tex_y][(int)tex_x].Green;
                model.objColor.z = texels[(int)tex_y][(int)tex_x].Red;
                Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                        pix = phong(model, x, y, depthZ, depthW, 0.0);
                } else {
                        pix = phong(model, x, y, depthZ, depthW, 1.0);
                }
                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0,    q += q_step;
        }
    }
    for (float y = y_end1; y < y_end2; y += 1.0) {
        const float yA = y - y_start;
        const float yB = y - y_end1;

        float x_start = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yB) + t.v[1].x) - 0.5);

        float tex_ys = (tv1 * yA) + t.tex[0].v;
        float tex_ye = (tv2 * yB) + t.tex[1].v;

        float tex_xs = (tu1 * yA) + t.tex[0].u;
        float tex_xe = (tu2 * yB) + t.tex[1].u;

        float tex_ws = (tw1 * yA) + t.tex[0].w;
        float tex_we = (tw2 * yB) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(float));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1, z2, w1, w2;
        if (winding < 0) {
            z1 = (zb * yA) + t.v[0].z;
            z2 = (zc * yB) + t.v[1].z;
            w1 = (wb * yA) + t.v[0].w;
            w2 = (wc * yB) + t.v[1].w;
        } else {
            z2 = (za * yA) + t.v[0].z;
            z1 = (zc * yB) + t.v[1].z;
            w2 = (wa * yA) + t.v[0].w;
            w1 = (wc * yB) + t.v[1].w;
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2,    w1w2 = w1 - w2;
        const float twews = tex_we - tex_ws,    tyeys = tex_ye - tex_ys,    txexs = tex_xe - tex_xs;
        const float q_step = 1.0 / xexs;
        float q = 0.0, xxs = 0.0;

        for (float x = x_start; x < x_end; x += 1.0) { 
            const float tex_w = tex_ws + (q * twews);
            const float tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
            const float tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

            const float barycentric = xxs / xexs;
            const float depthZ = z2 + (barycentric * z1z2);
            const float depthW = w2 + (barycentric * w1w2);

            if (depthW > depth_buffer[(int)y][(int)x]) {
                model.objColor.x = texels[(int)tex_y][(int)tex_x].Blue;
                model.objColor.y = texels[(int)tex_y][(int)tex_x].Green;
                model.objColor.z = texels[(int)tex_y][(int)tex_x].Red;
                Vector shadow = shadowTest(model, x, y, depthZ, depthW);
                if ( shadow.z > (shadow_buffer[(int)shadow.y][(int)shadow.x] + model.bias) ) {
                    pix = phong(model, x, y, depthZ, depthW, 0.0);
                } else {
                    pix = phong(model, x, y, depthZ, depthW, 1.0);
                }
                memcpy(&pixels[(int)y][(int)x], &pix, sizeof(Pixel));
                depth_buffer[(int)y][(int)x] = depthW;
            }
            xxs += 1.0,    q += q_step;
        }
    }
}

