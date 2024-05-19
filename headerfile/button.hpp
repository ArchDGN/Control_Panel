#ifndef CONTROL_PANEL_BUTTON_HPP
    #define CONTROL_PANEL_BUTTON_HPP

    #include <SDL2/SDL.h>
    #include<string>
    #include<vector>
    #include<memory>

    #include "../headerfile/mouse.hpp"

    class button
    {
        private:

            int *_window_width;
            int *_window_height;

            std::unique_ptr<mouse> *_mouse_control;

            struct Button {
                std::string id;
                int x;
                int y;
                int w;
                int h;
                void (*pointer_to_function)();
            };

            std::vector<Button> _button_list;


        public:
            button() = delete;
            explicit button(std::unique_ptr<mouse> *mouse, int *window_width, int *window_height);
            ~button() = default;

            void create_button_by_id(std::string id, int x, int y, int w, int h, void (*pointer_to_function)());
            void edit_button_by_id(const std::string& id, int x, int y, int w, int h, void (*pointer_to_function)());
            void delete_button_by_id(const std::string& id);
            Button* return_button_by_id(const std::string& id);

            bool is_button_clicked(Button *button);
            bool check_all_buttons_clicked();
            bool specific_button_clicked(const std::string &id);


    };

#endif //CONTROL_PANEL_BUTTON_HPP
