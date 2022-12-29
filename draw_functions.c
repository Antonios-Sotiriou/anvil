#include "header_files/draw_functions.h"

const void draw_line(Pixel **buffer, float x1, float y1, float x2, float y2, const int red, const int green, const int blue) {

    float delta_y = y2 - y1;
    float delta_x = x2 - x1;

    float fabsdy = fabs(delta_y);
    float fabsdx = fabs(delta_x);

    int start_y = ceil(y1 - 0.5);
    int end_y = ceil(y2 - 0.5);
    int start_x = ceil(x1 - 0.5);
    int end_x = ceil(x2 - 0.5);
        
    int step_y;
    int step_x;

    if ( (delta_x == 0) && (delta_y == 0) ) {
        buffer[start_y][start_x].Red = red;
        buffer[start_y][start_x].Green = green;
        buffer[start_y][start_x].Blue = blue;
    } else if ( fabsdx >= fabsdy ) {
        float slope = delta_y / delta_x;

        if (delta_x < 0) {

            for (int x = start_x; x > end_x; x--) {
                step_y = (slope * (x - start_x)) + y1;

                buffer[step_y][x].Red = red;
                buffer[step_y][x].Green = green;
                buffer[step_y][x].Blue = blue;
            }
        } else {

            for (int x = start_x; x < end_x; x++) {
                step_y = (slope * (x - start_x)) + y1;

                buffer[step_y][x].Red = red;
                buffer[step_y][x].Green = green;
                buffer[step_y][x].Blue = blue;
            }
        }
    } else if ( fabsdx < fabsdy ) {
        float slope = delta_x / delta_y;

        if (delta_y < 0) {

            for (int y = start_y; y > end_y; y--) {
                step_x = (slope * (y - start_y)) + x1;

                buffer[y][step_x].Red = red;
                buffer[y][step_x].Green = green;
                buffer[y][step_x].Blue = blue;
            }
        } else {

            for (int y = start_y; y < end_y; y++) {
                step_x = (slope * (y - start_y)) + x1;

                buffer[y][step_x].Red = red;
                buffer[y][step_x].Green = green;
                buffer[y][step_x].Blue = blue;
            }
        }
    } else {
        fprintf(stderr, "An Error has occured! draw_line().");
        exit(EXIT_FAILURE);
    }
}


