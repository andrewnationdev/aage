#ifndef SCRIPTS_H
#define SCRIPTS_H

#include "./engine.h"
#include "./game.h"

enum ObjectType {
    PLAYER = 0,
    WALL,
    COIN,
    ENEMY
};

void script_init_elements(EngineContext *ctx);

void script_update_elements(EngineContext *ctx);

void render_main_menu(EngineContext *ctx, GameState *current_state);

void render_game_over(EngineContext *ctx, GameState *current_state);


#endif
