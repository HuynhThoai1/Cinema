#include <iostream>
#include "Menu.h"

#ifdef _WIN32
    #include <windows.h> // Nếu là Windows thì dùng cái này
#endif

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); // Chỉ chạy dòng này nếu là Windows
    #endif

    Menu menu;

    menu.showMainMenu();

    return 0;
}