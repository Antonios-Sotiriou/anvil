#include "header_files/scanline.h"

extern Pixel **pixels;
extern float **depth_buffer;
extern float **shadow_buffer;
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
const void fillTriangle(Triangle t) {
    Vector temp_v, temp_vn;
    Textor temp_vt;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {

                temp_v = t.v[i];
                temp_vt = t.vt[i];
                temp_vn = t.vn[i];

                t.v[i] = t.v[j];
                t.vt[i] = t.vt[j];
                t.vn[i] = t.vn[j];

                t.v[j] = temp_v;
                t.vt[j] = temp_vt;
                t.vn[j] = temp_vn;
            }

    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    fillGeneral(t, winding);
    drawLine(t.v[0].x, t.v[0].y, t.v[1].x, t.v[1].y, 255, 0, 0);
    drawLine(t.v[1].x, t.v[1].y, t.v[2].x, t.v[2].y, 0, 255, 0);
    drawLine(t.v[2].x, t.v[2].y, t.v[0].x, t.v[0].y, 0, 0, 255);
}
const static void fillGeneral(const Triangle t, const float winding) {
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x,    x02 = t.v[0].x - t.v[2].x,    x21 = t.v[2].x - t.v[1].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y,    y02 = t.v[0].y - t.v[2].y,    y21 = t.v[2].y - t.v[1].y;

    const float orient = ((t.v[1].x - t.v[0].x) * y02) - ((t.v[1].y - t.v[0].y) * x02);
    float ma = ( (x10 == 0) || (y10 == 0) ) ? 0 : x10 / y10;
    float mb = ( (x20 == 0) || (y20 == 0) ) ? 0 : x20 / y20;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    const int y_start = t.v[0].y + 0.5;
    const int y_end1 = t.v[1].y + 0.5;
    const int y_end2 = t.v[2].y + 0.5;
    int t_start = t.v[0].x + 0.5;
    int t_end = t.v[0].x + 0.5;

    const float area = ((t.v[0].x - t.v[1].x) * y21) - ((t.v[0].y - t.v[1].y) * x21);
    // float ya = ((t_start - t.v[0].x) * y10) - ((y_start - t.v[0].y) * x10);
    // float yb = ((t_start - t.v[1].x) * y21) - ((y_start - t.v[1].y) * x21);
    // float yc = ((t_start - t.v[2].x) * y02) - ((y_start - t.v[2].y) * x02);
    float ya = -(y_start - t.v[0].y) * x10;
    float yb = -(y_start - t.v[1].y) * x21;
    float yc = -(y_start - t.v[2].y) * x02;

    if (y10 != 0)
        for (int y = y_start; y < y_end1; y++) {
            const int yA = y - y_start;

            int x_start = ((ma * yA) + t.v[0].x) + 0.5;
            int x_end = ((mb * yA) + t.v[0].x) + 0.5;
            // printf("Upper  x_start: %d,    t_start: %d\n", x_start, t_start);
            // printf("Upper  x_end  : %d,    t_end  : %d\n", x_end, t_end);

            float xa = ((x_start - t.v[0].x) * y10) + ya;
            float xb = ((x_start - t.v[1].x) * y21) + yb;
            float xc = ((x_start - t.v[2].x) * y02) + yc;
            // float xa = ya;
            // float xb = yb;
            // float xc = yc;

            for (int x = x_start; x < x_end; x++) {
                const float a = xa / area;
                const float b = xb / area;
                const float c = xc / area;

                const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
                const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

                if ( depthW > depth_buffer[y][x] ) {

                    model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                    model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                    model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                    depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                }
                xa += y10, xb += y21, xc += y02;
            }
            ya += -x10, yb += -x21, yc += -x02;
            t_start += ma, t_end += mb;
        }

    if (y21 == 0)
        return;

    ma = ( (x21 == 0) || (y21 == 0) ) ? 0 : x21 / y21;
    mb = ( (x20 == 0) || (y20 == 0) ) ? 0 : x20 / y20;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    for (int y = y_end1; y < y_end2; y++) {
        const int yB = y - y_end2;

        int x_start = ((ma * yB) + t.v[2].x) + 0.5;
        int x_end = ((mb * yB) + t.v[2].x) + 0.5;
        // printf("Lower  x_start: %d,    t_start: %d\n", x_start, t_start);
        // printf("Lower  x_end  : %d,    t_end  : %d\n", x_end, t_end);
        // printf("Lower  x_start: %d,    x_end: %d\n", x_start, x_end);
        float xa = ((x_start - t.v[0].x) * y10) + ya;
        float xb = ((x_start - t.v[1].x) * y21) + yb;
        float xc = ((x_start - t.v[2].x) * y02) + yc;
        // float xa = ya;
        // float xb = yb;
        // float xc = yc;

        for (int x = x_start; x < x_end; x++) {
            const float a = xa / area;
            const float b = xb / area;
            const float c = xc / area;

            const float depthZ = a * t.v[2].z + b * t.v[0].z + c * t.v[1].z;
            const float depthW = a * t.v[2].w + b * t.v[0].w + c * t.v[1].w;

            if ( depthW > depth_buffer[y][x] ) {

                model.normal.x = a * t.vn[2].x + b * t.vn[0].x + c * t.vn[1].x;
                model.normal.y = a * t.vn[2].y + b * t.vn[0].y + c * t.vn[1].y;
                model.normal.z = a * t.vn[2].z + b * t.vn[0].z + c * t.vn[1].z;

                depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
            }
            xa += y10, xb += y21, xc += y02;
        }
        ya += -x10, yb += -x21, yc += -x02;
        t_start += ma, t_end += mb;
    }
}
const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width) {
    Vector temp_v, temp_vn;
    Textor temp_vt;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {

                temp_v = t.v[i];
                temp_vt = t.vt[i];
                temp_vn = t.vn[i];

                t.v[i] = t.v[j];
                t.vt[i] = t.vt[j];
                t.vn[i] = t.vn[j];

                t.v[j] = temp_v;
                t.vt[j] = temp_vt;
                t.vn[j] = temp_vn;
            }
    
    model.normal = t.fn;
    float winding = 1 / winding3D(t);
    model.bias = (winding <= 0.000026 && winding >= 0.0) ? 0.0017 : 0.0009;
    texGeneral(t, winding, texels, tex_height, tex_width);
}
const static void texGeneral(const Triangle t, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
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

    const int y_start = t.v[0].y;
    const int y_end1 = t.v[1].y;
    const int y_end2 = t.v[2].y;

    const float tu10 = (t.vt[1].u - t.vt[0].u) / y10,    tu20 = (t.vt[2].u - t.vt[0].u) / y20,    tu21 = (t.vt[2].u - t.vt[1].u) / y21;
    const float tv10 = (t.vt[1].v - t.vt[0].v) / y10,    tv20 = (t.vt[2].v - t.vt[0].v) / y20,    tv21 = (t.vt[2].v - t.vt[1].v) / y21;
    const float tw10 = (t.vt[1].w - t.vt[0].w) / y10,    tw20 = (t.vt[2].w - t.vt[0].w) / y20,    tw21 = (t.vt[2].w - t.vt[1].w) / y21;

    if (y10 != 0)
        for (int y = y_start; y < y_end1; y++) {
            const int yA = y - y_start;

            const float nt = ((float)yA / (y_end1 - y_start));
            const float nc = ((float)yA / (y_end2 - y_start));  
            Vector ny1 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[1], t.vn[0]), nt));
            Vector ny2 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[2], t.vn[0]), nc));
            if (winding > 0) {
                swap(&ny1, &ny2, sizeof(Vector));
            }

            int x_start = ((ma * yA) + t.v[0].x);
            int x_end = ((mb * yA) + t.v[0].x);

            float tex_ys = (tv10 * yA) + t.vt[0].v;
            float tex_ye = (tv20 * yA) + t.vt[0].v;

            float tex_xs = (tu10 * yA) + t.vt[0].u;
            float tex_xe = (tu20 * yA) + t.vt[0].u;

            float tex_ws = (tw10 * yA) + t.vt[0].w;
            float tex_we = (tw20 * yA) + t.vt[0].w;

            if (x_start > x_end) {
                swap(&x_start, &x_end, sizeof(int));
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

            for (int x = x_start; x < x_end; x++) {

                const float barycentric = xxs / xexs;
                const float depthZ = z0 + (barycentric * z1z0);
                const float depthW = w0 + (barycentric * w1w0);

                if (depthW > depth_buffer[y][x]) {
                    const float tex_w = tex_ws + (q * twews);
                    const int tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
                    const int tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

                    model.normal = add_vecs(ny1, multiply_vec(sub_vecs(ny2, ny1), barycentric));
                    memcpy(&model.objColor, &texels[tex_y][tex_x], sizeof(Pixel));

                    memcpy(&pixels[y][x], &pix, sizeof(Pixel));
                    depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
                }
                xxs += 1.0,    q += q_step;
            }
        }
    if (y21 == 0)
        return;
    for (int y = y_end1; y < y_end2; y++) {
        const int yA = y - y_start;
        const int yB = y - y_end1;

        const float nt = ((float)yB / (y_end2 - y_end1));
        const float nc = ((float)yA / (y_end2 - y_start));
        Vector ny1 = add_vecs(t.vn[1], multiply_vec(sub_vecs(t.vn[2], t.vn[1]), nt));
        Vector ny2 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[2], t.vn[0]), nc));

        int x_start = ((mb * yA) + t.v[0].x);
        int x_end = ((mc * yB) + t.v[1].x);

        float tex_ys = (tv20 * yA) + t.vt[0].v;
        float tex_ye = (tv21 * yB) + t.vt[1].v;

        float tex_xs = (tu20 * yA) + t.vt[0].u;
        float tex_xe = (tu21 * yB) + t.vt[1].u;

        float tex_ws = (tw20 * yA) + t.vt[0].w;
        float tex_we = (tw21 * yB) + t.vt[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(int));
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
            swap(&ny1, &ny2, sizeof(Vector));
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2,    w1w2 = w1 - w2;
        const float twews = tex_we - tex_ws,    tyeys = tex_ye - tex_ys,    txexs = tex_xe - tex_xs;
        const float q_step = 1.0 / xexs;
        float q = 0.0, xxs = 0.0;

        for (int x = x_start; x < x_end; x++) {

            const float barycentric = xxs / xexs;
            const float depthZ = z2 + (barycentric * z1z2);
            const float depthW = w2 + (barycentric * w1w2);

            if (depthW > depth_buffer[y][x]) {
                const float tex_w = tex_ws + (q * twews);
                const int tex_y = ((tex_ys + (q * tyeys)) * tex_height) / tex_w;
                const int tex_x = ((tex_xs + (q * txexs)) * tex_width) / tex_w;

                model.normal = add_vecs(ny1, multiply_vec(sub_vecs(ny2, ny1), barycentric));
                memcpy(&model.objColor, &texels[tex_y][tex_x], sizeof(Pixel));

                memcpy(&pixels[y][x], &pix, sizeof(Pixel));
                depth_buffer[y][x] = phong(model, x, y, depthZ, depthW);
            }
            xxs += 1.0,    q += q_step;
        }
    }
}

