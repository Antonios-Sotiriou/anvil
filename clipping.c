#include "header_files/clipping.h"
#include "header_files/vectors_math.h"

Mesh clipp(Mesh bf, Vector plane_p, Vector plane_n) {

    Mesh r;
    r.t = malloc(sizeof(Triangle) * bf.indexes);
    int index = 0;
    int dynamic_inc = 1;

    int clipped_count = 0;
    Triangle clipped[2];
    for (int i = 0; i < bf.indexes; i++) {

        clipped_count = clipp_triangle(plane_p, plane_n, bf.t[i], &clipped[0], &clipped[1]);

        if (clipped_count) {
            
            if (clipped_count == 1) {
                r.t[index] = clipped[0];
                index++;
            } else if (clipped_count == 2) {
                r.t = realloc(r.t, sizeof(Triangle) * (bf.indexes + dynamic_inc));
                r.t[index] = clipped[0];

                r.t[index + 1] = clipped[1];
                index += 2;
                dynamic_inc++;
            } else if (clipped_count == 3) {
                r.t[index] = clipped[0];
                index++;
            }
        }
    }
    r.indexes = index;
    return r;
}

Vector plane_intersect(Vector plane_p, Vector plane_n, Vector line_start, Vector line_end, float *t) {

    float plane_d = -dot_product(plane_n, plane_p);
    float ad = dot_product(line_start, plane_n);
    float bd = dot_product(line_end, plane_n);
    *t = ((-plane_d - ad) / (bd - ad));
    Vector line_ste = sub_vecs(line_end, line_start);
    Vector line_ti = multiply_vec(line_ste, *t);

    return add_vecs(line_start, line_ti);
}
/* Return signed shortest distance from point to plane, plane normal must be normalised. */
float dist(Vector plane_p, Vector plane_n, Vector v) {

    return ( ((plane_n.x * v.x) + (plane_n.y * v.y) + (plane_n.z * v.z)) - dot_product(plane_n, plane_p) );
}

int clipp_triangle(Vector plane_p, Vector plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2) {

    Vector inside_points[3];     int inside_count = 0;
    Vector outside_points[3];    int outside_count = 0;

    // Get signed distance of each point in triangle to plane.
    float d0 = dist(plane_p, plane_n, in_t.v[0]);
    float d1 = dist(plane_p, plane_n, in_t.v[1]);
    float d2 = dist(plane_p, plane_n, in_t.v[2]);

    if (d0 >= 0) {
        inside_points[inside_count] = in_t.v[0];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[0];
        outside_count++;
    }
    if (d1 >= 0) {
        inside_points[inside_count] = in_t.v[1];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[1];
        outside_count++;
    }
    if (d2 >= 0) {
        inside_points[inside_count] = in_t.v[2];
        inside_count++;
    } else {
        outside_points[outside_count] = in_t.v[2];
        outside_count++;
    }

    float t;
    if (inside_count == 0) {
        return 0; /* Triangle is outside and must be ignored. */
    } else if (inside_count == 3) {
        *out_t1 = in_t;
        out_t1->normal = in_t.normal;
        return 3; /* Triangle is inside and it needs no clipping. */
    } else if (inside_count == 1 && outside_count == 2) {
        out_t1->v[0] = inside_points[0];

        if ( len_vec(inside_points[0]) == len_vec(in_t.v[1]) ) {
            out_t1->v[1] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[1], &t);
            out_t1->v[1].w = (inside_points[0].w * (1 - t)) + (outside_points[1].w * t);
            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[2].w = (inside_points[0].w * (1 - t)) + (outside_points[0].w * t);
        } else {
            out_t1->v[1] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[1].w = (inside_points[0].w * (1 - t)) + (outside_points[0].w * t);
            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[1], &t);
            out_t1->v[2].w = (inside_points[0].w * (1 - t)) + (outside_points[1].w * t);
        }
        out_t1->normal = in_t.normal;
        return 1; /* A new Triangle is created. */
    } else if (inside_count == 2 && outside_count == 1) {
        if ( len_vec(outside_points[0]) == len_vec(in_t.v[1]) ) {
            out_t1->v[0] = inside_points[1];
            out_t1->v[1] = inside_points[0];
            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t1->v[2].w = (inside_points[0].w * (1 - t)) + (outside_points[0].w * t);

            out_t2->v[0] = plane_intersect(plane_p, plane_n, inside_points[1], outside_points[0], &t);
            out_t2->v[0].w = (inside_points[1].w * (1 - t)) + (outside_points[0].w * t);
            out_t2->v[1] = inside_points[1];
            out_t2->v[2] = out_t1->v[2];
        } else {
            out_t1->v[0] = inside_points[0];
            out_t1->v[1] = inside_points[1];
            out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[1], outside_points[0], &t);
            out_t1->v[2].w = (inside_points[1].w * (1 - t)) + (outside_points[0].w * t);

            out_t2->v[0] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0], &t);
            out_t2->v[0].w = (inside_points[0].w * (1 - t)) + (outside_points[0].w * t);
            out_t2->v[1] = inside_points[0];
            out_t2->v[2] = out_t1->v[2];
        }
        out_t1->normal = in_t.normal;
        out_t2->normal = in_t.normal;
        return 2; /* Two new Triangles are created. */
    }
    return 0;
}

