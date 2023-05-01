#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

const Pixel phong(Phong model, const float pixX, const float pixY, const float pixZ, const float pixW, const float shadow) {
    Vector pixel = {
        .x = ((pixX / model.halfWidth) - 1.0),
        .y = ((pixY / model.halfHeight) - 1.0),
        .z = (pixZ + 1.0),
    };

    Vector lightdir = norm_vec(sub_vecs(model.lightPos, pixel));
    float diff = dot_product(model.normal, lightdir);
    if ( diff < 0 )
        diff = 0;

    Vector diffuse = norm_vec(multiply_vec(model.LightColor, diff));

    Vector viewdir = norm_vec(sub_vecs(model.CameraPos, pixel));

    Vector reflectdir = multiply_vec(cross_product(cross_product(lightdir, model.normal), sub_vecs(lightdir, model.normal)), 2.00);
    float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);
    Vector specular = multiply_vec(model.Specular, spec);

    Pixel result;
    if (shadow) {
        result.Blue = (specular.x + diffuse.x + model.Ambient.x) * model.objColor.Blue;
        result.Green = (specular.y + diffuse.y + model.Ambient.y) * model.objColor.Green;
        result.Red = (specular.z + diffuse.z + model.Ambient.z) * model.objColor.Red;
    } else {
        result.Blue = model.Ambient.x * model.objColor.Blue;
        result.Green = model.Ambient.y * model.objColor.Green;
        result.Red = model.Ambient.z * model.objColor.Red;
    }

    return result;
}

