#include <iostream>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../headerfile/window.hpp"
#include "../headerfile/draw.hpp"
#include "../headerfile/mouse.hpp"
#include "../headerfile/keyboard.hpp"
#include "../headerfile/text.hpp"
#include "../headerfile/system_exec.hpp"
#include "../headerfile/files_display.hpp"

void window::run_program()
{

    mouse mouse_control{};          // Init de la souris
    keyboard keyboard_control{};    // Init du clavier

    std::unique_ptr<text> text1(new text{_window_width, _window_height, "TimesNewRomance.ttf", 50, Square_Color::White, 255, _renderer});    // Init du text

    std::unique_ptr<system_exec> system_exec1(new system_exec);    // Init du system_exec

    std::unique_ptr<draw> draw_on_window(new draw{_renderer, &_rect, _window_width, _window_height, Square_Color::Gray1});
    std::unique_ptr<draw> *draw = &draw_on_window;

    files_display set_files_display{draw, _window_width, _window_height};

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

            draw_on_window->set_font_color();

            /*
            keyboard_control.is_pressed(_event);    // Verifie si une touche est presse
            keyboard_control.is_released(_event);   // Verifie si une touche est relache


            mouse_control.get_position(_event, &mouse_pos_x, &mouse_pos_y);         // Attibut au variable mouse_pos_x et mouse_pos_y la position de la souris
             */

            draw_on_window->draw_font();    // Affiche le font
            draw_on_window->draw_text(text1, system_exec1);    // Affiche le text

            set_files_display.display();

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