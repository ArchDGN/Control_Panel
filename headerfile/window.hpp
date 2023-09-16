#ifndef __WINDOW__
    #define __WINDOW__

    #include <string>
    #include <SDL2/SDL.h>

    #include "../headerfile/mouse.hpp"
    #include "../headerfile/keyboard.hpp"

    void get_error (std::string error, std::string error_log, int code);

    class window
    {
    private:

        int *_window_width;
        int *_window_height;
        const std::string *_prog_name;
        SDL_Surface* _ico;

        int mouse_pos_x;
        int mouse_pos_y;

        SDL_Event _event;
        bool _quit;

        SDL_Window *_prog_window;
        SDL_Renderer *_renderer;
        SDL_Rect _rect;

    public:
        window() = delete;
        window(int *window_width, int *window_height, const std::string *prog_name, SDL_Surface* ico);
        ~window();

        void run_program();
    };
    

#endif