#include "Food.h"

Food::Food() : id(""), name(""), basePrice(0) {}

Food::Food(std::string id, std::string name, int price) 
    : id(id), name(name), basePrice(price) {}

std::string Food::getId() const { return id; }
std::string Food::getName() const { return name; }
int Food::getPrice() const { return basePrice; }

void Food::display() const {
    // Sử dụng std::setw và căn lề trái
    std::cout << std::left << std::setw(10) << id 
              << std::setw(25) << name 
              << std::setw(10) << basePrice << " VND" << std::endl;
}