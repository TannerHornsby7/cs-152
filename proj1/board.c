#include <stdlib.h>
#include <stdio.h>
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

/*
The board_free function fully frees the board, including whichever internal
representation it is using. For this and all the remaining functions, raise
an error if the input board claims to use other than the matrix 
representation. Because you will not encounter such boards during this phase
of the project, the details of such boards are not specified in this
document, and your code should immediately flag any such boards as
unsupported.
*/
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
