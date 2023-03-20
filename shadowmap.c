#include "header_files/shadowmap.h"

const void createShadowmap(float **shadow_buffer, Mesh c) {

    // for (int i = 0; i < c.t_indexes; i++) {

        for (int j = 0; j < c.indexes; j++) {

            shadowTriangle(shadow_buffer, &c.t[j]);
        }

    // }
}
const void shadowTriangle(float **shadow_buffer, Triangle *t) {
    Vector temp_v;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t->v[i].y <= t->v[j].y) {
                temp_v = t->v[i];
                t->v[i] = t->v[j];
                t->v[j] = temp_v;
            }

    float winding = winding3D(*t);

    if ( (t->v[1].y - t->v[2].y) == 0 )
        shadowNorthway(shadow_buffer, *t, winding);
    else if ( (t->v[0].y - t->v[1].y) == 0 )
        shadowSouthway(shadow_buffer, *t, winding);
    else
        shadowGeneral(shadow_buffer, *t, winding);
}
const void shadowNorthway(float **shadow_buffer, const Triangle t, const float winding) {
    float ma, mb, za, zb, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end = ceilf(t.v[1].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {
        const float yA = y - y_start;

        float x_start = ceilf(((ma * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * yA) + t.v[0].z;
        float z1 = (zb * yA) + t.v[0].z;
        if (winding > 0)
            swap(&z0, &z1, sizeof(float));

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = (z0 * (1 - barycentric)) + (z1 * barycentric);

            if (depth < shadow_buffer[(int)y][(int)x]) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
        }
    }
}
const void shadowSouthway(float **shadow_buffer, const Triangle t, const float winding) {
    float mb, mc, zb, zc, depth;
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[1].y - 0.5);
    float y_end = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end; y += 1.0) {
        const float yA = y - y_start;

        float x_start = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * yA) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1 = (zb * yA) + t.v[0].z;
        float z2 = (zc * yA) + t.v[1].z;
        if (winding > 0)
            swap(&z1, &z2, sizeof(float));

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = (z2 * (1 - barycentric)) + (z1 * barycentric);

            if (depth < shadow_buffer[(int)y][(int)x]) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
        }
    }
}
const void shadowGeneral(float **shadow_buffer, const Triangle t, const float winding) {
    float ma, mb, mc, za, zb, zc, depth;
    ma = (t.v[1].x - t.v[0].x) / (t.v[1].y - t.v[0].y);
    mb = (t.v[2].x - t.v[0].x) / (t.v[2].y - t.v[0].y);
    mc = (t.v[2].x - t.v[1].x) / (t.v[2].y - t.v[1].y);

    za = (t.v[1].z - t.v[0].z) / (t.v[1].y - t.v[0].y);
    zb = (t.v[2].z - t.v[0].z) / (t.v[2].y - t.v[0].y);
    if (winding > 0)
        swap(&za, &zb, sizeof(float));

    zc = (t.v[2].z - t.v[1].z) / (t.v[2].y - t.v[1].y);

    float y_start = ceilf(t.v[0].y - 0.5);
    float y_end1 = ceilf(t.v[1].y - 0.5);
    float y_end2 = ceilf(t.v[2].y - 0.5);

    for (float y = y_start; y < y_end1; y += 1.0) {
        const float yA = y - y_start;

        float x_start = ceilf(((ma * yA) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mb * yA) + t.v[0].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z0 = (za * yA) + t.v[0].z;
        float z1 = (zb * yA) + t.v[0].z;

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = ((z0 * (1 - barycentric)) + (z1 * barycentric));

            if ( depth < shadow_buffer[(int)y][(int)x] ) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
        }
    }
    for (float y = y_end1; y < y_end2; y += 1.0) {
        const float yA = y - y_start;
        const float yB = y - y_end1;

        float x_start = ceilf(((mb * (y - y_start)) + t.v[0].x) - 0.5);
        float x_end = ceilf(((mc * (y - y_end1)) + t.v[1].x) - 0.5);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(float));

        float z1, z2;
        if (winding < 0) {
            z1 = (zb * yA) + t.v[0].z;
            z2 = (zc * yB) + t.v[1].z;
        } else {
            z2 = (za * yA) + t.v[0].z;
            z1 = (zc * yB) + t.v[1].z;
        }

        for (float x = x_start; x < x_end; x += 1.0) {

            float barycentric = (x - x_start) / (x_end - x_start);
            depth = ((z2 * (1 - barycentric)) + (z1 * barycentric));

            if ( depth < shadow_buffer[(int)y][(int)x] ) {
                shadow_buffer[(int)y][(int)x] = depth;
            }
        }
    }
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

