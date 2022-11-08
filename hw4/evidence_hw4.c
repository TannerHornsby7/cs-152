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

char* t_str1[] = {"banana", "apple","pear", "grape"};
char* t_str2[] = {"b", "a","p", "e"};
char* t_str3[] = {"Hi", "Bi","Ci", "Ki"};
char* t_str4[] = {"a", "e","r", "p"};


void evidence_concat_strings() {
    printf("\n==== Evidence: String Concatenation ====\n");
    printf("Expecting banana apple pear grape: %s\n", concat_strings(t_str1, 4, ' ')); // -
    printf("Expecting b+a+p+e: %s\n", concat_strings(t_str2, 4, '+')); // 0
    printf("Expecting Hi_Bi_Ci_Ki: %s\n", concat_strings(t_str3, 4, '_')); // +
    printf("Expecting a/e/r/p: %s\n", concat_strings(t_str4, 4, '/')); // mix
}

// measurements and conversions tests
struct measurement t1 = {2, "meters", 2};
struct measurement t2 = {4, "meters", 2};
struct measurement t3 = {10, "feet", 1};
struct measurement t4 = {8, "feet", 2};
struct measurement t5 = {14.2, "feet", 2};


void evidence_measurements_conversions() {
    printf("\n==== Evidence: Measurements ====\n");

    // adding
    printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    //printf("Expecting Error:");
    //add_measurements(t2, t3);
    //printf("Expecting Error:");
    //add_measurements(t3, t4);
    printf("Expecting 22.2 meters: %f %s\n", add_measurements(t4, t5).value, t5.units);

    // scaling
     printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    //printf("Expecting Error:");
    //add_measurements(t2, t3);
    //printf("Expecting Error:");
    //add_measurements(t3, t4);
    printf("Expecting 22.2 meters: %f %s\n", add_measurements(t4, t5).value, t5.units);

    // measure products
     printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    //printf("Expecting Error:");
    //add_measurements(t2, t3);
    //printf("Expecting Error:");
    //add_measurements(t3, t4);
    printf("Expecting 22.2 meters: %f %s\n", add_measurements(t4, t5).value, t5.units);

    // measure to string
     printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    //printf("Expecting Error:");
    //add_measurements(t2, t3);
    //printf("Expecting Error:");
    //add_measurements(t3, t4);
    printf("Expecting 22.2 meters: %f %s\n", add_measurements(t4, t5).value, t5.units);

    

    printf("\n==== Evidence: Conversions ====\n");
    printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    //printf("Expecting Error:");
    //add_measurements(t2, t3);
    //printf("Expecting Error:");
    //add_measurements(t3, t4);
    printf("Expecting 22.2 meters: %f %s\n", add_measurements(t4, t5).value, t5.units);
}

int main(int argc, char *argv[]) {
    evidence_flip_case();
    evidence_matches();
    evidence_concat_strings();
    evidence_measurements_conversions();
    return 0;
}