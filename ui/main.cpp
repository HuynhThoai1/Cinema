#include <iostream>
#include <windows.h>//thu vien windows
#include "Menu.h"


int main() {
    SetConsoleOutputCP(65001);//thêm dong nay de in duoc tieng viet co dau
    Menu menu;

    menu.showMainMenu();

    return 0;
}