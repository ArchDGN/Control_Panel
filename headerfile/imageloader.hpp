#ifndef __IMAGE__
    #define __IMAGE__

    #include <string>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>

    class imageloader
    {
        private:
            const int *_window_width, *_window_height;

            SDL_Surface* _image_surface;
            SDL_Texture* _image_texture;

            SDL_Rect _src_rect, _dest_rect;
            int _image_width, _image_height;
            float _zoom_point_x, _zoom_point_y;
            int _zoom_factor;

        public:

            imageloader() = delete;
            imageloader(SDL_Window *prog_window, SDL_Renderer *renderer, std::string image_name, const int *w, const int *h);
            ~imageloader();

            SDL_Texture* get_image();
            void close_error(SDL_Window *prog_window, SDL_Renderer *renderer);

            void zoom_in();
            void zoom_out();
            void set_zoom_point(int x, int y);
            void set_default_srcRect();
            void set_default_destRect();

            SDL_Rect get_src_rect();
            SDL_Rect get_dest_rect();
            SDL_Rect* get_ptr_src_rect();
            SDL_Rect* get_ptr_dest_rect();
    };

#endif