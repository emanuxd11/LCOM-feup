#include "Room.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    MENU_STATE,
    GAME_STATE
} GameState;

typedef struct {
    Room* room;
    GameState state;
} Game;
