/**
 * @file Menu.h
 * @brief Màn hình chính (Landing Page): Đăng nhập, Đăng ký.
 */
#ifndef MENU_H
#define MENU_H

#include "../bus/UserBUS.h"
#include "AdminMenu.h"
#include "CustomerMenu.h"

class Menu {
private:
    UserBUS userBus;       // Xử lý đăng nhập/đăng ký
    AdminMenu adminMenu;   // Menu con cho Admin
    CustomerMenu custMenu; // Menu con cho Customer

public:
    Menu();
    /**
     * @brief Hiển thị menu chính và điều hướng người dùng.
     */
    void showMainMenu();
};

#endif