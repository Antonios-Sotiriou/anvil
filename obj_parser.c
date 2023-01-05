#include "header_files/obj_parser.h"

static Face *get_faces(const char path[]);
static Vector *get_vectors(const char path[]);
static Textor *get_textors(const char path[]);
static Vector *get_normals(const char path[]);

/* Face array indexes */
static int f_indexes = 0;

void load_obj(Mesh *c, const char path[]) {

    Face *f = get_faces(path);
    if (!f)
        fprintf(stderr, "Could not create Faces array. load_obj() - get_faces()\n");

    Vector *v = get_vectors(path);
    if (!v)
        fprintf(stderr, "Could not create Vectors array. load_obj() - get_vectors()\n");

    Textor *tex = get_textors(path);
    if (!tex)
        fprintf(stderr, "Could not create Vectors array. load_obj() - get_textors()\n");

    Vector *n = get_normals(path);
    if (!n)
        fprintf(stderr, "Could not create Vectors array. load_obj() - get_normals()\n");

    c->indexes = f_indexes;
    c->t = malloc(sizeof(Triangle) * f_indexes);
    if (!c->t)
        fprintf(stderr, "Could not allocate memory for Triangles array. load_obj()\n");

    /* Assign the Faces of the Vectors to the Mesh triangle array creating the final object. */
    for (int i = 0; i < c->indexes; i++) {
        c->t[i].v[0] = v[f[i].va - 1];
        c->t[i].v[1] = v[f[i].vb - 1];
        c->t[i].v[2] = v[f[i].vc - 1];

        if (tex != NULL) {
            c->t[i].tex[0] = tex[f[i].ta - 1];
            c->t[i].tex[1] = tex[f[i].tb - 1];
            c->t[i].tex[2] = tex[f[i].tc - 1];
        }

        if (n != NULL)
            c->t[i].normal = n[f[i].na - 1];            
    }
    
    /* Free The Vectors and Faces arrays here cause they are not gonna be used anywhere else.Mesh must be freed some levels above.When program quits. */
    free(v);
    free(tex);
    free(n);
    free(f);
}
static Face *get_faces(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Face *f = { 0 };
    f = malloc(sizeof(Face));
    if (!f) {
        fprintf(stderr, "Could not allocate memory for Face struct. load_obj() -- malloc().\n");
        fclose(fp);
        return NULL;
    }
    int dynamic_inc = 1;
    int index = 0;

    char ch;
    /* v* Vector, t* Textor, n* Normal */
    int va, vb, vc, ta, tb, tc, na, nb, nc;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'f' )
            if ( (ch = getc(fp)) == ' ' )
                if (fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &va, &ta, &na, &vb, &tb, &nb, &vc, &tc, &nc) == 9){

                    f = realloc(f, sizeof(Face) * dynamic_inc);
                    if (!f) {
                        fprintf(stderr, "Could not reallocate memory for Face struct array. load_obj() -- realloc().\n");
                        fclose(fp);
                        free(f);
                        return NULL;
                    }

                    f[index].va = va;
                    f[index].ta = ta;
                    f[index].na = na;
                    f[index].vb = vb;
                    f[index].tb = tb;
                    f[index].nb = nb;
                    f[index].vc = vc;
                    f[index].tc = tc;
                    f[index].nc = nc;

                    index++;
                    dynamic_inc++;
                }
    }
    f_indexes = index;
    fclose(fp);
    return f;
}
static Vector *get_vectors(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Vector *v = { 0 };
    v = malloc(sizeof(Vector));
    if (!v) {
        fprintf(stderr, "Could not allocate memory for Vector struct. get_vectors() -- calloc().\n");
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
                    v[index].z = -1 * tempz;
                    v[index].w = 1.00;

                    index++;
                    dynamic_inc++;
                }
    }

    fclose(fp);
    return v;
}
static Textor *get_textors(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Textor *tex = { 0 };
    tex = malloc(sizeof(Textor));
    if (!tex) {
        fprintf(stderr, "Could not allocate memory for Textor struct. get_textors() -- calloc().\n");
        fclose(fp);
        return NULL;
    }

    int dynamic_inc = 1;
    int index = 0;
    char ch;
    float tempu, tempv;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'v' )
            if ( (ch = getc(fp)) == 't' )
                if ( (ch = getc(fp)) == ' ' )
                    if (fscanf(fp, "%f %f", &tempu, &tempv) == 2) {

                        tex = realloc(tex, sizeof(Textor) * dynamic_inc);
                        if (!tex) {
                            fprintf(stderr, "Could not reallocate memory for Vector struct array. get_textors() -- realloc().\n");
                            fclose(fp);
                            free(tex);
                            return NULL;
                        }

                        tex[index].u = tempu;
                        tex[index].v = tempv;
                        tex[index].w = 1.0;

                        index++;
                        dynamic_inc++;
                    }
    }

    fclose(fp);
    return tex;
}
static Vector *get_normals(const char path[]) {

    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return NULL;
    }

    Vector *n = { 0 };
    n = malloc(sizeof(Vector));
    if (!n) {
        fprintf(stderr, "Could not allocate memory for Textor struct. get_normals() -- calloc().\n");
        fclose(fp);
        return NULL;
    }

    int dynamic_inc = 1;
    int index = 0;
    char ch;
    float tempx, tempy, tempz;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'v' )
            if ( (ch = getc(fp)) == 'n' )
                if ( (ch = getc(fp)) == ' ' )
                    if (fscanf(fp, "%f %f %f", &tempx, &tempy, &tempz) == 3) {

                        n = realloc(n, sizeof(Vector) * dynamic_inc);
                        if (!n) {
                            fprintf(stderr, "Could not reallocate memory for Vector struct array. load_obj() -- realloc().\n");
                            fclose(fp);
                            free(n);
                            return NULL;
                        }
       
                        n[index].x = tempx;
                        n[index].y = tempy;
                        n[index].z = tempz;
                        n[index].w = 1.00;

                        index++;
                        dynamic_inc++;
                    }
    }

    fclose(fp);
    return n;
}
