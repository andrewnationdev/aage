/**
CÓDIGO ORIGINAL DESENVOLVIDO POR ANDRÉ PEREIRA JUSTINIANO,
Partes do código foram comentadas a fim de auxiliá-lo no uso e na expansão
dessa engine.
*/
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

	//Criar a janela de acordo com o tamanho e título definidos no context da Engine
	window_create(&window, 
		window.width, 
		window.height, 
		window.title);

	engine_init(&context);

	Camera2D camera = { 0 };

	camera.offset = { (float)window.width / 2.0f, (float)window.height / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	while(!window_should_close() && context.isRunning) {
        engine_handle_input(&context);
        engine_update(&context, 0.016f);

        if (context.num_objects > 0) {
            camera.target = { context.objects[0].position.x, context.objects[0].position.y };
        }

        window_clear();

        BeginMode2D(camera);
        
        engine_render(&context);
        
        EndMode2D();
        window_present();
    }

    window_destroy();
    return 0;
}