#include "../headerfile/files_display.hpp"

files_display::files_display(std::unique_ptr<draw> *draw, int *w, int *h): _draw{draw}, _window_width{w}, _window_height{h}
{

}

void files_display::display()
{
    int *w = _window_width;
    int *h = _window_height;

    //(*_draw)->draw_rectangle(*w/8 - 1, *h/10 - 1, *w - (*w/8) - (*w/9) + 2, *h - (*h/10) - (*h/16) + 2, 1000000, Square_Color::Red, 255);


    (*_draw)->set_font_color();
}