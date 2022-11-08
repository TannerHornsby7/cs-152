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
struct measurement t1 = {2, "m", 2};
struct measurement t2 = {4, "m", 2};
struct measurement t3 = {10, "ft", 1};
struct measurement t4 = {8, "ft", 2};
struct measurement t5 = {14.2, "ft", 2};


void evidence_measurements_conversions() {
    printf("\n==== Evidence: Measurements ====\n");

    // // adding
    // printf("Expecting 6 meters: %f %s\n", add_measurements(t1, t2).value, t2.units);
    // printf("Expecting Error:");
    // add_measurements(t2, t3);
    // printf("Expecting Error:");
    // add_measurements(t3, t4);
    // printf("Expecting 22.2 feet: %f %s\n", add_measurements(t4, t5).value, t5.units);

    // // scaling
    //  printf("Expecting 14 meters: %f %s\n", scale_measurement(t1, 7).value, t1.units);
    // printf("Expecting 142 feet: %f %s\n", scale_measurement(t5, 10).value, t5.units);

    // measure products
    struct measurement prod1 = multiply_measurements(t1, t2);
    // struct measurement prod2 = multiply_measurements(t2, t3); // repor error
    struct measurement prod3 = multiply_measurements(t3, t4);
    struct measurement prod4 = multiply_measurements(t4, t5);

    
     printf("mul: Expecting 8 meters ^ 4: %f %s ^ %d\n", prod1.value, prod1.units, prod1.exponent);
     printf("mul: Expecting 80 feet ^ 3: %f %s ^ %d\n", prod3.value, prod3.units, prod3.exponent);
     printf("mul: Expecting 113.6 fet ^ 4: %f %s ^ %d\n", prod4.value, prod4.units, prod4.exponent);

    // measure to string
    printf("\n");
    printf("tos: Expecting 10 feet: %s\n", measurement_tos(t3));
    printf("tos: Expecting 8 meters^4: %s\n", measurement_tos(prod1));
    printf("tos: Expecting 80 feet^3: %s\n", measurement_tos(prod3));
    printf("tos: Expecting 113.6 feet^4: %s\n", measurement_tos(prod4));


    printf("\n==== Evidence: Conversions ====\n");

    struct conversion t_conv1 = {"in", "cm", 2.54}; // in to cm
    struct conversion t_conv2 = {"ft", "in", 12};   // ft to in
    struct conversion t_conv3 = {"ft", "in", .083}; // in to ft

    struct conversion conversions[] = {t_conv1, t_conv2, t_conv3};

    struct measurement t3_conv = convert_units(conversions, 3, t3, "in");
    struct measurement t4_conv = convert_units(conversions, 3, t4, "in");
    struct measurement t5_conv = convert_units(conversions, 3, t5, "in");


    printf("conv: Expecting 120 inches: %f %s^%d\n", t3_conv.value, t3_conv.units, t3_conv.exponent);
    printf("conv: Expecting  inches ^ 2: %f %s^%d\n", t4_conv.value, t4_conv.units, t4_conv.exponent);
    printf("conv: Expecting  inches ^ 2: %f %s^%d\n", t5_conv.value, t5_conv.units, t5_conv.exponent);


    
}

int main(int argc, char *argv[]) {
    evidence_flip_case();
    evidence_matches();
    evidence_concat_strings();
    evidence_measurements_conversions();
    return 0;
}