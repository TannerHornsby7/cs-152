#include <stdlib.h>
#include <stdio.h>
#include "pos.h"

pos make_pos(unsigned int r, unsigned int c) {
    if (r + 10 < 10 - r || c + 10 < 10 - c) {
        printf("Error make_pos: negative input");
        exit(1);
    }
    pos res = {r, c};
    return res;
}
