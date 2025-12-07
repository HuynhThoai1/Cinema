#include "FoodBUS.h"
#include <vector>
#include <string>
using namespace std;

vector<Food> FoodBUS::getAll() {
    foodDal.loadFoods();
    return foodDal.getList();
}

int FoodBUS::calculateOrderTotal(const vector<string>& idList) {
    foodDal.loadFoods();
    vector<Food> foods = foodDal.getList();

    int total = 0;
    for (const auto& id : idList) { 
        for (const auto& f : foods) {
            if (f.getId() == id) { 
                total += f.getPrice();
            }
        }
    }
    return total;
}
