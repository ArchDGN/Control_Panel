#include <iostream>
#include <string>

#include "../headerfile/window.hpp"
#include "../headerfile/icon_loader.hpp"

icon_loader::icon_loader(SDL_Renderer *renderer, int *w, int *h) : _renderer(renderer), _window_width(w), _window_height(h)
{
    //std::cout << "icon_loader constructor" << std::endl;
}

void icon_loader::show_image(Image image)
{
    // Affichage de l'image
    SDL_RenderCopy(_renderer, image.texture, image._src_rect_ptr, image._dest_rect_ptr);
}


Image icon_loader::load_image(std::string image_name)
{
    // Creation d'une nouvelle image
    Image new_image;

    /*
     * Les images ont comme propriétés:
     *  - surface: c'est l'image chargée
     *  - texture: c'est la texture qui est indépendante de la surface
     *  - _src_rect: c'est le rectangle qui contient les coordonnées de l'image chargée
     *  - _dest_rect: c'est le rectangle qui contient les coordonnées de l'image affichée
     *
     *  - _src_rect_ptr: c'est un pointeur qui pointe sur le rectangle _src_rect
     *  - _dest_rect_ptr: c'est un pointeur qui pointe sur le rectangle _dest_rect
     * */

    // Chargement de l'image dans la surface
    new_image.surface = IMG_Load(image_name.c_str());        // Chargement de l'image, "image_name.c_str()" convertie le nom du format std::string au format char *
    if (!new_image.surface)                                      // Verification que l'image a bien etait chargee
        get_error("Erreur lors du chargement de l'image : ", IMG_GetError(), 0);

    // Creation de la texture a partir de la surface
    new_image.texture = SDL_CreateTextureFromSurface(_renderer, new_image.surface);     // Création d'une texture à partir de l'image chargée
    SDL_FreeSurface(new_image.surface);                                                         // Libération de la surface, la texture est indépendante

    // Vérification que la texture a bien été créée
    if (!new_image.texture)
        get_error("Erreur lors de la création de la texture : ", SDL_GetError(), 0);


    // Initialisation de src_rect a la taille de l'image
    new_image._src_rect = set_rect(new_image._src_rect, 0, 0, new_image.surface->w, new_image.surface->h);
    // Initialisation de dest_rect a la taille de la fenetre
    new_image._dest_rect = set_dest_rect(new_image._dest_rect, 0, 0, *_window_width, *_window_height);

    // Initialisation des pointeurs sur src_rect et dest_rect
    new_image._src_rect_ptr = &new_image._src_rect;
    new_image._dest_rect_ptr = &new_image._dest_rect;

    return new_image;
}

SDL_Rect icon_loader::set_rect(SDL_Rect src_rect, int x, int y, int width, int height)
{
    src_rect.x = x;
    src_rect.y = y;
    src_rect.w = width;
    src_rect.h = height;

    return src_rect;
}
void icon_loader::set_rect_ptr(SDL_Rect *src_rect, int x, int y, int width, int height)
{
    src_rect->x = x;
    src_rect->y = y;
    src_rect->w = width;
    src_rect->h = height;
}

SDL_Rect icon_loader::set_dest_rect(SDL_Rect dest_rect, int x, int y, int width, int height)
{
    dest_rect.x = x;
    dest_rect.y = y;
    dest_rect.w = width;
    dest_rect.h = height;

    return dest_rect;
}
void icon_loader::set_dest_rect_ptr(SDL_Rect *dest_rect, int x, int y, int width, int height)
{
    dest_rect->x = x;
    dest_rect->y = y;
    dest_rect->w = width;
    dest_rect->h = height;
}