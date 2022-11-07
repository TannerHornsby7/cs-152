#include <stdlib.h>
#include <stdio.h>
#include "hw4.h"

void evidence_flip_case() {
    printf("\n==== Evidence: Flip Case ====\n");
    printf("Expecting BANANA: %s\n", flip_case("banana")); // -
    printf("Expecting banana: %s\n", flip_case("BANANA")); // 0
    printf("Expecting bAnAnA: %s\n", flip_case("BaNaNa")); // +
    printf("Expecting bAN@123A: %s\n", flip_case("Ban@123a")); // mix
}
int main(int argc, char *argv[]) {
    evidence_flip_case();
    return 0;
}