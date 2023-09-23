#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <memory>

#include "../headerfile/draw.hpp"
#include "../headerfile/system_exec.hpp"

draw::draw(SDL_Renderer *renderer, SDL_Rect *rect, int *w, int *h, Square_Color fc) : _renderer(renderer), _rect(rect), _window_width(w), _window_height(h), _font_color(fc)
{
    set_color(Square_Color::NONE);
}
void draw::set_color(Square_Color color)
{

    // Set la couleur du renderer

    switch (color)
    {
        case Square_Color::Red:
            SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
            break;
        case Square_Color::Blue:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
            break;
        case Square_Color::Gray1:
            SDL_SetRenderDrawColor(_renderer, 20, 20, 20, 255);
            break;
        case Square_Color::Gray2:
            SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
            break;
        case Square_Color::LightGray1:
            SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
            break;

        default:
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
            break;
    }
}

void draw::draw_font()
{
    int *w = _window_width;
    int *h = _window_height;
    // Dessine le rectangle du haut de la fenetre
    draw_rectangle(0, 0, *w, *h / 10, *h, Square_Color::Gray2);
    // Dessine le rectangle a gauche de la fenetre
    draw_rectangle(0, 0, *w / 8, *h, *w, Square_Color::Gray2);
    // Dessine le rectangle en bas a droite de la fenetre
    draw_rectangle(*w - *w / 9, *h - *h / 4, *w, *h, *w, Square_Color::Gray2);

    // Dessine les contours des differents rectangles en gris clair
    draw_rectangle(0, 0, *w, *h, 2, Square_Color::LightGray1);
    draw_rectangle(0, 0, *w, *h / 10, 2, Square_Color::LightGray1);
    draw_rectangle(0, 0, *w / 8, *h, 2, Square_Color::LightGray1);
    draw_rectangle(*w - *w / 9, *h - *h / 4, *w, *h, 2, Square_Color::LightGray1);

    // Dessine le rectangle arrondi en haut a gauche de la fenetre
    draw_circle_x_square(5, 5, *w / 8 - 10, *h / 10 - 10, 20000, Square_Color::NONE);

    set_font_color();
}

void draw::draw_text(std::unique_ptr<text> &text1, std::unique_ptr<system_exec> &system_exec1)
{
    // Dessine le texte
    int *w = _window_width;
    int *h = _window_height;

    text1->draw_text(system_exec1->return_pwd(), *w / 8 + 10, *h / 20 - 20, *w - (*w / 8 + 10), 40, Text_Property::Revert_Cut_With_Points, Text_Property::Fit_Screen);

}

void draw::draw_rectangle(int x, int y, int width, int height, int radius, Square_Color color)
{
    /*
    x : coord d'origine x
    y : coord d'origine y
    width : longueur
    height : largeur
    radius : épaisseur de la bordure, si radius == width ou radius == height alors le rectangle est plein
    Square_Color : couleur
    */

    set_color(color);

    if (radius > width / 2)
        radius = width / 2;
    if (radius > height / 2)
        radius = height / 2;

    for (int i = 1; i <= radius; i++)
    {
        _rect->x = x + i;
        _rect->y = y + i;
        _rect->w = width - 2*i;
        _rect->h = height - 2*i;
        SDL_RenderDrawRect(_renderer, _rect);
    }

    set_font_color();
}

void draw::draw_circle(int x, int y, int min_radius, int max_radius, int min_angle, int max_angle, Square_Color color)
{
    /*
    x : coord d'origine x
    y : coord d'origine y
    min_radius : rayon du premier cercle
    max_radius : rayon du dernier cercle dessiner en px
    min_angle : angle en degre qui definie l'air du cercle a dessiner selon le cercle trigo
    mas_angle : angle en degre qui definie l'arriver sur le cercle trigo
    Square_Color : couleur
    */

    if (min_radius >= max_radius)
        min_radius = max_radius-1;

    set_color(color);

    _rect->w = 0;
    _rect->h = 0;
    for (int a = min_radius; a < max_radius; a++) {
        for (int i = min_angle; i < max_angle; i++) {
            _rect->x = x + a * cos(i * M_PI / 180);
            _rect->y = y - a * sin(i * M_PI / 180);
            SDL_RenderDrawRect(_renderer, _rect);
        }
    }
}

void draw::draw_circle_x_square(int x, int y, int width, int height, int radius, Square_Color color)
{
    //Cette fonction dessine une rectange avec les bords arrondi

    /*
    x : coord d'origine x
    y : coord d'origine y
    width : longueur
    height : largeur
    radius : épaisseur de la bordure, si radius == width ou radius == height alors le rectangle est plein
    Square_Color : couleur
    */

    if (height > width)
        height = width;

    if (radius > height / 2)
        radius = height /2;
    radius = height / 2 - radius;

    set_color(color);
    _rect->w = 0;
    _rect->h = 0;

    // Dessine les 2 cercles
    for (int a = radius; a <= height / 2; a++) {
        for (int i = 90; i < 271; i++) {
            _rect->x = x + height/2 + a * cos(i * M_PI / 180);
            _rect->y = y + height/2 - a * sin(i * M_PI / 180);
            if (i == 90 || i == 270)
            {
                _rect->w = width - height + 1;
                _rect->x-=1;
            }

            SDL_RenderDrawRect(_renderer, _rect);
            _rect->w = 0;
        }
    }

    for (int a = radius; a <= height / 2; a++) {
        for (int i = -90; i < 91; i++) {
            _rect->x = x + width - height/2 + a * cos(i * M_PI / 180);
            _rect->y = y + height/2 - a * sin(i * M_PI / 180);
            SDL_RenderDrawRect(_renderer, _rect);
        }
    }
}

void draw::set_font_color()
{
    set_color(_font_color);
}