#include "CustomerMenu.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h"
#include "TicketUI.h"
#include "FoodUI.h"
#include "ShowtimeUI.h"
#include <iostream>

using namespace std;

CustomerMenu::CustomerMenu() {
    // Do nothing
}
void CustomerMenu::setCurrentUser(User* user) {
    this->currentUser = user;
}
void CustomerMenu::show() {
    TicketUI ticketUI;
    MovieUI movieUI;
    FoodUI foodUI;
    ShowtimeUI showtimeUI;
    int choice;
    while (true) {
        clearScreen();
        printHeader("KHÁCH HÀNG");

        cout << CYAN << "1. Xem danh sách phim" << RESET << "\n";
        cout << CYAN << "2. Xem lịch chiếu phim" << RESET << "\n";
        cout << CYAN << "3. Đặt vé" << RESET << "\n";
        cout << CYAN << "4. Mua đồ ăn và đồ uống" << RESET << "\n";
        cout << CYAN << "0. Đăng xuất" << RESET << "\n";

        choice = InputUtils::readInt("Nhập lựa chọn: ");
        if (choice == 0) break;

        switch (choice) {
            case 1:
                movieUI.showAll();
                break;
            case 2:
                showtimeUI.runCustomer();
                break;
            case 3:
                if (currentUser != nullptr) {
                    ticketUI.setCurrentUser(currentUser->getId());
                } else {
                    cout << RED << "Lỗi: Không xác định được người dùng!" << RESET << "\n";
                    break;
                }
                ticketUI.run();
                break;
            case 4:
                foodUI.customerMenu();
                break;
            default:
                cout << YELLOW << ">> Sai lựa chọn!" << RESET << "\n";
        }
        cout << "(Ấn Enter để tiếp tục...)"; cin.ignore(); cin.get();
    }
}