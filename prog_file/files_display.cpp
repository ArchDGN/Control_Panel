#include <iostream>
#include <memory>

#include "../headerfile/files_display.hpp"

files_display::files_display(std::unique_ptr<draw> *draw, std::unique_ptr<icon_loader> *icl, int *w, int *h): _draw{draw}, _icon_loader(icl), _window_width{w}, _window_height{h}
{
    // Corespond au radius de la fenetre a un instant t, au lancement du programme mis a 0
    ref_width = 0;
    ref_height = 0;
}

void files_display::display(std::list<Image*> image_list_ptr)
{
    // Si la taille de la fenetre a change, on recalcule les coordonnees des icones
    // Car refwidth et refheight ne sont plus égaux a la taille de la fenetre
    if (ref_width != *_window_width || ref_height != *_window_height)
    {
        // red_width et ref_height sont mis a jour
        ref_width = *_window_width;
        ref_height = *_window_height;

        // Taille de la fenetre raccourci en w et h pour faciliter l'ecriture du code
        int *w = _window_width;
        int *h = _window_height;

        // Coordonnees des icones du début de la grille d'icones
        directory_arrow_x = *w/8 - 1;
        directory_arrow_y = *h/10 - 1;

        // Lageur et hauteur des grilles d'icones
        directory_arrow_width = *w - (*w/8) - (*w/9) + 2;
        directory_arrow_height = *h - (*h/10) - (*h/16) + 2;

        // Nombre d'icones a afficher sur la largeur
        number_of_files_w = directory_arrow_width / 100;
        // Centrage de la grille d'icones sur la largeur
        file_centered_w = (directory_arrow_width - (100 * number_of_files_w)) / 2;

        // Nombre d'icones a afficher sur la hauteur
        number_of_files_y = directory_arrow_height / 130;
        // Centrage de la grille d'icones sur la hauteur
        file_centered_h = (directory_arrow_height - (130 * number_of_files_y)) / 2;
    }

    // On sélectionne l'image directory
    image = image_list_ptr.begin();
    std::advance(image, 0);

    // On affiche les grille d'icones
    for (int file_y = 0; file_y < number_of_files_y; file_y++)
    {
        for (int file_x = 0; file_x < number_of_files_w; file_x++)
        {
            (*_icon_loader)->set_dest_rect_ptr((*image)->_dest_rect_ptr, directory_arrow_x + file_centered_w + (100*file_x), directory_arrow_y + file_centered_h + (130*file_y), 80, 80);
            (*_icon_loader)->show_image(**image);
        }
    }


    (*_draw)->set_font_color();
}