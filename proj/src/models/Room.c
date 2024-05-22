#include "Room.h"
#include "../utils/utils.h"

Room* newRoom(){
    Room *room = (Room*) malloc(sizeof(Room));
    Position position;
    position.x = 100;
    position.y = 100;
    room->player = newPlayer(position);

    for (int i = 0; i < 10; i++){
        Position catPosition;
        catPosition.x = randomNumer(30, 1000);
        catPosition.y = randomNumer(30, 700);
        
        room->cats[i] = newCat(catPosition);
   
    }


    return room;
}

void deleteRoom(Room* room) {
    deleteEntity(room->player);

    
    for (int i = 0; i < 10; i++) {
        if (room->cats[i] == NULL) continue;
        deleteEntity(room->cats[i]);
    }
    
    free(room->cats);

    
    for (int i = 0; i < 4; i++) {
        if (room->walls[i] == NULL) continue;
        deleteEntity(room->walls[i]);
    }
    
    free(room->walls);

    free(room);
}
