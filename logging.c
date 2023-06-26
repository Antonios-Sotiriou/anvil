#include "header_files/logging.h"

const void logVector(const vec4 v) {
    fprintf(stdout, "x: %f    y: %f    z: %f    w: %f\n", v.x, v.y, v.z, v.w);
}

const void logPixel(const Pixel p) {
    fprintf(stdout, "Red: %u    Green: %u    Blue: %u\n", p.Red, p.Green, p.Blue);
}

/* Logging Triangle values.If vec = 1 loggs vec4 values, if tex Texture, if norm Normal. */
const void logTriangle(const Triangle t, const int vec, const int tex, const int norm) {
    if (vec) {
        fprintf(stdout, "t.v[0].x: %f    t.v[0].y: %f    t.v[0].z: %f    t.v[0].w: %f\n", t.v[0].x, t.v[0].y, t.v[0].z, t.v[0].w);
        fprintf(stdout, "t.v[1].x: %f    t.v[1].y: %f    t.v[1].z: %f    t.v[1].w: %f\n", t.v[1].x, t.v[1].y, t.v[1].z, t.v[1].w);
        fprintf(stdout, "t.v[2].x: %f    t.v[2].y: %f    t.v[2].z: %f    t.v[2].w: %f\n\n", t.v[2].x, t.v[2].y, t.v[2].z, t.v[2].w);
    } else if (tex) {
        fprintf(stdout, "t.vt[0].u: %f    t.vt[0].v: %f    t.v[0].w: %f\n", t.vt[0].u, t.vt[0].v, t.vt[0].w);
        fprintf(stdout, "t.vt[1].u: %f    t.vt[1].v: %f    t.v[1].w: %f\n", t.vt[1].u, t.vt[1].v, t.vt[1].w);
        fprintf(stdout, "t.vt[2].u: %f    t.vt[2].v: %f    t.v[2].w: %f\n\n", t.vt[2].u, t.vt[2].v, t.vt[2].w);      
    } else if (norm) {
        logVector(t.fn);
    }
}

const void logMatrix(const Mat4x4 m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            fprintf(stdout, "m.m[%d][%d]: %.6f    ", i, j, m.m[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

const void logQuat(const Quat q) {
    fprintf(stdout, "w: %f  v[x: %f, y: %f, z: %f]\n", q.w, q.v.x, q.v.y, q.v.z);
}

const void logEvent(const XEvent e) {
    fprintf(stdout, "event.type: %d\n", e.type);
}

