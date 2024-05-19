#ifndef __MOUSE__
    #define __MOUSE__

    #include <SDL2/SDL.h>
    #include <array>

    class mouse
    {
        private:
            std::array<bool, 3> click_statue{};

            int _mouse_x{};
            int _mouse_y{};

            SDL_Event *_event;

        public:
            mouse() = delete;
            explicit mouse(SDL_Event *event);
            ~mouse() = default;

            void return_position(int *x, int *y);
            void update_position();

            bool left_button_pressed();
            bool middle_button_pressed();
            bool right_button_pressed();

            bool left_button_released();
            bool middle_button_released();
            bool right_button_released();

            int mouse_wheel();

            bool get_click_statue(int code);
    };
    

#endif