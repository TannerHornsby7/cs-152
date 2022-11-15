#include <stdlib.h>
#include <stdio.h>
#include "board.h"
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


evidence_logic(){
    
}
/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_pos();
    evidence_board();
    return 0;
}