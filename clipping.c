#include "header_files/clipping.h"

/* These headers must be removed when clipping is implemented and working correctly */
#include <stdio.h>
#include <stdlib.h>

void clipp(BackFace *bf) {

    Vector plane_p = { 0.0f, 0.0f, 0.5f },
           plane_n = { 0.0f, 0.0f, 1.0f };

    int clipped_count = 0;
    Triangle clipped[2] = { { {{ 0 }} }, { {{ 0 }} } };
    for (int i = 0; i < bf->indexes; i++) {
        clipped_count = clipp_triangle(plane_n, plane_p, bf->t[i], &clipped[0], &clipped[1]);

        if (clipped_count == 1) {
            bf->t[i] = clipped[0];
        } else if (clipped_count == 2) {
            bf->t = realloc(bf->t, sizeof(Triangle) * (bf->indexes + 1));
            bf->t[i] = clipped[0]; 
            bf->t[i + 1] = clipped[1];
            i++;     
        }
        printf("Clipped_count: %d\n", clipped_count);
    }
}

Vector plane_intersect(Vector plane_n, Vector plane_p, Vector line_start, Vector line_end) {

    plane_n = norm_vec(plane_n);
    float plane_d = -dot_product(plane_n, plane_p);
    float ad = dot_product(line_start, plane_n);
    float bd = dot_product(line_end, plane_n);
    float t = ((-plane_d - ad) / (bd - ad));
    Vector line_ste = sub_vecs(line_end, line_start);
    Vector line_ti = multiply_vec(line_ste, t);

    return add_vecs(line_start, line_ti);
}
/* Return signed shortest distance from point to plane, plane normal must be normalised. */
float dist(Vector plane_p, Vector plane_n, Vector v) {

    // v = norm_vec(v);
    return (plane_n.x * v.x + plane_n.y * v.y + plane_n.z * v.z - dot_product(plane_n, plane_p));
}

int clipp_triangle(Vector plane_p, Vector plane_n, Triangle in_t, Triangle *out_t1, Triangle *out_t2) {

    // Make sure plane normal is indeed normal.
    plane_n = norm_vec(plane_n);

    // Create two temporary storage arrays to classify points either side of plane
    // If distance sign is positive, point lies on "inside" of plane.
    Vector inside_points[3];     int inside_count = 0;
    Vector outside_points[3];    int outside_count = 0;

    // Get signed distance of each point in triangle to plane.
    float d0 = dist(plane_p, plane_n, in_t.v[0]);
    float d1 = dist(plane_p, plane_n, in_t.v[1]);
    float d2 = dist(plane_p, plane_n, in_t.v[2]);

    if (d0 >= 0)
        inside_points[inside_count++] = in_t.v[0];
    else
        outside_points[outside_count++] = in_t.v[0];
    if (d1 >= 0)
        inside_points[inside_count++] = in_t.v[1];
    else
        outside_points[outside_count++] = in_t.v[1];
    if (d2 >= 0)
        inside_points[inside_count++] = in_t.v[2];
    else
        outside_points[outside_count++] = in_t.v[2];

    // Now classify triangle points, and break the input triangle into 
    // smaller output triangles if required. There are four possible
    // outcomes...
    if (inside_count == 0) {
        // All points lie on the outside of plane, so clip whole triangle
        // It ceases to exist

        return 0; // No returned triangles are valid
    } else if (inside_count == 3) {
        // All points lie on the inside of plane, so do nothing
        // and allow the triangle to simply pass through
        *out_t1 = in_t;

        return 1; // Just the one returned original triangle is valid
    } else if (inside_count == 1 && outside_count == 2) {
        // Triangle should be clipped. As two points lie outside
        // the plane, the triangle simply becomes a smaller triangle

        // Copy appearance info to new triangle
        out_t1->col =  in_t.col;
        out_t1->sym = in_t.sym;

        // The inside point is valid, so keep that...
        out_t1->v[0] = inside_points[0];

        // but the two new points are at the locations where the 
        // original sides of the triangle (lines) intersect with the plane
        out_t1->v[1] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0]);
        out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[1]);

        return 1; // Return the newly formed single triangle
    } else if (inside_count == 2 && outside_count == 1) {
        // Triangle should be clipped. As two points lie inside the plane,
        // the clipped triangle becomes a "quad". Fortunately, we can
        // represent a quad with two new triangles

        // Copy appearance info to new triangles
        out_t1->col =  in_t.col;
        out_t1->sym = in_t.sym;

        out_t2->col =  in_t.col;
        out_t2->sym = in_t.sym;

        // The first triangle consists of the two inside points and a new
        // point determined by the location where one side of the triangle
        // intersects with the plane
        out_t1->v[0] = inside_points[0];
        out_t1->v[1] = inside_points[1];
        out_t1->v[2] = plane_intersect(plane_p, plane_n, inside_points[0], outside_points[0]);

        // The second triangle is composed of one of he inside points, a
        // new point determined by the intersection of the other side of the 
        // triangle and the plane, and the newly created point above
        out_t2->v[0] = inside_points[1];
        out_t2->v[1] = out_t1->v[2];
        out_t2->v[2] = plane_intersect(plane_p, plane_n, inside_points[1], outside_points[0]);

        return 2; // Return two newly formed triangles which form a quad
    }
    return 0;
}
