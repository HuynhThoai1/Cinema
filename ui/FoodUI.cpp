#include "FoodUI.h" 
#include <iostream>
#include <iomanip>
#include <vector>

FoodUI::FoodUI() {}

void FoodUI::process() {
    int choice;
    do {
        std::cout << "\n--- QUẢN LÝ MÓN ĂN ---\n";
        std::cout << "1. Xem danh sách\n2. Thêm món mới\n3. Tính tiền thử\n0. Quay lại\nChọn: ";
        std::cin >> choice; std::cin.ignore();
        switch (choice) {
            case 1: showAllFoods(); break;
            case 2: inputNewFood(); break;
            case 3: orderDemo(); break;
        }
    } while (choice != 0);
}

void FoodUI::inputNewFood() {
    std::string id, name; int price;
    std::cout << "Nhập ID: "; getline(std::cin, id);
    std::cout << "Nhập Tên: "; getline(std::cin, name);
    std::cout << "Nhập Giá: "; std::cin >> price; std::cin.ignore();
    foodBus.addNewFood(id, name, price);
    std::cout << ">> Đã thêm thành công!\n";
}

void FoodUI::showAllFoods() {
    std::vector<Food> list = foodBus.getAll();
    std::cout << "--------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID" << std::setw(20) << "TÊN" << "GIÁ\n";
    for(auto& f : list) {
        std::cout << std::left << std::setw(10) << f.getId() << std::setw(20) << f.getName() << f.getPrice() << std::endl;
    }
    std::cout << "--------------------------------\n";
}

void FoodUI::orderDemo() {
    std::cout << "Nhập số lượng món: "; int n; std::cin >> n; std::cin.ignore();
    std::vector<std::string> ids;
    for(int i=0; i<n; i++) {
        std::string id; std::cout << "Món thứ " << i+1 << ": "; getline(std::cin, id);
        ids.push_back(id);
    }
    std::cout << ">> Tổng tiền đơn hàng: " << foodBus.calculateOrderTotal(ids) << " VND\n";
}