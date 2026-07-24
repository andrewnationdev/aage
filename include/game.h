#ifndef GAME_H
#define GAME_H

#include "engine.h"

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_CREDITS
};

void game_init_level(EngineContext *ctx, GameState state);

void game_check_rules(EngineContext *ctx, GameState *current_state);

void game_render_gui(EngineContext *ctx, GameState *current_state);

#endif
