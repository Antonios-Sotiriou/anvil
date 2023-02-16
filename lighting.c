#include "header_files/lighting.h"
#include <stdio.h>
#include <stdlib.h>

const Pixel phong(Phong model) {
    model.PixelPos.z = 1 / model.PixelPos.z;
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

// const Pixel phong(Vector pixpos, const Vector normal, const Global light, const Global camera, const Vector obj_color) {
//     // printf("normal.x: %f    normal.y: %f    normal.z: %f    normal.w: %f\n", normal.x, normal.y, normal.z, normal.w);
//     float AmbientStrength = 0.1;
//     /* We multiply AmbientStrength with light color. */
//     Vector ambient = multiply_vec(light.C, AmbientStrength);
//     /* We multiply then the above result with the object color.  */
//     // printf("ambient.r: %f    ambient.b: %f    ambient.g: %f\n", ambient.x, ambient.y, ambient.z);
//     pixpos.x = (pixpos.x - 800 / 2.00) / (800 / 2.00);
//     pixpos.y = (pixpos.y - 800 / 2.00) / (800 / 2.00);
//     pixpos.z = 1 / pixpos.z;
//     // printf("pixpos.x: %f\n", (pixpos.x - (800 / 2.00)) / (800 / 2.00));
//     // printf("pixpos.y: %f\n", (pixpos.y - (800 / 2.00)) / (800 / 2.00));
//     // printf("pixpos.z: %f\n", 1 / pixpos.z);

//     Vector lightdir = norm_vec(sub_vecs(pixpos, light.Pos));
//     // printf("lightdir.r: %f    lightdir.b: %f    lightdir.g: %f\n", lightdir.x, lightdir.y, lightdir.z);
//     float diff = dot_product(normal, lightdir);
//     if ( diff < 0 )
//         diff = 0;

//     Vector diffuse = multiply_vec(light.C, diff);
//     // printf("diffuse.r: %f    diffuse.b: %f    diffuse.g: %f\n", diffuse.x, diffuse.y, diffuse.z);
//     float SpecularStrength = 0.5;
//     Vector viewdir = norm_vec(sub_vecs(camera.Pos, pixpos));
//     // printf("viewdir.r: %f    viewdir.b: %f    viewdir.g: %f\n", viewdir.x, viewdir.y, viewdir.z);
//     /* R = 2 * (N * L) * (N - L)  */
//     Vector reflectdir = multiply_vec(cross_product(cross_product(normal, multiply_vec(lightdir, -1.0)), sub_vecs(normal, lightdir)), 2.00);
//     float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);

//     Vector specular = multiply_vec(light.C, SpecularStrength * spec);
//     // printf("specular.r: %f    specular.b: %f    specular.g: %f\n", specular.x, specular.y, specular.z);
//     // printf("diff: %f    Spec: %f\n", diff, spec);


//     Vector result = multiply_vec(cross_product(add_vecs(add_vecs(ambient, diffuse), specular), obj_color), 255.0);
//     // printf("obj_color.r: %f    obj_color.b: %f    obj_color.g: %f\n", obj_color.x, obj_color.y, obj_color.z);
//     // printf("light.C.r: %f    light.C.b: %f    light.C.g: %f\n", light.C.x, light.C.y, light.C.z);
//     // printf("result.r: %f    result.b: %f    result.g: %f\n", result.x, result.y, result.z);
//     Pixel pix = { 0 };
//     pix.Blue = result.x;
//     pix.Green = result.y;
//     pix.Red = result.z;
//     return pix;
// }

