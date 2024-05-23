#include "controllerKeyboard.h"
#include "utils/utils.h"


int control_game(Game *game, uint8_t scan_code) {
    if (scan_code == ESC_BREAK) {
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
        if (scan_code == TILE_UP || scan_code == TILE_DOWN || scan_code == TILE_LEFT || scan_code == TILE_RIGHT) {
            return control_player(&game->room->player, scan_code);
        }
    }

    return 0;
}


int control_player(Entity *entity, uint8_t scan_code) {

    entity->velocity = 0;

    switch(scan_code){
    switch(scan_code) {
        case TILE_UP:
            entity->direction = 90;
            entity->velocity = PLAYER_V;
            break;

        case TILE_DOWN:
            entity->direction = 270;
            entity->velocity = PLAYER_V;
            break;

        case TILE_LEFT:
            entity->position.x = 180;
            entity->velocity = PLAYER_V;
            break;

        case TILE_RIGHT:
            entity->position.x = 0;
            entity->velocity = PLAYER_V;
            break;
    }

    return 0;
}
