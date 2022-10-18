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