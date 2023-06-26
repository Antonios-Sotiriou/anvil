#include "header_files/scanline.h"

extern Pixel **pixels;
extern float **depth_buffer;
extern float **shadow_buffer;
extern Phong model;

const void fillTriangle(Triangle t) {
    vec4 temp_v, temp_vn;
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
    fillGeneral(t);
    if (winding > 0) {
        drawLine(t.v[0].x, t.v[0].y, t.v[1].x, t.v[1].y, 255, 0, 0);
        drawLine(t.v[1].x, t.v[1].y, t.v[2].x, t.v[2].y, 255, 0, 0);
        drawLine(t.v[2].x, t.v[2].y, t.v[0].x, t.v[0].y, 255, 0, 0);
    } else {
        drawLine(t.v[0].x, t.v[0].y, t.v[1].x, t.v[1].y, 0, 255, 0);
        drawLine(t.v[1].x, t.v[1].y, t.v[2].x, t.v[2].y, 0, 255, 0);
        drawLine(t.v[2].x, t.v[2].y, t.v[0].x, t.v[0].y, 0, 255, 0);  
    }
}
const static void fillGeneral(const Triangle t) {
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const int x10 = x1 - x0,    x21 = x2 - x1,    x02 = x0 - x2;
    const int y10 = y1 - y0,    y21 = y2 - y1,    y02 = y0 - y2;

    const int orient = ((x1 - x0) * y02) - ((y1 - y0) * x02);
    float ma = ( (x10 == 0) || (y10 == 0) ) ? 0 : (float)x10 / y10;
    float mb = ( (x02 == 0) || (y02 == 0) ) ? 0 : (float)x02 / y02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(int));

    const int y_start = y0;
    const int y_end1 = y1;
    const int y_end2 = y2;

    const int area = ((x0 - x1) * y21) - ((y0 - y1) * x21);
    int ya = ((x0 - x0) * y10) - ((y_start - y0) * x10);
    int yb = ((x0 - x1) * y21) - ((y_start - y1) * x21); /* area. */
    int yc = ((x0 - x2) * y02) - ((y_start - y2) * x02);
    // int ya = -(y_start - y0) * x10;
    // int yb = -(y_start - y1) * x21;
    // int yc = -(y_start - y2) * x02;

    int yA = 0;
    int t_start = (ma * yA) + x0;
    int t_end = (mb * yA) + x0;
    if (y10 != 0)
        for (int y = y_start; y < y_end1; y++) {
            // const int yA = y - y_start;

            int x_start = (ma * yA) + x0;
            int x_end = (mb * yA) + x0;
            
            // printf("x_start: %d,    t_start: %d\nx_end: %d,    t_end: %d\n", x_start, t_start, x_end, t_end);
            // int xa = ((x_start - x0) * y10) + ya;
            // int xb = ((x_start - x1) * y21) + yb;
            // int xc = ((x_start - x2) * y02) + yc;
            int xa = ya;
            int xb = yb;
            int xc = yc;
            // printf("xa      : %d,    xb      : %d,    xc      : %d\n", xa, xb, xc);
            // printf("fabs(xa): %d,    fabs(xb): %d,    fabs(xc): %d\n", (int)fabs(xa), (int)fabs(xb), (int)fabs(xc));
            for (int x = x_start; x < x_end; x++) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;
                // printf("a: %f,    b: %f,    c: %f\n", fabs((double)a), fabs((double)b), fabs((double)c));
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
            yA++;
        }

    if (y21 == 0)
        return;

    ma = ( (x21 == 0) || (y21 == 0) ) ? 0 : (float)x21 / y21;
    mb = ( (x02 == 0) || (y02 == 0) ) ? 0 : (float)x02 / y02;
    if (orient < 0)
        swap(&ma, &mb, sizeof(float));

    int yB = y_end1 - y_end2;
    for (int y = y_end1; y < y_end2; y++) {
        // const int yB = (y + 1) - y_end2;

        int x_start = (ma * yB) + x2;
        int x_end = (mb * yB) + x2;

        // int xa = ((x_start - x0) * y10) + ya;
        // int xb = ((x_start - x1) * y21) + yb;
        // int xc = ((x_start - x2) * y02) + yc;
        int xa = ya;
        int xb = yb;
        int xc = yc;

        for (int x = x_start; x < x_end; x++) {
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
            }
            xa += y10, xb += y21, xc += y02;
        }
        ya += -x10, yb += -x21, yc += -x02;
        yB++;
    }
}
const void texTriangle(Triangle t, Pixel **texels, const int tex_height, const int tex_width) {
    vec4 temp_v, temp_vn;
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
            vec4 ny1 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[1], t.vn[0]), nt));
            vec4 ny2 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[2], t.vn[0]), nc));
            if (winding > 0) {
                swap(&ny1, &ny2, sizeof(vec4));
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
        vec4 ny1 = add_vecs(t.vn[1], multiply_vec(sub_vecs(t.vn[2], t.vn[1]), nt));
        vec4 ny2 = add_vecs(t.vn[0], multiply_vec(sub_vecs(t.vn[2], t.vn[0]), nc));

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
            swap(&ny1, &ny2, sizeof(vec4));
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

