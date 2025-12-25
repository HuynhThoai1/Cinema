#include "FoodDAL.h"

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