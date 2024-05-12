#ifndef GAME_H
#define GAME_H

#include "Room.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    MENU_STATE,
    GAME_STATE,
    LEAVE_STATE
} GameState;

typedef struct {
    Room* room;
    GameState state;
} Game;

Game* createNewGame();

int randomNumer(int lower_bound, int upper_bound);

#endif /* GAME_H */
