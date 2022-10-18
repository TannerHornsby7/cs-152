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
    // printf("Expecting 1: %d\n", legal_keys(1, 1));
    // printf("Expecting 1: %d\n", legal_keys(1, 9));
    // printf("Expecting 16: %d\n", legal_keys(2, 1));
    // printf("Expecting 16: %d\n", legal_keys(2, 9));
    // printf("Expecting less then 256: %d\n", legal_keys(4, 2));
    // printf("Expecting less than 256 but bigger than above: %d\n", legal_keys(4, 4));
}

/* evidence periods_for_yield */
void evidence_periods_for_yield() {
    // printf("Expecting 1: %d\n", periods_for_yield(1, 1));
    // printf("Expecting 2: %d\n", periods_for_yield(.10, .21));
    // printf("Expecting 3: %d\n", periods_for_yield(.10, .22));
    // printf("Expecting 8: %d\n", periods_for_yield(.10, 1.0));
    // printf("Expecting 2: %d\n", periods_for_yield(.50, .51));
}

/* evidence pattern */
void evidence_pattern() {
    // printf("Expecting nothing:\n");
    // pattern(0, 0, 0);
    // printf("Expecting one dot:\n");
    // // pattern(1, 1, 1);
    // printf("Expecting ed image:\n");
    // pattern(5, 4, 3);
    printf("Expecting 2 3x3 parallelograms:\n");
    pattern(3, 3, 2);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_tens_letters();
    evidence_common_divisors();
    evidence_legal_keys();
    evidence_periods_for_yield();
    evidence_pattern();
    return 0;
}