#include "../models/Game.h"
#include "../models/Room.h"
#include "../utils/utils.h"

// keys
extern bool wIsDown;
extern bool aIsDown;
extern bool sIsDown;
extern bool dIsDown;
extern bool escWasPressed;


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

    player->velocity = 0;

    if (wIsDown) {
        player->direction = 90;
        player->velocity = PLAYER_V;
    }

    if (sIsDown) {
        player->direction = 270;
        player->velocity = PLAYER_V;
    }

    if (aIsDown) {
        player->direction = 180;
        player->velocity = PLAYER_V;
    }

    if (dIsDown) {
        player->direction = 0;
        player->velocity = PLAYER_V;
    }

    moveEntity(player);

    return 0;
}








