#include "FoodDAL.h"

// Implementation các hàm của FoodDAL
void FoodDAL::loadFoods() {
    listFood.clear();
    
    listFood.push_back(Food("F01", "Bap rang bo", 45000));
    listFood.push_back(Food("F02", "Nuoc ngot", 25000));
    listFood.push_back(Food("F03", "Combo 1", 65000));
}

vector<Food> FoodDAL::getList() const {
    return listFood;
}

Food* FoodDAL::getFoodById(string id) {
    for (auto &f : listFood) {
        if (f.getId() == id) return &f;
    }
    return nullptr;
}


Food::Food() {}
Food::Food(string id, string name, int price) : id(id), name(name), basePrice(price) {}
string Food::getId() const { return id; }
string Food::getName() const { return name; }
int Food::getPrice() const { return basePrice; }
void Food::display() const {
    cout << left << setw(10) << id << setw(20) << name << setw(10) << basePrice << " VND" << endl;
}