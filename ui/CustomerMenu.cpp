#include "CustomerMenu.h"
#include "../utils/InputUtils.h"
#include "TicketUI.h"

using namespace std;

CustomerMenu::CustomerMenu() {
    // Do nothing
}

void CustomerMenu::show() {
    TicketUI ticketUI;

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
                // TODO: tích hợp với MovieBUS
                cout << ">> MovieBUS::getAll()... (Chưa tích hợp)\n";
                break;
            case 2:
                ticketUI.run();
                break;
            default:
                cout << ">> Sai lựa chọn!\n";
        }
    }
}