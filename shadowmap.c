#include "header_files/shadowmap.h"

extern XWindowAttributes wa;
extern int HALFW;
extern int HALFH;
extern float **shadow_buffer;
extern Mat4x4 LookAt, LightMat, rePerspMat;

const void createShadowmap(Mesh c) {
    for (int m = 0; m < c.t_indexes; m++) {
        /* Creating 2Arrays for X and Y values to sort them. */
        float Ys[3] = { c.t[m].v[0].y, c.t[m].v[1].y, c.t[m].v[2].y };
        float Xs[3] = { c.t[m].v[0].x, c.t[m].v[1].x, c.t[m].v[2].x };
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

        shadowTriangle(c.t[m], Xs[0] + 0.5, Xs[2] + 0.5, Ys[0] + 0.5, Ys[2] + 0.5);
    }
}
const void shadowTriangle(const Triangle t, int minX, int maxX, int minY, int maxY) {
    const int maxHeight = wa.height - 1;
    const int maxWidth = wa.width - 1;
    const int x0 = t.v[0].x + 0.5,    x1 = t.v[1].x + 0.5,    x2 = t.v[2].x + 0.5;
    const int y0 = t.v[0].y + 0.5,    y1 = t.v[1].y + 0.5,    y2 = t.v[2].y + 0.5;
    const float z0 = t.v[0].z,    z1 = t.v[1].z,     z2 = t.v[2].z;
    const float w0 = t.v[0].w,    w1 = t.v[1].w,     w2 = t.v[2].w;
    const int x10 = x0 - x1,    x20 = x2 - x0,    x02 = x2 - x0,    x21 = x1 - x2;
    const int y10 = y0 - y1,    y20 = y2 - y0,    y02 = y2 - y0,    y21 = y1 - y2;

    const int tpA = ((y10 == 0) && (t.v[2].y > t.v[1].y)) || (y10 < 0) ? 1 : 0;
    const int tpB = ((y21 == 0) && (t.v[0].y > t.v[2].y)) || (y21 < 0) ? 1 : 0;
    const int tpC = ((y02 == 0) && (t.v[1].y > t.v[0].y)) || (y02 < 0) ? 1 : 0;

    minY = minY < 0 ? 0 : minY;
    maxY = maxY > maxHeight ? maxHeight : maxY;
    minX = minX < 0 ? 0 : minX;
    maxX = maxX > maxWidth ? maxWidth : maxX;

    const int area = ((x0 - x1) * y21) - ((y0 - y1) * x21);
    int ya = ((minX - x0) * y10) - ((minY - y0) * x10);
    int yb = ((minX - x1) * y21) - ((minY - y1) * x21);
    int yc = ((minX - x2) * y02) - ((minY - y2) * x02);

    for (int y = minY; y <= maxY; y++) {
        int xa = ya;
        int xb = yb;
        int xc = yc;
        int xflag = 0;
        for (int x = minX; x <= maxX; x++) {

            xa = ( (!xa) && (tpA) ) ? -1 : xa;
            xb = ( (!xb) && (tpB) ) ? -1 : xb;
            xc = ( (!xc) && (tpC) ) ? -1 : xc;

            if ( (xa | xb | xc) >= 0 ) {
                const float a = (float)xa / area;
                const float b = (float)xb / area;
                const float c = (float)xc / area;

                const float depthZ = a * z2 + b * z0 + c * z1;

                if (depthZ < shadow_buffer[y][x]) {
                    shadow_buffer[y][x] = depthZ;
                }
                xflag++;
            } else if (xflag) break;
            xa += y10,    xb += y21,    xc += y02;
        }
        ya += -x10,    yb += -x21,    yc += -x02;
    }
}
const Vector shadowTest(Vector pixel) {
    Vector r = pixel;
    r.w = 1;
    /* Transform to Model space coordinates. */
    r = vecxm(r, LookAt);

    /* Transform to Light space coordinates. */
    r = vecxm(r, LightMat);

    /* Transform to Screen space coordinates. */
    r.x = (1.0 + r.x) * HALFW;
    if (r.x >= wa.width)
        r.x = wa.width - 1;
    else if (r.x < 0)
        r.x = 0;

    r.y = (1.0 + r.y) * HALFH;
    if (r.y >= wa.height)
        r.y = wa.height - 1;
    else if (r.y < 0)
        r.y = 0;

    r.z *= 0.5;

    return r;
}

