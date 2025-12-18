/**
 * @file AdminMenu.h
 * @brief Giao diện menu dành cho Admin.
 */
#ifndef _ADMIN_MENU_H_
#define _ADMIN_MENU_H_
#include <iomanip>

#include "../bus/AdminBUS.h"
#include "../bus/MovieBUS.h"
#include "../bus/ShowtimeBUS.h"
#include "../bus/RevenueBUS.h"

using std::cout, std::cin;
using std::setw, std::left, std::right;

class AdminMenu {
private:
    MovieBUS movieBus; 
    ShowtimeBUS showtimeBus;
    RevenueBUS revenueBus;
    
    AdminBUS adminBus; 
    void manageUsersMenu();
public:
    AdminMenu();
    void show();
};

#endif