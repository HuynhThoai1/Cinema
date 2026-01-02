#include "RevenueUI.h"
#include "../utils/FormatUI.h"
#include "../utils/InputUtils.h"
#include <iostream>
#include <iomanip>

RevenueUI::RevenueUI() {}

void RevenueUI::process() {
    int choice;
    while (true) {
        clearScreen();
        printHeader("QUAN LY DOANH THU");
        
        std::cout << CYAN << "1. Xem báo cáo" << RESET << "\n";
        std::cout << CYAN << "2. Nhập doanh thu" << RESET << "\n";
        std::cout << CYAN << "0. Quay lại" << RESET << "\n";
        std::cout << "------------------------------------------\n";
        
        choice = InputUtils::readInt("Chọn: ");
        
        if (choice == 0) break;
        
        switch(choice) {
            case 1: 
                clearScreen();
                printHeader("BÁO CÁO DOANH THU");
                showAllRevenue();
                std::cout << "(Ấn Enter để tiếp tục...)"; std::cin.get();
                break;
            case 2: 
                clearScreen();
                printHeader("NHẬP DOANH THU");
                inputRevenue();
                std::cout << "(Ấn Enter để tiếp tục...)"; std::cin.get();
                break;
            default:
                std::cout << RED << ">> Lựa chọn không hợp lệ!" << RESET << "\n";
                std::cout << "(Ấn Enter để tiếp tục...)"; std::cin.get();
                break;
        }
    }
}

void RevenueUI::inputRevenue() {
    std::string date, movie; int tick, food;
    std::cout << YELLOW << "Ngày (dd/mm/yyyy): " << RESET; getline(std::cin, date);
    std::cout << YELLOW << "Mã phim: " << RESET; getline(std::cin, movie);
    tick = InputUtils::readInt(std::string(YELLOW) + "Tiền vé: " + RESET);
    food = InputUtils::readInt(std::string(YELLOW) + "Tiền đồ ăn: " + RESET);
    revBus.addRevenueRecord(date, movie, tick, food);
    std::cout << GREEN << ">> Đã lưu bản ghi doanh thu!" << RESET << "\n";
}

void RevenueUI::showAllRevenue() {
    std::vector<Revenue> list = revBus.getAll();
    
    std::cout << "\n";
    if (list.empty()) {
        std::cout << YELLOW << ">> Chưa có bản ghi doanh thu nào." << RESET << "\n";
        return;
    }
    
    std::cout << GREEN << ">> Tìm thấy " << list.size() << " bản ghi:\n" << RESET;
    
    // Header bảng
    std::cout << GREEN << "--------------------------------------------------------------------------------\n";
    std::cout << "| " << YELLOW << std::left << std::setw(6) << "ID"
              << GREEN << "| " << YELLOW << std::left << std::setw(25) << "Thoi Gian" 
              << GREEN << "| " << YELLOW << std::left << std::setw(8) << "Loai"
              << GREEN << "| " << YELLOW << std::left << std::setw(15) << "Ma"
              << GREEN << "| " << YELLOW << std::left << std::setw(12) << "So Tien"
              << GREEN << " |\n";
    std::cout << "--------------------------------------------------------------------------------" << RESET << "\n";
    
    int totalRevenue = 0;
    for(auto& r : list) {
        std::cout << GREEN << "| " << CYAN << std::left << std::setw(6) << r.getId()
                  << GREEN << "| " << RESET << std::left << std::setw(25) << r.getTimestamp() 
                  << GREEN << "| " << RESET << std::left << std::setw(8) << r.getRevenueType() 
                  << GREEN << "| " << RESET << std::left << std::setw(15) << r.getRelatedId()
                  << GREEN << "| " << RESET << std::left << std::setw(12) << (std::to_string(r.getAmount()) + " VND")
                  << GREEN << " |" << RESET << "\n";
        totalRevenue += r.getAmount();
    }
    std::cout << GREEN << "--------------------------------------------------------------------------------" << RESET << "\n";
    std::cout << YELLOW << "TỔNG DOANH THU: " << totalRevenue << " VND" << RESET << "\n";
    std::cout << GREEN << "--------------------------------------------------------------------------------" << RESET << "\n";
}