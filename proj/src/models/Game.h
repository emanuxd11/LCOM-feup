#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "../models/Room.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../drivers/utils.h"
#include "../drivers/rtclock.h"

#include "Datetime.h"
#include "Room.h"


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

int control_game(Game *game);
int control_player(Entity *entity);
int control_cat(Entity* cat);
void updateGameTime();

#endif /* GAME_H */
