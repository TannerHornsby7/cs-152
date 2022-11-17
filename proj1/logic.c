#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "logic.h"

/*
drop piece
magenetize
game outcome
*/

game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type) {
    if (type == BITS) {
        fprintf(stderr, "new_game: Invalid Type 'BITS'\n");
        exit(1);
    }
    if (square > height || square > width) {
        fprintf(stderr, "new_game: Invalid square vs hxw: %d vs %dx%d\n", square, height, width);
        exit(1);
    }
    game* res = (game *)malloc(sizeof(game));
    board* b = board_new(width, height, type);

    res->square = square;
    res->maglock = maglock;
    res->black_rem = 0;
    res->white_rem = 0;
    res->b = b;
    res->player = BLACKS_TURN;

    return res;
}

bool drop_piece(game* g, unsigned int column) {
    enum cell move = BLACK;
    pos place = {g->b->height - 1, column};

    while(board_get(g->b, place) != EMPTY) {
        if(place.r  == 0) {
            return false;
        }
        place.r--;
    }

   

    if (g->player == BLACKS_TURN) {
        move = BLACK;
        g->player = WHITES_TURN;
    } else {
        move = WHITE;
        g->player = BLACKS_TURN;
    }

    board_set(g->b, place, move);
    return true;
}
