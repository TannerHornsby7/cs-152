#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"


enum turn {
    BLACKS_TURN,
    WHITES_TURN
};

typedef enum turn turn;


enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;


struct game {
    unsigned int square, maglock, black_rem, white_rem;
    board* b;
    turn player;
};

typedef struct game game;


game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type);

void game_free(game* g);

bool drop_piece(game* g, unsigned int column);

bool magnetize(game* g);

outcome game_outcome(game* g);

int check_square(game* g, pos loc);

#endif /* LOGIC_H */