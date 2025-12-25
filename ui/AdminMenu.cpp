#include "AdminMenu.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h" // Đảm bảo include file này để dùng màu và hàm format
#include "RevenueUI.h"
#include "MovieUI.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout, std::cin, std::left, std::setw, std::vector, std::string;

AdminMenu::AdminMenu() {
    // Do nothing
}

void AdminMenu::manageUsersMenu() {
    int subChoice;
    while (true) {
        clearScreen();
        printHeader("QUAN LY NGUOI DUNG");

        cout << CYAN << "1. Xem danh sach User" << RESET << "\n";
        cout << CYAN << "2. Khoa tai khoan" << RESET << "\n";
        cout << CYAN << "3. Mo khoa tai khoan" << RESET << "\n";
        cout << CYAN << "0. Quay lai Menu chinh" << RESET << "\n";
        cout << "------------------------------------------\n";
        
        subChoice = InputUtils::readInt("Nhap lua chon: ");

        if (subChoice == 0) break; 

        switch (subChoice) {
            case 1: {
                clearScreen();
                printHeader("DANH SACH KHACH HANG");
                vector<User*> users = adminBus.getAllUsers();
                
                // Header bảng
                cout << "---------------------------------------------------------\n";
                cout << "| " << left << setw(5)  << "ID" 
                     << "| " << left << setw(25) << "Username"
                     << "| " << left << setw(15) << "Role"
                     << " |\n";
                cout << "---------------------------------------------------------\n";
                
                // Dữ liệu bảng
                for (auto u : users) {
                    if (u->getRole() == "Admin" || u->getRole() == "admin") continue;
                    
                    cout << "| " << left << setw(5)  << u->getId()
                         << "| " << left << setw(25) << u->getUsername()
                         << "| " << left << setw(15) << u->getRole()
                         << " |\n";
                }
                cout << "---------------------------------------------------------\n";
                
                cout << "(An Enter de quay lai...)"; 
                cin.ignore(); cin.get();
                break; 
            }
            case 2: {
                string id;
                cout << "Nhap ID can khoa: "; cin >> id;
                if (adminBus.lockUser(id)) {
                    cout << GREEN << ">> Khoa tai khoan thanh cong!" << RESET << "\n";
                } else {
                    cout << RED << ">> Loi: ID khong ton tai hoac la Admin." << RESET << "\n";
                }
                
                cout << "(An Enter de tiep tuc...)"; 
                cin.ignore(); cin.get();
                break;
            }
            case 3: {
                string id;
                cout << "Nhap ID can mo khoa: "; cin >> id;
                if (adminBus.unlockUser(id)) {
                    cout << GREEN << ">> Mo khoa thanh cong!" << RESET << "\n";
                } else {
                    cout << RED << ">> Loi: ID khong hop le." << RESET << "\n";
                }
                
                cout << "(An Enter de tiep tuc...)"; 
                cin.ignore(); cin.get();
                break;
            }
            default:
                cout << YELLOW << ">> Lua chon khong hop le!" << RESET << "\n";
                cout << "(An Enter de thu lai...)"; 
                cin.ignore(); cin.get();
        }
    }
}

void AdminMenu::show() {
    RevenueUI revenueUI;
    MovieUI movieUI;
    int choice;
    
    while (true) {
        clearScreen();
        printHeader("ADMIN DASHBOARD");

        cout << CYAN << "1. Quan ly Nguoi dung (Xem/Khoa/Mo)" << RESET << "\n";
        cout << CYAN << "2. Quan ly Phim (Movie Module)" << RESET << "\n";
        cout << CYAN << "3. Quan ly Doanh thu (Revenue Module)" << RESET << "\n";
        cout << CYAN << "4. Quan ly Do an (Food Module)" << RESET << "\n";
        cout << CYAN << "0. Dang xuat" << RESET << "\n";
        cout << "------------------------------------------\n";

        choice = InputUtils::readInt("Nhap lua chon: ");

        if (choice == 0) {
            cout << GREEN << ">> Dang dang xuat..." << RESET << "\n";
            // Có thể thêm sleep hoặc pause nhẹ ở đây nếu cần
            break;
        }
        
        switch (choice) {
        case 1: 
            this->manageUsersMenu(); 
            break;
        case 2: 
            movieUI.run();
            break;
        case 3:
            revenueUI.process();
            break;
        case 4:
            // Placeholder cho module Food
            cout << YELLOW << ">> Chuc nang thuoc Module Food (Chua tich hop)." << RESET << "\n";
            cout << "(An Enter de quay lai...)"; 
            cin.ignore(); cin.get();
            break;
        default:
            cout << YELLOW << ">> Lua chon khong hop le!" << RESET << "\n";
            cout << "(An Enter de thu lai...)"; 
            cin.ignore(); cin.get();
        }
    }
}