#include "../include/game.h"
#include "../include/gui.h"
#include <iostream>

/*** O JOGO É PROGRAMADO NESTE ARQUIVO */
void game_init_level(EngineContext *ctx, GameState state) {
    ctx->num_objects = 0;

    if (state == STATE_PLAYING) {
        engine_spawn_object(ctx, 120.0f, 160.0f, 0.0f, 0.0f, 25.0f, 25.0f);
        ctx->objects[ctx->num_objects - 1].color = BLUE;

        float block_w = 110.0f;
        float block_h = 150.0f;

        float street_w = 40.0f;
        float street_h = 50.0f;

        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                float x = col * (block_w + street_w);
                float y = row * (block_h + street_h);

                engine_spawn_object(ctx, x, y, 0.0f, 0.0f, block_w, block_h);
                ctx->objects[ctx->num_objects - 1].color = DARKGRAY;
            }
        }
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

//Interface gráfica (textos e menus)
void game_render_gui(EngineContext *ctx, GameState *current_state){
    if(*current_state == STATE_PLAYING){
        int pos_x_points = 20;
        int pos_y_points = 20;

        int pos_x_health = 20;
        int pos_y_health = 50;

        gui_draw_text(
            "PONTOS: 0000",
            pos_x_points,
            pos_y_points,
            20,
            WHITE
        );

        gui_draw_text(
            "VIDA: 100",
            pos_x_health,
            pos_y_health,
            20,
            RED
        );
    }
}
