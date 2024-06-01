
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

typedef enum {
    X_COLLISION,
    Y_COLLISION,
    NO_COLLISION
} CollisionType;

typedef struct {
    Position* position;
    HurtBox* hurtBox;
    double velocity;        // pixels/s
    int direction;     // angle, 0 being right
    EntityType type;  
    void* typeInfo;         // entity type specific info
} Entity;

Entity* newCat(int x, int y);  //returns pointer to new cat with random color

Entity* newPlayer(int x, int y);

Entity* newWall(int x, int y);


void deleteEntity(Entity* entity);

CollisionType checkCollision(Position cPosA, Entity* entityA, Entity* entityB);


#endif
