#ifndef SCRIPTS_H
#define SCRIPTS_H

#include "./engine.h"
#include "./game.h"
#include <string>
#include <vector>

enum ObjectType {
    PLAYER = 0,
    WALL,
    COIN,
    ENEMY
};

struct GameLevels {
    int level = 1;
    int points = 0;
    int max_levels = 3;
};

struct CreditsScreen {
    int pos_x;
    int pos_y;
    float roll_speed;
    std::vector<std::string> credits;
    float text_height;
};

void level_up(bool condition);

int current_level();

void script_init_elements(EngineContext *ctx);

void script_update_elements(EngineContext *ctx);

void render_main_menu(EngineContext *ctx, GameState *current_state);

void render_game_over(EngineContext *ctx, GameState *current_state);

void init_credits(CreditsScreen *credits, int screen_width, int screen_height);

void update_and_render_credits(CreditsScreen *credits,
    float deltaTime,
    GameState *game_state,
    int screen_height,
    int screen_width
);

#endif
