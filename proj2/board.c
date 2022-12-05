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

    free(b->u.matrix);
    free(b);
}

/*

The board may be more than ten rows or columns in size. 
If so, the indices should move on to using capital letters. 

The label for index 10 should be A, for index 11 should be B, and so on. 
Go all the way to the end of the alphabet if needed. If you have more 
than 36 rows or columns, 

then the lower-case letters should be used next. 
Once these characters are exhausted, 

use ? for all of the remaining rows or 
columns, if any, to indicate that you have run out of labels.

*/

// prints board with specified format
void board_show(board* b) {
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
    printf("\n  ");
     for(int i = 0; i < b->width; i++) {
        printf(" ");
    }
    printf("\n");

    for(int j = 0; j < b->height; j++) {
        if(j < 10){
            printf("%d", j);
        } else if (10 <= j && j < 36) {
            start = 'A';
            printf("%c", start + (j - 10));
        } else if (36 <= j && j < 62) {
            start = 'a';
            printf("%c", start + (j - 36));
        } else if (j >= 62) {
            printf("?");
        }

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
