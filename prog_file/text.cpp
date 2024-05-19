#include <iostream>
#include <string>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../headerfile/text.hpp"

text::text(int *window_width, int *window_height, const std::string& file_name, int pt_size, Square_Color color, Uint8 alpha, SDL_Renderer *renderer) : _window_width(window_width), _window_height(window_height), _renderer(renderer)
{
    //std::cout << "Init text" << std::endl;

    // Init de la police de charactere
    _TimesNewRomance = TTF_OpenFont(file_name.c_str(), pt_size);
    if (!_TimesNewRomance)
        std::cout << "Erreur lors de l'ouverture de la police : " << TTF_GetError() << std::endl;

    set_color(color, alpha);
}

text::~text()
{
    // Ferme la police de charactere
    if (_TimesNewRomance) {
        TTF_CloseFont(_TimesNewRomance);
        _TimesNewRomance = nullptr;
    }

    TTF_Quit();
}

void text::draw_text(std::string text_to_draw, int x, int y, int width, int height, Text_Property text, Text_Property screen)
{
    // Variable pour la longueur du texte en terme de charactere
    int text_lenght = text_to_draw.length();
    // Variable pour la taille du texte en pixel
    int auto_width = text_lenght * (height / 3);

    // Si le texte est plus grand que la taille de la fenetre alors on le coupe
    if (screen == Text_Property::Fit_Screen)
    {
        width = *_window_width - x;
    }

    // Si le texte est plus grand que la taille indique alors on le coupe
    if (auto_width > width && text == Text_Property::Cut)
    {
        text_lenght = width / (height / 3);
        auto_width = width;

        text_to_draw = text_to_draw.substr(0, text_lenght);
    }

    // Si le texte est plus grand que la taille indique alors on coupe le debut
    if (auto_width > width && text == Text_Property::Revert_Cut)
    {
        text_lenght = width / (height / 3);
        auto_width = width;

        text_to_draw = text_to_draw.substr(text_to_draw.length() - text_lenght, text_to_draw.length());
    }

    // Si le texte est plus grand que la taille de la indique alors on le coupe et on ajoute des points de suspension
    if (auto_width > width && text == Text_Property::Cut_With_Points)
    {
        text_lenght = width / (height / 3);
        auto_width = width;

        text_to_draw = text_to_draw.substr(0, text_lenght - 3);
        text_to_draw += "...";
    }

    // Si le texte est plus grand que la taille de la indique alors on coupe le debut et on ajoute des points de suspension
    if (auto_width > width && text == Text_Property::Revert_Cut_With_Points)
    {
        text_lenght = width / (height / 3);
        auto_width = width;

        text_to_draw = text_to_draw.substr(text_to_draw.length() - text_lenght + 3, text_to_draw.length());
        text_to_draw = "..." + text_to_draw;
    }

    // Si le texte est plus grand que la taille de la indique alors on change la taille de la police pour qu'il rentre
    if (auto_width > width && text == Text_Property::Change_Size)
    {
        height = (3 * width) / text_lenght;
        auto_width = text_lenght * (height / 3);
    }

    // Surface du texte
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_TimesNewRomance, text_to_draw.c_str(), _color);

    // Texture du texte
    SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    // Rect du texte, c'est a dire la position et la taille du texte
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  //controls the rect's x coordinate
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = auto_width; // controls the width of the rect
    Message_rect.h = height; // controls the height of the rect

    // Affiche le texte
    SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
}

void text::set_color(Square_Color color, Uint8 alpha)
{
    // Selectionne la couleur du texte

    switch (color)
    {
        case Square_Color::Red:
            _color = {255, 0, 0, alpha};
            break;
        case Square_Color::Blue:
            _color = {0, 0, 255, alpha};
            break;
        case Square_Color::Gray1:
            _color = {20, 20, 20, alpha};
            break;
        case Square_Color::Gray2:
            _color = {15, 15, 15, alpha};
            break;
        case Square_Color::LightGray1:
            _color = {100, 100, 100, alpha};
            break;
        case Square_Color::White:
            _color = {255, 255, 255, alpha};
            break;

        default:
            _color = {0, 0, 0, alpha};
            break;
    }
}
