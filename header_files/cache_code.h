/* Triangles must be checked for cross product. */
// Mesh bf = bfculling(cache);
// free(cache.t);
// if (!bf.indexes) {
//     free(bf.t);
//     return;
// }

/* Backface culling.Discarding Triangles that should not be painted.Creating a new dynamic Mesh stucture Triangles array. */
const static Mesh bfculling(const Mesh c) {
    Mesh r = { 0 };
    Triangle temp;
    Vector cp;
    float dpc;//, dpl;
    int counter = 1;
    int index = 0;
    r.t = malloc(sizeof(Triangle));
    if (!r.t)
        fprintf(stderr, "Could not allocate memory - bfculling() - malloc\n");

    for (int i = 0; i < c.indexes; i++) {
        temp = c.t[i];
        for (int j = 0; j < 3; j++) {

            if ( c.t[i].v[j].w > 0.00 ) {
                temp.v[j].x /= temp.v[j].w;
                temp.v[j].y /= temp.v[j].w;
                temp.v[j].z /= temp.v[j].w;
            }
        }
        cp = triangle_cp(temp);
        dpc = dot_product(norm_vec(Camera), norm_vec(cp));
        // dpl = dot_product(norm_vec(LightSC), norm_vec(cp));
        if (dpc > 0.00) {
            r.t = realloc(r.t, sizeof(Triangle) * counter);

            if (!r.t)
                fprintf(stderr, "Could not allocate memory - bfculling() - realloc\n");

            r.t[index] = c.t[i];

            // if (dpl < 0.00)
            //     r.t[index].color = 0xff00fb;

            counter++;
            index++;
        }
    }
    r.indexes = index;
    return r;
}