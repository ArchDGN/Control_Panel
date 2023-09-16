#ifndef __KEYBOARD__
    #define __KEYBOARD__

    #include <array>

    #include <SDL2/SDL.h>

        class keyboard
        {
        private:
            const int key_array_size = 2;
            int key_name[2];
            int key_name_kp[2];
            std::array<bool, 2> key_statue;
            
        public:
            keyboard();
            ~keyboard() = default;

            void is_pressed(SDL_Event event);
            void is_released(SDL_Event event);

            bool get_info(int key_code);

        };

#endif