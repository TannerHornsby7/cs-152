#ifndef BOARD_H
#define BOARD_H

#include "pos.h"



enum cell {
    EMPTY,
    BLACK,
    WHITE
};

typedef enum cell cell;


union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};

typedef union board_rep board_rep;


enum type {
    MATRIX, BITS
};


struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};

typedef struct board board;


board* board_new(unsigned int width, unsigned int height, enum type type);

// frees a board
void board_free(board* b);

// shows a board
void board_show(board* b);

// gets a cell value from a board
cell board_get(board* b, pos p);

// sets a cell value for a board
void board_set(board* b, pos p, cell c);

// checks if a provided position is on a board
int board_validp(board *b, pos p);

// checks if a board is full
int board_full(board *b);

#endif /* BOARD_H */