#include "header_files/drawline.h"

extern Pixel **pixels;

const Pixel antialliasing(const Pixel a, const Pixel b) {
    Pixel r = { 0 };
    r.Red = (a.Red + b.Red) * 0.5;
    r.Green = (a.Green + b.Green) * 0.5;
    r.Blue = (a.Blue + b.Blue) * 0.5;
    return r;
}
const void drawLine(float x1, float y1, float x2, float y2, const float red, const float green, const float blue) {
    Pixel pix = { blue, green, red }, s1, s2;
    Pixel test1 = { 255, 255, 255 };
    Pixel test2 = { 255, 0, 0 };
    float delta_y = y2 - y1;
    float delta_x = x2 - x1;

    float fabsdy = fabs(delta_y);
    float fabsdx = fabs(delta_x);

    int start_y = y1 + 0.5;
    int end_y = y2 + 0.5;
    int start_x = x1 + 0.5;
    int end_x = x2 + 0.5;

    int step_y, step_x;
    int step_cache = start_y;
    if ( (delta_x == 0) && (delta_y == 0) ) {
        memcpy(&pixels[start_y][start_x], &pix, sizeof(Pixel));
    } else if ( fabsdx >= fabsdy ) {
        float slope = delta_y / delta_x;

        if (delta_x < 0) {

            for (int x = start_x; x > end_x; x--) {
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[step_y][x], &pix, sizeof(Pixel));
                if ( step_cache != step_y) {
                    s1 = antialliasing(pixels[step_y][x], pixels[step_cache][x]);
                    s2 = antialliasing(pixels[step_y][x], pixels[step_y][x + 1]);
                    memcpy(&pixels[step_cache][x], &test1, sizeof(Pixel));
                    memcpy(&pixels[step_y][x + 1], &test2, sizeof(Pixel));
                }
                step_cache = step_y;
            }
        } else {
            int step_cache;
            for (int x = start_x; x < end_x; x++) {
                step_y = (slope * (x - start_x)) + y1;
                memcpy(&pixels[step_y][x], &pix, sizeof(Pixel));
                step_cache = step_y;
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (int y = start_y; y > end_y; y--) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[y][step_x], &pix, sizeof(Pixel));
            }
        } else {

            for (int y = start_y; y < end_y; y++) {
                step_x = (slope * (y - start_y)) + x1;
                memcpy(&pixels[y][step_x], &pix, sizeof(Pixel));
            }
        }
    } else {
        fprintf(stderr, "An Error has occured! draw_line().");
        exit(EXIT_FAILURE);
    }
}


