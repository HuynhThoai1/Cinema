#include "FoodUI.h" 
#include "../bus/FoodBUS.h"
#include "../utils/FormatUI.h"
#include "../utils/InputUtils.h"
#include <iostream>
#include <iomanip>
#include <vector>

FoodUI::FoodUI() {}

void FoodUI::adminMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("QUẢN LÝ MÓN ĂN (ADMIN)");
        std::cout << CYAN << "1. Xem danh sách món ăn" << RESET << "\n";
        std::cout << CYAN << "2. Thêm món ăn mới" << RESET << "\n";
        std::cout << CYAN << "3. Cập nhật món ăn" << RESET << "\n";
        std::cout << CYAN << "4. Xóa món ăn" << RESET << "\n";
        std::cout << CYAN << "0. Quay lại" << RESET << "\n";
        std::cout << "------------------------------------------\n";
        choice = InputUtils::readInt(string(YELLOW) + ">> Chọn: " + RESET);

        switch (choice) {
            case 1: clearScreen(); printHeader("DANH SÁCH MÓN ĂN"); showAllFoods(); break;
            case 2: clearScreen(); printHeader("THÊM MÓN ĂN MỚI"); inputNewFood(); break;
            case 3: clearScreen(); printHeader("CẬP NHẬT MÓN ĂN"); updateFood(); break;
            case 4: clearScreen(); printHeader("XÓA MÓN ĂN"); deleteFood(); break;
            case 0: std::cout << GREEN << "Quay lại menu chính..." << RESET << "\n"; break;
            default: std::cout << RED << "(!) Lựa chọn không hợp lệ!" << RESET << "\n";
        }
        if (choice != 0) { std::cout << "(Nhấn Enter để tiếp tục...)"; std::cin.get(); }
    } while (choice != 0);
}

void FoodUI::customerMenu() {
    int choice;
    do {
        clearScreen();
        printHeader("MENU THỨC ĂN");
        std::cout << CYAN << "1. Xem menu thức ăn" << RESET << "\n";
        std::cout << CYAN << "2. Mua thức ăn" << RESET << "\n";
        std::cout << CYAN << "0. Quay lại" << RESET << "\n";
        std::cout << "------------------------------------------\n";
        choice = InputUtils::readInt(string(YELLOW) + ">> Chọn: " + RESET);

        switch (choice) {
            case 1: clearScreen(); printHeader("DANH SÁCH MÓN ĂN"); showAllFoods(); break;
            case 2: clearScreen(); printHeader("MUA THỨC ĂN"); purchaseFood(); break;
            case 0: std::cout << GREEN << "Quay lại menu chính..." << RESET << "\n"; break;
            default: std::cout << RED << "(!) Lựa chọn không hợp lệ!" << RESET << "\n";
        }
        if (choice != 0) { std::cout << "(Nhấn Enter để tiếp tục...)"; std::cin.get(); }
    } while (choice != 0);
}

void FoodUI::inputNewFood() {
    std::string id, name; int price;
    std::cout << YELLOW << "Nhập ID món: " << RESET; getline(std::cin, id);
    std::cout << YELLOW << "Nhập Tên món: " << RESET; getline(std::cin, name);
    price = InputUtils::readInt(string(YELLOW) + "Nhập Giá (VND): " + RESET);

    if (price <= 0) {
        std::cout << RED << "(!) Giá phải lớn hơn 0!" << RESET << "\n";
        return;
    }

    foodBus.addNewFood(id, name, price);
    std::cout << GREEN << ">> Đã thêm món ăn thành công!" << RESET << "\n";
}

void FoodUI::updateFood() {
    std::string id;
    showAllFoods();
    std::cout << "Nhập ID món cần cập nhật: "; getline(std::cin, id);
    
    // Kiểm tra món ăn có tồn tại không
    std::vector<Food> list = foodBus.getAll();
    bool found = false;
    for(auto& f : list) {
        if(f.getId() == id) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        std::cout << RED << ">> Không tìm thấy món ăn với ID: " << id << RESET << "\n";
        return;
    }
    
    std::string newName;
    int newPrice;
    std::cout << YELLOW << "Nhập tên mới: " << RESET; getline(std::cin, newName);
    newPrice = InputUtils::readInt(string(YELLOW) + "Nhập giá mới (VND): " + RESET);
    
    if (newPrice <= 0) {
        std::cout << RED << ">> Lỗi: Giá phải lớn hơn 0!" << RESET << "\n";
        return;
    }

    bool ok = foodBus.updateFood(id, newName, newPrice);
    if (ok) {
        std::cout << GREEN << ">> Đã cập nhật món ăn thành công!" << RESET << "\n";
    } else {
        std::cout << RED << ">> Cập nhật thất bại!" << RESET << "\n";
    }
}

