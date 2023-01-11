#include "header_files/lighting.h"

const Vector phong(Vector pixpos, const Vector normal, const Global light, const Global camera, const Vector obj_color) {
    float AmbientStrength = 0.1;
    Vector ambient;
    ambient.x = light.C.x * AmbientStrength;
    ambient.y = light.C.y * AmbientStrength;
    ambient.z = light.C.z * AmbientStrength;

    pixpos.x = (pixpos.x - (800 / 2.00)) / (800 / 2.00);
    pixpos.y = (pixpos.y - (800 / 2.00)) / (800 / 2.00);
    pixpos.z = 1 / pixpos.z;

    Vector lightdir = norm_vec(sub_vecs(pixpos, light.Pos));
    float diff = dot_product(normal, lightdir);
    if ( diff < 0 )
        diff = 0;

    Vector diffuse;
    diffuse.x = light.C.x * diff;
    diffuse.y = light.C.y * diff;
    diffuse.z = light.C.z * diff;

    float SpecularStrength = 0.5;
    Vector viewdir = norm_vec(sub_vecs(camera.Pos, pixpos));
    /* R = 2 * (N * L) * (N - L)  */
    Vector reflectdir = multiply_vec(cross_product(cross_product(normal, lightdir), sub_vecs(normal, lightdir)), 2.00);
    float spec = powf(dot_product(viewdir, norm_vec(reflectdir)), 32.00);

    Vector specular;
    specular.x = light.C.x * SpecularStrength * spec;
    specular.y = light.C.y * SpecularStrength * spec;
    specular.z = light.C.z * SpecularStrength * spec;

    Vector result;
    result.x = ceil((((specular.x + diffuse.x + ambient.x) * obj_color.x) * 255.0) + 0.5);
    result.y = ceil((((specular.y + diffuse.y + ambient.y) * obj_color.y) * 255.0) + 0.5);
    result.z = ceil((((specular.z + diffuse.z + ambient.z) * obj_color.z) * 255.0) + 0.5);

    return result;
}

