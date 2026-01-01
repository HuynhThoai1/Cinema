#include "Revenue.h"
#include <sstream>

Revenue::Revenue() : id(""), timestamp(""), revenueType(""), relatedId(""), amount(0), additionalInfo("") {}

Revenue::Revenue(std::string id, std::string timestamp, std::string type, std::string relatedId, int amount, std::string info) 
    : id(id), timestamp(timestamp), revenueType(type), relatedId(relatedId), amount(amount), additionalInfo(info) {}

std::string Revenue::getId() const { return this->id; }
std::string Revenue::getTimestamp() const { return this->timestamp; }
std::string Revenue::getRevenueType() const { return this->revenueType; }
std::string Revenue::getRelatedId() const { return this->relatedId; }
int Revenue::getAmount() const { return this->amount; }
std::string Revenue::getAdditionalInfo() const { return this->additionalInfo; }

std::string Revenue::getDateOnly() const {
    // Tách ngày từ timestamp (dd/mm/yyyy HH:MM:SS) -> lấy phần dd/mm/yyyy
    if (timestamp.empty()) return "";
    size_t spacePos = timestamp.find(' ');
    if (spacePos != std::string::npos) {
        return timestamp.substr(0, spacePos);
    }
    return timestamp;
}

void Revenue::display() const {
    std::cout << std::left << std::setw(8) << id 
              << std::setw(20) << timestamp 
              << std::setw(8) << revenueType 
              << std::setw(10) << relatedId
              << std::setw(12) << amount
              << additionalInfo << std::endl;
}