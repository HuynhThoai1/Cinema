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
        printHeader("HE THONG QUAN LY RAP CHIEU PHIM");

        cout << CYAN << "1. Dang nhap" << RESET << "\n";
        cout << CYAN << "2. Dang ky" << RESET << "\n";
        cout << CYAN << "0. Thoat" << RESET << "\n";
        cout << "------------------------------------------" << "\n";

        choice = InputUtils::readInt("Nhap lua chon: ");

        if (choice == 0) {
            cout << GREEN << "Tam biet!" << RESET << "\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string u, p;
                cout << "Username: "; cin >> u;
                cout << "Password: "; cin >> p;

                User* loggedInUser = userBus.login(u, p);

                if (loggedInUser != nullptr) {
                    cout << GREEN << "\n>> Dang nhap thanh cong! Xin chao: " << RESET << loggedInUser->getUsername() << "\n";

                    if (loggedInUser->getRole() == "Admin" || loggedInUser->getRole() == "admin") {
                        adminMenu.show();
                    } else {
                        custMenu.setCurrentUser(loggedInUser);
                        custMenu.show();
                    }
                } else {
                    cout << RED << ">> Dang nhap that bai (Sai thong tin hoac tai khoan bi khoa)!" << RESET << "\n";
                    cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
                }
                break;
            }
            case 2: {
                std::string u, p;
                cout << "Tao Username: "; cin >> u;
                cout << "Tao Password: "; cin >> p;
                if (userBus.registerUser(u, p)) {
                    cout << GREEN << ">> Dang ky thanh cong! Vui long dang nhap." << RESET << "\n";
                } else {
                    cout << RED << ">> Username da ton tai!" << RESET << "\n";
                }
                cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
                break;
            }
            default:
                cout << YELLOW << "Lua chon khong hop le!" << RESET << "\n";
                cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
        }
    }
}