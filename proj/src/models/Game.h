#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "../models/Room.h"
#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../drivers/utils_drivers.h"
#include "../drivers/rtclock.h"

#include "Cloud.h"
#include "Datetime.h"


typedef enum {
    MENU_STATE,
    GAME_STATE,
    PET_STATE,
    INSTRUCTIONS_STATE,
    LEAVE_STATE,
} GameState;

typedef struct {
    Room *room;
    GameState state;
} Game;

Game* createNewGame();
void deleteGame(Game* game);

int control_game(Game *game);
int control_player(Game* game);
int control_cat(Game* game, Entity* cat);

void moveEntity(Entity* entity, Room* room);

void updateGameTime();

#endif /* GAME_H */
