#include "../models/Game.h"

Game* createNewGame(){
    Game *game = (Game*) malloc(sizeof(Game));
    game->state = MENU_STATE;
    //game->menu_sprite = create_sprite("../images/cat0.xpm", 0, 0, 0, 0);
    return game;
}
