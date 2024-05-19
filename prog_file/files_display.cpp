#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#include "../headerfile/files_display.hpp"
#include "../headerfile/system_exec.hpp"

files_display::files_display(std::unique_ptr<draw> *draw, std::unique_ptr<icon_loader> *icl, std::unique_ptr<system_exec> *system_exec_ptr, std::unique_ptr<text> *text_ptr, int *w, int *h): _draw{draw}, _icon_loader(icl), _system_exec(system_exec_ptr), _text_display(text_ptr), _window_width{w}, _window_height{h}
{
    // Corespond au radius de la fenetre a un instant t, au lancement du programme mis a 0
    ref_width = 0;
    ref_height = 0;
}

void files_display::display()
{
    std::vector<int> file = (*_system_exec)->return_file_and_directory_count();
    //std::cout << "Nombre de fichiers : " << file.front() << std::endl;

    // Si la taille de la fenetre a change, on recalcule les coordonnees des icones
    // Car refwidth et refheight ne sont plus égaux a la taille de la fenetre
    if (ref_width != *_window_width || ref_height != *_window_height)
    {
        refresh_display_info();
    }

    // On sélectionne l'image directory
    std::string id = "directory";

    int file_x = 0;
    int file_y = 0;

    std::string final;
    size_t pos1 = 0;
    size_t pos = file_name.find('\n',pos1);
    for (int nb_files = 0; nb_files < (file[0] + file[1]); nb_files++)
    {
        final =  file_name.substr(pos1, pos - pos1);
        final.resize(30, ' ');

        button_display(file_x, file_y);
        icon_display(file_x, file_y, id);
        text_display(file_x, file_y, final);


        file_x++;
        pos1 = pos+1;
        pos = file_name.find('\n',pos1);
        if (file_x == max_number_of_files_w)
        {
            file_x = 0;
            file_y++;
        }

        if (nb_files == file[0] - 1)
        {
            id = "file";
        }

        if (file_y == max_number_of_files_h)
        {
            break;
        }
    }

    (*_draw)->set_font_color();
}

void files_display::button_display(int file_x, int file_y)
{
    (*_draw)->draw_rectangle(file_coord_x + (100 * file_x), file_coord_y + (130 * file_y), 80, 80, 2000, Square_Color::Blue, 255);
    (*_draw)->draw_rectangle(file_coord_x + (100 * file_x) - 5, file_coord_y + (130 * file_y) + 85, 90, 40, 2000, Square_Color::Red, 255);
}

void files_display::icon_display(int file_x, int file_y, const std::string& id)
{
    (*_icon_loader)->set_dest_rect_by_id(id, file_coord_x + (100 * file_x), file_coord_y + (130 * file_y), 80, 80);
    (*_icon_loader)->show_image_by_id(id);
}

void files_display::text_display(int file_x, int file_y, const std::string& text)
{
    (*_text_display)->draw_text(text.substr(0, 15), file_coord_x + (100 * file_x) - 5, file_coord_y + (130 * file_y) + 80, 90, 20, Text_Property::Cut, Text_Property::NONE);
    (*_text_display)->draw_text(text.substr(15, 15), file_coord_x + (100 * file_x) - 5, file_coord_y + (130 * file_y) + 100, 90, 20, Text_Property::Cut, Text_Property::NONE);
}

void files_display::refresh_display_info()
{
    // red_width et ref_height sont mis a jour
    ref_width = *_window_width;
    ref_height = *_window_height;

    int directory_arrow_width;
    int directory_arrow_height;
    int directory_arrow_x;
    int directory_arrow_y;
    int file_centered_w;
    int file_centered_h;

    // Taille de la fenetre raccourci en w et h pour faciliter l'ecriture du code
    int *w = _window_width;
    int *h = _window_height;

    // Coordonnees des icones du début de la grille d'icones
    directory_arrow_x = *w/5 - 1;
    directory_arrow_y = *h/10 - 1;

    // Lageur et hauteur des grilles d'icones
    directory_arrow_width = *w - (*w/5) - (*w/9) + 2;
    directory_arrow_height = *h - (*h/10) - (*h/16) + 2;

    // Nombre d'icones a afficher sur la largeur
    max_number_of_files_w = directory_arrow_width / 100;
    // Nombre d'icones a afficher sur la hauteur
    max_number_of_files_h = directory_arrow_height / 130;

    // Centrage de la grille d'icones sur la largeur
    file_centered_w = (directory_arrow_width - (100 * max_number_of_files_w)) / 2;
    // Centrage de la grille d'icones sur la hauteur
    file_centered_h = (directory_arrow_height - (130 * max_number_of_files_h)) / 2;

    // Coordonnees de la premiere icone
    file_coord_x = directory_arrow_x + file_centered_w;
    file_coord_y = directory_arrow_y + file_centered_h;

    file_name = (*_system_exec)->return_ofl(Command_Option::Rewrite);
}