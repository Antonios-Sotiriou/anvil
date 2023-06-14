#include "header_files/grfk_pipeline.h"

enum { Pos, U, V, N, C};
extern int HALFH, HALFW, DEBUG;
extern float NPlane, FPlane;
extern Vec4 light[];
extern Mat4x4 OrthoMat, LightMat, WorldMat, ViewMat;
extern XWindowAttributes wa;

const void shadowPipeline(Scene s) {
    Mat4x4 lm = lookat(light[Pos], light[U], light[V], light[N]);
    Mat4x4 Lview = inverse_mat(lm);
    LightMat = mxm(Lview, OrthoMat);

    for (int i = 0; i < s.indexes; i++) {

        Mesh cache = meshxm(s.m[i], LightMat);

        /* At this Point triangles must be clipped against near plane. */
        Vec4 plane_near_p = { 0.0, 0.0, NPlane },
            plane_near_n = { 0.0, 0.0, 1.0 };
        Mesh nf = clipp(cache, plane_near_p, plane_near_n);

        if (nf.t_indexes) {
            /* Applying Backface culling before we proceed to full frustum clipping. */
            Mesh bf = shadowcull(nf);

            /* Sending to translation from NDC to Screen Coordinates. */
            Mesh uf = viewtoscreen(bf);

            createShadowmap(uf);
            free(uf.t);
            free(uf.v);
        } else {
            free(nf.t);
            free(nf.v);
        }
    }
}
const void grfkPipeLine(Scene s) {

    for (int i = 0; i < s.indexes; i++) {

        Mesh cache = meshxm(s.m[i], WorldMat);

        /* Transform normals in View Space before clipping and perspective division. */
        normalsxm(&cache, ViewMat);

        /* At this Point triangles must be clipped against near plane. */
        Vec4 plane_near_p = { 0.0, 0.0, NPlane },
            plane_near_n = { 0.0, 0.0, 1.0 };
        Mesh nf = clipp(cache, plane_near_p, plane_near_n);

        /* Applying perspective division. */
        if (nf.t_indexes) {
            ppdiv(&nf);

            /* Applying Backface culling before we proceed to full frustum clipping. */
            Mesh bf = bfculling(nf);

            /* Sending to translation from NDC to Screen Coordinates. */
            Mesh uf = viewtoscreen(bf);

            rasterize(uf);
            free(uf.t);
            free(uf.v);
        } else {
            free(nf.t);
            free(nf.v);
        }
    }
} // ##############################################################################################################################################
/* Perspective division. */
const void ppdiv(Mesh *c) {

    for (int i = 0; i < c->t_indexes; i++) {
        for (int j = 0; j < 3; j++) {
            if ( c->t[i].v[j].w > 0.00 ) {
                c->t[i].v[j].x /= c->t[i].v[j].w;
                c->t[i].v[j].y /= c->t[i].v[j].w;
                c->t[i].v[j].z /= c->t[i].v[j].w;
            }
        }
    }
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic Mesh stucture Triangles array. */
const static Mesh shadowcull(const Mesh c) {
    Mesh r = c;
    Vec4 cp;
    float dpc;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.t_indexes; i++) {
        dpc = winding3D(c.t[i]);

        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];

            counter++;
            index++;
        }
    }
    r.t_indexes = index;
    free(c.t);
    return r;
}
/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic Mesh stucture Triangles array. */
const static Mesh bfculling(const Mesh c) {
    Mesh r = c;
    Vec4 cp;
    float dpc;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.t_indexes; i++) {
        dpc = winding3D(c.t[i]);

        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];

            counter++;
            index++;
        }
    }
    r.t_indexes = index;
    free(c.t);
    return r;
}
/* Translates the Mesh's Triangles from world to Screen Coordinates. */
const static Mesh viewtoscreen(const Mesh c) {
    float w = 0.0;
    for (int i = 0; i < c.t_indexes; i++) {
        for (int j = 0; j < 3; j++) {
            w = c.t[i].v[j].w;
            c.t[i].v[j].x = (++c.t[i].v[j].x) * HALFW;
            c.t[i].v[j].y = (++c.t[i].v[j].y) * HALFH;
            c.t[i].v[j].z *= 0.5;//( (1 / c.t[i].v[j].z) - (1 / ZNear) ) / ( (1 / ZFar) - (1 / ZNear) );//(c.t[i].v[j].z - ZNear) / (ZFar - ZNear);
            c.t[i].v[j].w = 1 / w;

            c.t[i].vt[j].u /= w;
            c.t[i].vt[j].v /= w;
            c.t[i].vt[j].w = c.t[i].v[j].w;
        }
    }

    /* Far Plane clipping and side clipping. */
    Vec4 plane_far_p = { 0.0, 0.0, FPlane },
           plane_far_n = { 0.0, 0.0, 1.0 };
    Mesh ff = clipp(c, plane_far_p, plane_far_n);

    // if (DEBUG == 1) {
        Vec4 plane_right_p = { wa.width - 1.0, 0.0, 0.0 },
            plane_right_n = { -1.0, 0.0, 0.0 };
        Mesh rf = clipp(ff, plane_right_p, plane_right_n);

        Vec4 plane_down_p = { 0.0, wa.height - 1.0, 0.0 },
            plane_down_n = { 0.0, -1.0, 0.0 };
        Mesh df = clipp(rf, plane_down_p, plane_down_n);

        Vec4 plane_left_p = { 0.0, 0.0, 0.0 },
            plane_left_n = { 1.0, 0.0, 0.0 };
        Mesh lf = clipp(df, plane_left_p, plane_left_n);

        Vec4 plane_up_p = { 0.0, 0.0, 0.0 },
            plane_up_n = { 0.0, 1.0, 0.0 };
        Mesh uf = clipp(lf, plane_up_p, plane_up_n);
        return uf;
    // }
    // return ff;
}
/* Rasterize given Mesh by passing them to the appropriate function. */
const static void rasterize(const Mesh c) {
    signed int tex_h = c.texture_height - 1;
    signed int tex_w = c.texture_width - 1;

    for (int i = 0; i < c.t_indexes; i++) {

        if (DEBUG == 1) {
            drawLine(c.t[i].v[0].x, c.t[i].v[0].y, c.t[i].v[1].x, c.t[i].v[1].y, 255, 0, 0);
            drawLine(c.t[i].v[1].x, c.t[i].v[1].y, c.t[i].v[2].x, c.t[i].v[2].y, 255, 0, 0);
            drawLine(c.t[i].v[2].x, c.t[i].v[2].y, c.t[i].v[0].x, c.t[i].v[0].y, 255, 0, 0);
        } else if (DEBUG == 2) {
            // clock_t start_time = start();
            fillTriangle(c.t[i]);
            // end(start_time);
        } else {
            // clock_t start_time = start();
            texTriangle(c.t[i], c.texels, tex_h, tex_w);
            // end(start_time);
        }
    }
}

