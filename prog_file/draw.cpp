#include <iostream>
#include <SDL2/SDL.h>

#include "../headerfile/draw.hpp"

draw::draw(SDL_Renderer *renderer, const int *w, const int *h) : _renderer(renderer), _window_width(w), _window_height(h)
{
    set_color(Square_Color::NONE);

    _zoom_point_x = *_window_width / 2;      // Initialisation des trois variable pour le zoom
    _zoom_point_y = *_window_height / 2;     //    Les cooordonné x,y du point visé
    _zoom_factor = 1;                   //    Le facteur de zoom 1 = pas de zoom, 40 maximum du zoom
    default_zoom();
}
void draw::set_color(Square_Color color)
{
    switch (color)
    {
    case Square_Color::Red:
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
        break;
    case Square_Color::Blue:
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
        break;
    
    default:
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        break;
    }
}

void draw::draw_grid()
{
    draw_square( 100, 100, 100, 100, Square_Color::Red);

}

void draw::draw_square(int x1, int y1, int width, int height, Square_Color color)
{
    set_color(color);

    SDL_RenderDrawLine(_renderer, x1, y1, x1 + width, y1);    // x1 y1 x2 y2    Ligne du haut
    SDL_RenderDrawLine(_renderer, x1, y1 + height, x1 + width, y1 + height);    // x1 y1 x2 y2  Ligne du bas

    SDL_RenderDrawLine(_renderer, x1, y1, x1, y1 + height);    // x1 y1 x2 y2   Cote gauche
    SDL_RenderDrawLine(_renderer, x1 + width, y1, x1 + width, y1 + height);    // x1 y1 x2 y2   Cote droit

}


void draw::grid_set_zoom_point(int x, int y)
{
    if (_zoom_factor == 1)  // Pas de zoom
    {
        _zoom_point_x = float(x);     // Place le point de zoom sur les coordonnées de la souris
        _zoom_point_y = float(y);     //

    } else  // Si la fenetre est deja zoomer alors le zoom est remis a 1
    {
        _zoom_factor = 1;
        default_zoom();
    }
    
}

void draw::grid_zoom_in()
{
    if (_zoom_factor < 41)
    {
        _zoom_factor++;

        zoom_value.x -= round(_zoom_point_x / 10);      // On deplace les coordonne d'origine x, y de l'image en fonction de la position de la souris
        zoom_value.y -= round(_zoom_point_y / 10);      // Par rexemple pour un zoom en bas a droite l'image double de taille et est deplace en -360x, -180y
                                                        // Par rexemple pour un zoom en haut a gauche l'image double de taille et est deplace en 0x, 0y

        zoom_value.w += *_window_width / 10;         // Zoom avec une force de 10 donc
        zoom_value.h += *_window_height / 10;        //      lageur et hauteur / 10

    }
}

void draw::grid_zoom_out()
{
    if (_zoom_factor > 1)
    {
        _zoom_factor--;

        zoom_value.x += round(_zoom_point_x / 10);      // On deplace les coordonne d'origine x, y de l'image en fonction de la position de la souris
        zoom_value.y += round(_zoom_point_y / 10);      // Par rexemple pour un zoom en bas a droite l'image double de taille et est deplace en -360x, -180y
                                                        // Par rexemple pour un zoom en haut a gauche l'image double de taille et est deplace en 0x, 0y

        zoom_value.w -= *_window_width / 10;         // Zoom avec une force de 10 donc
        zoom_value.h -= *_window_height / 10;        //      lageur et hauteur / 10
    }
}

void draw::default_zoom()
{
    zoom_value.x = 0;
    zoom_value.y = 0;
    zoom_value.w = *_window_width;
    zoom_value.h = *_window_height;
}