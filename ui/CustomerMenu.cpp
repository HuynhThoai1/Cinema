#include "CustomerMenu.h"
#include "../utils/InputUtils.h"

using namespace std;

CustomerMenu::CustomerMenu() {
    // Do nothing
}

void CustomerMenu::show() {
    int choice;
    while (true) {
        cout << "\n--- KHÁCH HÀNG ---\n";
        cout << "1. Xem danh sách phim\n";
        cout << "2. Đặt vé\n";
        cout << "0. Đăng xuất\n";
        choice = InputUtils::readInt("Nhập lựa chọn: ");


        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << ">> MovieBUS::getAll()... (Chưa tích hợp)\n";
                break;
            case 2:
                cout << ">> BookingFacade::bookTicket()... (chưa tích hợp)\n";
                break;
            default:
                cout << ">> Sai lựa chọn!\n";
        }
    }
}