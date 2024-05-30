#ifndef __WINDOW__
    #define __WINDOW__

    #include <string>
    #include <SDL2/SDL.h>
    #include <list>
    #include <memory>

    #include "../headerfile/mouse.hpp"
    #include "../headerfile/keyboard.hpp"
    #include "../headerfile/icon_loader.hpp"
    #include "../headerfile/text.hpp"
    #include "../headerfile/system_exec.hpp"
    #include "../headerfile/draw.hpp"
    #include "../headerfile/button.hpp"
    #include "../headerfile/files_display.hpp"

    void get_error (const std::string& error, const std::string& error_log, int code);

    class window
    {
    private:

        int *_window_width;
        int *_window_height;
        const std::string *_prog_name;
        SDL_Surface* _ico;

        SDL_Event _event{};
        bool _quit;

        SDL_Window *_prog_window;
        SDL_Renderer *_renderer;
        SDL_Rect _rect{};

        std::unique_ptr<icon_loader> iconLoader;
        std::unique_ptr<icon_loader> *iconLoader_ptr{};

        std::unique_ptr<mouse> mouse_control;
        std::unique_ptr<mouse> *mouse_control_ptr{};
        std::unique_ptr<keyboard> keyboard_control;

        std::unique_ptr<button> button_control;
        std::unique_ptr<button> *button_control_ptr{};

        std::unique_ptr<text> text1;
        std::unique_ptr<text> *text_ptr = &text1;

        std::unique_ptr<system_exec> system_exec1;
        std::unique_ptr<system_exec> *system_exec_ptr{};

        std::unique_ptr<draw> draw_on_window;
        std::unique_ptr<draw> *draw_ptr{};

        std::unique_ptr<files_display> set_files_display;

    public:
        window() = delete;
        explicit window(int *window_width, int *window_height, const std::string *prog_name, SDL_Surface* ico);
        ~window();

        void run_program();
        void initialize_program();
        void initialize_image();
    };
    

#endif