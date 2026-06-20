#ifndef ENGINE_H
#define ENGINE_H

#include "gameobject.h"

struct EngineContext {
	bool isRunning;
	GameObject objects[1024];
	int num_objects = 0;
	int height;
	int width;
	float friction;
};

void engine_init(EngineContext *ctx);
void engine_update(EngineContext *ctx, float deltaTime);
void engine_render(EngineContext *ctx);
void engine_shutdown(EngineContext *ctx);
void engine_handle_input(EngineContext *ctx);
void engine_spawn_object(EngineContext *ctx, 
	float pos_x, 
	float pos_y, 
	float speed_x, 
	float speed_y, 
	float width, 
	float height
);

#endif