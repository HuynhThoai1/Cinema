#include "Menu.h"
#include "../utils/InputUtils.h"
#include <iostream>

using std::cout, std::cin;

Menu::Menu() {
    // Do nothing
}

void Menu::showMainMenu() {
    int choice;
    while (true) {
        cout << "\n================================\n";
        cout << "  HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM  \n";
        cout << "================================\n";
        cout << "1. Đăng nhập\n";
        cout << "2. Đăng ký\n";
        cout << "0. Thoát\n";
        choice = InputUtils::readInt("Nhập lựa chọn: ");

        if (choice == 0) {
            cout << "Tạm biệt!\n";
            break;
        }

        switch (choice)
        {
        case 1: {
            string u, p;
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;

            User* loggedInUser = userBus.login(u, p);

            if (loggedInUser != nullptr) {
                // Lấy thông tin user vừa đăng nhập
                User* currentUser = loggedInUser;

                if (currentUser->getRole() == "Admin" || currentUser->getRole() == "admin") {
                    adminMenu.show();
                }
                else {
                    custMenu.show();
                }
            }
            else {
                cout << ">> Đăng nhập thất bại (Sai thông tin hoặc tài khoản bị khóa)!\n";
            }
            break;
        }
        case 2: {
            string u, p;
            cout << "Tạo Username: "; cin >> u;
            cout << "Tạo Password: "; cin >> p;
            if (userBus.registerUser(u, p)) {
                cout << ">> Đăng ký thành công! Vui lòng đăng nhập.\n";
            }
            else {
                cout << ">> Username đã tồn tại!\n";
            }
            break;
        }
        default:
            cout << "Lựa chọn không hợp lệ!\n";
        }   
    }
}