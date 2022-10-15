#include <math.h>
#include <stdio.h>
#include "lab3.h"

void makePlane(int xleft, int xright, int ybottom, int ytop) {
    
    for ( int j = 0; j < ytop; j++) {
        for( int i = 0; i < xleft; i++) {
            printf(" ");
        }
        printf("|");
        for( int i = 0; i < xright; i++) {
            printf(" ");
        }
        printf("\n");
    }
    for( int i = 0; i < xleft; i++) {
        printf("-");
    }
    printf("+");
    for( int i = 0; i < xright; i++) {
        printf("-");
    }
    printf("\n");
     for ( int j = 0; j < ybottom; j++) {
        for( int i = 0; i < xleft; i++) {
            printf(" ");
        }
        printf("|");
        for( int i = 0; i < xright; i++) {
            printf(" ");
        }
        printf("\n");
    }
}

void graph(double a, double b, double c, double step, int xleft, int xright, int ybottom, int ytop) {
    makePlane(xleft, xright, ybottom, ytop);
}