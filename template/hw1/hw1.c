#include <math.h>
#include "hw1.h"

int is_buoyant(double weight, double radius) {
    if (62.4 * (4 / 3.0) * M_PI *  pow(radius, 3) >= weight) {
        return 1;
    }
    else {
        return 0;
    }
}

unsigned int pods_to_order(unsigned int people, unsigned int cups_per_day, 
unsigned int days) {
    int cups = people * days * cups_per_day;
    if(cups % 96 == 0) {
        return cups;
    } else {
        return (cups / 96) * 96 + 96;
    }
}

unsigned int gcd(unsigned int n, unsigned int m) {
    if(m == 0) { return n; };
    return gcd(m, n % m);
}