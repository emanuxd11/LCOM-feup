#ifndef ROOM_H
#define ROOM_H


#include "../models/Entity.h"
#include "../models/Cloud.h"

#define CLOUD_QNT 5


typedef struct {
    Entity* player;
    Entity* cats[10];
    Entity* walls[4];
    Position* center;
    Cloud clouds[CLOUD_QNT];
    uint8_t stage;
    uint8_t n_cats;
} Room;


Room* newRoom();
void deleteRoom(Room* room);

int addCat(Room* room);   //called after a cooldown; cooldown is shorter in higher stages
int removeCat(Room* room ,Entity* cat);   //called if the specified cat is pet correctly

int advanceStage(Room* room);

Entity* getSelectedCat(Room* room);

#endif /* ROOM_H */
