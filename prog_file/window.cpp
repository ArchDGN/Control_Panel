#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headerfile/window.hpp"
#include "../headerfile/imageloader.hpp"
#include "../headerfile/mouse.hpp"
#include "../headerfile/keyboard.hpp"
#include "../headerfile/draw.hpp"

void window::run_program()
{

    mouse mouse_control{};          // Init de la souris
    keyboard keyboard_control{};    // Init du clavier

    imageloader texture_background{_prog_window, _renderer, "carte.jpg", _window_width, _window_height};     // On charge l'image dans l'objet "texture_background"
    draw draw_on_window{_renderer, _window_width, _window_height};

    while (!_quit)
    {
        while (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                _quit = true;
            }

            SDL_RenderClear(_renderer);     // Efface l'affichade

            keyboard_control.is_pressed(_event);    // Verifie si une touche est presse
            keyboard_control.is_released(_event);   // Verifie si une touche est relache
            get_keyboard_for_texture(keyboard_control, texture_background, draw_on_window); // Les condition relative au zoom dans la texture sont dans la fonction "window::get_keyboard_for_texture"


            mouse_control.get_position(_event, &mouse_pos_x, &mouse_pos_y);         // Attibut au variable mouse_pos_x et mouse_pos_y la position de la souris
            get_mouse_for_texture(mouse_control, texture_background, draw_on_window);    // Les conditon relatives a la souris sont dans la fonction "window::get_mouse_for_texture"


            SDL_RenderCopy(_renderer, texture_background.get_image(), texture_background.get_ptr_src_rect(), texture_background.get_ptr_dest_rect());      // Ajoute le render donc l'image

            draw_on_window.draw_grid();


            SDL_RenderPresent(_renderer);   // Affiche le render

        }
    }
}

window::window(const int *window_width, const int *window_height, const std::string *prog_name) : _window_width(window_width), _window_height(window_height), _prog_name(prog_name)
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0)      // SDL init
        get_error("Erreur lors de l'initialisation de SDL : ", SDL_GetError(), -1);

                                // Passe le format du nom de la fenetre de std::string a const char *
    _prog_window = SDL_CreateWindow(_prog_name->c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, *_window_width, *_window_height, SDL_WINDOW_SHOWN);     // Creation de la fenetre
    if (!_prog_window)
        get_error("Erreur lors de la création de la fenêtre : ", SDL_GetError(), 0);

    _renderer = SDL_CreateRenderer(_prog_window, -1, SDL_RENDERER_ACCELERATED);     // Creation du render
    if (!_renderer) {
        SDL_DestroyWindow(_prog_window);
        get_error("Erreur lors de la création du renderer : ", SDL_GetError(), 0);
    }

    _quit = false;  // Init de la variable qui permet de quitter le programme, une fois a "true" la boucle while principale se coupe et le programme s'arrete

}

window::~window()
{
    SDL_RenderClear(_renderer);         //  Clear de tout les asset
    SDL_DestroyRenderer(_renderer);     //
    SDL_DestroyWindow(_prog_window);    //      Le programme finit correctement, sans erreur
    SDL_Quit();                         //
}

void window::get_mouse_for_texture(mouse &mouse_control, imageloader &texture_background, draw &draw_grid)
{
    if (mouse_control.middle_button_pressed(_event) == true)            // Si l'utilisateur fait click molette, essai d'initialiser la position du zoom
    {
        texture_background.set_zoom_point(mouse_pos_x, mouse_pos_y);    // Il y a une condition dans la fonction si l'utilisateur zoom deja alors le zoom est rest a 5 sinon le point de zoom est place
        draw_grid.grid_set_zoom_point(mouse_pos_x, mouse_pos_y);
    }

    if (mouse_control.mouse_wheel(_event) == 1)     // zoom avant
    {
        texture_background.zoom_in();
        draw_grid.grid_zoom_in();
    }

    if (mouse_control.mouse_wheel(_event) == -1)    // zoom arriere
    {
        texture_background.zoom_out();
        draw_grid.grid_zoom_out();
    }
}

void window::get_keyboard_for_texture(keyboard &keyboard_control, imageloader &texture_background, draw &draw_grid)
{
    if (keyboard_control.get_info(SDLK_PLUS) == true || keyboard_control.get_info(SDLK_KP_PLUS) == true)        // touche clavier " + "
    {
        texture_background.zoom_in();                                                                           // zoom avant
        draw_grid.grid_zoom_in();
    }

    if (keyboard_control.get_info(SDLK_MINUS) == true || keyboard_control.get_info(SDLK_KP_MINUS) == true)      // touche clavier " - "
    {
        texture_background.zoom_out();                                                                          // zoom arriere
        draw_grid.grid_zoom_out();
    }
}