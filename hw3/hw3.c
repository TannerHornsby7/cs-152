#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hw3.h"

int all_positive(int a[], unsigned int alen) {

    for(int i = 0; i < alen; i++) {
        if (a[i] <= 0) { return 0;};
    }

    return 1;
}

int exists_positive(int a[], unsigned int alen) {
    
    for(int i = 0; i < alen; i++) {
        if (a[i] > 0) { return 1;};
    }

    return 0;
}

int first_positive(int a[], unsigned int alen) {

    for (int i = 0; i < alen; i++)
    {
        if(a[i] > 0) {
            return i;
        }
    }
    return -1;
}

unsigned int number_positives(int a[], unsigned int alen) {

    int count = 0;

    for (int i = 0; i < alen; i++)
    {
        if(a[i] > 0) {
            count++;
        }
    }
    return count;
}

void negate(int a[], unsigned int alen) {
    for (int i = 0; i < alen; i++)
    {
        a[i] *= -1;
    }    
}

int* partial_sums(int a[], unsigned int alen) {
    int* res = (int *)malloc(sizeof(int) * alen);
    int partial_sum = 0;

    for(int i = 0; i < alen; i++) {
        partial_sum += a[i];
        res[i] = partial_sum;
    }

    return res;
}

void reverse(int a[], unsigned int alen) {
    int temp = 0;
    for (int i = 0; i < alen / 2; i++)
    {
        temp = a[i];
        a[i] = a[alen - 1 - i];
        a[alen - 1 - i] = temp;
    }    
}

int* merge(int* a, unsigned int alen, int* b, unsigned int blen) {
    int* res = (int*)malloc(sizeof(int) * (alen + blen));
    int ait = 0, bit = 0, i = 0;

    //inserting in order
    while(ait < alen && bit < blen) {
        if(a[ait] < b[bit]) {
            res[i] = a[ait++];
        }
        else {
            res[i] = b[bit++];
        }
        i++;
    }

    //appending leftovers
    while(ait < alen) {
        res[i++] = a[ait++];
    }
    while(bit < blen) {
        res[i++] = b[bit++];
    }

    return res;
}