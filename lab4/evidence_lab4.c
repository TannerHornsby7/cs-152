#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

/* evidence graph */
void evidence_graph() {
    printf("*** testing graph ***\n");
//  graph(a, b, c, s, xleft, xright, ybottom, ytop) {
    // graph(0, 0, 4, 1, -5, 5, -5, 5); // constant function
    // graph(1, 0, 0, 1, -5, 5, -5, 5); // standard quadratic (x^2)
    // graph(1, 0, 0, .5, -5, 5, -5, 5); // standard quadratic (x^2) steps down
    // graph(1, 0, 0, 2, -5, 5, -5, 5); // standard quadratic (x^2) steps up
    // graph(-.1, 0, 0, .5, -50, 50, -50, 50); // negative quadratic
    graph(-.1, 4, 14, 1, -50, 50, -50, 50); // cuts off when out of bounds
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_graph();
    return 0;
}