#include "header_files/world_objects.h"

enum { Pos, U, V, N, C};
extern Scene scene;
extern Vec4 light[];

/* Enumerate objects to form the scene. Add every new objects name at 1 position before the end, AKA ( before LastObj entry). */
enum { Cube, LastObj };

/* This function is responsible to position the objects in world space. */
const void initMeshes(Scene *s) {
    Mesh space = { 0 }, terrain = { 0 }, jupiter = { 0 }, earth = { 0 }, sun = { 0 };
    Mat4x4 ScaleMat, TransMat, PosMat;

    // space = load_obj("objects/spacedom.obj");
    // memcpy(space.texture_file, "textures/spacedom_texture.bmp", sizeof(char) * 30);
    // loadTexture(&space);
    // ScaleMat = scale_mat(1000.0);
    // TransMat = translation_mat(0.0, 0.0, 500.0);
    // PosMat = mxm(ScaleMat, TransMat);
    // s->m[4] = meshxm(space, PosMat);
    // free(space.v);
    // free(space.t);

    terrain = load_obj("objects/terrain.obj");
    memcpy(terrain.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    loadTexture(&terrain);
    ScaleMat = scale_mat(10.0);
    // rotate_y(&terrain, 90);
    TransMat = translation_mat(0.0, 0.0, 500.0);
    PosMat = mxm(ScaleMat, TransMat);
    s->m[0] = meshxm(terrain, PosMat);
    free(terrain.v);
    free(terrain.t);

    jupiter = load_obj("objects/earth.obj");
    memcpy(jupiter.texture_file, "textures/stones.bmp", sizeof(char) * 20);
    loadTexture(&jupiter);
    ScaleMat = scale_mat(10.0);
    TransMat = translation_mat(-10.0, 0.0, 580.0);
    PosMat = mxm(ScaleMat, TransMat);
    s->m[1] = meshxm(jupiter, PosMat);
    free(jupiter.v);
    free(jupiter.t);

    earth = load_obj("objects/earth.obj");
    memcpy(earth.texture_file, "textures/Earth.bmp", sizeof(char) * 19);
    loadTexture(&earth);
    ScaleMat = scale_mat(0.5);
    TransMat = translation_mat(1.0, -1.0, 510.0);
    PosMat = mxm(ScaleMat, TransMat);
    // normalsxm(&earth, PosMat);
    s->m[2] = meshxm(earth, PosMat);
    free(earth.v);
    free(earth.t);

    sun = load_obj("objects/spacedom.obj");
    memcpy(sun.texture_file, "textures/light.bmp", sizeof(char) * 19);
    loadTexture(&sun);
    ScaleMat = scale_mat(0.5);
    TransMat = translation_mat(light[Pos].x, light[Pos].y, light[Pos].z);
    PosMat = mxm(ScaleMat, TransMat);
    s->m[3] = meshxm(sun, PosMat);
    free(sun.v);
    free(sun.t);
}
/* Teams all objects oth the world in a scene for further procesing. */
const void createScene(Scene *s) {
    s->m = malloc(sizeof(Mesh) * 4);
    s->indexes = 4;
}
const void releaseScene(Scene *s) {
    for (int i = 0; i < s->indexes; i++) {
        free(s->m[i].t);
        free(s->m[i].v);
        free2darray((void*)s->m[i].texels, s->m[i].texture_height);
    }
    free(s->m);
}
/* Loads the appropriate Textures and importand Texture infos. */
const static void loadTexture(Mesh *c) {

    BMP_Header bmp_header;
    BMP_Info texture;

    FILE *fp;
    fp = fopen(c->texture_file, "rb");
    if (fp == NULL){
        fclose(fp);
        fprintf(stderr, "Could not open file < %s >! loadTexture() -- fopen().\n", c->texture_file);
    } else {
        fread(&bmp_header, sizeof(BMP_Header), 1, fp);
        fseek(fp, 14, SEEK_SET);
        fread(&texture, sizeof(BMP_Info), 1, fp);
        fseek(fp, (14 + texture.Size), SEEK_SET);

        c->texture_height = texture.Height;
        c->texture_width = texture.Width;
        c->texels = create2darray((void*)c->texels, sizeof(Pixel), texture.Height, texture.Width);

        for (int y = (texture.Height - 1); y >= 0; y--) {
            for (int x = 0; x < texture.Width; x++) {
                fread(&c->texels[y][x], sizeof(Pixel), 1, fp);
            }
        }
    }
    fclose(fp);
}

