#include <iostream>
#include <string>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headerfile/imageloader.hpp"
#include "../headerfile/window.hpp"
#include "../headerfile/draw.hpp"

imageloader::imageloader(SDL_Window *prog_window, SDL_Renderer *renderer, std::string image_name, const int *w, const int *h) : _window_width(w), _window_height(h)
{
    _image_surface = IMG_Load(image_name.c_str());        // Chargement de l'image, "image_name.c_str()" convertie le nom du format std::string au format char *
    if (!_image_surface)                                 // Verification que l'image a bien etait chargee
    {
        close_error(prog_window, renderer);
        get_error("Erreur lors du chargement de l'image : ", IMG_GetError(), 0);
    }

    _image_width = _image_surface->w;   // On récupere la largeur et la hauteur de l'image
    _image_height = _image_surface->h;  //

    _image_texture = SDL_CreateTextureFromSurface(renderer, _image_surface);          // Création d'une texture à partir de l'image chargée
    SDL_FreeSurface(_image_surface);                                                 // Libération de la surface, la texture est indépendante

    if (!_image_texture)     // Vérification que la texture a bien été créée
    {
        close_error(prog_window, renderer);
        get_error("Erreur lors de la création de la texture : ", SDL_GetError(), 0);
        
    }

    _zoom_point_x = *_window_width / 2;      // Initialisation des trois variable pour le zoom
    _zoom_point_y = *_window_height / 2;     //    Les cooordonné x,y du point visé
    _zoom_factor = 1;                   //    Le facteur de zoom 1 = pas de zoom, 40 maximum du zoom

    set_default_srcRect();      // Initialisation des valeur de src-rect et de dest_rect
    set_default_destRect();     // Permet de zoom en recadrant l'image
}

imageloader::~imageloader()
{
    SDL_DestroyTexture(_image_texture);     // Detruit la texture
}

SDL_Texture* imageloader::get_image()
{
    return _image_texture;       // retourne la texture pour l'utiliser
}

void imageloader::close_error(SDL_Window *prog_window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);      //Destruction du render
    SDL_DestroyWindow(prog_window);     //Destruction de la fenetre
}

void imageloader::set_zoom_point(int x, int y)
{
    if (_zoom_factor == 1)  // Pas de zoom
    {
        _zoom_point_x = float(x);;     // Place le point de zoom sur les coordonnées de la souris
        _zoom_point_y = float(y);;     //

    } else  // Si la fenetre est deja zoomer alors le zoom est remis a 1
    {
        _zoom_factor = 1;           //
        set_default_destRect();     // L'image repend c'est caracteristique initial afin d'annule le zoom
        set_default_srcRect();      //
    }
    
}

void imageloader::zoom_in()
{
    if (_zoom_factor < 41)
    {
        _zoom_factor++;

        _dest_rect.x -= round(_zoom_point_x / 10);      // On deplace les coordonne d'origine x, y de l'image en fonction de la position de la souris
        _dest_rect.y -= round(_zoom_point_y / 10);      // Par rexemple pour un zoom en bas a droite l'image double de taille et est deplace en -360x, -180y
                                                        // Par rexemple pour un zoom en haut a gauche l'image double de taille et est deplace en 0x, 0y

        _dest_rect.w += *_window_width / 10;         // Zoom avec une force de 10 donc
        _dest_rect.h += *_window_height / 10;        //      lageur et hauteur / 10

        //std::cout << _dest_rect.x << " " << _dest_rect.y << std::endl;
    }
}

void imageloader::zoom_out()    // Inverse de la fonction zoom_in
{
    if (_zoom_factor > 1)
    {
        _zoom_factor--;

        _dest_rect.x += round(_zoom_point_x / 10);
        _dest_rect.y += round(_zoom_point_y / 10);

        _dest_rect.w -= *_window_width / 10;
        _dest_rect.h -= *_window_height / 10;
    }
}

SDL_Rect imageloader::get_src_rect()
{
    return _src_rect;   // renvoie src_rect
}
SDL_Rect imageloader::get_dest_rect()
{
    return _dest_rect;  // renvoi dest_rec
}
SDL_Rect* imageloader::get_ptr_src_rect()
{
    return &_src_rect;  // renvoie le pointer de src_rect pour la fonction de sdl qui afficher l'image
}
SDL_Rect* imageloader::get_ptr_dest_rect()
{
    return &_dest_rect; // renvoie le pointer de dest_rect pour la fonction de sdl qui afficher l'image
}


void imageloader::set_default_srcRect() // init src_rect
{
    if (_zoom_factor == 1)
    {
        _src_rect.x = 0;
        _src_rect.y = 0;
        _src_rect.w = _image_width;
        _src_rect.h = _image_height;
    }
}

void imageloader::set_default_destRect()    //init dest_rect
{
    if (_zoom_factor == 1)
    {
        _dest_rect.x = 0;
        _dest_rect.y = 0;
        _dest_rect.w = *_window_width;
        _dest_rect.h = *_window_height;
    }
}