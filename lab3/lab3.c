#include <math.h>
#include "lab3.h"

void graph(double a, double b, double c, double step, int xleft, int xright,
 int ybottom, int ytop) {

 }

void makePlane(int xleft, int xright, int ybottom, int ytop) {
    
    for ( int j = 0; j < ytop; j++) {
        for( int i = 0; i < xleft; i++) {
            printf(" ");
        }
        printf("|");
        for( int i = 0; i < xright; i++) {
            printf(" ");
        }
    }
    for( int i = 0; i < xleft; i++) {
        printf("-");
    }
    printf("+");
    for( int i = 0; i < xright; i++) {
        printf("-");
    }
     for ( int j = 0; j < ybottom; j++) {
        for( int i = 0; i < xleft; i++) {
            printf(" ");
        }
        printf("|");
        for( int i = 0; i < xright; i++) {
            printf(" ");
        }
    }
}