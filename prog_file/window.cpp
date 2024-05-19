#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <thread>

#include "../headerfile/window.hpp"
#include "../headerfile/draw.hpp"
#include "../headerfile/files_display.hpp"
#include "../headerfile/button.hpp"

void window::run_program()
{

    initialize_program();

    iconLoader->load_image_with_id("directory", "icon/directoryv2.png");
    iconLoader->load_image_with_id("file", "icon/filev2.png");

    // Objet: Affichage des fichiers
    files_display set_files_display{draw_ptr, iconLoader_ptr, system_exec_ptr, text_ptr, _window_width, _window_height};
    //

    // Init des variables pour le calcul du nombre d'iteration par seconde, fps
    int count = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    Uint32 frameStart, frameTime;
    const int FRAME_DELAY = 1000 / 120;
    //

    while (!_quit)
    {
        frameStart = SDL_GetTicks();

        //
        // Cette partie de code permet de calculer le nombre d'iteration par seconde
        // Et de limiter le nombre d'iteration par seconde a 120
        count++;
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end_time - start_time;

        if (elapsed_seconds.count() >= 1.0) {
            //std::cout << "Nombre d'itérations par seconde : " << count << std::endl;
            count = 0;
            start_time = std::chrono::high_resolution_clock::now();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0 / 120.0)));
        // Fin de la partie
        //

        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                //std::cout << "Quit" << std::endl;
                _quit = true;
            }

            SDL_RenderClear(_renderer);     // Efface l'affichade
            SDL_GetWindowSize(_prog_window, _window_width, _window_height);

            draw_on_window->set_font_color();

            button_control->check_all_buttons_clicked();    // Verifie si un bouton a ete clique

            draw_on_window->draw_font();    // Affiche le font
            draw_on_window->draw_text(text1, system_exec1);    // Affiche le text

            set_files_display.display();   // Affiche les fichiers

            SDL_RenderPresent(_renderer);   // Affiche le render

            frameTime = SDL_GetTicks() - frameStart;
            if (frameTime < FRAME_DELAY) {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
        }
    }
}


void window::initialize_program()
{

    // Creation de l'objet qui permet de charger les icones
    iconLoader = std::make_unique<icon_loader>(_renderer, _window_width, _window_height);
    iconLoader_ptr = &iconLoader;

    // Souris + Clavier
    mouse_control = std::make_unique<mouse>(&_event);          // Init de la souris
    mouse_control_ptr = &mouse_control;                        // Pointeur qui pointe sur la souris

    keyboard_control = std::make_unique<keyboard>();    // Init du clavier
    //

    // Objet: Bouton
    button_control = std::make_unique<button>(mouse_control_ptr, _window_width, _window_height);
    button_control_ptr = &button_control;

    // Objet: Affichage du texte
    text1 = std::make_unique<text>(_window_width, _window_height, "roboto/Roboto-Medium.ttf", 32, Square_Color::White, 255, _renderer);
    text_ptr = &text1;
    //

    // Objet: Execution de commande systeme
    system_exec1 = std::make_unique<system_exec>();
    system_exec_ptr = &system_exec1;
    //

    // Objet: Dessin de l'interface
    draw_on_window = std::make_unique<draw>(_renderer, &_rect, _window_width, _window_height, Square_Color::Gray1);
    draw_ptr = &draw_on_window;
    //
}


window::window(int *window_width, int *window_height, const std::string *prog_name, SDL_Surface* ico)
    : _window_width(window_width), _window_height(window_height), _prog_name(prog_name), _ico(ico)
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
    if (_renderer) {
        SDL_RenderClear(_renderer);
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_prog_window) {
        SDL_DestroyWindow(_prog_window);
        _prog_window = nullptr;
    }

    SDL_Quit();
}
