#include "../models/Entity.h"
#include "CatInfo.h"
#include <math.h>
#include "../utils/utils.h"

Entity* newPlayer(int x, int y){
    Entity *entity = (Entity*) malloc(sizeof(Entity));
    entity->position = newPosition(x, y);
    entity->type = PLAYER;

    return entity;
}

Entity* newCat(int x, int y) {
    Entity* cat = (Entity*) malloc(sizeof(Entity));

    printf("BEFORE: %d, %d\n", x, y);
    cat->position = newPosition(x, y);
    printf("AFTER: %d, %d\n\n", cat->position->x, cat->position->y);
    
    cat->hurtBox = newHurtBox(20, 20);

    cat->velocity = 0;
    cat->direction = 0;
    cat->type = CAT;
    cat->typeInfo = newCatInfo();

    return cat;
}

void deleteEntity(Entity* entity) {
    deleteHurtBox(entity->hurtBox);
    deletePosition(entity->position);
    free(entity->typeInfo);
    free(entity);
}

Position candidatePos(Entity* entity) {

    Position cPos;

    cPos.x = entity->position->x + ((entity->velocity / FRAME_RATE) * cos(degToRad(entity->direction)));
    cPos.y = entity->position->y - ((entity->velocity / FRAME_RATE) * sin(degToRad(entity->direction)));

    printf("\n x: %d; y : %d", cPos.x, cPos.y);

    return cPos;
}

void moveEntity(Entity* entity) {
    Position cPos = candidatePos(entity);

    //add collision checks

    entity->position->x = cPos.x;
    entity->position->y = cPos.y;

}

