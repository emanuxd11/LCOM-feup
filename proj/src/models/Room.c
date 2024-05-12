#include <Room.h>

Room* newRoom(){
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 100;
    Entity* player = newPlayer(position);
    room->player = *player;
    free(player);

    for (int i = 0; i < 10; i++){
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