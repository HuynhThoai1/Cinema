#include <iostream>
#include "ui/FoodUI.h"     
#include "ui/RevenueUI.h"  

using namespace std;

int main() {
    FoodUI foodApp;
    RevenueUI revApp;
    int choice;

    do {
        cout << "\n=== RAP CHIEU PHIM ===\n";
        cout << "1. Quan ly Mon An\n";
        cout << "2. Quan ly Doanh Thu\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice; cin.ignore();

        switch(choice) {
            case 1: foodApp.process(); break;
            case 2: revApp.process(); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Sai lenh!\n";
        }
    } while (choice != 0);

    return 0;
}