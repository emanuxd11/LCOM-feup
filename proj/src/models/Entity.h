#include "../aux_structs/HurtBox.h"
#include "../aux_structs/Position.h"
#include <stdio.h>
#include <stdlib.h>


typedef enum {
    PLAYER,
    // TODO add various types of cats here
    CAT,
    WALL
} EntityType;

typedef struct {
    Position position;
    HurtBox hurtBox;
    double velocity;
    uint16_t direction;
    EntityType type;  
    void* typeInfo;         //entity type specific info
} Entity;

Entity* newCat(Position position);

Entity* newPlayer(Position Position);

Entity* newWall(Position position, HurtBox hurtBox);

int moveEntity(Entity* entity);

//bool checkCollision(Entity* entityA, Entity* entityB);   //true if entities will collide according to their current movements

