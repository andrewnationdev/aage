#include "../include/engine.h"
#include "../include/gameobject.h"
#include "raylib.h"
#include <iostream>
#include <stdbool.h>
#include <stdlib.h>

void engine_init(EngineContext *ctx) {
	ctx->isRunning = true;
	ctx->friction = 0.95f;

	engine_spawn_object(ctx, 344, 267, 1.5, 1.5, 30, 55);
	engine_spawn_object(ctx, 215, 467, 1.6, 1.9, 55, 30);
}

void engine_update(EngineContext *ctx, float deltaTime) {
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

		if(curr_x > ctx->width ||
		        curr_x < 0) {
			ctx->objects[obj].speed.x *= -1;
			curr_x = (curr_x < 0) ? 0 : ctx->width;
			ctx->objects[obj].health -= 10;
		}

		if(curr_y > ctx->height ||
		        curr_y < 0
		  ) {
			ctx->objects[obj].speed.y *= -1;
			curr_y = (curr_y < 0) ? 0 : ctx->height;
			ctx->objects[obj].health -= 10;
		}

		ctx->objects[obj].position.x = curr_x;
		ctx->objects[obj].position.y = curr_y;
	}
}

void engine_render(EngineContext *ctx) {
	for(int obj = 0; obj < ctx->num_objects; obj++) {
		/*printf("Obj ID %d at (x=%f, y=%f) [health=%d]\n",
		       ctx->objects[obj].id,
		       ctx->objects[obj].position.x,
		       ctx->objects[obj].position.y,
			   ctx->objects[obj].health
			);*/
		float x = ctx->objects[obj].position.x;
		float y = ctx->objects[obj].position.y;
		float width = ctx->objects[obj].width;
		float height = ctx->objects[obj].height;

		DrawRectangle(
			x,
			y,
			width,
			height,
			RED
		);
	}
}

void engine_shutdown(EngineContext *ctx) {
	ctx->isRunning = false;
}

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