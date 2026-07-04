#include "../include/engine.h"
#include "../include/gameobject.h"
#include "raylib.h"
#include <iostream>
#include <stdbool.h>
#include <stdlib.h>

void engine_init(EngineContext *ctx) {
	ctx->isRunning = true;
	ctx->friction = 0.95f;
}

void engine_update(EngineContext *ctx, float deltaTime) {
	//Aqui se atualizam as posições do objeto e a física
	for(int obj = 0; obj < ctx->num_objects; obj++) {
		float x_speed = ctx->objects[obj].speed.x;
		float y_speed = ctx->objects[obj].speed.y;

		x_speed *= ctx->friction;
		y_speed *= ctx->friction;

		ctx->objects[obj].speed.x = x_speed;
        ctx->objects[obj].speed.y = y_speed;

		float curr_x = ctx->objects[obj].position.x + x_speed * deltaTime;
		float curr_y = ctx->objects[obj].position.y + y_speed * deltaTime;

		if(ctx->objects[obj].health <= 0){
			gameobject_destroy(ctx, obj);
			obj--;
			continue;
		}

		if(curr_x + ctx->objects[obj].width > ctx->width || curr_x < 0) {
			ctx->objects[obj].speed.x *= -1;
			curr_x = (curr_x < 0) ? 0 : (ctx->width - ctx->objects[obj].width);
		}

		if(curr_y + ctx->objects[obj].height > ctx->height || curr_y < 0) {
			ctx->objects[obj].speed.y *= -1;
		}

		ctx->objects[obj].position.x = curr_x;
		ctx->objects[obj].position.y = curr_y;
	}
}

//Renderiza-se o jogo aqui
void engine_render(EngineContext *ctx) {
	for(int obj = 0; obj < ctx->num_objects; obj++) {
		float x = ctx->objects[obj].position.x;
		float y = ctx->objects[obj].position.y;
		float width = ctx->objects[obj].width;
		float height = ctx->objects[obj].height;

		//Função do Raylib que desenha o retângulo na tela
		DrawRectangle(
			x,
			y,
			width,
			height,
			ctx->objects[obj].color
		);
	}
}

void engine_shutdown(EngineContext *ctx) {
	ctx->isRunning = false;
}

//Cria um novo objeto no jogo
void engine_spawn_object(EngineContext *ctx, float pos_x, float pos_y, float speed_x, float speed_y, float width, float height) {
	gameobject_create(&ctx->objects[ctx->num_objects], ctx->num_objects, pos_x, pos_y, speed_x, speed_y, width, height);

	ctx->num_objects += 1;
}

void engine_handle_input(EngineContext *ctx) {
	if(ctx->num_objects == 0) return;

	if (IsKeyDown(KEY_W)) {
        ctx->objects[0].speed.y = -40.0f;
        std::cout << "[W PRESSED]" << std::endl;
    }
    
    if (IsKeyDown(KEY_S)) {
        ctx->objects[0].speed.y = 40.0f;
        std::cout << "[S PRESSED]" << std::endl;
    }
    
    if (IsKeyDown(KEY_A)) {
        ctx->objects[0].speed.x = -40.0f;
        std::cout << "[A PRESSED]" << std::endl;
    }
    
    if (IsKeyDown(KEY_D)) {
        ctx->objects[0].speed.x = 40.0f;
        std::cout << "[D PRESSED]" << std::endl;
    }
}