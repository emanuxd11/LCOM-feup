#include "../models/Entity.h"
#include "CatInfo.h"
#include <math.h>
#include "../utils/utils.h"

Entity* newPlayer(Position Position){
    Entity *entity = (Entity*) malloc(sizeof(Entity));
    entity->position = Position;
    entity->type = PLAYER;

    return entity;
}

Entity* newCat(Position position) {
    Entity* cat = (Entity*) malloc(sizeof(Entity));

    cat->position = position;
    
    HurtBox hurtBox;
    hurtBox.deltaX = 20;
    hurtBox.deltaY = 20;
    cat->hurtBox = hurtBox;

    cat->velocity = 0;
    cat->direction = 0;
    cat->type = CAT;
    cat->typeInfo = newCatInfo();

    return cat;
}

void deleteEntity(Entity* entity) {
    free(entity->typeInfo);
    free(entity);
}

Position candidatePos(Entity* entity) {
    Position candidatePos;

    candidatePos.x = entity->position.x + ((entity->velocity / FRAME_RATE) * cos(degToRad(entity->direction)));
    candidatePos.y = entity->position.y - ((entity->velocity / FRAME_RATE) * sin(degToRad(entity->direction)));

    printf("\n x: %d; y : %d", candidatePos.x, candidatePos.y);

    return candidatePos;
}

void moveEntity(Entity* entity) {
    Position cPos = candidatePos(entity);

    //add collision checks

    entity->position = cPos;
}

