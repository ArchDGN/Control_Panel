#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "../headerfile/window.hpp"

int main()
{
    const int window_width = 1800;       //3600 <- taille image x
    const int window_height = 950;      //1894 <- taille image y

    const std::string prog_name = "Control Panel";
    window prog{&window_width, &window_height, &prog_name};

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