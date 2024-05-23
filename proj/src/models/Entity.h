
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utils/aux_structs/HurtBox.h"
#include "../utils/aux_structs/Position.h"



typedef enum {
    PLAYER,
    CAT,
    CAT0,
    CAT1,
    CAT2,
    CAT3,
    CAT4,
    WALL
} EntityType;

typedef struct {
    Position position;
    HurtBox hurtBox;
    double velocity;        // pixels/s
    uint16_t direction;     // [0,360[, 0 being right
    EntityType type;  
    void* typeInfo;         // entity type specific info
} Entity;

Entity* newCat(Position position);  //returns pointer to new cat with random color

Entity* newPlayer(Position Position);

Entity* newWall(Position position, HurtBox hurtBox);

void deleteEntity(Entity* entity);

Position candidatePos(Entity* entity);  // returns next position according to velocity and direction

void moveEntity(Entity* Entity);        //will move entity according to candidatePos and collisions

//bool checkCollision(Entity* entityA, Entity* entityB);   //true if entities will collide according to their current movements

#endif
