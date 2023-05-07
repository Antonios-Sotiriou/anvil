#include "header_files/shadowmap.h"

extern float **shadow_buffer;
extern Phong model;

const void createShadowmap(Mesh c) {

    for (int i = 0; i < c.t_indexes; i++)
        shadowTriangle(c.t[i]);
}
const void shadowTriangle(Triangle t) {
    Vector temp_v;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (t.v[i].y < t.v[j].y) {
                temp_v = t.v[i];
                t.v[i] = t.v[j];
                t.v[j] = temp_v;
            }

    float winding = winding3D(t);
    shadowGeneral(t, winding);
}
const void shadowGeneral(const Triangle t, const float winding) {
    const float x10 = t.v[1].x - t.v[0].x,    x20 = t.v[2].x - t.v[0].x,    x21 = t.v[2].x - t.v[1].x;
    const float y10 = t.v[1].y - t.v[0].y,    y20 = t.v[2].y - t.v[0].y,    y21 = t.v[2].y - t.v[1].y;
    const float z10 = t.v[1].z - t.v[0].z,    z20 = t.v[2].z - t.v[0].z,    z21 = t.v[2].z - t.v[1].z;
    const float w10 = t.v[1].w - t.v[0].w,    w20 = t.v[2].w - t.v[0].w,    w21 = t.v[2].w - t.v[1].w;
    const float ma = x10 / y10,    mb = x20 / y20,    mc = x21 / y21;
    float za = z10 / y10,    zb = z20 / y20,    zc = z21 / y21;
    float wa = w10 / y10,    wb = w20 / y20,    wc = w21 / y21;

    if (winding > 0)
        swap(&za, &zb, sizeof(float));

    const int y_start = t.v[0].y;
    const int y_end1 = t.v[1].y;
    const int y_end2 = t.v[2].y;

    if (y10 != 0)
        for (int y = y_start; y < y_end1; y++) {
            const int yA = y - y_start;

            int x_start = ((ma * yA) + t.v[0].x);
            int x_end = ((mb * yA) + t.v[0].x);
            if (x_start > x_end)
                swap(&x_start, &x_end, sizeof(int));

            const float z0 = (za * yA) + t.v[0].z;
            const float z1 = (zb * yA) + t.v[0].z;

            const float xexs = x_end - x_start;
            const float z1z0 = z1 - z0;
            float xxs = 0.0;
            for (int x = x_start; x < x_end; x++) {

                const float barycentric = xxs / xexs;
                const float depth = z0 + (barycentric * z1z0);

                if ( depth < shadow_buffer[y][x] ) {
                    shadow_buffer[y][x] = depth;
                }
                xxs += 1.0;
            }
        }
    if (y21 == 0)
        return;
    for (int y = y_end1; y < y_end2; y++) {
        const int yA = y - y_start;
        const int yB = y - y_end1;

        int x_start = ((mb * yA) + t.v[0].x);
        int x_end = ((mc * yB) + t.v[1].x);
        if (x_start > x_end)
            swap(&x_start, &x_end, sizeof(int));

        float z1, z2;
        if (winding < 0) {
            z1 = (zb * yA) + t.v[0].z;
            z2 = (zc * yB) + t.v[1].z;
        } else {
            z2 = (za * yA) + t.v[0].z;
            z1 = (zc * yB) + t.v[1].z;
        }

        const float xexs = x_end - x_start;
        const float z1z2 = z1 - z2;
        float xxs = 0.0;
        for (int x = x_start; x < x_end; x++) {

            const float barycentric = xxs / xexs;
            const float depth = z2 + (barycentric * z1z2);

            if ( depth < shadow_buffer[y][x] ) {
                shadow_buffer[y][x] = depth;
            }
            xxs += 1.0;
        }
    }
}
const Vector shadowTest(const float pixX, const float pixY, const float pixZ, const float pixW) {
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

