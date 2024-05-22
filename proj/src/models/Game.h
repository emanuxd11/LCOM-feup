#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "../models/Room.h"

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

void deleteGame(Game* game);

#endif /* GAME_H */
