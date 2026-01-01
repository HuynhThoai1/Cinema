#include "AdminMenu.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h" // Đảm bảo include file này để dùng màu và hàm format
#include "RevenueUI.h"
#include "MovieUI.h"
#include "ShowtimeUI.h"
#include "FoodUI.h"
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
        printHeader("QUẢN LÝ NGƯỜI DÙNG");

        cout << CYAN << "1. Xem danh sách User" << RESET << "\n";
        cout << CYAN << "2. Khóa tài khoản" << RESET << "\n";
        cout << CYAN << "3. Mở khóa tài khoản" << RESET << "\n";
        cout << CYAN << "0. Quay lại Menu chính" << RESET << "\n";
        cout << "------------------------------------------\n";
        
        subChoice = InputUtils::readInt("Nhập lựa chọn: ");

        if (subChoice == 0) break; 

        switch (subChoice) {
            case 1: {
                clearScreen();
                printHeader("DANH SÁCH KHÁCH HÀNG");
                vector<User*> users = adminBus.getAllUsers();
                
                cout << "\n";
                if (users.empty()) {
                    cout << YELLOW << ">> Chưa có người dùng nào." << RESET << "\n";
                    cout << "(Ấn Enter để quay lại...)"; 
                    cin.ignore(); cin.get();
                    break;
                }
                
                // Header bảng
                cout << GREEN << "---------------------------------------------------------\n";
                cout << "| " << YELLOW << left << setw(5)  << "ID" 
                     << GREEN << "| " << YELLOW << left << setw(25) << "Username"
                     << GREEN << "| " << YELLOW << left << setw(15) << "Role"
                     << GREEN << " |\n";
                cout << "---------------------------------------------------------" << RESET << "\n";
                
                // Dữ liệu bảng
                for (auto u : users) {
                    if (u->getRole() == "Admin" || u->getRole() == "admin") continue;
                    
                    cout << GREEN << "| " << CYAN << left << setw(5)  << u->getId()
                         << GREEN << "| " << RESET << left << setw(25) << u->getUsername()
                         << GREEN << "| " << RESET << left << setw(15) << u->getRole()
                         << GREEN << " |" << RESET << "\n";
                }
                cout << GREEN << "---------------------------------------------------------" << RESET << "\n";
                
                cout << "(Ấn Enter để quay lại...)"; 
                cin.get();
                break; 
            }
            case 2: {
                string id;
                cout << "Nhập ID cần khóa: "; cin >> id;
                if (adminBus.lockUser(id)) {
                    cout << GREEN << ">> Khóa tài khoản thành công!" << RESET << "\n";
                } else {
                    cout << RED << ">> Lỗi: ID không tồn tại hoặc là Admin." << RESET << "\n";
                }
                
                cout << "(Ấn Enter để tiếp tục...)"; 
                cin.ignore(); cin.get();
                break;
            }
            case 3: {
                string id;
                cout << "Nhập ID cần mở khóa: "; cin >> id;
                if (adminBus.unlockUser(id)) {
                    cout << GREEN << ">> Mở khóa thành công!" << RESET << "\n";
                } else {
                    cout << RED << ">> Lỗi: ID không hợp lệ." << RESET << "\n";
                }
                
                cout << "(Ấn Enter để tiếp tục...)"; 
                cin.ignore(); cin.get();
                break;
            }
            default:
                cout << YELLOW << ">> Lựa chọn không hợp lệ!" << RESET << "\n";
                cout << "(Ấn Enter để thử lại...)"; 
                cin.ignore(); cin.get();
        }
    }
}

void AdminMenu::show() {
    RevenueUI revenueUI;
    MovieUI movieUI;
    ShowtimeUI showtimeUI;
    FoodUI foodUI;
    int choice;
    
    while (true) {
        clearScreen();
        printHeader("ADMIN DASHBOARD");

        cout << CYAN << "1. Quản lý Người dùng (Xem/Khóa/Mở)" << RESET << "\n";
        cout << CYAN << "2. Quản lý Phim (Movie Module)" << RESET << "\n";
        cout << CYAN << "3. Quản suất chiếu (Movie Module)" << RESET << "\n";
        cout << CYAN << "4. Quản lý Doanh thu (Revenue Module)" << RESET << "\n";
        cout << CYAN << "5. Quản lý Đồ ăn (Food Module)" << RESET << "\n";
        cout << CYAN << "0. Đăng xuất" << RESET << "\n";
        cout << "------------------------------------------\n";

        choice = InputUtils::readInt("Nhập lựa chọn: ");

        if (choice == 0) {
            cout << GREEN << ">> Đang đăng xuất..." << RESET << "\n";
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
            showtimeUI.runAdmin();
            break;
        case 4:
            revenueUI.process();
            break;
        case 5:
            foodUI.adminMenu();
            break;
        default:
            cout << YELLOW << ">> Lựa chọn không hợp lệ!" << RESET << "\n";
            cout << "(Ấn Enter để thử lại...)"; 
            cin.ignore(); cin.get();
        }
    }
}