#include "header_files/draw_functions.h"

const void drawline(Pixel **pixels, float x1, float y1, float x2, float y2, const int red, const int green, const int blue) {

    float delta_y = y2 - y1;
    float delta_x = x2 - x1;

    float fabsdy = fabs(delta_y);
    float fabsdx = fabs(delta_x);

    int start_y = ceil(y1 - 0.5);
    int end_y = ceil(y2 - 0.5);
    int start_x = ceil(x1 - 0.5);
    int end_x = ceil(x2 - 0.5);
        
    int step_y;
    int step_x;

    if ( (delta_x == 0) && (delta_y == 0) ) {
        pixels[start_y][start_x].Red = red;
        pixels[start_y][start_x].Green = green;
        pixels[start_y][start_x].Blue = blue;
    } else if ( fabsdx >= fabsdy ) {
        float slope = delta_y / delta_x;

        if (delta_x < 0) {

            for (int x = start_x; x > end_x; x--) {
                step_y = (slope * (x - start_x)) + y1;

                pixels[step_y][x].Red = red;
                pixels[step_y][x].Green = green;
                pixels[step_y][x].Blue = blue;
            }
        } else {

            for (int x = start_x; x < end_x; x++) {
                step_y = (slope * (x - start_x)) + y1;

                pixels[step_y][x].Red = red;
                pixels[step_y][x].Green = green;
                pixels[step_y][x].Blue = blue;
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (int y = start_y; y > end_y; y--) {
                step_x = (slope * (y - start_y)) + x1;

                pixels[y][step_x].Red = red;
                pixels[y][step_x].Green = green;
                pixels[y][step_x].Blue = blue;
            }
        } else {

            for (int y = start_y; y < end_y; y++) {
                step_x = (slope * (y - start_y)) + x1;

                pixels[y][step_x].Red = red;
                pixels[y][step_x].Green = green;
                pixels[y][step_x].Blue = blue;
            }
        }
    } else {
        fprintf(stderr, "An Error has occured! draw_line().");
        exit(EXIT_FAILURE);
    }
}
const void filltriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const float light, const int red, const int green, const int blue) {
    Vector temp_v;
    Textor temp_t;

    /* Sorting Vectors from smaller to larger y. */
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
        fillnorthway(pixels, depth_buffer, *t, light, winding, red, green, blue);
    else if ( (t->v[0].y - t->v[1].y) == 0 )
        fillsouthway(pixels, depth_buffer, *t, light, winding, red, green, blue);
    else
        fillgeneral(pixels, depth_buffer, *t, light, winding, red, green, blue);
}
const void fillnorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, const int red, const int green, const int blue) {
    float ma, mb, za, zb, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);

    int y_start = (int)ceil(t.v[0].y - 0.5);
    int y_end = (int)ceil(t.v[1].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = ceil(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z0 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = red * (light * depth);
                pixels[y][x].Green = green * (light * depth);
                pixels[y][x].Blue = blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const void fillsouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, const int red, const int green, const int blue) {
    float mb, mc, zb, zc, depth;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[1].y - 0.5);
    int y_end = ceil(t.v[2].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mc * (y - y_start)) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float z2 = (zc * (y - y_start)) + t.v[1].z;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z2 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = red * (light * depth);
                pixels[y][x].Green = green * (light * depth);
                pixels[y][x].Blue = blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const void fillgeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, const int red, const int green, const int blue) {
    float ma, mb, mc, za, zb, zc, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    if ( (t.v[1].x < t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    } else if ( (t.v[1].x < t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    }
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[0].y - 0.5);
    int y_end1 = ceil(t.v[1].y - 0.5);
    int y_end2 = ceil(t.v[2].y - 0.5);

    for (int y = y_start; y < y_end1; y++) {

        int x_start = ceil(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z0 * (1 - barycentric)) + (z1 * barycentric));// - (z0 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = red * (light * depth);
                pixels[y][x].Green = green * (light * depth);
                pixels[y][x].Blue = blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
    for (int y = y_end1; y < y_end2; y++) {

        int x_start = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mc * (y - y_end1)) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z1, z2;
        if (winding < 0) {
            z1 = (zb * (y - y_start)) + t.v[0].z;
            z2 = (zc * (y - y_end1)) + t.v[1].z;
        } else {
            z2 = (za * (y - y_start)) + t.v[0].z;
            z1 = (zc * (y - y_end1)) + t.v[1].z;
        }

        for (int x = x_start; x < x_end; x++) {

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z2 * (1 - barycentric)) + (z1 * barycentric));// - (z2 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = red * (light * depth);
                pixels[y][x].Green = green * (light * depth);
                pixels[y][x].Blue = blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
        }
    }
}
const void textriangle(Pixel **pixels, float **depth_buffer, Triangle *t, const float light, Pixel **texels, const BMP_Info texture) {
    Vector temp_v;
    Textor temp_t;
    const int tex_height = texture.Height - 1;
    const int tex_width = texture.Width - 1;

    /* Sorting Vectors from smaller to larger y. */
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
        texnorthway(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
    else if ( (t->v[0].y - t->v[1].y) == 0 )
        texsouthway(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
    else
        texgeneral(pixels, depth_buffer, *t, light, winding, texels, tex_height, tex_width);
}
const void texnorthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float ma, mb, za, zb, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);

    float tu1 = (t.tex[1].u - t.tex[0].u) / (t.v[1].y - t.v[0].y);
    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);

    float tv1 = (t.tex[1].v - t.tex[0].v) / (t.v[1].y - t.v[0].y);
    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);

    float tw1 = (t.tex[1].w - t.tex[0].w) / (t.v[1].y - t.v[0].y);
    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);

    int y_start = (int)ceil(t.v[0].y - 0.5);
    int y_end = (int)ceil(t.v[1].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = ceil(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);

        float tex_ys = (tv1 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv2 * (y - y_start)) + t.tex[0].v;

        float tex_xs = (tu1 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu2 * (y - y_start)) + t.tex[0].u;

        float tex_ws = (tw1 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw2 * (y - y_start)) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(int));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        float q_step = 1.0 / (float)(x_end - x_start);
        float q = 0.0;

        for (int x = x_start; x < x_end; x++) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            int tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            int tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z0 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = texels[tex_y][tex_x].Red * (light * depth);
                pixels[y][x].Green = texels[tex_y][tex_x].Green * (light * depth);
                pixels[y][x].Blue = texels[tex_y][tex_x].Blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
            q += q_step;
        }
    }
}
const void texsouthway(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float mb, mc, zb, zc, depth;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);
    float tu3 = (t.tex[2].u - t.tex[1].u) / (t.v[2].y - t.v[1].y);

    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);
    float tv3 = (t.tex[2].v - t.tex[1].v) / (t.v[2].y - t.v[1].y);

    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);
    float tw3 = (t.tex[2].w - t.tex[1].w) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[1].y - 0.5);
    int y_end = ceil(t.v[2].y - 0.5);

    for (int y = y_start; y < y_end; y++) {

        int x_start = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mc * (y - y_start)) + t.v[1].x) - 0.5);

        float tex_ys = (tv2 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv3 * (y - y_start)) + t.tex[1].v;

        float tex_xs = (tu2 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu3 * (y - y_start)) + t.tex[1].u;

        float tex_ws = (tw2 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw3 * (y - y_start)) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(int));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1 = (zb * (y - y_start)) + t.v[0].z;
        float z2 = (zc * (y - y_start)) + t.v[1].z;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        float q_step = 1.0 / (float)(x_end - x_start);
        float q = 0.0;

        for (int x = x_start; x < x_end; x++) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            int tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            int tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = (z2 * (1 - barycentric)) + (z1 * barycentric);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = texels[tex_y][tex_x].Red * (light * depth);
                pixels[y][x].Green = texels[tex_y][tex_x].Green * (light * depth);
                pixels[y][x].Blue = texels[tex_y][tex_x].Blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
            q += q_step;
        }
    }
}
const void texgeneral(Pixel **pixels, float **depth_buffer, const Triangle t, const float light, const float winding, Pixel **texels, const int tex_height, const int tex_width) {
    float ma, mb, mc, za, zb, zc, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    if ( (t.v[1].x < t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    } else if ( (t.v[1].x < t.v[0].x) && (t.v[1].x >= t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    } else if ( (t.v[1].x >= t.v[0].x) && (t.v[1].x < t.v[2].x) ) {
        if (winding < 0) {
            za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
            zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
        } else {
            za = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
            zb = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
        }
    }
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    int y_start = ceil(t.v[0].y - 0.5);
    int y_end1 = ceil(t.v[1].y - 0.5);
    int y_end2 = ceil(t.v[2].y - 0.5);

    float tu1 = (t.tex[1].u - t.tex[0].u) / (t.v[1].y - t.v[0].y);
    float tu2 = (t.tex[2].u - t.tex[0].u) / (t.v[2].y - t.v[0].y);
    float tu3 = (t.tex[2].u - t.tex[1].u) / (t.v[2].y - t.v[1].y);

    float tv1 = (t.tex[1].v - t.tex[0].v) / (t.v[1].y - t.v[0].y);
    float tv2 = (t.tex[2].v - t.tex[0].v) / (t.v[2].y - t.v[0].y);
    float tv3 = (t.tex[2].v - t.tex[1].v) / (t.v[2].y - t.v[1].y);

    float tw1 = (t.tex[1].w - t.tex[0].w) / (t.v[1].y - t.v[0].y);
    float tw2 = (t.tex[2].w - t.tex[0].w) / (t.v[2].y - t.v[0].y);
    float tw3 = (t.tex[2].w - t.tex[1].w) / (t.v[2].y - t.v[1].y);


    for (int y = y_start; y < y_end1; y++) {

        int x_start = ceil(((ma * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);

        float tex_ys = (tv1 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv2 * (y - y_start)) + t.tex[0].v;

        float tex_xs = (tu1 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu2 * (y - y_start)) + t.tex[0].u;

        float tex_ws = (tw1 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw2 * (y - y_start)) + t.tex[0].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(int));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float q_step = 1.0 / (float)(x_end - x_start);
        float q = 0.0;

        float z0 = (za * (y - y_start)) + t.v[0].z;
        float z1 = (zb * (y - y_start)) + t.v[0].z;

        for (int x = x_start; x < x_end; x++) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            int tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            int tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z0 * (1 - barycentric)) + (z1 * barycentric));// - (z0 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = texels[tex_y][tex_x].Red * (light * depth);
                pixels[y][x].Green = texels[tex_y][tex_x].Green * (light * depth);
                pixels[y][x].Blue = texels[tex_y][tex_x].Blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
            q += q_step;
        }
    }
    for (int y = y_end1; y < y_end2; y++) {

        int x_start = ceil(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        int x_end = ceil(((mc * (y - y_end1)) + t.v[1].x) - 0.5);

        float tex_ys = (tv2 * (y - y_start)) + t.tex[0].v;
        float tex_ye = (tv3 * (y - y_end1)) + t.tex[1].v;

        float tex_xs = (tu2 * (y - y_start)) + t.tex[0].u;
        float tex_xe = (tu3 * (y - y_end1)) + t.tex[1].u;

        float tex_ws = (tw2 * (y - y_start)) + t.tex[0].w;
        float tex_we = (tw3 * (y - y_end1)) + t.tex[1].w;

        if (x_start > x_end) {
            swap(&x_start, &x_end, sizeof(int));
            swap(&tex_ys, &tex_ye, sizeof(float));
            swap(&tex_xs, &tex_xe, sizeof(float));
            swap(&tex_ws, &tex_we, sizeof(float));
        }

        float z1, z2;
        if (winding < 0) {
            z1 = (zb * (y - y_start)) + t.v[0].z;
            z2 = (zc * (y - y_end1)) + t.v[1].z;
        } else {
            z2 = (za * (y - y_start)) + t.v[0].z;
            z1 = (zc * (y - y_end1)) + t.v[1].z;
        }

        float q_step = 1.0 / (float)(x_end - x_start);
        float q = 0.0;

        for (int x = x_start; x < x_end; x++) {
            float tex_w = ((tex_ws * (1 - q)) + (tex_we * q));
            int tex_y = (((tex_ys * (1 - q)) + (tex_ye * q)) * tex_height) / tex_w;
            int tex_x = (((tex_xs * (1 - q)) + (tex_xe * q)) * tex_width) / tex_w;

            float barycentric = (float)(x - x_start) / (float)(x_end - x_start);
            depth = ((z2 * (1 - barycentric)) + (z1 * barycentric));// - (z2 - z1);

            if (depth > depth_buffer[y][x]) {
                pixels[y][x].Red = texels[tex_y][tex_x].Red * (light * depth);
                pixels[y][x].Green = texels[tex_y][tex_x].Green * (light * depth);
                pixels[y][x].Blue = texels[tex_y][tex_x].Blue * (light * depth);
                depth_buffer[y][x] = depth;
            }
            q += q_step;
        }
    }
}

