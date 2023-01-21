#include "header_files/exec_time.h"

const clock_t start(void) {
    return clock();
}
const void end(const clock_t start_time) {
    clock_t end_time = clock();
    double exec_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    fprintf(stdout, "Execution Time : %f\n", exec_time);
}

const void log_global(const Global g) {
    printf("Pos.x: %f    Pos.y: %f    Pos.z: %f\n", g.Pos.x, g.Pos.y, g.Pos.z);
    printf("U.x:   %f    U.y:   %f    U.z:   %f\n", g.U.x, g.U.y, g.U.z);
    printf("V.x:   %f    V.y:   %f    V.z:   %f\n", g.V.x, g.V.y, g.V.z);
    printf("N.x:   %f    N.y:   %f    N.z:   %f\n", g.N.x, g.N.y, g.N.z);
}

const void log_vector(const Vector v) {
    printf("v.x: %f    v.y: %f    v.z: %f    v.w: %f\n", v.x, v.y, v.z, v.w);
}
