#include "header_files/vectors_math.h"

/* Computing the average of the Z values of the Triangle's Vectors.Returns the average float value. */
const float depth(const Triangle t) {
    float res = 0;
    for (int i = 0; i < 3; i++) {
        res += t.v[i].z;
    }
    return res / 3;
}
/* Sorts Mesh's Triangles according to Triangle's Vectors Z value average. */
Mesh sort_triangles(Mesh *c) {

    Triangle temp = { 0 };
    int pos = 0;

    for (int i = 0; i < c->t_indexes; i++) {
        
        for (int j = pos; j < c->t_indexes; j++) {

            if (depth(c->t[i]) > depth(c->t[j])) {
                temp = c->t[i];
                c->t[i] = c->t[j];
                c->t[j] = temp;
            }
        }
        pos++;
    }
    return *c;
}
/* Computes the length of a vector with the use of Pythagorean Theorem. */
const float len_vec(const vec4 v) {
    return sqrtf(dot_product(v, v));
}
/* Normalizes a vec4 so he ranges from 0 to 1.Returns a new vec4. */
const vec4 norm_vec(const vec4 v) {
    float len = len_vec(v);
    vec4 res = { v.x / len, v.y / len, v.z / len };
    return res;
}
/* Multiplies a vec4 by the given num.Returns a new vec4. */
const vec4 multiply_vec(const vec4 v1, const float num) {
    vec4 res =  { v1.x * num, v1.y * num, v1.z * num };
    return res;
}
/* Divides a vec4 by the given num.Returns a new vec4. */
const vec4 divide_vec(const vec4 v1, const float num) {
    vec4 res =  { v1.x / num, v1.y / num, v1.z / num };
    return res;
}
/* Adits two Vectors.Returns a new vec4. */
const vec4 add_vecs(const vec4 v1, const vec4 v2) {
    vec4 res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return res;
}
/* Subtracts two Vectors.Returns a new vec4. */
const vec4 sub_vecs(const vec4 v1, const vec4 v2) {
    vec4 res = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return res;
}
/* Computes the Cross Product of two given Vectors.Returns a new vec4. */ 
const vec4 cross_product(const vec4 v1, const vec4 v2) {
    vec4 cp;
    cp.x = v1.y * v2.z - v1.z * v2.y;
    cp.y = v1.z * v2.x - v1.x * v2.z;
    cp.z = v1.x * v2.y - v1.y * v2.x;
    return cp;
}
/* Computes the Dot Product of two given Vectors. */
float dot_product(const vec4 v1, const vec4 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
/* Computes the Cross Product of a given Triangle.Returns a vec4 which represents the Cross Product. */
const vec4 triangle_cp(const Triangle t) {
    vec4 cp, line1, line2;
    line1 = sub_vecs(t.v[1], t.v[0]);
    line2 = sub_vecs(t.v[2], t.v[0]);

    cp = cross_product(line1, line2);
    return cp;
}
/* Identifies if the Vectors of the given Triangle < t > are in clockwise order < CW > or not. */
const float winding3D(const Triangle t) {
    float step1, step2, step3;
    step1 = (t.v[0].x * t.v[1].y) - (t.v[0].y * t.v[1].x);
    step2 = (t.v[1].x * t.v[2].y) - (t.v[1].y * t.v[2].x);
    step3 = (t.v[2].x * t.v[0].y) - (t.v[2].y * t.v[0].x);
    return step1 + step2 + step3;
}
/* Identifies if the Vectors of the given Triangle < t > are in clockwise order < CW > or not. */
const float winding2D(const Triangle t) {
    float step1, step2, step3;
    step1 = (t.v[0].x * t.v[1].y) - (t.v[0].y * t.v[1].x);
    step2 = (t.v[1].x * t.v[2].y) - (t.v[1].y * t.v[2].x);
    step3 = (t.v[2].x * t.v[0].y) - (t.v[2].y * t.v[0].x);
    return step1 + step2 + step3;
}

