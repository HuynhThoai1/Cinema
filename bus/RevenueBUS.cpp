#include "RevenueBUS.h"

RevenueBUS::RevenueBUS() {
    revenueDal.loadRevenues();
}

void RevenueBUS::addRevenueRecord(std::string date, std::string movieId, int ticketAmount, int foodAmount) {
    int size = revenueDal.getList().size();
    std::string newId = "R" + std::to_string(size + 1);
    
    if(size < 9) newId = "R0" + std::to_string(size + 1);

    Revenue r(newId, date, movieId, ticketAmount, foodAmount);
    revenueDal.addRevenue(r);
}

std::vector<Revenue> RevenueBUS::getAll() {
    return revenueDal.getList();
}

// Đã thêm định nghĩa cho hàm getByDate mà bạn nói thiếu
std::vector<Revenue> RevenueBUS::getByDate(std::string date) {
    std::vector<Revenue> result;
    for (const auto& r : revenueDal.getList()) {
        if (r.getDate() == date) {
            result.push_back(r);
        }
    }
    return result;
}