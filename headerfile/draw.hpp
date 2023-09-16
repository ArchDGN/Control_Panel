#ifndef __DRAW__
    #define __DRAW__

    #include <SDL2/SDL.h>


    enum class Square_Color
    {
        Red,
        Blue,

        Gray1,
        Gray2,

        LightGray1,

        NONE
    };


    class draw
    {
    private:
        SDL_Renderer *_renderer;
        SDL_Rect *_rect;
        int *_window_width, *_window_height;
        const Square_Color _font_color;

        float _zoom_point_x, _zoom_point_y;
        int _zoom_factor;

        struct zoom
        {
            int x, y;
            int w, h;
        };

        zoom zoom_value{};
        
    public:
        draw() = delete;
        draw(SDL_Renderer *renderer, SDL_Rect *rect, int *w, int *h, Square_Color fc);
        ~draw() = default;

        void set_color(Square_Color color);

        void draw_font();
        void set_font_color();
        void draw_rectangle(int x, int y, int width, int height, int radius, Square_Color color);
        void draw_circle(int x, int y, int min_radius, int max_radius, int min_angle, int max_angle, Square_Color color);
        void draw_circle_x_square(int x, int y, int width, int height, int radius, Square_Color color);
    };


#endif