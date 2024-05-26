#include "../models/Game.h"

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
        
        if (control_player(&game->room->player)) return 1;
        
    }

    return 0;
}

int control_player(Entity *entity) {

    entity->velocity = 0;

    if (wIsDown) {
        entity->direction = 90;
        entity->velocity = PLAYER_V;
    }

    if (sIsDown) {
        entity->direction = 270;
        entity->velocity = PLAYER_V;
    }

    if (aIsDown) {
        entity->position.x = 180;
        entity->velocity = PLAYER_V;
    }

    if (dIsDown) {
        entity->position.x = 0;
        entity->velocity = PLAYER_V;
    }

    return 0;
}


Room *newRoom() {
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 100;
    Entity *player = newPlayer(position);
    room->player = *player;
    free(player);

    for (int i = 0; i < 10; i++) {
        Position catPosition;
        catPosition.x = getRandomInt(30, 1000);
        catPosition.y = getRandomInt(30, 700);
        Entity cat;
        cat.position = catPosition;
        // TODO: Add random number to generate a random cat
        cat.type = CAT0;
        room->cats[i] = cat;
    }

    return room;
}








