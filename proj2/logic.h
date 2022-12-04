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

// creates a new game
game* new_game(unsigned int square, unsigned int maglock, unsigned int width,
               unsigned int height, enum type type);

// frees a game
void game_free(game* g);

// drops a piece into the game board (returns false if unable)
bool drop_piece(game* g, unsigned int column);

// performs the magnetize operation on the game board (returns false if unable)
bool magnetize(game* g);

// returns the outcome of a game
outcome game_outcome(game* g);

#endif /* LOGIC_H */