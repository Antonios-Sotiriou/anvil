#include "header_files/shadowmap.h"
#include "header_files/exec_time.h"
const void createShadowmap(float **shadow_buffer, Mesh c) {

    for (int i = 0; i < c.t_indexes; i++)
        shadowTriangle(shadow_buffer, c.t[i]);
}
const void shadowTriangle(float **shadow_buffer, Triangle t) {
    Vector temp_v;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {
                temp_v = t.v[i];
                t.v[i] = t.v[j];
                t.v[j] = temp_v;
            }

    float winding = winding3D(t);

    // if ( (t.v[1].y - t.v[2].y) == 0 )
    //     shadowNorthway(shadow_buffer, t, winding);
    // else if ( (t.v[0].y - t.v[1].y) == 0 )
    //     shadowSouthway(shadow_buffer, t, winding);
    // else
        // clock_t start_time = start();
        shadowGeneral(shadow_buffer, t, winding);
        // end(start_time);
}
const void shadowNorthway(float **shadow_buffer, const Triangle t, const float winding) {
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z;
    const float ma = x10 / y10,    mb = x20 / y20;
    float za = z10 / y10,    zb = z20 / y20;

    const float y_start = ceilf(t.v[0].y - 0.5);
    const float y_end = ceilf(t.v[1].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((ma * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yys) + t.v[0].x) - 0.5);
        // if (x_start > x_end)
        //     swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * yys) + t.v[0].z;
        float z1 = (zb * yys) + t.v[0].z;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        const float xexs = x_end - x_start;
        const float z1z0 = z1 - z0;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depth = z0 + (barycentric * z1z0);

            if ( depth < shadow_buffer[(int)y][(int)x] ) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
            xxs += 1.0;
        }
        yys += 1.0;
    }
}
const void shadowSouthway(float **shadow_buffer, const Triangle t, const float winding) {
    const float x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float mb = x20 / y20,    mc = x21 / y21;
    const float zb = z20 / y20,    zc = z21 / y21;

    const float y_start = ceilf(t.v[1].y - 0.5);
    const float y_end = ceilf(t.v[2].y - 0.5);
    float yys = 0.0;
    for (float y = y_start; y < y_end; y += 1.0) {

        float x_start = ceilf(((mb * yys) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yys) + t.v[1].x) - 0.5);
        // if (x_start > x_end)
        //     swap(&x_start, &x_end, sizeof(float));

        float z1 = (zb * yys) + t.v[0].z;
        float z2 = (zc * yys) + t.v[1].z;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2;
        float xxs = 0.0;
        for (float x = x_start; x < x_end; x += 1.0) {

            const float barycentric = xxs / xexs;
            const float depth = z2 + (barycentric * z1z2);

            if ( depth < shadow_buffer[(int)y][(int)x] ) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
            xxs += 1.0;
        }
        yys += 1;
    }
}
const void shadowGeneral(float **shadow_buffer, const Triangle t, const float winding) {
    // const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    // const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    // const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    // const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    // const float ma = x10 / y10,    mb = x20 / y20,    mc = x21 / y21;
    // float za = z10 / y10,    zb = z20 / y20,    zc = z21 / y21;
    // float wa = w10 / y10,    wb = w20 / y20,    wc = w21 / y21;

    // if (winding > 0)
    //     swap(&za, &zb, sizeof(float));

    const float y_start = t.v[0].y;
    const float y_end1 = t.v[1].y;
    const float y_end2 = t.v[2].y;

    const float barycentric = (t.v[1].y - y_start) / (y_end2 - y_start);
    Vector newVec = {
        .x = t.v[0].x + (barycentric * (t.v[2].x - t.v[0].x)),
        .y = t.v[1].y,
        .z = t.v[0].z + (barycentric * (t.v[2].z - t.v[0].z)),
        .w = t.v[0].w + (barycentric * (t.v[2].w - t.v[0].w))
    };
    Triangle up = {
        .v[0] = t.v[0],
        .v[1] = newVec,
        .v[2] = t.v[1],
    };
    if (up.v[1].x > up.v[2].x)
        swap(&up.v[1], &up.v[2], sizeof(Vector));
    Triangle down = {
        .v[0] = t.v[1],
        .v[1] = newVec,
        .v[2] = t.v[2],
    };
    if (down.v[0].x > down.v[1].x)
        swap(&down.v[0], &down.v[1], sizeof(Vector));

    shadowNorthway(shadow_buffer, up, winding3D(up));
    shadowSouthway(shadow_buffer, down, winding3D(down));

    // const float y_start = ceilf(t.v[0].y - 0.5);
    // const float y_end1 = ceilf(t.v[1].y - 0.5);
    // const float y_end2 = ceilf(t.v[2].y - 0.5);

    // for (float y = y_start; y < y_end1; y += 1.0) {
    //     const float yA = y - y_start;

    //     float x_start = ceilf(((ma * yA) + t.v[0].x) - 0.5);
    //     float x_end = ceilf(((mb * yA) + t.v[0].x) - 0.5);
    //     if (x_start > x_end)
    //         swap(&x_start, &x_end, sizeof(float));

    //     const float z0 = (za * yA) + t.v[0].z;
    //     const float z1 = (zb * yA) + t.v[0].z;

    //     const float xexs = x_end - x_start;
    //     const float z1z0 = z1 - z0;
    //     float xxs = 0.0;
    //     for (float x = x_start; x < x_end; x += 1.0) {

    //         const float barycentric = xxs / xexs;
    //         const float depth = z0 + (barycentric * z1z0);

    //         if ( depth < shadow_buffer[(int)y][(int)x] ) {
    //             shadow_buffer[(int)y][(int)x] = depth;
    //         }
    //         xxs += 1.0;
    //     }
    // }
    // for (float y = y_end1; y < y_end2; y += 1.0) {
    //     const float yA = y - y_start;
    //     const float yB = y - y_end1;

    //     float x_start = ceilf(((mb * yA) + t.v[0].x) - 0.5);
    //     float x_end = ceilf(((mc * yB) + t.v[1].x) - 0.5);
    //     if (x_start > x_end)
    //         swap(&x_start, &x_end, sizeof(float));

    //     float z1, z2;
    //     if (winding < 0) {
    //         z1 = (zb * yA) + t.v[0].z;
    //         z2 = (zc * yB) + t.v[1].z;
    //     } else {
    //         z2 = (za * yA) + t.v[0].z;
    //         z1 = (zc * yB) + t.v[1].z;
    //     }

    //     const float xexs = x_end - x_start;
    //     const float z1z2 = z1 - z2;
    //     float xxs = 0.0;
    //     for (float x = x_start; x < x_end; x += 1.0) {

    //         const float barycentric = xxs / xexs;
    //         const float depth = z2 + (barycentric * z1z2);

    //         if ( depth < shadow_buffer[(int)y][(int)x] ) {
    //             shadow_buffer[(int)y][(int)x] = depth;
    //         }
    //         xxs += 1.0;
    //     }
    // }
}
const Vector shadowTest(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW) {
    /* Transform to NDC space coordinates. */
    float ndcx = (pixX / model.halfWidth) - 1.0;
    float ndcy = (pixY / model.halfHeight) - 1.0;
    float ndcz = pixZ + 1.0;
    float ndcw = 1 / pixW;
    
    /* Transform to Homogeneus / Clipp coordinates. */
    ndcx *= ndcw;
    ndcy *= ndcw;
    ndcz *= ndcw;

    /* Transform to View space coordinates. */
    Vector r = { ndcx, ndcy, ndcz, ndcw };
    r = vecxm(r, model.ViewSpace);

    /* Transform to Model space coordinates. */
    r.w = 1.0;
    r = vecxm(r, model.ModelSpace);

    /* Transform to Light space coordinates. */
    r = vecxm(r, model.LightSpace);

    /* Transform to Screen space coordinates. */
    r.x = (1.0 + r.x) * model.halfWidth;
    if (r.x >= model.width)
        r.x = model.width - 1;
    else if (r.x < 0)
        r.x = 0;

    r.y = (1.0 + r.y) * model.halfHeight;
    if (r.y >= model.height)
        r.y = model.height - 1;
    else if (r.y < 0)
        r.y = 0;

    r.z -= 1.0;

    return r;
}

