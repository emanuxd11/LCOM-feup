#include "../models/Entity.h"
#include "CatInfo.h"
#include <math.h>
#include "../utils/utils.h"

Entity* newPlayer(int x, int y){
    Entity *entity = (Entity*) malloc(sizeof(Entity));

    entity->position = newPosition(x, y);
    entity->hurtBox = newHurtBox(30, 30);

    entity->velocity = 0;
    entity->direction = 0;

    entity->type = PLAYER;
    entity->typeInfo = NULL;

    return entity;
}

Entity* newCat(int x, int y) {
    Entity* cat = (Entity*) malloc(sizeof(Entity));

    cat->position = newPosition(x, y);
    
    cat->hurtBox = newHurtBox(30, 30);

    cat->velocity = 0;
    cat->direction = 0;

    cat->type = CAT;
    cat->typeInfo = newCatInfo();

    return cat;
}

void deleteEntity(Entity* entity) {
    if (entity->hurtBox != NULL) deleteHurtBox(entity->hurtBox);
    if (entity->position != NULL) deletePosition(entity->position);
    if (entity->typeInfo != NULL) free(entity->typeInfo);
    free(entity);
}

CollisionType checkCollision(Position cPosA, Entity* entityA, Entity* entityB) {
    double leftA = cPosA.x;
    double rightA = cPosA.x + entityA->hurtBox->deltaX;
    double topA = cPosA.y;
    double bottomA = cPosA.y + entityA->hurtBox->deltaY;

    double leftB = entityB->position->x;
    double rightB = entityB->position->x + entityB->hurtBox->deltaX;
    double topB = entityB->position->y;
    double bottomB = entityB->position->y + entityB->hurtBox->deltaY;

    bool xOverlap = (leftA < rightB) && (rightA > leftB);
    bool yOverlap = (topA < bottomB) && (bottomA > topB);

    if (xOverlap && yOverlap) {
        double xOverlapAmount = fmin(rightA, rightB) - fmax(leftA, leftB);
        double yOverlapAmount = fmin(bottomA, bottomB) - fmax(topA, topB);

        if (xOverlapAmount < yOverlapAmount) {
            return X_COLLISION;
        }
        if (yOverlapAmount < xOverlapAmount){
            return Y_COLLISION;
        }
        return XY_COLLISION;
    }

    return NO_COLLISION;
}
/*
CollisionType checkCollision(Position cPosA, Entity* entityA, Entity* entityB) {

    if ((cPosA.x + entityA->hurtBox->deltaX
        >= entityB->position->x - entityB->hurtBox->deltaX)
        || (cPosA.x - entityA->hurtBox->deltaX
        <= entityB->position->x + entityB->hurtBox->deltaX)) {
        return X_COLLISION;
    }

    if ((cPosA.y + entityA->hurtBox->deltaY
        >= entityB->position->y - entityB->hurtBox->deltaY)
        || (cPosA.y - entityA->hurtBox->deltaY
        <= entityB->position->y + entityB->hurtBox->deltaY)) return Y_COLLISION;
    
    return NO_COLLISION;
}
*/


