#include <string>
#include <SDL2/SDL.h>

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
