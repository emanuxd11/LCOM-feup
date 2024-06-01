#include "../models/Game.h"
#include "../models/Room.h"
#include "../utils/utils.h"
#include <math.h>
#include "CatInfo.h"

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
        
        control_player(game);
        
        for (int i = 0; i < 10; i++) {
            control_cat(game, game->room->cats[i]);
        }
        
    }

    return 0;
}

int control_player(Game* game) {
    Entity* player = game->room->player;

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
    

    moveEntity(player, game->room);

    return 0;
}

int control_cat(Game* game, Entity* cat) {
    CatInfo* catInfo = (CatInfo*) cat->typeInfo;
    
    
    if (catInfo->moveCountdown == 0) {
        catInfo->isIdle = !catInfo->isIdle;
        cat->velocity = CAT_V;

        cat->direction = randomNumer(1, 360);

        catInfo->moveCountdown = randomNumer(100, 300);
    }

    if (catInfo->isIdle) {
        cat->velocity = 0;
    }

    catInfo->moveCountdown--;
    moveEntity(cat, game->room);

    return 0;
}

void updateGameTime() {
    datetime = rtc_read_datetime();
}

Position candidatePos(Entity* entity, Room* room) {

    Position cPos;

    double distance = entity->velocity / FRAME_RATE;

    cPos.x = entity->position->x + (distance * cos(degToRad(entity->direction)));
    cPos.y = entity->position->y - (distance * sin(degToRad(entity->direction)));

    // check border
    if (cPos.x > 1024 || cPos.x < 0) cPos.x = entity->position->x;
    if (cPos.y > 768 || cPos.y < 0) cPos.y = entity->position->y;

    Entity* otherEntity;

    // check collisions with cats
    for (int i = 0; i < 10; i++) {
        otherEntity = room->cats[i];
        
        if (otherEntity == NULL
            || (entity->position->x == otherEntity->position->x && entity->position->y == otherEntity->position->y)) continue;

        switch (checkCollision(cPos, entity, otherEntity)) {
            
            case X_COLLISION:
                cPos.x = entity->position->x;
                break;

            case Y_COLLISION:
                cPos.y = entity->position->y;
                break;
                
            case NO_COLLISION:
                break;
        }

    }

    if (entity->type != PLAYER) {
        switch (checkCollision(cPos, entity, room->player)) {
            case X_COLLISION:
                cPos.x = entity->position->x;
                break;
            case Y_COLLISION:
                cPos.y = entity->position->y;
                break;
            case NO_COLLISION:
                break;
        }

    }

    return cPos;
}

void moveEntity(Entity* entity, Room* room) {
    Position cPos = candidatePos(entity, room);

    //add collision checks

    entity->position->x = cPos.x;
    entity->position->y = cPos.y;

}
