/**
 * @file Food.cpp
 * @brief Cài đặt chi tiết cho lớp Food.
 */

#include "Food.h"
using namespace std;

Food::Food() : id(""), name(""), basePrice(0) {}

Food::Food(string id, string name, int price) 
    : id(id), name(name), basePrice(price) {}

string Food::getId() const { return id; }
string Food::getName() const { return name; }
int Food::getPrice() const { return basePrice; }

void Food::display() const {
    cout << left << setw(10) << id 
         << setw(25) << name 
         << setw(10) << basePrice << " VND" << endl;
}