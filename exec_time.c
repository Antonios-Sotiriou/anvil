#include "header_files/exec_time.h"

const clock_t start(void) {
    return clock();
}
const void end(const clock_t start_time) {
    clock_t end_time = clock();
    double exec_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    fprintf(stdout, "Execution Time : %f\n", exec_time);
}

const void log_global(const Global obj) {
    printf("Pos.x: %f    Pos.y: %f    Pos.z: %f\n", obj.Pos.x, obj.Pos.y, obj.Pos.z);
    printf("U.x:   %f    U.y:   %f    U.z:   %f\n", obj.U.x, obj.U.y, obj.U.z);
    printf("V.x:   %f    V.y:   %f    V.z:   %f\n", obj.V.x, obj.V.y, obj.V.z);
    printf("N.x:   %f    N.y:   %f    N.z:   %f\n", obj.N.x, obj.N.y, obj.N.z);
}
