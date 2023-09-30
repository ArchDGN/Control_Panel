#ifndef CONTROL_PANEL_FILES_DISPLAY_HPP
    #define CONTROL_PANEL_FILES_DISPLAY_HPP

    #include <SDL2/SDL.h>
    #include <memory>
    #include <list>

    #include "../headerfile/data.hpp"
    #include "../headerfile/draw.hpp"
    #include "../headerfile/icon_loader.hpp"

    class files_display
    {
        private:
            std::unique_ptr<draw> *_draw;
            std::unique_ptr<icon_loader> *_icon_loader;

            int *_window_width;
            int *_window_height;

            int ref_width;
            int ref_height;


            int directory_arrow_x;
            int directory_arrow_y;
            int directory_arrow_width;
            int directory_arrow_height;
            int number_of_files_w;
            int file_centered_w;
            int number_of_files_y;
            int file_centered_h;

            std::list<Image*>::iterator image;

        public:
            files_display() = delete;
            files_display(std::unique_ptr<draw> *draw, std::unique_ptr<icon_loader> *icl, int *w, int *h);
            ~files_display() = default;

            void display(std::list<Image*> image_list_ptr);
    };


#endif //CONTROL_PANEL_FILES_DISPLAY_HPP
