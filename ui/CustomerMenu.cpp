#include "CustomerMenu.h"
#include "../utils/InputUtils.h"
#include "../utils/FormatUI.h"
#include "TicketUI.h"
#include "FoodUI.h"
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
    int choice;
    while (true) {
        clearScreen();
        printHeader("KHACH HANG");

        cout << CYAN << "1. Xem danh sach phim" << RESET << "\n";
        cout << CYAN << "2. Dat ve" << RESET << "\n";
        cout << CYAN << "3. Mua do an va do uong" << RESET << "\n";
        cout << CYAN << "0. Dang xuat" << RESET << "\n";

        choice = InputUtils::readInt("Nhap lua chon: ");

        if (choice == 0) break;

        switch (choice) {
            case 1:
                movieUI.showAll();
                break;
            case 2:
                if (currentUser != nullptr) {
                    ticketUI.setCurrentUser(currentUser->getId());
                } else {
                    cout << RED << "Loi: Khong xac dinh duoc nguoi dung!" << RESET << "\n";
                    break;
                }
                ticketUI.run();
                break;
            case 3:
                // TODO: tích hợp với FoodBUS cho customer
                foodUI.process();
                break;
            default:
                cout << YELLOW << ">> Sai lua chon!" << RESET << "\n";
        }
        cout << "(An Enter de tiep tuc...)"; cin.ignore(); cin.get();
    }
}