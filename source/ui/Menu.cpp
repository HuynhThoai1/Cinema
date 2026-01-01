#include "Menu.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout, std::cin;

Menu::Menu() {
    // Nothing special
}

void Menu::showMainMenu() {
    int choice;
    while (true) {
        clearScreen();
        printHeader("HỆ THỐNG QUẢN LÝ RẠP CHIẾU PHIM");

        cout << CYAN << "1. Đăng nhập" << RESET << "\n";
        cout << CYAN << "2. Đăng ký" << RESET << "\n";
        cout << CYAN << "0. Thoát" << RESET << "\n";
        cout << "------------------------------------------" << "\n";

        choice = InputUtils::readInt("Nhập lựa chọn: ");

        if (choice == 0) {
            cout << GREEN << "Tạm biệt!" << RESET << "\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string u, p;
                cout << YELLOW << "Username: " << RESET; cin >> u;
                cout << YELLOW << "Password: " << RESET; cin >> p;

                User* loggedInUser = userBus.login(u, p);

                if (loggedInUser != nullptr) {
                    cout << GREEN << "\n>> Đăng nhập thành công! Xin chào: " << RESET << loggedInUser->getUsername() << "\n";

                    if (loggedInUser->getRole() == "Admin" || loggedInUser->getRole() == "admin") {
                        adminMenu.show();
                    } else {
                        custMenu.setCurrentUser(loggedInUser);
                        custMenu.show();
                    }
                } else {
                    cout << RED << ">> Đăng nhập thất bại (Sai thông tin hoặc tài khoản bị khóa)!" << RESET << "\n";
                    cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
                }
                break;
            }
            case 2: {
                std::string u, p;
                cout << "Tạo Username: "; cin >> u;
                cout << "Tạo Password: "; cin >> p;
                if (userBus.registerUser(u, p)) {
                    cout << GREEN << ">> Đăng ký thành công! Vui lòng đăng nhập." << RESET << "\n";
                } else {
                    cout << RED << ">> Username đã tồn tại!" << RESET << "\n";
                }
                cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
                break;
            }
            default:
                cout << YELLOW << "Lựa chọn không hợp lệ!" << RESET << "\n";
                cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
        }
    }
}