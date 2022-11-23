#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"

board* board_new(unsigned int width, unsigned int height, enum type type) {
    board* res = (board *)malloc(sizeof(board));
    res->width = width;
    res->height = height;
    res->type = type;
    cell** rmatrix = (cell **)malloc(sizeof(cell *) * height);

    for(int i = 0; i < height; i++) {
        rmatrix[i] = malloc(width * sizeof(*rmatrix[i]));
        for(int j = 0; j < width; j++) {
            rmatrix[i][j] = EMPTY;
        }
    }
    
    res->u.matrix = rmatrix;
    return res;
}


void board_free(board* b) {
    for(int i = 0; i < b->height; i++) {
        free(b->u.matrix[i]);
    }

    if(b->u.bits) {
        printf("Error: Restricted type Choice - BITS\n");
        exit(1);
    }

    free(b->u.matrix);
    free(b);
}

// prints board with specified format
void board_show(board* b) {
    printf("  ");
    for(int i = 0; i < b->width; i++) {
        printf("%d", i);
    }
    printf("\n  ");
     for(int i = 0; i < b->width; i++) {
        printf(" ");
    }
    printf("\n");

    for(int j = 0; j < b->height; j++) {
        printf("%d ", j);
        for(int i = 0; i < b->width; i++) {
            cell t_cell = b->u.matrix[j][i];
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

cell board_get(board* b, pos p) {
    return b->u.matrix[p.r][p.c];
}

void board_set(board* b, pos p, cell c) {
    b->u.matrix[p.r][p.c] = c;
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
