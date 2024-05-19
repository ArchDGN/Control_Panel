#ifndef CONTROL_PANEL_TEXT_HPP
    #define CONTROL_PANEL_TEXT_HPP

    #include <string>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    #include "../headerfile/data.hpp"

    class text
    {

    private:
        int *_window_width;
        int *_window_height;

        SDL_Renderer *_renderer;
        TTF_Font *_TimesNewRomance;
        SDL_Color _color{};

    public:
        text() = delete;
        text(int *window_width, int *window_height, const std::string& file_name, int pt_size, Square_Color color, Uint8 alpha, SDL_Renderer *renderer);
        ~text();

        void set_color(Square_Color color, Uint8 alpha);
        void draw_text(std::string text_to_draw, int x, int y, int width, int height, Text_Property text, Text_Property screen);

    };


#endif //CONTROL_PANEL_TEXT_HPP
