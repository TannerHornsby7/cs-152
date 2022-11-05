#include <math.h>
#include <stdio.h>
#include "waves.h"
#include "stdlib.h"
#include <string.h>

double dist(double x0, double y0, double x1, double y1) {
    return sqrt(pow((x0 - y0), 2) + pow((x1 - y1), 2));
}


void print_header(int side_length) {
    int MAX_RGB = 255;
    printf("P3\n");
    printf("%d %d\n", side_length, side_length);
    printf("%d\n", MAX_RGB);
}


void draw_from_cmd(int s, double r, double g, double b, int x, int y) {
    int x_foff = (s / 2) + x; // adjusted offsets
    int y_foff = (s / 2) - y;

    print_header(s);
    for(int i = 0; i < s; i++) { // cols
        for (int j = 0; j < s; j++) // rows
        {
            int re = (int) fabs(sin(r * dist(i, x_foff, j, y_foff)) * 255);
            int gr = (int) fabs(sin(g * dist(i, x_foff, j, y_foff)) * 255);
            int bl = (int) fabs(sin(b * dist(i, x_foff, j, y_foff)) * 255);

            printf("%d %d %d\n", re, gr, bl);
        }
    }
}


void cmds_to_draw(int argc, char** argv) {
    int s = 0, x = 0, y = 0;
    double r = 1, g = 1, b = 1;
    for(int i = 1; i < argc; i++) {
        char* flag = argv[i];
        if(strcmp(flag, "-s") == 0) {
             s = atoi(argv[i + 1]);
        }
        else if(strcmp(flag, "-r") == 0) {
            r = atof(argv[i + 1]);
        }
        else if(strcmp(flag, "-g") == 0) {
            g = atof(argv[i + 1]);
        }
        else if(strcmp(flag, "-b") == 0) {
            b = atof(argv[i + 1]);
        }
        else if(strcmp(flag, "-x") == 0) {
            x = atoi(argv[i + 1]);
        }
        else if(strcmp(flag, "-y") == 0) {
            y = atoi(argv[i + 1]);
        }
    }
    draw_from_cmd(s, r, g, b, x, y);
}