#include "../../include/gui.h"

void gui_draw_text(
    const char *text,
    int x,
    int y,
    int font_size,
    Color color
){
    DrawText(text, x, y, font_size, color);
}
