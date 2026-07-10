#include "../../include/window.h"
#include "raylib.h"

void window_create(WindowContext *win, int width, int height, const char* title){
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

bool window_should_close(){
    return WindowShouldClose();
}

void window_clear(){
    BeginDrawing();
    ClearBackground(BLACK);
}

void window_present(){
    EndDrawing();
}

void window_destroy(){
    CloseWindow();
}
