#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/engine.h"
#include "../include/window.h"

int main()
{
	std::cout<<"Initializing game engine..." << std::endl;

	EngineContext context;
	WindowContext window;

	//Inicializa o contexto da Engine
	context.isRunning = true;
	context.height = 800;
	context.width = 600;

	//Inicializa a janela
	window.title = "AAGE - Window";
	window.width = context.width;
	window.height = context.height;

	int frames = 0;

	window_create(&window, 
		window.width, 
		window.height, 
		window.title);

	engine_init(&context);

	while(!window_should_close() && context.isRunning) {
		window_clear();
		engine_handle_input(&context);
		engine_update(&context, 1.016f);
		engine_render(&context);
		window_present();

		frames++;
	}

	window_destroy();

	return 0;
}