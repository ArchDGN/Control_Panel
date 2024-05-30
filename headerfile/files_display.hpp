#ifndef CONTROL_PANEL_FILES_DISPLAY_HPP
    #define CONTROL_PANEL_FILES_DISPLAY_HPP

    #include <SDL2/SDL.h>
    #include <memory>
    #include <list>

    #include "../headerfile/data.hpp"
    #include "../headerfile/draw.hpp"
    #include "../headerfile/icon_loader.hpp"
    #include "../headerfile/button.hpp"

    class files_display
    {
        private:
            std::unique_ptr<draw> *_draw;
            std::unique_ptr<icon_loader> *_icon_loader;
            std::unique_ptr<system_exec> *_system_exec;
            std::unique_ptr<text> *_text_display;
            std::unique_ptr<button> *_button;

            int *_window_width;
            int *_window_height;

            int ref_width;
            int ref_height;

            int max_number_of_files_w{};
            int max_number_of_files_h{};
            int file_coord_x{};
            int file_coord_y{};

            int total_number_of_files;

            bool _refresh_button = true;

            std::string file_name;

            void refresh_display_info();

        public:
            files_display() = delete;
            files_display(std::unique_ptr<draw> *draw, std::unique_ptr<icon_loader> *icl, std::unique_ptr<system_exec> *system_exec_ptr, std::unique_ptr<text> *text_ptr, std::unique_ptr<button> *button, int *w, int *h);
            ~files_display() = default;

            void display();
            void text_display(int file_x, int file_y, const std::string& text);
            void icon_display(int file_x, int file_y, const std::string& id);
            void button_display(int file_x, int file_y);

            void add_button_click(int file_x, int file_y, const std::string& id, const std::string &nb_id);
            void refresh_after_button_click(const std::string &id);
            void remove_all_file_and_directory_buttons();

    };


#endif //CONTROL_PANEL_FILES_DISPLAY_HPP
