#include "../models/Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Game* createNewGame() {
    Game *game = (Game*) malloc(sizeof(Game));
    game->state = GAME_STATE;
    game->room = newRoom();
    return game;
}

Room* newRoom() {
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 100;
    Entity* player = newPlayer(position);
    room->player = *player;
    free(player);

    for (int i = 0; i < 10; i++) {
        Position catPosition;
        catPosition.x = randomNumer(30, 1000);
        catPosition.y = randomNumer(30, 700);
        Entity cat;
        cat.position = catPosition;
        // TODO: Add random number to generate a random cat
        cat.type = CAT0;
        room->cats[i] = cat;
    }


    return room;
}

Entity* newPlayer(Position Position) {
    Entity *entity = (Entity*) malloc(sizeof(Entity));
    entity->position = Position;
    entity->type = PLAYER;

    return entity;
}

int randomNumer(int lower_bound, int upper_bound) {
    int random_number;

    static int seed_initialized = 0;
    if (!seed_initialized) {
        srand(time(NULL));
        seed_initialized = 1;
    }

    random_number = lower_bound + rand() % (upper_bound - lower_bound + 1);
    
    return random_number;
}

