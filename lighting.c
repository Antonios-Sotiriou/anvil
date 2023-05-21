#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

#include "header_files/logging.h"
#include "header_files/exec_time.h"
#include "header_files/matrices.h"

extern int HALFW;
extern int HALFH;
extern Mat4x4 rePerspMat;

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const int shadow) {
    Pixel result;
    Vector diffuse = { 0 }, specular = { 0 };
    float w = 1 / pixW;
    Vector pixel = {
        .x = ((pixX / HALFW) - 1.0) * w,
        .y = ((pixY / HALFH) - 1.0) * w,
        .z = (pixZ / 0.5) * w,
        .w = w
    };
    pixel = vecxm(pixel, rePerspMat);
    model.normal = norm_vec(model.normal);

    Vector lightdir = norm_vec(sub_vecs(pixel, model.lightPos));
    float diff = dot_product(lightdir, model.normal);
    if ( diff > 0 ) {
        diffuse = multiply_vec(model.LightColor, diff);

        Vector reflectdir = multiply_vec(cross_product(cross_product(multiply_vec(lightdir, -1), model.normal), sub_vecs(multiply_vec(lightdir, -1), model.normal)), 2.00);
        float dot = dot_product(norm_vec(pixel), norm_vec(reflectdir));
        if ( dot < 0 )
            dot = 0;

        float spec = pow(dot, 32);
        specular = multiply_vec(model.Specular, spec);
    }

    if (!shadow) {
        result.Blue = (specular.x + diffuse.x + model.Ambient.x) * model.objColor.Blue;
        result.Green = (specular.y + diffuse.y + model.Ambient.y) * model.objColor.Green;
        result.Red = (specular.z + diffuse.z + model.Ambient.z) * model.objColor.Red;
    } else {
        result.Blue = model.Ambient.x * model.objColor.Blue;
        result.Green = model.Ambient.y * model.objColor.Green;
        result.Red = model.Ambient.z * model.objColor.Red;
    }

    /* Reseting the shadow bias after lighting calculations are done. */
    model.bias = 0.0;
    return result;
}

