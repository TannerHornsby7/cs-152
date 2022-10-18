#include <stdlib.h>
#include <stdio.h>
#include "hw2.h"

/* evidence tens_letters */
void evidence_tens_letters() {
    // printf("*** testing tens_letters ***\n");
    // printf("Expecting 4: %c\n", tens_letters('0'));
    // printf("Expecting 5: %c\n", tens_letters('6'));
    // printf("Expecting 3: %c\n", tens_letters('1'));
    // printf("Expecting 6: %c\n", tens_letters('7'));
}

/* evidence tens_letters */
void evidence_common_divisors() {
    // printf("*** testing tens_letters ***\n");
    // printf("Expecting 1: ");
    // common_divisors(1, 1);
    // printf("Expecting 1 2 3 6: ");
    // common_divisors(6, 12);
}
/* evidence legal_keys */
void evidence_legal_keys() {
    printf("Expecting 1: %d\n", legal_keys(1, 1));
    printf("Expecting 1: %d\n", legal_keys(1, 9));
    printf("Expecting 16: %d\n", legal_keys(2, 1));
    printf("Expecting 16: %d\n", legal_keys(2, 9));
    printf("Expecting less then 256: %d\n", legal_keys(4, 2));
    printf("Expecting less than 256 but bigger than above: %d\n", legal_keys(4, 4));

}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_tens_letters();
    evidence_common_divisors();
    evidence_legal_keys();
    return 0;
}