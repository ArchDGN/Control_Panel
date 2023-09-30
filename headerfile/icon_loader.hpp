#ifndef CONTROL_PANEL_ICON_LOADER_HPP
    #define CONTROL_PANEL_ICON_LOADER_HPP

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <string>

    struct Image
    {
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Rect _src_rect, _dest_rect;
        SDL_Rect *_src_rect_ptr, *_dest_rect_ptr;
    };

    class icon_loader
    {
        private:
            SDL_Renderer *_renderer;
            int *_window_width, *_window_height;

        public:
            icon_loader() = delete;
            icon_loader(SDL_Renderer *renderer, int *w, int *h);
            ~icon_loader() = default;

            Image load_image(std::string image_name);
            SDL_Rect set_rect(SDL_Rect src_rect, int x, int y, int width, int height);
            void set_rect_ptr(SDL_Rect *src_rect, int x, int y, int width, int height);
            SDL_Rect set_dest_rect(SDL_Rect dest_rect, int x, int y, int width, int height);
            void set_dest_rect_ptr(SDL_Rect *dest_rect, int x, int y, int width, int height);

            void show_image(Image image);
    };


#endif //CONTROL_PANEL_ICON_LOADER_HPP
