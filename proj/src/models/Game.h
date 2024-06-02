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
    INSTRUCTIONS_STATE,
    LEAVE_STATE,
} GameState;

typedef struct {
    Room *room;
    GameState state;
    int counter;
} Game;

Game* createNewGame();
void deleteGame(Game* game);

int control_game(Game *game);
int control_player(Game* game);
int control_cat(Game* game, Entity* cat);

int petting_helper_on_mouse_int(Game* game);
int petting_helper_on_timer_int(Game* game);

Position futurePos(Entity* entity, Room* room);
void moveEntity(Entity* entity, Room* room);

void updateGameTime();

#endif /* GAME_H */
