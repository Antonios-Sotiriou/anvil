#include "header_files/camera.h"

extern float DeltaTime;

/* Rotates the camera to look left. */
const void look_left(Global *g, const float angle) {
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(-2, g->V);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
}
/* Rotates the camera to look right. */
const void look_right(Global *g, const float angle) {
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(2, g->V);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
}
const void move_forward(Global *g) {
    g->Pos = add_vecs(g->Pos, multiply_vec(g->N, 0.2));
}
const void move_backward(Global *g) {
    g->Pos = sub_vecs(g->Pos, multiply_vec(g->N, 0.2));
}
/* Rotates the camera to look Up. */
const void look_up(Global *g, const float angle) {

    /* A working example with Quaternion rotation. */
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(-2, g->U);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
}
/* Rotates the camera to look Down. */
const void look_down(Global *g, const float angle) {

    /* A working example with Quaternion rotation. */
    Quat u = setQuat(0, g->U);
    Quat v = setQuat(0, g->V);
    Quat n = setQuat(0, g->N);

    Quat xrot = rotationQuat(2, g->U);
    Quat rerot = conjugateQuat(xrot);

    Quat resu = multiplyQuats(multiplyQuats(xrot, u), rerot);
    Quat resv = multiplyQuats(multiplyQuats(xrot, v), rerot);
    Quat resn = multiplyQuats(multiplyQuats(xrot, n), rerot);

    g->U = resu.v;
    g->V = resv.v;
    g->N = resn.v;
}
/* Moves camera position left. */
const void move_left(Global *g) {
    g->Pos = sub_vecs(g->Pos, multiply_vec(g->U, 0.1));
}
/* Moves camera position right. */
const void move_right(Global *g) {
    g->Pos = add_vecs(g->Pos, multiply_vec(g->U, 0.1));
}
/* Moves camera position Up. */
const void move_up(Global *g) {
    // g->Pos = sub_vecs(g->Pos, multiply_vec(g->V, 0.1));
    g->Pos.y -= 0.1;
}
/* Moves camera position Down. */
const void move_down(Global *g) {
    // g->Pos = add_vecs(g->Pos, multiply_vec(g->V, 0.1));
    g->Pos.y += 0.1;
}