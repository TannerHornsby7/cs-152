#include <stdlib.h>
#include <stdio.h>
#include "hw1.h"

/* evidence_is_buoyant: test expt */
void evidence_is_buoyant()
{
    printf("*** testing is_buoyant\n");
    printf("- expecting 1: %d\n", is_buoyant(0, 2)); // weightless object floats
    printf("- expecting 0: %d\n", is_buoyant(2, 0)); // no radius will return false
    printf("- expecting 1: %d\n", is_buoyant(261380.496, 10)); // 4/3 * pi *(r=10)^3 * 62.4  = 261380.496
    printf("- expecting 1: %d\n", is_buoyant(251380.496, 10)); // 4/3 * pi *(r=10)^3 * 62.4  = 261380.496
    printf("- expecting 0: %d\n", is_buoyant(271380.496, 10)); // 4/3 * pi *(r=10)^3 * 62.4  = 261380.496
    printf("- expecting 0: %d\n", is_buoyant(301380.496, 10)); // 4/3 * pi *(r=10)^3 * 62.4  = 261380.496
}

/* evidence_is_buoyant: test expt */
void evidence_pods_to_order()
{
    printf("*** testing pods_to_order\n");
    printf("- expecting 480: %d\n", pods_to_order(9, 5, 10));
    printf("- expecting 960: %d\n", pods_to_order(96, 10, 1)); 
    printf("- expecting 96: %d\n", pods_to_order(1, 1, 1)); 
    printf("- expecting 192: %d\n", pods_to_order(2, 10, 5));
}

/* evidence_gcd: test expt */
void evidence_gcd()
{
    printf("*** testing gcd\n");
    printf("- expecting 1: %d\n", gcd(9, 5));
    printf("- expecting 5: %d\n", gcd(200, 45));
    printf("- expecting 10: %d\n", gcd(100, 10));
    printf("- expecting 10: %d\n", gcd(60, 50));
    printf("- expecting 25: %d\n", gcd(100, 25));

}

/* main: run the evidence functions above */
int main(int argc, char *argv[])
{
    evidence_is_buoyant();
    evidence_pods_to_order();
    evidence_gcd();

    return 0;
}