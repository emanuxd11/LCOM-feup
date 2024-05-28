#include "../models/Game.h"

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

    if (wIsDown) entity->position.y -= 10;
    if (aIsDown) entity->position.x -= 10;
    if (sIsDown) entity->position.y += 10;
    if (dIsDown) entity->position.x += 10;

    return 0;
}


Room *newRoom() {
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 500;
    Entity *player = newPlayer(position);
    room->player = *player;
    free(player);

    for (int i = 0; i < 10; i++) {
        Position catPosition;
        catPosition.x = getRandomInt(30, 1000);
        catPosition.y = getRandomInt(370, 700);
        Entity cat;
        cat.position = catPosition;
        // TODO: Add random number to generate a random cat
        cat.type = CAT0;
        room->cats[i] = cat;
    }

    return room;
}

Entity *newPlayer(Position Position) {
    Entity *entity = (Entity *) malloc(sizeof(Entity));
    entity->position = Position;
    entity->type = PLAYER;

    return entity;
}

void updateGameTime() {
    datetime = rtc_read_datetime();
}
