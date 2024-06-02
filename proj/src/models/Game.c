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
extern bool eWasPressed;

Datetime datetime;

Game *createNewGame() {
  Game *game = (Game *) malloc(sizeof(Game));
  // game->state = MENU_STATE;
  game->state = GAME_STATE;
  game->room = newRoom();
  game->counter = 0;
  return game;
}

void deleteGame(Game* game) {
    deleteRoom(game->room);
    free(game);
}
    
Entity* selectedCat;
int control_game(Game *game) {
  if (escWasPressed) {
    escWasPressed = false;
    switch (game->state) {
      case MENU_STATE:
        game->state = LEAVE_STATE;
        break;
      case GAME_STATE:
        game->state = MENU_STATE;
        break;
      case INSTRUCTIONS_STATE:
        game->state = MENU_STATE;
        break;
      default:
        game->state = LEAVE_STATE;
    }
  }
  if (game->state == GAME_STATE) {
      
    control_player(game);
    selectedCat = getSelectedCat(game->room);
    
    for (int i = 0; i < 10; i++) {
        control_cat(game, game->room->cats[i]);
    }

    if (eWasPressed) {
        eWasPressed = false;
        if (selectedCat != NULL) game->state = PET_STATE;
    }
      
  }
  if (game->state == PET_STATE) {
    // TO DO: start state machin corresponding to selectedCat and draw that cat
    game->state = MENU_STATE;
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

Position futurePos(Entity* entity, Room* room) {

    Position cPos = candidatePos(entity);

    // check border
    if (cPos.x > 1024 || cPos.x < 0) cPos.x = entity->position->x;
    if (cPos.y > 768 || cPos.y < 0) cPos.y = entity->position->y;

    Entity* otherEntity;

    // check collisions with cats
    for (int i = 0; i < 10; i++) {
        otherEntity = room->cats[i];
        
        if (otherEntity == NULL
            || (entity->position->x == otherEntity->position->x && entity->position->y == otherEntity->position->y)) continue;

        if (checkCollision(cPos, entity, otherEntity) != NO_COLLISION) {
            entity->direction = entity->direction + 180;
            entity->velocity = 1;
            cPos = candidatePos(entity);
        }

    }

    // check collisions with player 
    if (entity->type != PLAYER) {
        if (checkCollision(cPos, entity, room->player) != NO_COLLISION) {
            entity->direction = entity->direction + 180;
            entity->velocity = 1;
            cPos = candidatePos(entity);
        }

    }

    return cPos;
}



void moveEntity(Entity* entity, Room* room) {
    Position fPos = futurePos(entity, room);

    entity->position->x = fPos.x;
    entity->position->y = fPos.y;

}


