#ifndef CONTROL_PANEL_ICON_LOADER_HPP
    #define CONTROL_PANEL_ICON_LOADER_HPP

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <string>
    #include <vector>
    #include <map>

    class icon_loader
    {
        private:

            SDL_Renderer *_renderer;
            int *_window_width, *_window_height;

            struct Image
            {
                std::string id;
                SDL_Texture* texture;
                SDL_Rect _src_rect, _dest_rect;
                SDL_Rect *_src_rect_ptr, *_dest_rect_ptr;
            };

            std::vector<Image> _image_list;

            static SDL_Rect set_rect(SDL_Rect src_rect, int x, int y, int width, int height);
            static SDL_Rect set_dest_rect(SDL_Rect dest_rect, int x, int y, int width, int height);

        public:
            icon_loader() = delete;
            icon_loader(SDL_Renderer *renderer, int *w, int *h);
            ~icon_loader();

            void load_image_with_id(const std::string& id, const std::string& image_link);
            void set_rect_by_id(const std::string& id, int x, int y, int width, int height);
            void set_dest_rect_by_id(const std::string& id, int x, int y, int width, int height);
            void show_image_by_id(const std::string& id);

            Image* return_image_by_id(const std::string& id);

    };


#endif //CONTROL_PANEL_ICON_LOADER_HPP
