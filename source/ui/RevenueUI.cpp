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
        
        std::cout << CYAN << "1. Xem bao cao" << RESET << "\n";
        std::cout << CYAN << "2. Nhap doanh thu" << RESET << "\n";
        std::cout << CYAN << "0. Quay lai" << RESET << "\n";
        std::cout << "------------------------------------------\n";
        
        choice = InputUtils::readInt("Chon: ");
        
        if (choice == 0) break;
        
        switch(choice) {
            case 1: 
                clearScreen();
                printHeader("BAO CAO DOANH THU");
                showAllRevenue();
                std::cout << "(An Enter de tiep tuc...)"; std::cin.get();
                break;
            case 2: 
                clearScreen();
                printHeader("NHAP DOANH THU");
                inputRevenue();
                std::cout << "(An Enter de tiep tuc...)"; std::cin.get();
                break;
            default:
                std::cout << RED << ">> Lua chon khong hop le!" << RESET << "\n";
                std::cout << "(An Enter de tiep tuc...)"; std::cin.get();
                break;
        }
    }
}

void RevenueUI::inputRevenue() {
    std::string date, movie; int tick, food;
    std::cout << YELLOW << "Ngay (dd/mm/yyyy): " << RESET; getline(std::cin, date);
    std::cout << YELLOW << "Ma phim: " << RESET; getline(std::cin, movie);
    tick = InputUtils::readInt(std::string(YELLOW) + "Tien ve: " + RESET);
    food = InputUtils::readInt(std::string(YELLOW) + "Tien do an: " + RESET);
    revBus.addRevenueRecord(date, movie, tick, food);
    std::cout << GREEN << ">> Da luu ban ghi doanh thu!" << RESET << "\n";
}

void RevenueUI::showAllRevenue() {
    std::vector<Revenue> list = revBus.getAll();
    
    std::cout << "\n";
    if (list.empty()) {
        std::cout << YELLOW << ">> Chua co ban ghi doanh thu nao." << RESET << "\n";
        return;
    }
    
    std::cout << GREEN << ">> Tim thay " << list.size() << " ban ghi:\n" << RESET;
    
    // Header bang
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
    std::cout << YELLOW << "TONG DOANH THU: " << totalRevenue << " VND" << RESET << "\n";
    std::cout << GREEN << "--------------------------------------------------------------------------------" << RESET << "\n";
}