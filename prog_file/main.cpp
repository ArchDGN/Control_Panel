#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../headerfile/window.hpp"

int main()
{
    int window_width = 1800;
    int window_height = 980;
    SDL_Surface* ico;

    ico = SDL_LoadBMP("github2.bmp");
    const std::string prog_name = "Control Panel";
    window prog{&window_width, &window_height, &prog_name, ico};

    prog.run_program();
    return 0;
}


void get_error (std::string error, std::string error_log, int code)
{
    std::cerr << error << error_log << std::endl;   // Affiche l'erreur ainsi que le log SDL associe

    if (code != -1)     // Si l'erreur survient a l'initialisation de la sdl alors le code renvoyé est -1
        SDL_Quit();     // Il n'y a donc pas besoin de quitter la sdl car elle na pas put s'initialiser
                        // Si la sdl a put s'initialiser et qu'une erreur survient apres le code renvoye est 0
    exit(-1);
}