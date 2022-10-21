#include <stdlib.h>
#include <stdio.h>
#include "waves.h"

/* evidence graph */
void evidence_dist() {
    printf("*** testing dist ***\n");
    printf("Evidence dist, expecting 0: %f\n", dist(1, 1, 1, 1)); // 0
    printf("Evidence dist, expecting 1.414214: %f\n", dist(1, 2, 1, 2)); // reg
    printf("Evidence dist, expecting 1.414214: %f\n", dist(2, 1, 2, 1)); // inv
    printf("Evidence dist, expecting 14.14...: %f\n", dist(1, 11, 1, 11));

    // printf("Evidence dist, expecting 1", dist(1, 1, 2, 2));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_dist();
    return 0;
}