#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "logic.h"

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

// void b_mag(board* b, int row, int i) {
//     if(i = b->width - 1) return;
//     pos p1, p2;
//     for(int j = i; j >= 0; j--) {
//         p1 = make_pos(j, row);
//         p2 = make_pos(j + 1, row);
//     }
// }

// void w_mag(board* b, int row, int i) {
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
    enum cell whose = switch_turns(g);
    // if(whose == BLACK) {
    //     b_mag();
    // } else {
    //     w_mag();
    // }
    mag_grav(g->b);
    return true;
}


int check_square(game* g, pos loc) {
    unsigned int s = g->square;
    cell main_square = board_get(g->b, loc);
    for(int i = 0; i < s; i++) { //starts from top left
        for(int j = 0; j < s; j++) {
            pos new_loc = {i + loc.r, j + loc.c};
            if(!board_validp(g->b, new_loc)){
                return 0;
            } else {
                cell new_square = board_get(g->b, new_loc);
                if(new_square != main_square) return 0;
            }
        }
    }
    return 1;
}

// iterate through arr h - s and w - s calling check square on each loc

outcome game_outcome(game* g) {
    int s = g->square, h = g->b->height, w = g->b->width, bw = 0, ww = 0, d = 0;

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            pos loc = {i, j};
            if(check_square(g, loc)){
                cell winner = board_get(g->b, loc);
                if(winner == BLACK){
                    bw = 1;
                }
                
                if (winner == WHITE) {
                    ww = 1;
                }
            };
        }
    }

    if(bw && ww) {
        return DRAW;
    } else if (bw) {
        return BLACK_WIN;
    } else if (ww) {
        return WHITE_WIN;
    }
    else {
        if(board_full(g->b)) {
            return DRAW;
        } else {
            return IN_PROGRESS;
        }
    }
}

// 1) game outcome
// 2) b/w mag
// 3) mag mag_grav
// 4) linked list probs
// 5) valgrind
// 6) lecture listen

// fix gravity function to move pieces based on what is magnetized
// create b and w mag functions to pull pieces to sides
// complete linked list practice problems