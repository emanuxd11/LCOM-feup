#include "controllerKeyboard.h"

int controllGame(Game* game, uint8_t scan_code){
    if (scan_code == ESC_BREAK){
        switch(game->state){
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

    if (game->state == GAME_STATE){
        if (scan_code == TILE_UP || scan_code == TILE_DOWN || scan_code == TILE_LEFT || scan_code == TILE_RIGHT){
            return controllPlayer(&game->room->player, scan_code);
        }
    }

    return 0;
}


int controllPlayer(Entity* entity, uint8_t scan_code){

    switch(scan_code){
        case TILE_UP:
            entity->position.y -= 10;
            break;
        case TILE_DOWN:
            entity->position.y += 10;
            break;
        case TILE_LEFT:
            entity->position.x -= 10;
            break;
        case TILE_RIGHT:
            entity->position.x += 10;
            break;
    }
    return 0;
}


