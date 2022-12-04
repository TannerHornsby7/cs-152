#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "board.h"
#include "logic.h"

//-h 3 -w 4 -s 2 -l 5
int main(int argc, char *argv[]) {
    // initializing command line args
    unsigned int s, l, w, h;
    if(argc < 9) {
        printf("Too few arguments: %d", argc);
        exit(1);
    }
    if(argc > 9) {
        printf("Too many arguments: %d", argc);
        exit(1);
    }
    for(int i = 1; i < argc; i++){
        if(!strcmp(argv[i], "-s")) s = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-l")) l = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-w")) w = atoi(argv[i+1]);
        if(!strcmp(argv[i], "-h")) h = atoi(argv[i+1]);

    }

    game* g = new_game(s, l, w, h, MATRIX);
    while(true){
        char* move;
        board_show(g->b);
        printf("It is %s's turn\n", (g->player == BLACKS_TURN) ? "BLACK" : "WHITE");
        scanf("%c%*c", &move);

        if(move == '!'){
            magnetize(g);
        } 
            // drop_piece(g, )
    }
    return 0;
}