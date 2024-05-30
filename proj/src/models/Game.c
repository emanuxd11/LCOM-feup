#include "../models/Game.h"
#include "../models/Room.h"
#include "../utils/utils.h"
#include <math.h>

// keys
extern bool wIsDown;
extern bool aIsDown;
extern bool sIsDown;
extern bool dIsDown;
extern bool escWasPressed;


Datetime datetime;

Game *createNewGame() {
    Game *game = (Game *) malloc(sizeof(Game));
    game->state = GAME_STATE;
    game->room = newRoom();
    return game;
}

void deleteGame(Game* game) {
    deleteRoom(game->room);
    free(game);
}
    
int control_game(Game *game) {
    if (escWasPressed) {
        escWasPressed = false;
        switch(game->state) {
            case MENU_STATE:
                game->state = LEAVE_STATE;
                break;
            case GAME_STATE:
                game->state = MENU_STATE;
            default:
                game->state = LEAVE_STATE;
        }
        return 0;
    }

    if (game->state == GAME_STATE) {
        
        if (control_player(game->room->player)) return 1;
        
    }

    return 0;
}

int control_player(Entity *player) {

    // x and y coords of player velocity vector
    int xDir = 0;
    int yDir = 0;

    if (wIsDown) yDir+=1;

    if (sIsDown) yDir-=1;

    if (aIsDown) xDir-=1;

    if (dIsDown) xDir+=1;

    player->velocity = PLAYER_V;

    if (xDir == 0 && yDir == 0) player->velocity = 0;  // no movement key down
    // very hardcoded and ugly yes but do not fret! it is also very localized
    else if (xDir == 0) player->direction = 90 * yDir;
    else if (yDir == 0) player->direction = xDir == 1 ? 0 : -180;
    else if (xDir == 1 && yDir == 1) player->direction = 45;
    else if (xDir == -1 && yDir == 1) player->direction = 135;
    else if (xDir == 1 && yDir == -1) player->direction = -45;
    else if (xDir == -1 && yDir == -1) player->direction = -135;
    

    moveEntity(player);

    return 0;
}

int control_cat(Entity* cat) {

    return 0;
}

void updateGameTime() {
    datetime = rtc_read_datetime();
}
