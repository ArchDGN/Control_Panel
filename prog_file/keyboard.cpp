#include <iostream>
#include <algorithm>
#include <array>

#include <SDL2/SDL.h>

#include "../headerfile/keyboard.hpp"

/*
    Certaine touche on deux code, un simple et un " KP " a prendre en compte
*/

keyboard::keyboard()
{
    key_name[0] = SDLK_PLUS;            //  Code +
    key_name_kp[0] = SDLK_KP_PLUS;      //

    key_name[1] = SDLK_MINUS;           //  Code -
    key_name_kp[1] = SDLK_KP_MINUS;     //

    key_statue.fill(false);
}


bool keyboard::get_info(int key_code)
{
    int* key_to_find = std::find(key_name, key_name + key_array_size, key_code);                // Cherche si la touche demander apartient a key_name
    int* key_to_find_kp = std::find(key_name_kp, key_name_kp + key_array_size, key_code);       //// Cherche si la touche demander apartient a key_name_kp

    if (key_to_find != key_name + key_array_size) {                 //  Condition: cle trouve ?
        int found_index = std::distance(key_name, key_to_find);     //  found_index = position de la cle dans l'array
        return key_statue[found_index];                             //  renvoie le statue de la cle true == pressee, sinon false

    } else if (key_to_find_kp != key_name_kp + key_array_size) {
        
        int found_index = std::distance(key_name, key_to_find);     // Meme chose que precedemment mais pour la verion KP
        return key_statue[found_index];

    } else {

        return false;
    }

    return false;
}


void keyboard::is_pressed(SDL_Event event)  // Verifie si la touche a ete pressee selon son code ( voir SDL_Keycode.htm )
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS)
            key_statue[0] = true;

        if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS)
            key_statue[1] = true;
    }
}

void keyboard::is_released(SDL_Event event) // Verifie si la touche a ete relachee selon son code ( voir SDL_Keycode.htm )
{
    if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_KP_PLUS)
            key_statue[0] = false;
        if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_KP_MINUS)
            key_statue[1] = false;
    }
}