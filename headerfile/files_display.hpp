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
              std::unique_ptr<system_exec> *_system_exec;

            int *_window_width;
            int *_window_height;

            int ref_width;
            int ref_height;

            int max_number_of_files_w;
            int max_number_of_files_h;
            int file_coord_x;
            int file_coord_y;

            std::vector<Image *>::iterator image;


            void refresh_display_info();
        public:
            files_display() = delete;
            files_display(std::unique_ptr<draw> *draw, std::unique_ptr<icon_loader> *icl, std::unique_ptr<system_exec> *system_exec_ptr, int *w, int *h);
            ~files_display() = default;

            void display(std::vector<Image*> image_list_ptr);
    };


#endif //CONTROL_PANEL_FILES_DISPLAY_HPP
