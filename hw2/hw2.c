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
    case '5':
        return '4';
        break;
    case '7': 
    case '8':
        return '6';
        break;
    default:
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