#ifndef __MOUSE__
    #define __MOUSE__

    #include <SDL2/SDL.h>
    #include <array>

    class mouse
    {
        private:
            std::array<bool, 3> click_statue;

        public:
            mouse();
            ~mouse() = default;

            void get_position(SDL_Event event, int *x, int *y);

            bool left_button_pressed(SDL_Event event);
            bool middle_button_pressed(SDL_Event event);
            bool right_button_pressed(SDL_Event event);

            bool left_button_released(SDL_Event event);
            bool middle_button_released(SDL_Event event);
            bool right_button_released(SDL_Event event);

            int mouse_wheel(SDL_Event event);

            bool get_click_statue(SDL_Event event, int code);
    };
    

#endif