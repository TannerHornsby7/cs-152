#include <stdlib.h>
#include <stdio.h>
#include "hw4.h"

//helper to print arrays
void print_array(char** arr, unsigned int len){
    for(int i = 0; i < len; i++){
        printf("Line # %d: %s\n", i + 1, arr[i]);
    }
}

void evidence_flip_case() {
    printf("\n==== Evidence: Flip Case ====\n");
    printf("Expecting BANANA: %s\n", flip_case("banana")); // -
    printf("Expecting banana: %s\n", flip_case("BANANA")); // 0
    printf("Expecting bAnAnA: %s\n", flip_case("BaNaNa")); // +
    printf("Expecting bAN@123A: %s\n", flip_case("Ban@123a")); // mix
}


void evidence_matches() {
    unsigned int nmatches = 0;
    printf("\n==== Evidence: Matches ====\n");
    print_array(matches("Waluigi", "i", &nmatches), nmatches);
    printf("Expecting 2: %d\n", nmatches);

    print_array(matches("Hello, Hallo, Hillo", "H?l", &nmatches), nmatches);
    printf("Expecting 3: %d\n", nmatches);
    
    print_array(matches("Bi Hi a;ldjfa;lkdsf", "?i", &nmatches), nmatches);
    printf("Expecting 2: %d\n", nmatches);
}

int main(int argc, char *argv[]) {
    evidence_flip_case();
    evidence_matches();
    return 0;
}