#include "header_files/clipping.h"

const Mesh clipp(const Mesh c, vec4 plane_p, vec4 plane_n) {

    Mesh r = c;
    r.t = malloc(sizeof(Triangle) * c.t_indexes);
    int index = 0;
    int dynamic_inc = 1;

    int clipped_count = 0;
    Triangle clipped[2];
    for (int i = 0; i < c.t_indexes; i++) {

        clipped_count = clipp_triangle(plane_p, plane_n, c.t[i], &clipped[0], &clipped[1]);

        if (clipped_count) {
            
            if (clipped_count == 1) {
                r.t[index] = clipped[0];
                index++;
            } else if (clipped_count == 2) {
                r.t = realloc(r.t, sizeof(Triangle) * (c.t_indexes + dynamic_inc));
                r.t[index] = clipped[0];

                r.t[index + 1] = clipped[1];
                index += 2;
                dynamic_inc++;
            } else if (clipped_count == 3) {
                r.t[index] = c.t[i];
                index++;
            }
        }
    }
    r.t_indexes = index;
    free(c.t);
    return r;
}

const vec4 plane_intersect(vec4 plane_p, vec4 plane_n, vec4 line_start, vec4 line_end, float *t) {
    float plane_d = -dot_product(plane_n, plane_p);
    float ad = dot_product(line_start, plane_n);
    float bd = dot_product(line_end, plane_n);
    *t = ((-plane_d - ad) / (bd - ad));
    vec4 line_ste = sub_vecs(line_end, line_start);
    vec4 line_ti = multiply_vec(line_ste, *t);

    return add_vecs(line_start, line_ti);
}
/* Return signed shortest distance from point to plane, plane normal must be normalised. */
float dist(vec4 plane_p, vec4 plane_n, vec4 v) {
    return ( ((plane_n.x * v.x) + (plane_n.y * v.y) + (plane_n.z * v.z)) - dot_product(plane_n, plane_p) );
}

