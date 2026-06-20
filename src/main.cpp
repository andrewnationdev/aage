#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/engine.h"

int main()
{
	std::cout<<"Initializing game engine..." << std::endl;

	EngineContext context;
	context.isRunning = true;
	context.height = 800.0;
	context.width = 600.0;

	int frames = 0;

	engine_init(&context);

	while(context.isRunning) {
		engine_handle_input(&context);
		engine_update(&context, 1.016f);
		engine_render(&context);

		if(frames > 60) engine_shutdown(&context);

		frames++;
	}

	return 0;
}