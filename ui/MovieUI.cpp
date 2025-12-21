#include "MovieUI.h"

#include <iostream>
#include "../bus/MovieBUS.h"

void MovieUI::menu() {
    std::cout << "===== MOVIE MENU =====\n";
    std::cout << "1. View all movies\n";
    std::cout << "2. Add movie\n";
    std::cout << "3. Update movie\n";
    std::cout << "4. Delete movie\n";
    std::cout << "0. Back\n";
    // TODO: hook into MovieBUS like other UI modules
}