int clipp_triangle(vec4 plane_p, vec4 plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2) {

    vec4 inside_points[3];     int inside_count = 0;
    vec4 outside_points[3];    int outside_count = 0;
    Textor inside_vt[3];
    Textor outside_vt[3];
    vec4 inside_vn[3];
    vec4 outside_vn[3];

    // Get signed distance of each point in triangle to plane.
    float d0 = dist(plane_p, plane_n, in_t.v[0]);
    float d1 = dist(plane_p, plane_n, in_t.v[1]);
    float d2 = dist(plane_p, plane_n, in_t.v[2]);

    if (d0 >= 0) {
        inside_points[inside_count] = in_t.v[0];
        inside_vt[inside_count] = in_t.vt[0];
        inside_vn[inside_count] = in_t.vn[0];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[0];
        outside_vt[outside_count] = in_t.vt[0];
        outside_vn[outside_count] = in_t.vn[0];
        outside_count++;
    }
    if (d1 >= 0) {
        inside_points[inside_count] = in_t.v[1];
        inside_vt[inside_count] = in_t.vt[1];
        inside_vn[inside_count] = in_t.vn[1];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[1];
        outside_vt[outside_count] = in_t.vt[1];
        outside_vn[outside_count] = in_t.vn[1];
        outside_count++;
    }
    if (d2 >= 0) {
        inside_points[inside_count] = in_t.v[2];
        inside_vt[inside_count] = in_t.vt[2];
        inside_vn[inside_count] = in_t.vn[2];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[2];
        outside_vt[outside_count] = in_t.vt[2];
        outside_vn[outside_count] = in_t.vn[2];
        outside_count++;
    }

    float t;
    if (inside_count == 0) {
        return 0; /* Triangle is outside and must be ignored. */
    } else if (inside_count == 3) {
        return 3; /* Triangle is inside and it needs no clipping. */
    } else if (inside_count == 1 && outside_count == 2) {
        out_t1->v[0] = inside_points[0];
        out_t1->vt[0] = inside_vt[0];
        out_t1->vn[0] = inside_vn[0];

        if ( len_vec(inside_points[0]) == len_vec(in_t.v[1]) ) {
            out_t1->v[1] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[1], &t);
            out_t1->v[1].w = inside_points[0].w + (t * (outside_points[1].w - inside_points[0].w));
            out_t1->vt[1].u = inside_vt[0].u + (t * (outside_vt[1].u - inside_vt[0].u));
            out_t1->vt[1].v = inside_vt[0].v + (t * (outside_vt[1].v - inside_vt[0].v));
            out_t1->vt[1].w = inside_vt[0].w + (t * (outside_vt[1].w - inside_vt[0].w));

            out_t1->vn[1].x = inside_vn[0].x + (t * (outside_vn[1].x - inside_vn[0].x));
            out_t1->vn[1].y = inside_vn[0].y + (t * (outside_vn[1].y - inside_vn[0].y));
            out_t1->vn[1].z = inside_vn[0].z + (t * (outside_vn[1].z - inside_vn[0].z));

            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[2].w = inside_points[0].w + (t * (outside_points[0].w - inside_points[0].w));
            out_t1->vt[2].u = inside_vt[0].u + (t * (outside_vt[0].u - inside_vt[0].u));
            out_t1->vt[2].v = inside_vt[0].v + (t * (outside_vt[0].v - inside_vt[0].v));
            out_t1->vt[2].w = inside_vt[0].w + (t * (outside_vt[0].w - inside_vt[0].w));

            out_t1->vn[2].x = inside_vn[0].x + (t * (outside_vn[0].x - inside_vn[0].x));
            out_t1->vn[2].y = inside_vn[0].y + (t * (outside_vn[0].y - inside_vn[0].y));
            out_t1->vn[2].z = inside_vn[0].z + (t * (outside_vn[0].z - inside_vn[0].z));
        } else {
            out_t1->v[1] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[1].w = inside_points[0].w + (t * (outside_points[0].w - inside_points[0].w));
            out_t1->vt[1].u = inside_vt[0].u + (t * (outside_vt[0].u - inside_vt[0].u));
            out_t1->vt[1].v = inside_vt[0].v + (t * (outside_vt[0].v - inside_vt[0].v));
            out_t1->vt[1].w = inside_vt[0].w + (t * (outside_vt[0].w - inside_vt[0].w));

            out_t1->vn[1].x = inside_vn[0].x + (t * (outside_vn[0].x - inside_vn[0].x));
            out_t1->vn[1].y = inside_vn[0].y + (t * (outside_vn[0].y - inside_vn[0].y));
            out_t1->vn[1].z = inside_vn[0].z + (t * (outside_vn[0].z - inside_vn[0].z));

            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[1], &t);
            out_t1->v[2].w = inside_points[0].w + (t * (outside_points[1].w - inside_points[0].w));
            out_t1->vt[2].u = inside_vt[0].u + (t * (outside_vt[1].u - inside_vt[0].u));
            out_t1->vt[2].v = inside_vt[0].v + (t * (outside_vt[1].v - inside_vt[0].v));
            out_t1->vt[2].w = inside_vt[0].w + (t * (outside_vt[1].w - inside_vt[0].w));

            out_t1->vn[2].x = inside_vn[0].x + (t * (outside_vn[1].x - inside_vn[0].x));
            out_t1->vn[2].y = inside_vn[0].y + (t * (outside_vn[1].y - inside_vn[0].y));
            out_t1->vn[2].z = inside_vn[0].z + (t * (outside_vn[1].z - inside_vn[0].z));
        }
        out_t1->fn = in_t.fn;
        return 1; /* A new Triangle is created. */
    } else if (inside_count == 2 && outside_count == 1) {
        if ( len_vec(outside_points[0]) == len_vec(in_t.v[1]) ) {
            out_t1->v[0] = inside_points[1];
            out_t1->vt[0] = inside_vt[1];
            out_t1->vn[0] = inside_vn[1];

            out_t1->v[1] = inside_points[0];
            out_t1->vt[1] = inside_vt[0];
            out_t1->vn[1] = inside_vn[0];

            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[2].w = inside_points[0].w + (t * (outside_points[0].w - inside_points[0].w));
            out_t1->vt[2].u = inside_vt[0].u + (t * (outside_vt[0].u - inside_vt[0].u));
            out_t1->vt[2].v = inside_vt[0].v + (t * (outside_vt[0].v - inside_vt[0].v));
            out_t1->vt[2].w = inside_vt[0].w + (t * (outside_vt[0].w - inside_vt[0].w));

            out_t1->vn[2].x = inside_vn[0].x + (t * (outside_vn[0].x - inside_vn[0].x));
            out_t1->vn[2].y = inside_vn[0].y + (t * (outside_vn[0].y - inside_vn[0].y));
            out_t1->vn[2].z = inside_vn[0].z + (t * (outside_vn[0].z - inside_vn[0].z));

            out_t2->v[0] = plane_intersect(plane_p, plane_n, inside_points[1], outside_points[0], &t);
            out_t2->v[0].w = inside_points[1].w + (t * (outside_points[0].w - inside_points[1].w));
            out_t2->vt[0].u = inside_vt[1].u + (t * (outside_vt[0].u - inside_vt[1].u));
            out_t2->vt[0].v = inside_vt[1].v + (t * (outside_vt[0].v - inside_vt[1].v));
            out_t2->vt[0].w = inside_vt[1].w + (t * (outside_vt[0].w - inside_vt[1].w));

            out_t2->vn[0].x = inside_vn[1].x + (t * (outside_vn[0].x - inside_vn[1].x));
            out_t2->vn[0].y = inside_vn[1].y + (t * (outside_vn[0].y - inside_vn[1].y));
            out_t2->vn[0].z = inside_vn[1].z + (t * (outside_vn[0].z - inside_vn[1].z));

            out_t2->v[1] = inside_points[1];
            out_t2->vt[1] = inside_vt[1];
            out_t2->vn[1] = inside_vn[1];

            out_t2->v[2] = out_t1->v[2];
            out_t2->vt[2] = out_t1->vt[2];
            out_t2->vn[2] = out_t1->vn[2];
        } else {
            out_t1->v[0] = inside_points[0];
            out_t1->vt[0] = inside_vt[0];
            out_t1->vn[0] = inside_vn[0];

            out_t1->v[1] = inside_points[1];
            out_t1->vt[1] = inside_vt[1];
            out_t1->vn[1] = inside_vn[1];

            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[1], outside_points[0], &t);
            out_t1->v[2].w = inside_points[1].w + (t * (outside_points[0].w - inside_points[1].w));
            out_t1->vt[2].u = inside_vt[1].u + (t * (outside_vt[0].u - inside_vt[1].u));
            out_t1->vt[2].v = inside_vt[1].v + (t * (outside_vt[0].v - inside_vt[1].v));
            out_t1->vt[2].w = inside_vt[1].w + (t * (outside_vt[0].w - inside_vt[1].w));

            out_t1->vn[2].x = inside_vn[1].x + (t * (outside_vn[0].x - inside_vn[1].x));
            out_t1->vn[2].y = inside_vn[1].y + (t * (outside_vn[0].y - inside_vn[1].y));
            out_t1->vn[2].z = inside_vn[1].z + (t * (outside_vn[0].z - inside_vn[1].z));

            out_t2->v[0] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t2->v[0].w = inside_points[0].w + (t * (outside_points[0].w - inside_points[0].w));
            out_t2->vt[0].u = inside_vt[0].u + (t * (outside_vt[0].u - inside_vt[0].u));
            out_t2->vt[0].v = inside_vt[0].v + (t * (outside_vt[0].v - inside_vt[0].v));
            out_t2->vt[0].w = inside_vt[0].w + (t * (outside_vt[0].w - inside_vt[0].w));

            out_t2->vn[0].x = inside_vn[0].x + (t * (outside_vn[0].x - inside_vn[0].x));
            out_t2->vn[0].y = inside_vn[0].y + (t * (outside_vn[0].y - inside_vn[0].y));
            out_t2->vn[0].z = inside_vn[0].z + (t * (outside_vn[0].z - inside_vn[0].z));

            out_t2->v[1] = inside_points[0];
            out_t2->vt[1] = inside_vt[0];
            out_t2->vn[1] = inside_vn[0];

            out_t2->v[2] = out_t1->v[2];
            out_t2->vt[2] = out_t1->vt[2];
            out_t2->vn[2] = out_t1->vn[2];
        }
        out_t1->fn = in_t.fn;
        out_t2->fn = in_t.fn;
        return 2; /* Two new Triangles are created. */
    }
    return 0;
}

