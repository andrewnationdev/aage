#include "../include/physics.h"

bool check_aabb_collision(GameObject *a, GameObject *b){
    if(a->position.x + a->width < b->position.x)
        return false;

    if(a->position.x > b->position.x + b->width)
        return false;

    if(a->position.y + a->height < b->position.y)
        return false;

    if(a->position.y > b->position.y + b->height)
        return false;

    return true;
}