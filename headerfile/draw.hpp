#ifndef __DRAW__
    #define __DRAW__

    #include <SDL2/SDL.h>

    #include "../headerfile/data.hpp"
    #include "../headerfile/text.hpp"
    #include "../headerfile/system_exec.hpp"

    class draw
    {
    private:
        SDL_Renderer *_renderer;
        SDL_Rect *_rect;
        int *_window_width, *_window_height;
        const Square_Color _font_color;
        
    public:
        draw() = delete;
        draw(SDL_Renderer *renderer, SDL_Rect *rect, int *w, int *h, Square_Color fc);
        ~draw() = default;

        void set_color(Square_Color color, int alpha);

        void draw_font();
        void draw_text(std::unique_ptr<text> &text1, std::unique_ptr<system_exec> &system_exec1);

        void set_font_color();
        void draw_rectangle(int x, int y, int width, int height, int radius, Square_Color color, int alpha);
        void draw_circle(int x, int y, int min_radius, int max_radius, int min_angle, int max_angle, Square_Color color, int alpha);
        void draw_circle_x_square(int x, int y, int width, int height, int radius, Square_Color color, int alpha);
    };


#endif