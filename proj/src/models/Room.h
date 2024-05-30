#ifndef _ROOM_H_
#define _ROOM_H_

#include "Entity.h"


#define CLOUD_QNT 5


typedef struct {
    Entity player;
    Entity cats[10];
    Entity walls[4];
    Cloud clouds[CLOUD_QNT];
    uint8_t stage;
} Room;


Room* newRoom();
void deleteRoom(Room* room);

int addCat(Room* room);   //called after a cooldown; cooldown is shorter in higher stages
int removeCat(Room* room ,Entity* cat);   //called if the specified cat is pet correctly

int advanceStage(Room* room);

#endif
