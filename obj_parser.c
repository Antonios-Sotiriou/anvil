#include "header_files/obj_parser.h"

static Vector *get_vectors(const char path[]);
static Face *get_faces(const char path[]);

/* Vector and Face arrays indexes */
static int v_indexes = 0;
static int f_indexes = 0;

void load_obj(Mesh *c, const char path[]) {

    Vector *v = get_vectors(path);
    if (!v)
        fprintf(stderr, "Could not create Vectors array. load_obj() - get_vectors()\n");

    Face *f = get_faces(path);
    if (!f)
        fprintf(stderr, "Could not create Faces array. load_obj() - get_faces()\n");

    c->indexes = f_indexes;
    c->t = malloc(sizeof(Triangle) * f_indexes);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for Triangles array. load_obj()\n");

    /* Assign the Faces of the Vectors to the Mesh triangle array creating the final object. */
    for (int i = 0; i < c->indexes; i++) {
        c->t[i].v[0] = v[f[i].a - 1];    c->t[i].v[0].w = 1.00;
        c->t[i].v[1] = v[f[i].b - 1];    c->t[i].v[1].w = 1.00;
        c->t[i].v[2] = v[f[i].c - 1];    c->t[i].v[2].w = 1.00;
        c->t[i].color = 0xa517a2;
    }
    
    /* Free The Vectors and Faces arrays here cause they are not gonna be used anywhere else.Mesh must be freed some levels above.When program quits. */
    free(v);
    free(f);
}
static Vector *get_vectors(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Vector *v;
    v = malloc(sizeof(Vector));
    if (!v) {
        fprintf(stderr, "Could not allocate memory for Vector struct. load_obj() -- malloc().\n");
        fclose(fp);
        return NULL;
    }

    int dynamic_inc = 1;
    int index = 0;
    char ch;
    float tempx, tempy, tempz;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'v' )
            if ( (ch = getc(fp)) == ' ' )
                if (fscanf(fp, "%f %f %f", &tempx, &tempy, &tempz) == 3) {

                    v = realloc(v, sizeof(Vector) * dynamic_inc);
                    if (!v) {
                        fprintf(stderr, "Could not reallocate memory for Vector struct array. load_obj() -- realloc().\n");
                        fclose(fp);
                        free(v);
                        return NULL;
                    }

                    v[index].x = tempx;
                    v[index].y = tempy;
                    v[index].z = tempz;

                    index++;
                    dynamic_inc++;
                }
    }
    v_indexes = index;
    fclose(fp);
    return v;
}
static Face *get_faces(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Face *f;
    f = malloc(sizeof(Face));
    if (!f) {
        fprintf(stderr, "Could not allocate memory for Face struct. load_obj() -- malloc().\n");
        fclose(fp);
        return NULL;
    }
    int dynamic_inc = 1;
    int index = 0;

    char ch;
    int tempa, tempb, tempc;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'f' )
            if ( (ch = getc(fp)) == ' ' )
                if (fscanf(fp, "%d %d %d", &tempa, &tempb, &tempc) == 3){

                    f = realloc(f, sizeof(Face) * dynamic_inc);
                    if (!f) {
                        fprintf(stderr, "Could not reallocate memory for Face struct array. load_obj() -- realloc().\n");
                        fclose(fp);
                        free(f);
                        return NULL;
                    }

                    f[index].a = tempa;
                    f[index].b = tempb;
                    f[index].c = tempc;

                    index++;
                    dynamic_inc++;
                }
    }
    f_indexes = index;
    fclose(fp);
    return f;
}

