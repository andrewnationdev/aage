#include "../../include/scripts.h"
#include "../../include/physics.h"
#include "../../include/engine.h"

void spawn_enemies(EngineContext *ctx){
    engine_spawn_object(ctx, 122.0f, 250.0f, 0.0f, 100.0f, 20, 20);
    int i_first_enemy = ctx->num_objects - 1;
    ctx->objects[i_first_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_first_enemy].color = RED;

    engine_spawn_object(ctx, 50.0f, 162.0f, 150.0f, 0.0f, 20, 20);
    int i_second_enemy = ctx->num_objects - 1;
    ctx->objects[i_second_enemy].type = ObjectType::ENEMY;
    ctx->objects[i_second_enemy].color = RED;
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
