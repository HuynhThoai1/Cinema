#include "AdminMenu.h"
#include "../utils/InputUtils.h"
#include "RevenueUI.h"

AdminMenu::AdminMenu() {
    // Do nothing
}

void AdminMenu::manageUsersMenu() {
    int subChoice;
    while (true) {
        cout << "\n   ------------------------\n";
        cout << "   | QUẢN LÝ NGƯỜI DÙNG   |\n";
        cout << "   ------------------------\n";
        cout << "   1. Xem danh sách User\n";
        cout << "   2. Khóa tài khoản\n";
        cout << "   3. Mở khóa tài khoản\n";
        cout << "   0. Quay lại Menu chính\n";
        subChoice = InputUtils::readInt("Nhập lựa chọn: ");

        if (subChoice == 0) break; 

        switch (subChoice) {
            case 1: {
                vector<User*> users = adminBus.getAllUsers();
                cout << "\n   [DANH SÁCH KHÁCH HÀNG]\n";
                cout << "   -----------------------------------------------------\n";
                cout << "   | "
                     << left << setw(3)  << "ID" 
                     << " | "
                     << left << setw(25) << "Username"
                     << " | "
                     << left << setw(15) << "Role"
                     << " |\n";
                cout << "   -----------------------------------------------------\n";
                for (auto u : users) {
                    if (u->getRole() == "Admin" || u->getRole() == "admin") continue;
                    
                    cout << "   | "
                         << left << setw(3)  << u->getId()
                         << " | "
                         << left << setw(25) << u->getUsername()
                         << " | "
                         << left << setw(15) << u->getRole()
                         << " |\n";
                }
                cout << "   -----------------------------------------------------\n";
                break; 
            }
            case 2: {
                string id;
                cout << "   Nhập ID cần khóa: "; cin >> id;
                if (adminBus.lockUser(id)) cout << "   >> Khóa thành công!\n";
                else cout << "   >> Lỗi: ID không tồn tại hoặc là Admin.\n";
                break;
            }
            case 3: {
                string id;
                cout << "   Nhập ID cần mở: "; cin >> id;
                if (adminBus.unlockUser(id)) cout << "   >> Mở khóa thành công!\n";
                else cout << "   >> Lỗi: ID không hợp lệ.\n";
                break;
            }
            default:
                cout << "   >> Sai lựa chọn!\n";
        }
    }
}

void AdminMenu::show() {
    RevenueUI revenueUI;
    int choice;
    while (true) {
        cout << "\n--- ADMIN DASHBOARD ---\n";
        cout << "1. Quản lý Người dùng (Xem/Khóa/Mở)\n";
        cout << "2. Quản lý phim (Movie Module)\n";
        cout << "3. Quản lý Doanh thu (Revenue Module)\n";
        cout <<"0. Đăng xuất\n";
        choice = InputUtils::readInt("Nhập lựa chọn: ");

        if (choice == 0) break;
        
        switch (choice) {
        case 1: 
            this->manageUsersMenu(); 
            break;
        case 2: 
            // TODO: tích hợp với MovieBUS
            cout << ">> Chức năng thuộc Module Movie (Chưa tích hợp).\n";
            //movieBus.addMovie()
            break;
        case 3:
            revenueUI.process();
            break;
        default:
            cout << ">> Sai lựa chọn!";
        }
    }
}