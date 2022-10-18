#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hw2.h"

unsigned char tens_letters(unsigned char number) {
    
    switch (number)
    {
    case '1':
        return '3';
        break;
    case '2':
    case '3':
    case '4':
    case '6':
    case '9':
        return '5';
        break;
    case '0':
    case '5':
        return '4';
        break;
    case '7': 
    case '8':
        return '6';
        break;
    default:
        printf("Enter a char of the form 0-9");
        exit(1);
        break;
    }
}

void common_divisors(unsigned int n, unsigned int m) {
    int length = 0;
    if (n < m) {
        length = n;
    } else {
        length = m;
    }
    
    printf("1");
    for(int i = 2; i <= length; i++) {
        if(n % i == 0 && m % i == 0) {
            printf(" %d", i);
        }
    }
    printf("\n");
}

// helper factorial
unsigned int factorial(unsigned int val) {
    for(int i = val; i >= 1; i--) {
        val *= i;
    }
    return val;
}

unsigned int legal_keys(unsigned char depths, unsigned char macs) {
    unsigned int variations = 0;
    unsigned int combinations = 1;

    for(int q = 0; q < 4; q++){
        for(int i = 1; i <= depths; i++) {
            for(int j = 0; j <= macs; j++) {
                // bottom range
                if( i - j > 1 ) {
                    variations += 1;
                }
                // top range
                if ( i + j < depths ) {
                    variations += 1;
                }
            }
        }
        combinations *= variations;
        variations = 0;
    }

    return combinations;
}