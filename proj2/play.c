#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "logic.h"

unsigned int label_to_index(char move){
    // 65 = A
    // 97 = a
    int val = move - '0'; // evaluates to deci val move - deci val 0
    if(0 <= val && val <= 9) {
        return val;
    }
    else if (17 <= val && val <= 43) return val - 7;
    else if (49 <= val && val <= 75) return val - 13; // 52 - 13 = 39
    else return 0;
}

// return 1 if game over, 0 if game continue;
int wc(game* g){
    outcome out = game_outcome(g);

    if(out > 0){
        if(out == 1) {
            printf("BLACK WINS\n");
        }
        else if(out == 2) {
            printf("WHITE WINS!!\n");
        }
        else {
            printf("DRAW!!!\n");
        }
        return 1;
    } else {
        return 0;
    }
}
//-h 3 -w 4 -s 2 -l 5
int main(int argc, char *argv[]) {
    // initializing command line args
    unsigned int s, l, w, h, r;

    if(argc < 10) {
        printf("Too few arguments: %d", argc);
        exit(1);
    }

    if(argc > 10) {
        printf("Too many arguments: %d", argc);
        exit(1);
    }

    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-s")) s = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-l")) l = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-w")) w = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-h")) h = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-b")) r = BITS;
        if(!strcmp(argv[i], "-m")) r = MATRIX;

    }

    game* g = new_game(s, l, w, h, r);
    char move;

    while(true){
        board_show(g->b);
        printf("It is %s's turn\n", (g->player == BLACKS_TURN) ? "BLACK" : "WHITE");
        scanf("%c%*c", &move);


        if(move == '!'){
            magnetize(g);
            if(wc(g)) return 0;
            continue;
        } 

        unsigned int mv = move - '0';

        if((mv > 9 && mv < 17) || (mv > 43 && mv < 49) || mv > 75) {
            printf("\n Error, invalid move input: %c(%d)\n", move, mv);
            move = '0';
            continue;
        }

        unsigned int index = label_to_index(move);
        if(index >= g->b->width) {
            printf("column index %c(%d) is outside the width of the board %d", move, index, g->b->width);
            continue;
        }


        if(!drop_piece(g, index)) continue;

        mag_grav(g);

        if(wc(g)) return 0;
    }
    return 0;
}