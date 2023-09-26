#include "../headerfile/files_display.hpp"

files_display::files_display(std::unique_ptr<draw> *draw, int *w, int *h): _draw{draw}, _window_width{w}, _window_height{h}
{

}

void files_display::display()
{
    int *w = _window_width;
    int *h = _window_height;

    int directory_arrow_x = *w/8 - 1;
    int directory_arrow_y = *h/10 - 1;
    int directory_arrow_width = *w - (*w/8) - (*w/9) + 2;
    int directory_arrow_height = *h - (*h/10) - (*h/16) + 2;

    (*_draw)->draw_rectangle(directory_arrow_x, directory_arrow_y, directory_arrow_width, directory_arrow_height, 1000000, Square_Color::Red, 255);

    int number_of_files_w = directory_arrow_width / 100;
    int file_centered_w = (directory_arrow_width - (100 * number_of_files_w)) / 2;

    int number_of_files_y = directory_arrow_height / 100;
    int file_centered_h = (directory_arrow_height - (100 * number_of_files_y)) / 2;

    for (int file_y = 0; file_y < number_of_files_y; file_y++)
    {
        for (int file_x = 0; file_x < number_of_files_w; file_x++)
        {
            (*_draw)->draw_rectangle(directory_arrow_x + file_centered_w + (100*file_x), directory_arrow_y + file_centered_h + (100*file_y), 80, 80, 1000000, Square_Color::Blue, 255);
        }
    }

    //(*_draw)->draw_rectangle(directory_arrow_x + 5, directory_arrow_y + 5, 80, 80, 1000000, Square_Color::Blue, 255);


    (*_draw)->set_font_color();
}