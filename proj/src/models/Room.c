#include "Room.h"
#include "../utils/utils.h"

Room* newRoom(){
    Room *room = (Room*) malloc(sizeof(Room));
    room->player = newPlayer(100, 100);
    room->center = newPosition(512, 371);

    int catX, catY;

    for (int i = 0; i < 10; i++){

        catX = randomNumer(30, 1000);
        catY = randomNumer(30, 700);
        
        room->cats[i] = newCat(catX, catY);
   
    }


    return room;
}

void deleteRoom(Room* room) {
    deleteEntity(room->player);

    
    for (int i = 0; i < 10; i++) {
        if (room->cats[i] == NULL) continue;
        deleteEntity(room->cats[i]);
    }

    
    for (int i = 0; i < 4; i++) {
        if (room->walls[i] == NULL) continue;
        deleteEntity(room->walls[i]);
    }


    free(room);
}
