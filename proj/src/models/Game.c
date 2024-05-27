#include "../models/Game.h"


Datetime datetime;

Game *createNewGame() {
    Game *game = (Game *) malloc(sizeof(Game));
    game->state = GAME_STATE;
    game->room = newRoom();
    return game;
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
