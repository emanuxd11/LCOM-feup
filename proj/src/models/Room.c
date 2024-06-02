#include "Room.h"
#include "../utils/utils.h"
#include "../drivers/utils_drivers.h"
#include <math.h>
#include "CatInfo.h"

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

    int cloud_x_offset = 0;
    for (int i = 0; i < CLOUD_QNT; i++) {
        Cloud cloud = {
          .x = cloud_x_offset,
          .y = 80 + getRandomInt(-50, 30),
          .velocity = getRandomFloat(1.3, 1.7),
        };
        room->clouds[i] = cloud;
        cloud_x_offset += getRandomInt(50, 300);
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

Entity* getSelectedCat(Room* room) {
    
    Entity* currCat;
    Entity* closestCat;
    double distToPlayer;
    double minDistToPlayer = SELECT_RADIUS;
    
    for (int i = 0; i < 10; i++) {
        currCat = room->cats[i];
        if (currCat == NULL) continue;

        ((CatInfo*)currCat->typeInfo)->isSelected = false;
        distToPlayer = sqrt(pow(room->player->position->x - currCat->position->x, 2)
                            + pow(room->player->position->y - currCat->position->y, 2));
        
        if (distToPlayer >= SELECT_RADIUS) continue;
        if (distToPlayer < minDistToPlayer) {
            minDistToPlayer = distToPlayer;
            closestCat = currCat;
        }
    }
    ((CatInfo*)closestCat->typeInfo)->isSelected = true;
    return closestCat;
}
