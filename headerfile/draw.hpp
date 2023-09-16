#ifndef __DRAW__
    #define __DRAW__

    #include <SDL2/SDL.h>


    enum class Square_Color
    {
        Red,
        Blue,

        NONE
    };


    class draw
    {
    private:
        SDL_Renderer *_renderer;
        const int *_window_width, *_window_height;

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
        draw(SDL_Renderer *renderer, const int *w, const int *h);
        ~draw() = default;

        void set_color(Square_Color color);

        void draw_grid();
        void draw_square(int x1, int y1, int width, int height, Square_Color color);

        void default_zoom();
        void grid_zoom_in();
        void grid_zoom_out();
        void grid_set_zoom_point(int x, int y);
    };


#endif