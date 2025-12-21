#include "FoodBUS.h"

FoodBUS::FoodBUS() {
    foodDal.loadFoods(); 
}

std::vector<Food> FoodBUS::getAll() {
    return foodDal.getList();
}

void FoodBUS::addNewFood(std::string id, std::string name, int price) {
    if (price < 0) return; 
    Food f(id, name, price);
    foodDal.addFood(f);
}

int FoodBUS::calculateOrderTotal(const std::vector<std::string>& idList) {
    int total = 0;
    for (const std::string& id : idList) {
        Food* f = foodDal.getFoodById(id);
        if (f) {
            total += f->getPrice();
        }
    }
    return total;
}