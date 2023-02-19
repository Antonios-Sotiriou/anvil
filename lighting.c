#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

const Pixel phong(Phong model) {
    model.PixelPos.z = 1 / model.PixelPos.w;
    model.PixelPos.x = (model.PixelPos.x / model.halfWidth) - 1.0;
    model.PixelPos.y = (model.PixelPos.y / model.halfHeight) - 1.0;

    Vector lightdir = norm_vec(sub_vecs(model.lightPos, model.PixelPos));
    float diff = dot_product(model.normal, lightdir);
    if ( diff < 0 )
        diff = 0;

    Vector diffuse;
    diffuse.x = model.LightColor.x * diff;
    diffuse.y = model.LightColor.y * diff;
    diffuse.z = model.LightColor.z * diff;

    Vector viewdir = norm_vec(sub_vecs(model.PixelPos, model.CameraPos));
    /* R = 2 * (N * L) * (N - L)  */
    Vector reflectdir = multiply_vec(cross_product(cross_product(model.normal, lightdir), sub_vecs(model.normal, lightdir)), 2.00);
    float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);
    model.Specular = multiply_vec(norm_vec(model.Specular), spec);

    Pixel result;
    result.Blue = ceilf((((model.Specular.x + diffuse.x + model.Ambient.x) * model.objColor.x) * 255.0) + 0.5);
    result.Green = ceilf((((model.Specular.y + diffuse.y + model.Ambient.y) * model.objColor.y) * 255.0) + 0.5);
    result.Red = ceilf((((model.Specular.z + diffuse.z + model.Ambient.z) * model.objColor.z) * 255.0) + 0.5);

    return result;
}

