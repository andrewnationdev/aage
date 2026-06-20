#ifndef WINDOW_H
#define WINDOW_H

struct WindowContext {
    const char* title;
    int width;
    int height;
};

void window_create(WindowContext *win, int width, int height, const char* title);

bool window_should_close();

void window_clear();

void window_present();

void window_destroy();

#endif