#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"

board* board_new(unsigned int width, unsigned int height, enum type type) {

    board* res = (board *)malloc(sizeof(board));
    res->width = width;
    res->height = height;
    res->type = type;

    if(type == MATRIX){
        // cell matrix creation
        cell** rmatrix = (cell **)malloc(sizeof(cell *) * height);

        for(int i = 0; i < height; i++) {
            rmatrix[i] = malloc(width * sizeof(*rmatrix[i]));
            for(int j = 0; j < width; j++) {
                rmatrix[i][j] = EMPTY;
            }
        }
        res->u.matrix = rmatrix;
    } else {
        // BITS matrix creation
        unsigned int bits = width * height * 2;
        unsigned int ints;

        if(bits % 32 == 0) {
            ints = bits / 32;
        } else {
            ints = (bits / 32) + 1;
        }

        unsigned int* barray = (unsigned int *)malloc(sizeof(unsigned int) * ints);
        unsigned int curr_int = 0;
        int k = 0;

        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i ++){
                int cell_num = (j*(width) + (i + 1));
                if(cell_num % 17 == 0) {
                    barray[k++] = curr_int;
                    curr_int = 0;
                    // printf("\n");
                }
                // printf("10");
                curr_int = curr_int | 0 << (2 * cell_num - 1);
            }
        }
        barray[k] = curr_int;
        res->u.bits = barray;
    }

    return res;
}


void board_free(board* b) {
    
    if (b->type == MATRIX) {
        for(int i = 0; i < b->height; i++) {
        free(b->u.matrix[i]);
        }
        free(b->u.matrix);
    } else {
        free(b->u.bits);
    }

    free(b);
}

cell board_get(board* b, pos p) {
    if(b->type == MATRIX) {
        return b->u.matrix[p.r][p.c];
    } else {
        // BITS matrix creation

        // multiply p.r by p->width
        // add one to p.c
        // val = b->u.bits[]

        unsigned int bitindex = p.r * b->width + p.c + 1; // pos's bit loc
        unsigned int val = (b->u.bits[bitindex / 16] >> 2 * (bitindex % 16)) & 3;
        cell tmp = EMPTY;
        switch (val)
        {
        case 0:
            tmp = EMPTY;
            break;
        case 1:
            tmp = BLACK;
            break;
        case 2:
            tmp = WHITE;
            break;
        }

        return tmp;
    }
}

void board_set(board* b, pos p, cell c) {
    if(b->type == MATRIX) {
        b->u.matrix[p.r][p.c] = c;
    } else {
        // BITS matrix creation

        // multiply p.r by p->width
        // add one to p.c
        // val = b->u.bits[]

        unsigned int bitindex = p.r * b->width + p.c + 1; // pos's bit loc
        cell tmp = EMPTY;
        switch (c)
        {
        case EMPTY:
            tmp = 0;
            break;
        case BLACK:
            tmp = 1;
            break;
        case WHITE:
            tmp = 2;
            break;
        }

        b->u.bits[bitindex / 16] |= tmp << 2 * (bitindex % 16);
    }
}


// prints board with specified format
void board_show(board* b) {
    printf("\n");
    char start = 'A';
    printf("  ");
    for(int i = 0; i < b->width; i++) {
        if(i < 10){
            printf("%d", i);
        } else if (10 <= i && i < 36) {
            start = 'A';
            printf("%c", start + (i - 10));
        } else if (36 <= i && i < 62) {
            start = 'a';
            printf("%c", start + (i - 36));
        } else if (i >= 62) {
            printf("?");
        }
    }
    printf("\n");

    for(int j = 0; j < b->height; j++) {
        if(j < 10){
            printf("%d ", j);
        } else if (10 <= j && j < 36) {
            start = 'A';
            printf("%c ", start + (j - 10));
        } else if (36 <= j && j < 62) {
            start = 'a';
            printf("%c ", start + (j - 36));
        } else if (j >= 62) {
            printf("? ");
        }

        for(int i = 0; i < b->width; i++) {
            pos spot = {j, i};
            cell t_cell = board_get(b, spot);
            if(t_cell == EMPTY) {
                printf(".");
            } else if (t_cell == BLACK) {
                printf("*");
            } else {
                printf("o");
            }
        }
        printf("\n");
    }
}

int board_validp(board *b, pos p) {
    int valid = 1;
    if(p.c < 0 || p.c >= b->width ) {
        valid = 0;
    }
    if(p.r < 0 || p.r >= b->height) {
        valid = 0;
    }
    return valid;
}

int board_full(board *b) {
    for(int i = 0; i < b->height; i++){
        for(int j = 0; j < b->width; j++) {
            pos loc = {i, j};
            if(board_get(b, loc) == EMPTY) return false;
        }
    }
    return true;
}
