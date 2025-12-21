#include "ShowtimeUI.h"

#include <iostream>
#include "../bus/ShowtimeBUS.h"

void ShowtimeUI::menu() {
    std::cout << "===== SHOWTIME MENU =====\n";
    std::cout << "1. View all showtimes\n";
    std::cout << "2. Add showtime\n";
    std::cout << "3. Update showtime\n";
    std::cout << "4. Delete showtime\n";
    std::cout << "0. Back\n";
    // TODO: hook into ShowtimeBUS like other UI modules
}
