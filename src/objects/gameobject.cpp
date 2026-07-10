#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include "../../include/gameobject.h"
#include "../../include/engine.h"

//Você pode adicionar outras propriedades aqui relevantes para o objeto
void gameobject_create(GameObject *obj, int id, float x, float y, float sx, float sy, float width, float height) {
    obj->id = id;
    obj->position.x = x;
    obj->position.y = y;
    obj->speed.x = sx;
    obj->speed.y = sy;
    obj->health = 100;
    obj->width = width;
    obj->height = height;
    obj->color = BLUE;
}

//Remova o objeto do jogo aqui
void gameobject_destroy(EngineContext *ctx, int index){
    ctx->objects[index] = ctx->objects[ctx->num_objects - 1];
	ctx->objects[ctx->num_objects - 1] = {};
	ctx->num_objects--;
}
