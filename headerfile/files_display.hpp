#ifndef CONTROL_PANEL_FILES_DISPLAY_HPP
    #define CONTROL_PANEL_FILES_DISPLAY_HPP

    #include <SDL2/SDL.h>
    #include <memory>

    #include "../headerfile/data.hpp"
    #include "../headerfile/draw.hpp"

    class files_display
    {
        private:
            std::unique_ptr<draw> *_draw;

            int *_window_width;
            int *_window_height;

        public:
            files_display() = delete;
            files_display(std::unique_ptr<draw> *draw, int *w, int *h);
            ~files_display() = default;

            void display();
    };


#endif //CONTROL_PANEL_FILES_DISPLAY_HPP
