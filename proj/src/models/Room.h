#ifndef ROOM_H
#define ROOM_H


#include "Entity.h"

typedef struct {
    Entity* player;
    Entity* cats[10];
    Entity* walls[4];
    uint8_t stage;
    //bool isDay;
} Room;



Room* newRoom();

void deleteRoom(Room* room);

int removeCat(Room* room ,Entity* cat);   //called if the specified cat is pet correctly

int addCat(Room* room);   //called after a cooldown; cooldown is shorter in higher stages

int advanceStage(Room* room);

#endif /* ROOM_H */
