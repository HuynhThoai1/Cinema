/**
 * @file Menu.h
 * @brief Màn hình chính (Landing Page): Đăng nhập, Đăng ký.
 */
#ifndef MENU_H
#define MENU_H

#include "../bus/UserBUS.h"
#include "AdminMenu.h"
#include "CustomerMenu.h"

/**
 * @class Menu
 * @brief Lớp điều hướng cấp cao nhất (Entry Point).
 * @details Xử lý luồng Đăng nhập, Đăng ký và chuyển hướng người dùng 
 *          vào AdminMenu hoặc CustomerMenu dựa trên Role.
 */
class Menu {
private:
    UserBUS userBus;       ///< Xử lý logic đăng nhập, đăng ký, session
    AdminMenu adminMenu;   ///< Giao diện con dành cho Admin
    CustomerMenu custMenu; ///< Giao diện con dành cho Customer

public:
    Menu();
    
    /**
     * @brief Hiển thị menu chính (Login/Register).
     * @details Đây là hàm được gọi đầu tiên trong main(). 
     *          Chứa vòng lặp vô hạn cho đến khi người dùng chọn Thoát.
     */
    void showMainMenu();
};

#endif