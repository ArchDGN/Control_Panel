#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../headerfile/window.hpp"
#include "../headerfile/draw.hpp"
#include "../headerfile/mouse.hpp"
#include "../headerfile/keyboard.hpp"

void window::run_program()
{

    mouse mouse_control{};          // Init de la souris
    keyboard keyboard_control{};    // Init du clavier

    draw draw_on_window{_renderer, &_rect, _window_width, _window_height, Square_Color::Gray1};

    while (!_quit)
    {
        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                _quit = true;
            }

            SDL_RenderClear(_renderer);     // Efface l'affichade
            SDL_GetWindowSize(_prog_window, _window_width, _window_height);

            draw_on_window.set_font_color();

            keyboard_control.is_pressed(_event);    // Verifie si une touche est presse
            keyboard_control.is_released(_event);   // Verifie si une touche est relache


            mouse_control.get_position(_event, &mouse_pos_x, &mouse_pos_y);         // Attibut au variable mouse_pos_x et mouse_pos_y la position de la souris

            draw_on_window.draw_font();

            TTF_Font *TimesNewRomance = TTF_OpenFont("TimesNewRomance.ttf", 120);
            SDL_Color White = {255, 255, 255, 255};
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TimesNewRomance, "put your text here", White);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
            SDL_Rect Message_rect; //create a rect
            Message_rect.x = 500;  //controls the rect's x coordinate
            Message_rect.y = 500; // controls the rect's y coordinte
            Message_rect.w = 200; // controls the width of the rect
            Message_rect.h = 50; // controls the height of the rect
            SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);

            SDL_RenderPresent(_renderer);   // Affiche le render

        }
    }
}

window::window(int *window_width, int *window_height, const std::string *prog_name, SDL_Surface* ico) : _window_width(window_width), _window_height(window_height), _prog_name(prog_name), _ico(ico)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)      // SDL init
        get_error("Erreur lors de l'initialisation de SDL : ", SDL_GetError(), -1);

                                // Passe le format du nom de la fenetre de std::string a const char *
    _prog_window = SDL_CreateWindow(_prog_name->c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *_window_width, *_window_height, SDL_WINDOW_SHOWN);     // Creation de la fenetre
    if (!_prog_window)
        get_error("Erreur lors de la création de la fenêtre : ", SDL_GetError(), 0);
    SDL_SetWindowResizable(_prog_window, SDL_TRUE);
    SDL_SetWindowMinimumSize(_prog_window, 400, 400);

    _renderer = SDL_CreateRenderer(_prog_window, -1, SDL_RENDERER_ACCELERATED);     // Creation du render
    if (!_renderer) {
        SDL_DestroyWindow(_prog_window);
        get_error("Erreur lors de la création du renderer : ", SDL_GetError(), 0);
    }

    SDL_SetWindowIcon(_prog_window, ico);

    TTF_Init(); // Initialisation du module d'affichage de texte

    _quit = false;  // Init de la variable qui permet de quitter le programme, une fois a "true" la boucle while principale se coupe et le programme s'arrete

}

window::~window()
{
    SDL_RenderClear(_renderer);         //  Clear de tout les asset
    SDL_DestroyRenderer(_renderer);     //
    SDL_DestroyWindow(_prog_window);    //      Le programme finit correctement, sans erreur
    TTF_Quit();
    SDL_Quit();                         //
}