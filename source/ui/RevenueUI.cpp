#include "RevenueUI.h"
#include <iostream>
#include <iomanip>

RevenueUI::RevenueUI() {}

void RevenueUI::process() {
    int choice;
    do {
        std::cout << "\n--- QUẢN LÝ DOANH THU ---\n";
        std::cout << "1. Xem báo cáo\n2. Nhập doanh thu\n0. Quay lại\nChọn: ";
        std::cin >> choice; std::cin.ignore();
        switch(choice) {
            case 1: showAllRevenue(); break;
            case 2: inputRevenue(); break;
        }
    } while(choice != 0);
}

void RevenueUI::inputRevenue() {
    std::string date, movie; int tick, food;
    std::cout << "Ngày (dd/mm/yyyy): "; getline(std::cin, date);
    std::cout << "Mã phim: "; getline(std::cin, movie);
    std::cout << "Tiền vé: "; std::cin >> tick;
    std::cout << "Tiền đồ ăn: "; std::cin >> food; std::cin.ignore();
    revBus.addRevenueRecord(date, movie, tick, food);
    std::cout << ">> Đã lưu bản ghi doanh thu!\n";
}

void RevenueUI::showAllRevenue() {
    std::vector<Revenue> list = revBus.getAll();
    std::cout << "--------------------------------------------------------\n";
    std::cout << std::left << std::setw(6) << "ID" << std::setw(25) << "THỜI GIAN" 
              << std::setw(8) << "LOẠI" << std::setw(15) << "MÃ" << "SỐ TIỀN\n";
    std::cout << "--------------------------------------------------------\n";
    
    int totalRevenue = 0;
    for(auto& r : list) {
        std::cout << std::left << std::setw(6) << r.getId() 
                  << std::setw(25) << r.getTimestamp() 
                  << std::setw(8) << r.getRevenueType() 
                  << std::setw(15) << r.getRelatedId()
                  << r.getAmount() << " VND\n";
        totalRevenue += r.getAmount();
    }
    std::cout << "--------------------------------------------------------\n";
    std::cout << "TỔNG DOANH THU: " << totalRevenue << " VND\n";
    std::cout << "--------------------------------------------------------\n";
}