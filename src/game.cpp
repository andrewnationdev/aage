#include "../include/game.h"
#include <iostream>

/*** O JOGO É PROGRAMADO NESTE ARQUIVO */
void game_init_level(EngineContext *ctx, GameState state) {
    ctx->num_objects = 0; 

    if (state == STATE_PLAYING) {
        std::cout << "Carregando Fase 1..." << std::endl;

        engine_spawn_object(ctx, 344, 267, 1.5f, 1.5f, 30.0f, 55.0f);
        engine_spawn_object(ctx, 100, 100, 2.0f, 1.0f, 40.0f, 40.0f);
    }
}

void game_check_rules(EngineContext *ctx, GameState *current_state) {
    if (*current_state == STATE_PLAYING) {
        if (ctx->num_objects == 0 || ctx->objects[0].health <= 0) {
            std::cout << "Game Over! Voltando ao Menu..." << std::endl;
            *current_state = STATE_GAME_OVER;
            game_init_level(ctx, STATE_GAME_OVER);
        }
    }
}