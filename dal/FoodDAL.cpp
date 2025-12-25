#include "FoodDAL.h"
#include <algorithm>

void FoodDAL::loadFoods() {
    listFood.clear();
    std::ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) return;

    std::string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> data;
        
        while (getline(ss, segment, ',')) {
            data.push_back(segment);
        }

        if (data.size() == 3) {
            try {
                listFood.push_back(Food(data[0], data[1], std::stoi(data[2])));
            } catch (...) {}
        }
    }
    inFile.close();
}

void FoodDAL::saveFoods() {
    std::ofstream outFile(FILE_NAME);
    if (outFile.is_open()) {
        for (const auto& f : listFood) {
            outFile << f.getId() << "," << f.getName() << "," << f.getPrice() << std::endl;
        }
        outFile.close();
    }
}

void FoodDAL::addFood(const Food& food) {
    listFood.push_back(food);
    this->saveFoods();
}

std::vector<Food> FoodDAL::getList() const { 
    return listFood; 
}

Food* FoodDAL::getFoodById(std::string id) {
    for (auto &f : listFood) {
        if (f.getId() == id) return &f;
    }
    return nullptr;
}

bool FoodDAL::updateFood(std::string id, std::string newName, int newPrice) {
    for (auto &f : listFood) {
        if (f.getId() == id) {
            // Thay thế phần tử bằng đối tượng mới với dữ liệu cập nhật
            f = Food(id, newName, newPrice);
            saveFoods();
            return true;
        }
    }
    return false;
}

bool FoodDAL::deleteFood(std::string id) {
    auto it = std::remove_if(listFood.begin(), listFood.end(), [&](const Food &f){
        return f.getId() == id;
    });
    if (it != listFood.end()) {
        listFood.erase(it, listFood.end());
        saveFoods();
        return true;
    }
    return false;
}