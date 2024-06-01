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
} Room;


Room* newRoom();
void deleteRoom(Room* room);

int addCat(Room* room);   //called after a cooldown; cooldown is shorter in higher stages
int removeCat(Room* room ,Entity* cat);   //called if the specified cat is pet correctly

int advanceStage(Room* room);

Position candidatePos(Entity* entity, Room* room);  // returns next position according to velocity, direction and collisions

void moveEntity(Entity* Entity, Room* room);        //will move entity according to candidatePos

#endif /* ROOM_H */
