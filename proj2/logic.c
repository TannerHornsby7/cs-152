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

void game_free(game* g){
    board_free(g->b);
    free(g);
}

enum cell switch_turns(game* g) {

    if(g->black_rem > 0 && g->white_rem > 0) {
        g->black_rem--;
        g->white_rem--;
        return switch_turns(g);
    }

    // correct so that if other player is in maglock we don't switch
    enum cell move;
    if (g->player == BLACKS_TURN) {
        if(g->black_rem > 0) {
            g->black_rem--;
            g->player = BLACKS_TURN;
            return switch_turns(g);
        }
        move = BLACK;
        if(g->white_rem == 0) g->player = WHITES_TURN;
        else g->white_rem--;
    } else {
        if(g->white_rem > 0) {
            g->white_rem--;
            g->player = BLACKS_TURN;
            return switch_turns(g);
        }
        move = WHITE;
        if(g->white_rem == 0) g->player = BLACKS_TURN;
        else g->black_rem--;
    }

    return move;
}

bool drop_piece(game* g, unsigned int column) {
    pos place = {0, column};
    pos next = {0, column};

    if(!board_validp(g->b, place)) {
        printf("\ninvalid board location!\n");
        return false;
    }

    if (board_get(g->b, place) != EMPTY) {
        printf("Column %d is full!", column);
        return false;
    }

    for(int i = 0; i < g->b->height; i++){
        place.r = i;
        next.r = i + 1;
        if(i == g->b->height - 1 || board_get(g->b, next) != EMPTY){
            break;
        }
    }

    enum cell move = switch_turns(g);
    board_set(g->b, place, move);
    return true;
}

void swp(board* b, pos loc1, pos loc2) {
    enum cell val1 = board_get(b, loc1);
    enum cell val2 = board_get(b, loc2);

    board_set(b, loc1, val2);
    board_set(b, loc2, val1);
}

void mag_grav(game* g) {
    cell skip_piece = EMPTY;

    if(g->black_rem != 0 && g->white_rem != 0) return;

    else if(g->black_rem != 0){
        skip_piece = BLACK;
    }
    else if(g->white_rem != 0) {
        skip_piece = WHITE;
    }

    for(int j = 0; j < g->b->width; j++){
        for(int i = g->b->height - 1; i > 0; i--) {
                pos above = {i - 1, j};
                pos curr = {i, j};

            while(board_validp(g->b, curr)){
                if(board_get(g->b, curr) == EMPTY && board_get(g->b, above) != skip_piece){
                    swp(g->b, curr, above);
                }
                above = curr;
                curr.r++;

            }
        }
    }
}

void mag_white(game* g){
    for(int j = g->b->width - 1; j > 0; j--) {
        for(int i = g->b->height - 1; i >= 0; i--){
            pos p1 = {i, j - 1};
            pos p2 = {i, j};

            while(board_validp(g->b, p2) && (board_get(g->b, p1) == WHITE && board_get(g->b, p2) == EMPTY)){
                swp(g->b, p1, p2);
                p1.c = j;
                p2.c = ++j;
            }
            mag_grav(g);
        }
    }
}

void mag_black(game* g){
    for(int j = 0; j < g->b->width - 1; j++) {
        for(int i = g->b->height - 1; i >= 0; i--){
            pos p1 = {i, j + 1};
            pos p2 = {i, j};

            while(board_validp(g->b, p2) && (board_get(g->b, p1) == BLACK && board_get(g->b, p2) == EMPTY)){
                swp(g->b, p1, p2);
                p1.c = j;
                p2.c = --j;
            }
            mag_grav(g);
        }
    }
}

bool magnetize(game* g) {
    if(g->player == WHITES_TURN && g->white_rem != 0) return false;
    if(g->player == BLACKS_TURN && g->black_rem != 0) return false;
    
    if(g->player == WHITES_TURN){
        g->white_rem = g->maglock;
        mag_white(g);
    } else {
        g->black_rem = g->maglock;
        mag_black(g);
    }
    mag_grav(g);
    enum cell whose = switch_turns(g);
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

outcome game_outcome(game* g) {
    int s = g->square, h = g->b->height, w = g->b->width, bw = 0, ww = 0, d = 0;

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            pos loc = {j, i};
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
        board_show(g->b);
        game_free(g);
        return DRAW;
    } else if (bw) {
        board_show(g->b);
        game_free(g);
        return BLACK_WIN;
    } else if (ww) {
        board_show(g->b);
        game_free(g);
        return WHITE_WIN;
    }
    else {
        if(board_full(g->b)) {
            board_show(g->b);
            game_free(g);
            return DRAW;
        } else {
            return IN_PROGRESS;
        }
    }
}


// fix turn alternation on maglock
// fix back2back maglock call
// test for any extra bugs, clean up, comment

// implement bitwise representation in board_new
//, board_set
//, board_get
//, and play.c


// fix turn switchin so it accounts for maglock turn skips (done!)
// fix mag so that it calls mag_grav after _rem reaches zero (done!)
// fix back2back maglock segfault (done!)
// fix alternate piece drop glitch (done!)
// fix mag_grav seg fault (done!)
// make evidence suite (done !)




