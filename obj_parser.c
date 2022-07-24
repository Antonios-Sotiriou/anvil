#include "header_files/obj_parser.h"

Mesh load_obj(const char path[]) {

    Mesh c;
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file : %s.\n", path);
        return c;
    }
    printf("Reached this point\n");
    // c.t = malloc(sizeof(Triangle));
    if (!c.t) {
        fprintf(stderr, "Could not allocate memory for struct. load_obj() -- malloc().\n");
        fclose(fp);
        return c;
    }
    int dynamic_inc = 1;
    int t_index = 0;
    int v_index = 0;

    char ch;
    float tempx, tempy, tempz;

    while (!feof(fp)) {
        if ( (ch = getc(fp)) == 'v' )
            if ( (ch = getc(fp)) == ' ' )
                if (fscanf(fp, "%f %f %f", &tempx, &tempy, &tempz) == 3){

                    /* We must prevent no reason reallocations here. */
                    if (!v_index) {
                        // c.t = realloc(c.t, sizeof(Triangle) * dynamic_inc);
                        if (!c.t) {
                            fprintf(stderr, "Could not reallocate memory for struct. load_obj() -- realloc().\n");
                            fclose(fp);
                            free(c.t);
                            return c;
                        }
                    }

                    c.t[t_index].v[v_index].x = tempx;
                    c.t[t_index].v[v_index].y = tempy;
                    c.t[t_index].v[v_index].z = tempz;

                    v_index++;

                    if (v_index > 2) {
                        t_index++;
                        dynamic_inc++;
                        v_index = 0;
                    }
                }


        if ( (ch = getc(fp)) == 's' )
            if ( (ch = getc(fp)) == ' ' )
                printf("Offset\n");
    }

    c.indexes = t_index;
    fclose(fp);

    return c;
}

