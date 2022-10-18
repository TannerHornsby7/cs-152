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


unsigned int legal_keys(unsigned char depths, unsigned char macs) {

    unsigned int combinations = 0;

    if(depths == 1) { return 1; };

    for(int i = 0; i < 4; i++) {
        for(int k = 1; k <= depths; k++) {
            // printf("k: %d\n", k);
            for(int m = 1; m <= macs; m++) {
                if ( k + m  <= depths )
                {
                    // printf("k+m: %d\n", k + m);
                    combinations++;
                }
            }
            for(int m = 0; m <= macs; m++) {
                if ( k - m >= 1) {
                    // printf("k-m: %d\n", k - m);
                    combinations++;
                }
            }
        }
    }
    return combinations;
}

// yield calculator
double yield_calc(double rate, unsigned int periods) {
    return (pow((1 + rate), periods) - 1);
}


unsigned int periods_for_yield(double rate, double yield) {
    // catching rate errors
    if (rate < 0) {
        printf("invalid rate"); 
        exit(1); 
    }
    // catching yield errors
    if (yield <= 0) {
        printf("invalid yield"); 
        exit(1); 
    }

    unsigned int periods = 1;
    while(yield_calc(rate, periods) < yield) {
        periods++;
    }
    return periods;
}


void pattern(unsigned char side, unsigned char width, unsigned char height) {
    unsigned int space = 0;
    for(int h = 0; h < height; h++) {
        for(int s = 0; s < side; s++) {
            space = 0;
            while(space < s) {
                printf(" ");
                space++;
            }
            for(int i = 0; i < width; i++) {
                printf("*   ");
            }
            printf("\n");
        }
    }
}