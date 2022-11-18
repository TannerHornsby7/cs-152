#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "logic.h"

/*
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

enum cell switch_turns(game* g) {
    enum cell move;
    if (g->player == BLACKS_TURN) {
        move = BLACK;
        g->player = WHITES_TURN;
        g->black_rem--;
    } else {
        move = WHITE;
        g->player = BLACKS_TURN;
        g->white_rem--;
    }

    return move;
}

bool drop_piece(game* g, unsigned int column) {
    enum cell move = switch_turns(g);
    pos place = {g->b->height - 1, column};

    while(board_get(g->b, place) != EMPTY) {
        if(place.r  == 0) {
            return false;
        }
        place.r--;
    }

    board_set(g->b, place, move);
    return true;
}

// shift elements of the row array
// call the same shift on the columns
// create shift helper that takes a row of cells, gravity bool, and a player
// this helper does the corresponding shift and returns true if a shift occured
// 
// magnetize
// call row shifts
// call gravity shifts
// call switch_turn done
/*
for(int i = 0; i < height; i++) {
    
}
*/

// set base to the bottom column element
// start index at base
// if index is empty, switch it with the element above it
// iterate through the whole column doing this, reseting the base each time

void swp(board* b, pos loc1, pos loc2) {
    enum cell val1 = board_get(b, loc1);
    enum cell val2 = board_get(b, loc2);

    board_set(b, loc1, val2);
    board_set(b, loc2, val1);
}

void col_shift(board* b, int col, int i) {
    if(i == b->height - 1) return;
    pos p1, p2;
    for(int j = i; j >= 0; j--) {
        p1 = make_pos(j, col);
        p2 = make_pos(j + 1, col);
        swp(b, p1, p2);
    }
}

// void row_shift(board* b, int row, int i) {
//     if(i = b->width - 1) return;
//     pos p1, p2;
//     for(int j = i; j >= 0; j--) {
//         p1 = make_pos(j, row);
//         p2 = make_pos(j + 1, row);
//     }
// }

void mag_grav(board* b) {
    for(int i = 0; i < b->width; i++) {
        for(int j = 0; j < b->height-1; j++)
        { // iterate through the column elements, if
          // any are empty,
            pos p1 = make_pos(j, i);
            pos p2 = make_pos(j+1, i);

            if(board_get(b, p2) == EMPTY) {
                col_shift(b, i, j);
            }
        }
    }
}

bool magnetize(game* g) {
    mag_grav(g->b);
    return true;
}