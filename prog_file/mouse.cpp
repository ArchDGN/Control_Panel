#include <iostream>
#include <SDL2/SDL.h>

#include "../headerfile/mouse.hpp"

/*
    Tout les bouton principaux de la souris sont pris ici

    get_click_statue renvoi true tant que le bouton est appuyé sinon false
        prend SDL_Event event et le click demande
                                        : SDL_BUTTON_LEFT
                                        : SDL_BUTTON_MIDDLE
                                        : SDL_BUTTON_RIGHT

    les fonction button_pressed renvoient true uniquement au moment du click (une seul fois)
        prend SDL_Event event

    les fonction button released renvoient true uniquement au moment ou le click est relache (une seul fois)
        prend SDL_Event event

    get_position prend deux pointer d'entier et les modifie avec la position de la souris
        SDL_Event event, int *x, int *y

    mouse_wheel renvoie 1 ou -1 selon le sens dans lequel tourne la molette sinon 0 si elle tourne pas
        prend SDL_Event event


*/

mouse::mouse(SDL_Event *event): _event{event}
{
    click_statue.fill(false);

    update_position();
}

bool mouse::get_click_statue(int code)
{
    //std::cout << click_statue[0] << std::endl;
    switch (code)
    {
    case SDL_BUTTON_LEFT:
        left_button_pressed();
        left_button_released();
        return click_statue[0];

    case SDL_BUTTON_MIDDLE:
        middle_button_pressed();
        middle_button_released();
        return click_statue[1];

    case SDL_BUTTON_RIGHT:
        right_button_pressed();
        right_button_released();
        return click_statue[2];
    
    default:
        break;
    }

    return false;
}

void mouse::update_position()
{
    SDL_GetMouseState(&_mouse_x, &_mouse_y);
}

void mouse::return_position(int *x, int *y)
{
    update_position();

    *x = _mouse_x;
    *y = _mouse_y;
}

bool mouse::left_button_pressed()
{
    bool is_pressed = false;
    if (SDL_MOUSEBUTTONDOWN == (*_event).type)
            {
                if (SDL_BUTTON_LEFT == (*_event).button.button)
                {
                    is_pressed = true;
                    click_statue[0] = true;
                }
            }

    return is_pressed;
}

bool mouse::middle_button_pressed()
{
    bool is_pressed = false;
    if (SDL_MOUSEBUTTONDOWN == (*_event).type)
            {
                if (SDL_BUTTON_MIDDLE == (*_event).button.button)
                {
                    is_pressed = true;
                    click_statue[1] = true;
                }
            }

    return is_pressed;
}

bool mouse::right_button_pressed()
{
    bool is_pressed = false;
    if (SDL_MOUSEBUTTONDOWN == (*_event).type)
            {
                if (SDL_BUTTON_RIGHT == (*_event).button.button)
                {
                    is_pressed = true;
                    click_statue[2] = true;
                }
            }

    return is_pressed;
}

bool mouse::left_button_released()
{
    bool is_released = false;
    if (SDL_MOUSEBUTTONUP == (*_event).type)
            {
                if (SDL_BUTTON_LEFT == (*_event).button.button)
                {
                    is_released = true;
                    click_statue[0] = false;
                }
            }

    return is_released;
}

bool mouse::middle_button_released()
{
    bool is_released = false;
    if (SDL_MOUSEBUTTONUP == (*_event).type)
            {
                if (SDL_BUTTON_MIDDLE == (*_event).button.button)
                {
                    is_released = true;
                    click_statue[1] = false;
                }
            }

    return is_released;
}

bool mouse::right_button_released()
{
    bool is_released = false;
    if (SDL_MOUSEBUTTONUP == (*_event).type)
            {
                if (SDL_BUTTON_RIGHT == (*_event).button.button)
                {
                    is_released = true;
                    click_statue[2] = false;
                }
            }

    return is_released;
}

int mouse::mouse_wheel()
{
    if (SDL_MOUSEWHEEL == (*_event).type)
        return (*_event).wheel.y;

    return 0;
}
