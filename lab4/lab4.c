#include <math.h>
#include <stdio.h>
#include "lab3.h"

char valAt(double a, double b, double c, int x, int y, double s) {
    int f_val = ((a * pow(x, 2) + b * x + c) * s) / 1;
    // printf("%d", f_val);

    if(f_val == y) {
        return '*';
    }
    else if(x == 0 && y == 0) {
        return '+';
    }
    else if (x == 0) {
        return '|';
    }
    else if (y == 0) {
        return '-';
    }
    else {
        return ' ';
    }
}
void makeRow(double a, double b, double c, double s, int xleft, int xright, int
 y) {
    for( int i = xleft; i <= xright; i++) {
        printf("%c", valAt(a, b, c, i, y, s));
    }
    printf("\n");
}
void graph(double a, double b, double c, double s, int xleft, int xright, int 
ybottom, int ytop) {
    for(int j = ytop; j >= ybottom; j--) {
        makeRow(a, b, c, s, xleft, xright, j);
    }
}