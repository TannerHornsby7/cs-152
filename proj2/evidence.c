#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "logic.h"
#include "pos.h"

/* evidence pos */
void evidence_pos() {
    pos p1 = make_pos(1, 2);
    pos p2 = make_pos(0, 0);
    // pos p3 = make_pos(-3, 0);

    printf("*** Testing: Pos ***\n");
    printf("POS: (1, 2) = (%d, %d) \n", p1.r, p1.c);
    printf("POS: (0, 0) = (%d, %d) \n", p2.r, p2.c);
    // printf("POS: Expecting (-3, 0) = (%d, %d) \n", p3.r, p3.c);

}

/* evidence board */
void evidence_board() {
    // new free show set get
    board* b1 = board_new(1, 2, MATRIX);
    board* b2 = board_new(0, 0, BITS);
    // board* b3 = board_new(-2, 4, MATRIX);
    board* b4 = board_new(4, 4, MATRIX);


    printf("*** Testing: Board ***\n");
    printf("new: 1 x 2 M = %d x %d %d \n", b1->height, b1->width, b1->type);
    printf("new: 0 x 0 B = %d x %d %d \n", b2->height, b2->width, b2->type);
    printf("new: 4 x 4 M = %d x %d %d \n", b4->height, b4->width, b4->type);
    printf("\n");

    printf("new: 1 x 2 M = %d x %d %d \n", b1->height, b1->width, b1->type);
    printf("new: 0 x 0 B = %d x %d %d \n", b2->height, b2->width, b2->type);
    printf("new: 4 x 4 M = %d x %d %d \n", b4->height, b4->width, b4->type);

    printf("new: Checking element setting\n");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("new: checking elements in b4 %d\n", b4->u.matrix[i][j]);
        }
    }

    printf("show: Showing matrix b4:\n");
    board_show(b4);
    printf("setting top left to black and bottom right to white\n");
    pos tleft = {0 , 0};
    pos bright = {3, 3};
    board_set(b4, tleft, BLACK);
    board_set(b4, bright, WHITE);
    board_show(b4);
    printf("get: getting top left element 1 : %d\n", board_get(b4, tleft));
    printf("get: getting bottom right element 2 : %d\n", board_get(b4, bright));



    printf("\n");

}

void evidence_new_game(){
    // game* g1 = new_game(2, 3, 3, 3, BITS); // type error
    // game* g2 = new_game(2, 0, 1, 1, MATRIX); // square error
    game* g3 = new_game(2, 3, 3, 3, MATRIX); // 3x3 board with 2x2 square
    game* g4 = new_game(2, 3, 50, 2, MATRIX); // 3x3 board with 2x2 square
    // board_display(g1->b);
    board_show(g3->b); // expecting 3x3 matrix
    board_show(g4->b); // expecting 50x3 matrix
}

void evidence_drop_piece(){
    // CONSTANTS FOR TESTS
    pos topmid = {0, 1};
    pos topright = {0, 2};
    pos mid = {1, 1};
    pos botright = {2, 2};
    pos toolow = {-1, 4};
    pos toohigh = {0, 40000};
    game* g = new_game(2, 3, 3, 3, MATRIX); // 3x3 board with 2x2 square

    while (drop_piece(g, 0)) {
    }
    board_show(g->b); // col 0 should be full of black white black

    while (drop_piece(g, 2)) {
    }
    board_show(g->b); // col 0 should be full of white black white

    drop_piece(g, 2); // should return col full!
    drop_piece(g, 1);
    board_show(g->b); // left col full middle one right col full
    // passes all test! (fills col with alternating game pieces)

}

void evidence_mag_grav(){
    // CONSTANTS FOR TESTS
    pos topmid = {0, 1};
    pos topright = {0, 2};
    pos topleft = {0, 0};
    pos mid = {1, 1};
    pos botright = {2, 2};
    pos toolow = {-1, 4};
    pos toohigh = {0, 40000};
    game* g = new_game(2, 3, 3, 3, MATRIX); // 3x3 board with 2x2 square
    pos tr = make_pos(0, g->b->width - 1);

    // mag_grav(g);
    board_set(g->b, tr, BLACK);
    board_set(g->b, mid, WHITE);
    board_set(g->b, topmid, BLACK);
    board_show(g->b);

    mag_grav(g); // mid elements should move down together
    board_show(g->b);

    board_set(g->b, topleft, WHITE); // white in top left
    board_show(g->b);

    mag_grav(g);
    board_show(g->b); // white in bot left

    g->white_rem = 3;
    board_set(g->b, topleft, WHITE);
    board_show(g->b);
    mag_grav(g);
    board_show(g->b); // should stay the same as above
    g->white_rem = 0;
    mag_grav(g);
    board_show(g->b); // now it should fall as rem is 0

    // passes all tests! (when called, brings pieces down to lowest possible level)
}

void evidence_magnetize(){
    // CONSTANTS FOR TESTS
    pos topmid = {0, 1};
    pos topright = {0, 2};
    pos mid = {1, 1};
    pos botright = {2, 2};
    pos toolow = {-1, 4};
    pos toohigh = {0, 40000};
    game* g = new_game(2, 3, 3, 3, MATRIX); // 3x3 board with 2x2 square

    // board_set(g->b, topright, BLACK);
    // board_show(g->b);
    // printf("Expecting Whites turn(1): %d\n", g->player);
    // printf("Expecting %d : %d\n", 0, g->white_rem);
    // printf("Expecting %d : %d\n", 0, g->black_rem);
    // magnetize(g);
    // printf("Expecting Blacks turn(0): %d\n", g->player);
    // printf("Expecting %d : %d\n", g->maglock, g->white_rem);
    // printf("Expecting %d : %d\n", 0, g->black_rem);
    // board_show(g->b);

    // passes all tests!
}

void evidence_game_outcome(){
    // CONSTANTS FOR TESTS
    pos topmid = {0, 1};
    pos topright = {0, 2};
    pos mid = {1, 1};
    pos botright = {2, 2};
    pos toolow = {-1, 4};
    pos toohigh = {0, 40000};
    game* g = new_game(2, 3, 3, 3, MATRIX); // 3x3 board with 2x2 square

    for(int i = 0; i < g->b->width; i++){
         while (drop_piece(g, i)) {
    }
    }
    board_show(g->b);
    printf("Expecting 3: %d\n", game_outcome(g));

    printf("Expecting 0: %d\n", game_outcome(g));
    printf("Expecting 1: %d\n", board_validp(g->b, topmid));
    printf("Expecting 0: %d\n", board_validp(g->b, toolow));
    printf("Expecting 0: %d\n", board_validp(g->b, toohigh));
    printf("Expecting 1: %d\n", check_square(g, mid));
    printf("Expecting 0: %d\n", check_square(g, botright));
    printf("Expecting 1: %d\n", game_outcome(g));
}

/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    // evidence_pos();
    // evidence_board();
    // evidence_new_game();
    // evidence_drop_piece();
    evidence_mag_grav();
    // evidence_magnetize();
    // evidence_game_outcome();
    return 0;
}