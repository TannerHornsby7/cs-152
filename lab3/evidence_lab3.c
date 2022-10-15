#include <stdlib.h>
#include <stdio.h>
#include "lab3.h"

/* evidence_is_buoyant: test expt */
void evidence_graph()
{
    printf("*** testing graph\n");
    graph(0, 0, 0, 1, 5, 5, 5, 5);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_graph();

    return 0;
}