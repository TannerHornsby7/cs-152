#include <stdlib.h>
#include <stdio.h>
#include "hw3.h"

int ta_1[] = {-10, 0, -1};
int ta_2[] = {0, 0, 0};
int ta_3[] = {1, 3, 1};
int ta_4[] = {-100, -4, 1};
int ta_5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int ta_6[] = {-10, 5, 15};
int ta_7[] = {-8, 6, 12};

// function to display array contents
void a_disp(int* arr, int len) {
    printf(" [");
    for(int i = 0; i < len; i++) {
        if (i == len - 1) { 
            printf("%d]\n", arr[i]);
            return;
        }
        printf("%d, ", arr[i]);
    }
}


void evidence_all_positive() {
    printf("\n==== Evidence: All Positive ====\n");
    printf("Expecting 0: %d\n", all_positive(ta_1, 3)); // -
    printf("Expecting 0: %d\n", all_positive(ta_2, 3)); // 0
    printf("Expecting 1: %d\n", all_positive(ta_3, 3)); // +
    printf("Expecting 0: %d\n", all_positive(ta_4, 3)); // mix
}

void evidence_exists_positive() {
    printf("\n==== Evidence: Exists Positive ====\n");
    printf("Expecting 0: %d\n", exists_positive(ta_1, 3)); // -
    printf("Expecting 0: %d\n", exists_positive(ta_2, 3)); // 0
    printf("Expecting 1: %d\n", exists_positive(ta_3, 3)); // +
    printf("Expecting 1: %d\n", exists_positive(ta_4, 3)); // mix   
}

void evidence_first_positive() {
    printf("\n==== Evidence: First Positive ====\n");
    printf("Expecting -1: %d\n", first_positive(ta_1, 3)); // -
    printf("Expecting -1: %d\n", first_positive(ta_2, 3)); // 0
    printf("Expecting 0: %d\n", first_positive(ta_3, 3)); // +
    printf("Expecting 2: %d\n", first_positive(ta_4, 3)); // mix   
}

void evidence_number_positives() {
    printf("\n==== Evidence: Number Positive ====\n");
    printf("Expecting 0: %d\n", number_positives(ta_1, 3)); // -
    printf("Expecting 0: %d\n", number_positives(ta_2, 3)); // 0
    printf("Expecting 3: %d\n", number_positives(ta_3, 3)); // +
    printf("Expecting 1: %d\n", number_positives(ta_4, 3)); // mix   
}

void evidence_negate() {
    printf("\n==== Evidence: Negate ====\n");
    printf("Expecting [10, 0, 1]:");
    negate(ta_1, 3);
    a_disp(ta_1, 3);
    printf("Expecting [0, 0, 0]:");
    negate(ta_2, 3);
    a_disp(ta_2, 3);
    printf("Expecting [-1. -3, -1]:");
    negate(ta_3, 3);
    a_disp(ta_3, 3);
    printf("Expecting [100, 4, -1]:");
    negate(ta_4, 3); 
    a_disp(ta_4, 3);
}

void evidence_partial_sums() {
    printf("\n==== Evidence: Partial Sums ====\n");
    printf("Expecting [-10, -10, -11]:");
    a_disp(partial_sums(ta_1, 3), 3);
    printf("Expecting [0, 0, 0]:");
    a_disp(partial_sums(ta_2, 3), 3);
    printf("Expecting [1, 4, 5]:");
    a_disp(partial_sums(ta_3, 3), 3);
    printf("Expecting [-100, -104, -103]:"); 
    a_disp(partial_sums(ta_4, 3), 3);
}

void evidence_reverse() {
    printf("\n==== Evidence: Reverse ====\n");
    printf("Expecting [-1, 0, -10]:");
    reverse(ta_1, 3);
    a_disp(ta_1, 3);
    printf("Expecting [0, 0, 0]:");
    reverse(ta_2, 3);
    a_disp(ta_2, 3);
    printf("Expecting [1, 3, 1]:");
    reverse(ta_3, 3);
    a_disp(ta_3, 3);
    printf("Expecting [1, -4, -100]:");
    reverse(ta_4, 3); 
    a_disp(ta_4, 3);
    printf("Expecting [10, 9, ..., 1]:");
    reverse(ta_5, 10); 
    a_disp(ta_5, 10);
}

void evidence_merge(){
    printf("\n==== Evidence: Merge ====\n");
    printf("Expecting [0, 0, 0, 1, 2, ..., 10]:");
    a_disp(merge(ta_2, 3, ta_5, 10), 13);
    printf("Expecting [-10, -8, 5, 6, 12, 15]:");
    a_disp(merge(ta_6, 3, ta_7, 3), 6);
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_all_positive();
    evidence_exists_positive();
    evidence_first_positive();
    evidence_number_positives();
    // evidence_negate();
    // evidence_partial_sums();
    // evidence_reverse();
    evidence_merge();
    return 0;
}