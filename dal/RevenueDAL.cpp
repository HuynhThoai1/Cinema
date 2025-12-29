#include "RevenueDAL.h"

void RevenueDAL::loadRevenues() {
    listRevenue.clear();
    std::ifstream inFile(FILE_NAME);
    if (!inFile.is_open()) return;

    std::string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> data;
        while (getline(ss, segment, ',')) data.push_back(segment);

        // Format mới: id,timestamp,type,relatedId,amount,additionalInfo (6 fields)
        if (data.size() >= 5) {
            try {
                std::string info = (data.size() >= 6) ? data[5] : "";
                Revenue r(data[0], data[1], data[2], data[3], std::stoi(data[4]), info);
                listRevenue.push_back(r);
            } catch (...) {}
        }
    }
    inFile.close();
}

void RevenueDAL::saveRevenues() {
    std::ofstream outFile(FILE_NAME);
    if (outFile.is_open()) {
        for (const auto& r : listRevenue) {
            outFile << r.getId() << "," << r.getTimestamp() << "," << r.getRevenueType() << ","
                    << r.getRelatedId() << "," << r.getAmount() << "," << r.getAdditionalInfo() << std::endl;
        }
        outFile.close();
    }
}

void RevenueDAL::addRevenue(const Revenue& rev) {
    // [FIX] Load lại dữ liệu từ file trước khi thêm để tránh mất dữ liệu
    loadRevenues();
    listRevenue.push_back(rev);
    saveRevenues();
}

std::vector<Revenue> RevenueDAL::getList() const { 
    return listRevenue; 
}