#include <math.h>
#include <stdio.h>
#include "waves.h"

double dist(double x0, double y0, double x1, double y1) {
    return sqrt(pow((x0 - y0), 2) + pow((x1 - y1), 2));
}


void print_header(int side_length) {
    int MAX_RGB = 255;
    printf("P3\n");
    printf("%d %d\n", side_length, side_length);
    printf("%d\n", MAX_RGB);
}


void draw_waves(int side_length, int x_offset, int y_offset) {
    // calculating the real offset values
    int x_foff = (side_length / 2) + x_offset; // adjusted offsets
    int y_foff = (side_length / 2) - y_offset;

    print_header(side_length);
    for(int i = 0; i < side_length; i++) { // cols
        for (int j = 0; j < side_length; j++) // rows
        {
            int b = (int) fabs(sin(dist(i, x_foff, j, y_foff)) * 255);
            // tests
            // printf("x foff: %d\ny foff: %d\ni & j: %d %d\n %d\n", x_foff,
            // y_foff, i, j, b);
            printf("0 0 %d\n", b);
        }
        
    }
}