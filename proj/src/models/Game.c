#include "../models/Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game* createNewGame(){
    Game *game = (Game*) malloc(sizeof(Game));
    game->state = GAME_STATE;
    game->room = newRoom();
    return game;
}

void deleteGame(Game* game) {
    deleteRoom(game->room);
    free(game);
}







