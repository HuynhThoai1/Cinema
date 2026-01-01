#include "FormatUI.h"
#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const std::string &title) {
    std::cout << "\n" << BLUE << "========================================" << RESET << "\n";
    std::cout << "   " << YELLOW << title << RESET << "\n";
    std::cout << BLUE << "========================================" << RESET << "\n";
}
