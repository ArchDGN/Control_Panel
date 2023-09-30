#include <iostream>
#include <string>
#include <memory>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <thread>

#include "../headerfile/window.hpp"
#include "../headerfile/draw.hpp"
#include "../headerfile/files_display.hpp"

void window::run_program()
{
    //
    // Cette partie charge les icones
    //

    // Creation de l'objet qui permet de charger les icones
    std::unique_ptr<icon_loader> iconLoader1( new icon_loader{_renderer, _window_width, _window_height});
    // Creation d'un pointeur qui pointe sur l'objet icon_loader
    std::unique_ptr<icon_loader> *iconLoader_ptr = &iconLoader1;
    // Creation d'une liste qui contient les icones
    std::list<Image*> image_list_ptr;

    // Ajout des icones dans la liste, directory
    Image directory = iconLoader1->load_image("icon/directoryv2.png");
    image_list_ptr.push_back(&directory);

    // Ajout des icones dans la liste, file
    Image file = iconLoader1->load_image("icon/filev2.png");
    image_list_ptr.push_back(&file);

    //
    // Fin de la partie
    //

    // Souris + Clavier
    mouse mouse_control{};          // Init de la souris
    keyboard keyboard_control{};    // Init du clavier
    //

    // Objet: Affichage du texte
    std::unique_ptr<text> text1(new text{_window_width, _window_height, "TimesNewRomance.ttf", 50, Square_Color::White, 255, _renderer});    // Init du text
    //

    // Objet: Execution de commande systeme
    std::unique_ptr<system_exec> system_exec1(new system_exec);    // Init du system_exec
    //

    // Objet: Dessin de l'interface
    std::unique_ptr<draw> draw_on_window(new draw{_renderer, &_rect, _window_width, _window_height, Square_Color::Gray1});
    std::unique_ptr<draw> *draw = &draw_on_window;
    //

    // Objet: Affichage des fichiers
    files_display set_files_display{draw, iconLoader_ptr, _window_width, _window_height};
    //

    // Init des variables pour le calcul du nombre d'iteration par seconde, fps
    int count = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    //

    while (!_quit)
    {
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
        // Fin de la partie
        //

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0 / 120.0)));

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

            set_files_display.display(image_list_ptr);   // Affiche les fichiers

            SDL_RenderPresent(_renderer);   // Affiche le render

        }
    }

    for (auto &image : image_list_ptr)
    {
        SDL_DestroyTexture(image->texture);
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