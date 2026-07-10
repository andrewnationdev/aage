#ifndef SCRIPTS_H
#define SCRIPTS_H

#include "./engine.h"

enum ObjectType {
    PLAYER = 0,
    WALL,
    COIN,
    ENEMY
};

void script_init_elements(EngineContext *ctx);

void script_update_elements(EngineContext *ctx);

#endif
