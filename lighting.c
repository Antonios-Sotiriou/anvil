#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const float shadow) {
    Vector pixel = {
        .x = ((pixX / model.halfWidth) - 1.0),
        .y = ((pixY / model.halfHeight) - 1.0),
        .z = (1 / pixW),
    };

    Vector lightdir = norm_vec(sub_vecs(pixel, model.lightPos));
    float diff = dot_product(model.normal, lightdir);
    if ( diff < 0 )
        diff = 0;

    Vector diffuse = multiply_vec(model.LightColor, diff);

    Vector viewdir = norm_vec(sub_vecs(pixel, model.CameraPos));

    Vector reflectdir = multiply_vec(cross_product(cross_product(model.normal, lightdir), sub_vecs(model.normal, multiply_vec(lightdir, -1.0))), 2.00);
    float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);
    model.Specular = multiply_vec(model.Specular, spec);

    Pixel result;
    if (shadow) {
        result.Blue = (model.Specular.x + diffuse.x + model.Ambient.x) * model.objColor.x;
        result.Green = (model.Specular.y + diffuse.y + model.Ambient.y) * model.objColor.y;
        result.Red = (model.Specular.z + diffuse.z + model.Ambient.z) * model.objColor.z;
    } else {
        result.Blue = model.Ambient.x * model.objColor.x;
        result.Green = model.Ambient.y * model.objColor.y;
        result.Red = model.Ambient.z * model.objColor.z;
    }

    return result;
}

