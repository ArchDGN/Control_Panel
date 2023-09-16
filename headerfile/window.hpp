#ifndef __WINDOW__
    #define __WINDOW__

    #include <string>
    #include <SDL2/SDL.h>

    #include "../headerfile/mouse.hpp"
    #include "../headerfile/imageloader.hpp"
    #include "../headerfile/keyboard.hpp"
    #include "../headerfile/draw.hpp"

    void get_error (std::string error, std::string error_log, int code);

    class window
    {
    private:

        const int *_window_width;
        const int *_window_height;
        const std::string *_prog_name;

        int mouse_pos_x;
        int mouse_pos_y;

        SDL_Event _event;
        bool _quit;

        SDL_Window *_prog_window;
        SDL_Renderer *_renderer;

    public:
        window() = delete;
        window(const int *window_width, const int *window_height, const std::string *prog_name);
        ~window();

        void run_program();

        void get_mouse_for_texture(mouse &mouse_control, imageloader &texture_background, draw &draw_grid);
        void get_keyboard_for_texture(keyboard &keyboard_control, imageloader &texture_background, draw &draw_grid);
    };
    

#endif