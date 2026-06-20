#include "../include/engine.h"
#include "../include/gameobject.h"
#include <iostream>
#include <stdbool.h>
#include <stdlib.h>

void engine_init(EngineContext *ctx) {
	ctx->isRunning = true;

	engine_spawn_object(ctx, 344, 267, 1.5, 1.5);
	engine_spawn_object(ctx, 215, 467, 1.6, 1.9);
}

void engine_update(EngineContext *ctx, float deltaTime) {
	for(int obj = 0; obj < ctx->num_objects; obj++) {
		float curr_x = ctx->objects[obj].position.x;
		float curr_y = ctx->objects[obj].position.y;
		float x_speed = ctx->objects[obj].speed.x;
		float y_speed = ctx->objects[obj].speed.y;

		curr_x += x_speed * deltaTime;
		curr_y += y_speed * deltaTime;

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
		printf("Obj ID %d at (x=%f, y=%f) [health=%d]\n",
		       ctx->objects[obj].id,
		       ctx->objects[obj].position.x,
		       ctx->objects[obj].position.y,
			   ctx->objects[obj].health
			);
	}
}

void engine_shutdown(EngineContext *ctx) {
	ctx->isRunning = false;
}

void engine_spawn_object(EngineContext *ctx, float pos_x, float pos_y, float speed_x, float speed_y) {
	gameobject_create(&ctx->objects[ctx->num_objects], ctx->num_objects, pos_x, pos_y, speed_x, speed_y);

	ctx->num_objects += 1;
}

void engine_handle_input(EngineContext *ctx) {
	if(ctx->num_objects == 0) return;

	int random = (rand() % 4) + 1;

	switch(random) {
	case 1:
		ctx->objects[0].speed.x = 0;
		ctx->objects[0].speed.y = -5.0;
		std::cout << "[W PRESSED]" << std::endl;
		break;
	case 2:
		ctx->objects[0].speed.x = 0;
		ctx->objects[0].speed.y = 5.0;
		std::cout << "[S PRESSED]" << std::endl;
		break;
	case 3:
		ctx->objects[0].speed.x = -5.0;
		ctx->objects[0].speed.y = 0;
		std::cout << "[A PRESSED]" << std::endl;
		break;
	case 4:
		ctx->objects[0].speed.x = 5.0;
		ctx->objects[0].speed.y = 0;
		std::cout << "[D PRESSED]" << std::endl;
		break;
	default:
		break;
	}
}