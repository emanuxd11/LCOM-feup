#include <Entity.h>

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
}