#include <iostream>
#include "ui/FoodUI.h"     
#include "ui/RevenueUI.h"  

int main() {
    FoodUI foodApp;
    RevenueUI revApp;
    int choice;

    do {
        std::cout << "\n=== RẠP CHIẾU PHIM (HỆ THỐNG QUẢN LÝ) ===\n";
        std::cout << "1. Quản lý Món Ăn & Thức Uống\n";
        std::cout << "2. Quản lý Doanh Thu\n";
        std::cout << "0. Thoát\n";
        std::cout << "Chọn chức năng: ";
        std::cin >> choice; std::cin.ignore();

        switch(choice) {
            case 1: foodApp.process(); break;
            case 2: revApp.process(); break;
            case 0: std::cout << "Tạm biệt!\n"; break;
            default: std::cout << "Lệnh không hợp lệ!\n";
        }
    } while (choice != 0);

    return 0;
}