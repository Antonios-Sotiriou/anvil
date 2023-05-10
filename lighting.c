#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

#include "header_files/logging.h"
#include "header_files/exec_time.h"
#include "header_files/matrices.h"

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const float shadow) {
    Pixel result;
    Vector diffuse = { 0 }, specular = { 0 };
    float w = 1 / pixW;
    Vector pixel = {
        .x = ((pixX / model.halfWidth) - 1.0) * w,
        .y = ((pixY / model.halfHeight) - 1.0) * w,
        .z = (1 + pixZ) * w,
        .w = w
    };
    pixel = vecxm(pixel, model.ViewSpace);
    model.normal = norm_vec(model.normal);

    Vector lightdir = norm_vec(sub_vecs(pixel, model.lightPos));
    float diff = dot_product(model.normal, lightdir);
    // printf("diff: %f    \n", diff);
    if ( diff > 0 )
        diffuse = multiply_vec(model.LightColor, diff);

    // logVector(diffuse);
    // Vector viewdir = sub_vecs(model.CameraPos, pixel);

    Vector reflectdir = multiply_vec(cross_product(cross_product(multiply_vec(lightdir, -1), model.normal), sub_vecs(multiply_vec(lightdir, -1), model.normal)), 2.00);
    float dot = dot_product(norm_vec(pixel), norm_vec(reflectdir));
    if ( dot < 0 )
        dot = 0;
    // printf("dot: %f    ", dot);
    float spec = pow(dot, 32);
    // printf("spec: %f\n", spec);
    // if ( spec == 1 )
    //     spec = 1;
    // printf("spec: %f\n", spec);
    specular = multiply_vec(model.Specular, spec);
    // logVector(specular);
    if (shadow) {
        result.Blue = (specular.x + diffuse.x + model.Ambient.x) * model.objColor.Blue;
        result.Green = (specular.y + diffuse.y + model.Ambient.y) * model.objColor.Green;
        result.Red = (specular.z + diffuse.z + model.Ambient.z) * model.objColor.Red;
    } else {
        result.Blue = model.Ambient.x * model.objColor.Blue;
        result.Green = model.Ambient.y * model.objColor.Green;
        result.Red = model.Ambient.z * model.objColor.Red;
    }
    // result.Blue = specular.x * model.objColor.Blue;
    // result.Green = specular.y * model.objColor.Green;
    // result.Red = specular.z * model.objColor.Red;
    /* Reseting the shadow bias after lighting calculations are done. */
    model.bias = 0.0;
    return result;
}

