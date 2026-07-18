#include "../../include/scripts.h"
#include "../../include/physics.h"
#include "../../include/engine.h"
#include "../include/game.h"

void spawn_enemies(EngineContext *ctx){
    engine_spawn_object(ctx, 122.0f, 250.0f, 0.0f, 100.0f, 20, 20);
    int i_first_enemy = ctx->num_objects - 1;
    ctx->objects[i_first_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_first_enemy].color = RED;

    engine_spawn_object(ctx, 50.0f, 162.0f, 150.0f, 0.0f, 20, 20);
    int i_second_enemy = ctx->num_objects - 1;
    ctx->objects[i_second_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_second_enemy].color = RED;

    engine_spawn_object(ctx, 420.0f, 165.0f, 120.0f, 0.0f, 20, 20);
    int i_third_enemy = ctx->num_objects - 1;
    ctx->objects[i_third_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_third_enemy].color = RED;

    engine_spawn_object(ctx, 270.0f, 80.0f, 0.0f, 100.0f, 20, 20);
    int i_fourth_enemy = ctx->num_objects - 1;
    ctx->objects[i_fourth_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_fourth_enemy].color = RED;

    engine_spawn_object(ctx, 80.0f, 565.0f, 110.0f, 0.0f, 20, 20);
    int i_fifth_enemy = ctx->num_objects - 1;
    ctx->objects[i_fifth_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_fifth_enemy].color = RED;

    engine_spawn_object(ctx, 420.0f, 400.0f, 0.0f, -140.0f, 20, 20);
    int i_sixth_enemy = ctx->num_objects - 1;
    ctx->objects[i_sixth_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_sixth_enemy].color = RED;
}

void script_update_enemy_patrol(EngineContext *ctx) {
    float maxSpeed = 100.0f;

    for (int i = 1; i < ctx->num_objects; i++) {
        GameObject *enemy = &ctx->objects[i];

        if (enemy->type == ObjectType::ENEMY) {

            // Dispara se o atrito reduzir a velocidade
            if (enemy->speed.x != 0.0f) {
                enemy->speed.x = (enemy->speed.x > 0) ? maxSpeed : -maxSpeed;
            }
            if (enemy->speed.y != 0.0f) {
                enemy->speed.y = (enemy->speed.y > 0) ? maxSpeed : -maxSpeed;
            }

            for (int j = 1; j < ctx->num_objects; j++) {
                GameObject *block = &ctx->objects[j];

                if (block->type == ObjectType::WALL && check_aabb_collision(enemy, block)) {
                    enemy->position.x -= enemy->speed.x * ctx->deltaTime;
                    enemy->position.y -= enemy->speed.y * ctx->deltaTime;

                    enemy->speed.x *= -1.0f;
                    enemy->speed.y *= -1.0f;

                    enemy->position.x += enemy->speed.x * ctx->deltaTime;
                    enemy->position.y += enemy->speed.y * ctx->deltaTime;
                    break;
                }
            }
        }
    }
}

void spawn_coins(EngineContext *ctx){
    engine_spawn_object(ctx,50.0f, 167.0f, 0, 0, 15, 15);

    int index = ctx->num_objects - 1;

    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 122.0f, 60.0f, 0, 0, 15, 15);

    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 272.0f, 167.0f, 0, 0, 15, 15);

    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 422.0f, 167.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 272.0f, 350.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 50.0f, 367.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 422.0f, 367.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 122.0f, 567.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;

    engine_spawn_object(ctx, 422.0f, 567.0f, 0, 0, 15, 15);
    index = ctx->num_objects - 1;
    ctx->objects[index].type = ObjectType::COIN;
    ctx->objects[index].color = YELLOW;
}

void script_update_collect_coins(EngineContext *ctx){
    GameObject *player = &ctx->objects[0];

    for(int i = 1; i < ctx->num_objects; i++){
        GameObject *item = &ctx->objects[i];

        if(item->type == ObjectType::COIN &&
            check_aabb_collision(player, item)
        ){
            ctx->points = ctx->points + 100;

            //PlaySound(coin.wav)

            item->health = 0;

            break;
        }
    }
}

void script_update_elements(EngineContext *ctx){
    script_update_collect_coins(ctx);
    script_update_enemy_patrol(ctx);

    GameObject *player = &ctx->objects[0];

    for(int i = 1; i < ctx->num_objects; i++){
        GameObject *enemy = &ctx->objects[i];

        if(enemy->type == ObjectType::ENEMY && check_aabb_collision(player, enemy)){
            player->health -= 5 * ctx->deltaTime;

            break;
        }
    }
}

void script_init_elements(EngineContext *ctx){
    if(ctx->num_objects > 0){
        ctx->objects[0].type = ObjectType::PLAYER;
        spawn_coins(ctx);
        spawn_enemies(ctx);
    }
}

void render_main_menu(EngineContext *ctx, GameState *current_state) {
    if (IsKeyPressed(KEY_SPACE)) {
        ctx->objects[0].health = 100.0f;
        ctx->points = 0;

        game_init_level(ctx, STATE_PLAYING);

        *current_state = STATE_PLAYING;
    }

    const char* title_text = "RECTANGLE SURVIVAL";
    int title_width = MeasureText(title_text, 32);
    DrawText(title_text, (ctx->width - title_width) / 2, ctx->height / 2 - 50, 32, WHITE);

    const char* sub_text = "Pressione ESPAÇO para Jogar";
    int sub_width = MeasureText(sub_text, 20);
    DrawText(sub_text, (ctx->width - sub_width) / 2, ctx->height / 2 + 20, 20, GRAY);
}

void render_game_over(EngineContext *ctx, GameState *current_state) {
    if (IsKeyPressed(KEY_R)) {
        game_init_level(ctx, STATE_PLAYING);
        *current_state = STATE_PLAYING;
    }
    if (IsKeyPressed(KEY_M)) {
        *current_state = STATE_MENU;
    }

    DrawText("GAME OVER", ctx->width / 2 - 100, ctx->height / 2 - 50, 36, RED);
    DrawText("Pressione R para Reiniciar ou M para Menu", ctx->width / 2 - 180, ctx->height / 2 + 20, 18, WHITE);
}
