#include "../models/Game.h"

Game* createNewGame(){
    Game *game = (Game*) malloc(sizeof(Game));
    game->state = MENU_STATE;
    return game;
}
