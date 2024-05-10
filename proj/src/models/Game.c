#include "../models/Game.h"

Game* createNewGame(){
    Game *game = (Game*) malloc(sizeof(Game));
    game->state = MENU_STATE;
    game->room = newRoom();
    return game;
}

Room* newRoom(){
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 100;
    Entity* player = newPlayer(position);
    room->player = *player;
    free(player);
    return room;
}

Entity* newPlayer(Position Position){
    Entity *entity = (Entity*) malloc(sizeof(Entity));
    entity->position = Position;
    entity->type = PLAYER;

    return entity;
}
