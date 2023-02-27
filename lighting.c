#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const float shadow) {
    Vector pixel = {
        .x = (pixX / model.halfWidth) - 1.0,
        .y = (pixY / model.halfHeight) - 1.0,
        .z = 1 / pixW,
        .w = 1 / pixW,
    };

    Vector lightdir = norm_vec(sub_vecs(model.lightPos, pixel));
    float diff = dot_product(model.normal, lightdir);
    if ( diff < 0 )
        diff = 0;

    Vector diffuse;
    diffuse.x = model.LightColor.x * diff;
    diffuse.y = model.LightColor.y * diff;
    diffuse.z = model.LightColor.z * diff;

    Vector viewdir = norm_vec(sub_vecs(pixel, model.CameraPos));
    /* R = 2 * (N * L) * (N - L)  */
    Vector reflectdir = multiply_vec(cross_product(cross_product(model.normal, lightdir), sub_vecs(model.normal, lightdir)), 2.00);
    float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);
    model.Specular = multiply_vec(norm_vec(model.Specular), spec);

    Pixel result;
    result.Blue = ceilf(((((model.Specular.x * (1 - shadow)) + (diffuse.x * (1 - shadow)) + model.Ambient.x) * model.objColor.x) * 255.0) + 0.5);
    result.Green = ceilf(((((model.Specular.y * (1 - shadow)) + (diffuse.y * (1 - shadow)) + model.Ambient.y) * model.objColor.y) * 255.0) + 0.5);
    result.Red = ceilf(((((model.Specular.z * (1 - shadow)) + (diffuse.z * (1 - shadow)) + model.Ambient.z) * model.objColor.z) * 255.0) + 0.5);

    return result;
}

