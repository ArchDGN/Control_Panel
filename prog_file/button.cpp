#include "../headerfile/button.hpp"

#include <algorithm>
#include <utility>

#include <iostream>

button::button(std::unique_ptr<mouse> *mouse, int *window_width, int *window_height)
{
    _window_width = window_width;
    _window_height = window_height;

    _mouse_control = mouse;
}

void button::create_button_by_id(std::string id, int x, int y, int w, int h, void (*pointer_to_function)())
{
    Button button;
    button.id = std::move(id);
    button.x = x;
    button.y = y;
    button.w = w;
    button.h = h;
    button.pointer_to_function = pointer_to_function;
    _button_list.push_back(button);
}

void button::edit_button_by_id(const std::string& id, int x, int y, int w, int h, void (*pointer_to_function)())
{
    for (auto &i : _button_list)
    {
        if (i.id == id)
        {
            i.x = x;
            i.y = y;
            i.w = w;
            i.h = h;
            i.pointer_to_function = pointer_to_function;
        }
    }

}

void button::delete_button_by_id(const std::string& id)
{
    _button_list.erase(std::remove_if(_button_list.begin(), _button_list.end(), [id](Button &i){return i.id == id;}), _button_list.end());
}

button::Button* button::return_button_by_id(const std::string& id)
{
    for (auto &i : _button_list)
    {
        if (i.id == id)
        {
            return &i;
        }
    }
    return nullptr;
}

bool button::is_button_clicked(Button *button)
{
    int x, y;
    (*_mouse_control)->return_position(&x, &y);

    if (x > button->x && x < button->x + button->w && y > button->y && y < button->y + button->h)
    {
        button->pointer_to_function();
        return true;
    }

    return false;
}

bool button::check_all_buttons_clicked()
{
    bool clicked = false;
    if (!(*_mouse_control)->get_click_statue(SDL_BUTTON_LEFT))
    {
        return clicked;
    }
    for (auto &i : _button_list)
    {
        if (is_button_clicked(&i))
        {
            clicked = true;
        }
    }

    return clicked;
}

bool button::specific_button_clicked(const std::string &id) {
    Button *button = return_button_by_id(id);
    if (button != nullptr)
    {
        return is_button_clicked(button);
    }

    return false;
}
