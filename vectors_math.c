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
BackFace sort_triangles(BackFace *c) {

    Triangle temp = { 0 };
    int pos = 0;

    for (int i = 0; i < c->indexes; i++) {
        
        for (int j = pos; j < c->indexes; j++) {

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
const float len_vec(const Vector v) {
    return sqrtf(dot_product(v, v));
}
/* Normalizes a Vector so he ranges from 0 to 1.Returns a new Vector. */
const Vector norm_vec(const Vector v) {
    float len = len_vec(v);
    Vector res = { v.x / len, v.y / len, v.z / len };
    return res;
}
/* Multiplies a Vector by the given num.Returns a new Vector. */
const Vector multiply_vec(const Vector v1, const float num) {
    Vector res =  { v1.x * num, v1.y * num, v1.z * num };
    return res;
}
/* Divides a Vector by the given num.Returns a new Vector. */
const Vector divide_vec(const Vector v1, const float num) {
    Vector res =  { v1.x / num, v1.y / num, v1.z / num };
    return res;
}
/* Adits two Vectors.Returns a new Vector. */
const Vector add_vecs(const Vector v1, const Vector v2) {
    Vector res =  { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return res;
}
/* Subtracts two Vectors.Returns a new Vector. */
const Vector sub_vecs(const Vector v1, const Vector v2) {
    Vector res = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return res;
}
/* Computes the Cross Product of two given Vectors.Returns a new Vector. */ 
const Vector cross_product(const Vector v1, const Vector v2) {
    Vector cp;
    cp.x = v1.y * v2.z - v1.z * v2.y;
    cp.y = v1.z * v2.x - v1.x * v2.z;
    cp.z = v1.x * v2.y - v1.y * v2.x;
    return cp;
}
/* Computes the Dot Product of two given Vectors.Returns a new Vector. */
float dot_product(const Vector v1, const Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
/* Computes the Cross Product of a given Triangle.Returns a Vector which represents the Cross Product. */
const Vector triangle_cp(const Triangle t) {
    Vector cp, line1, line2;
    line1 = sub_vecs(t.v[1], t.v[0]);
    line2 = sub_vecs(t.v[2], t.v[0]);

    cp = cross_product(line1, line2);
    return cp;
}