void FoodUI::deleteFood() {
    std::string id;
    showAllFoods();
    std::cout << "Nhập ID món cần xóa: "; getline(std::cin, id);
    
    char confirm = InputUtils::readYesNo(string(YELLOW) + "Bạn có chắc chắn muốn xóa món này? (y/n): " + RESET);
    
    if (confirm == 'y') {
        bool ok = foodBus.deleteFood(id);
        if (ok) {
            std::cout << GREEN << ">> Đã xóa món ăn thành công!" << RESET << "\n";
        } else {
            std::cout << RED << ">> Xóa món ăn thất bại!" << RESET << "\n";
        }
    } else {
        std::cout << CYAN << ">> Đã hủy thao tác xóa." << RESET << "\n";
    }
}

void FoodUI::showAllFoods() {
    std::vector<Food> list = foodBus.getAll();
    if (list.empty()) {
        std::cout << RED << "\n>> Chưa có món ăn nào trong hệ thống." << RESET << "\n";
        return;
    }

    std::cout << BLUE << std::string(40, '=') << RESET << "\n";
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(25) << "TÊN MÓN" 
              << std::right << std::setw(12) << "GIÁ (VND)" << "\n";
    std::cout << BLUE << std::string(40, '=') << RESET << "\n";

    for (auto &f : list) {
        std::cout << std::left << std::setw(10) << f.getId()
                  << std::setw(25) << f.getName()
                  << std::right << std::setw(12) << f.getPrice() << "\n";
    }
    std::cout << BLUE << std::string(40, '=') << RESET << "\n";
}

void FoodUI::purchaseFood() {
    showAllFoods();
    
    std::vector<std::string> ids;
    std::vector<int> quantities;
    char continueOrder = 'y';
    
    do {
        std::string id;
        int quantity;
        
        std::cout << "\nNhập ID món muốn mua: "; 
        getline(std::cin, id);
        
        // Kiểm tra món ăn có tồn tại không
        std::vector<Food> list = foodBus.getAll();
        bool found = false;
        for(auto& f : list) {
            if(f.getId() == id) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << RED << ">> Không tìm thấy món ăn với ID: " << id << RESET << "\n";
            continueOrder = InputUtils::readYesNo(string(YELLOW) + "Tiếp tục mua? (y/n): " + RESET);
            continue;
        }
        
        quantity = InputUtils::readInt(string(YELLOW) + "Nhập số lượng: " + RESET);
        
        if (quantity <= 0) {
            std::cout << RED << ">> Số lượng phải lớn hơn 0!" << RESET << "\n";
            continueOrder = InputUtils::readYesNo(string(YELLOW) + "Tiếp tục mua? (y/n): " + RESET);
            continue;
        }
        
        ids.push_back(id);
        quantities.push_back(quantity);
        
        std::cout << GREEN << ">> Đã thêm vào giỏ hàng!" << RESET << "\n";
        continueOrder = InputUtils::readYesNo(string(YELLOW) + "Mua thêm món khác? (y/n): " + RESET);
        
    } while (continueOrder == 'y');
    
    if (ids.empty()) {
        std::cout << ">> Không có món nào được chọn.\n";
        return;
    }
    
    // Hiển thị hóa đơn
    std::cout << BLUE << std::string(50, '=') << RESET << "\n";
    std::cout << GREEN << "                    HÓA ĐƠN" << RESET << "\n";
    std::cout << BLUE << std::string(50, '=') << RESET << "\n";
    
    std::vector<Food> list = foodBus.getAll();
    int total = 0;
    
    for(size_t i = 0; i < ids.size(); i++) {
        for(auto& f : list) {
            if(f.getId() == ids[i]) {
                int subtotal = f.getPrice() * quantities[i];
                total += subtotal;
                std::cout << std::left << std::setw(25) << f.getName()
                          << std::right << std::setw(5) << quantities[i] << " x "
                          << std::setw(10) << f.getPrice() 
                          << " = " << std::setw(10) << subtotal << " VND\n";
                break;
            }
        }
    }
    
    std::cout << BLUE << std::string(50, '-') << RESET << "\n";
    std::cout << std::right << std::setw(40) << "TỔNG CỘNG: " 
              << YELLOW << std::setw(10) << total << RESET << " VND\n";
    std::cout << BLUE << std::string(50, '=') << RESET << "\n";
    
    // [MỚI] GHI NHẬN DOANH THU TỰ ĐỘNG
    if (total > 0) {
        // Tạo chuỗi thông tin chi tiết về các món đã mua
        std::stringstream infoStream;
        infoStream << "Items: ";
        for(size_t i = 0; i < ids.size(); i++) {
            if (i > 0) infoStream << ", ";
            infoStream << ids[i] << "x" << quantities[i];
        }
        revenueBus.recordRevenue("FOOD", "FOOD_ORDER", total, infoStream.str());
        std::cout << GREEN << "\n[DOANH THU] Đã ghi nhận " << total << " VND từ bán đồ ăn." << RESET << "\n";
    }
    
    std::cout << GREEN << "\n>> Cảm ơn quý khách! Chúc quý khách xem phim vui vẻ!" << RESET << "\n";
}