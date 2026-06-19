#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/gameobject.h"

void gameobject_create(GameObject *obj, int id, float x, float y, float sx, float sy) {
    obj->id = id;
    obj->position.x = x;
    obj->position.y = y;
    obj->speed.x = sx;
    obj->speed.y = sy;
}