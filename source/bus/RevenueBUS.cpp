#include "RevenueBUS.h"
#include <cstdlib>   // getenv, setenv
#include <ctime>     // tzset

RevenueBUS::RevenueBUS() {
    const char* tz = std::getenv("TZ");

    bool isUTC = (!tz || std::string(tz) == "UTC" || std::string(tz) == "Etc/UTC");

    if (isUTC) {
    #ifdef _WIN32
        // Windows: dùng _putenv_s
        _putenv_s("TZ", "Asia/Ho_Chi_Minh");
        _tzset();
    #else
        // Linux / Mac / Codespaces
        setenv("TZ", "Asia/Ho_Chi_Minh", 1);
        tzset();
    #endif
    }

    revenueDal.loadRevenues();
}

std::string RevenueBUS::getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    std::stringstream ss;
    ss << std::setfill('0') 
       << std::setw(2) << (ltm->tm_mday) << "/"
       << std::setw(2) << (1 + ltm->tm_mon) << "/"
       << (1900 + ltm->tm_year) << " "
       << std::setw(2) << (ltm->tm_hour) << ":"
       << std::setw(2) << (ltm->tm_min) << ":"
       << std::setw(2) << (ltm->tm_sec);
    
    return ss.str();
}

void RevenueBUS::recordRevenue(std::string type, std::string relatedId, int amount, std::string info) {
    // [FIX] Reload dữ liệu từ file trước để lấy size chính xác và tránh ID trùng
    revenueDal.loadRevenues();
    
    // Tự động tạo ID
    int size = revenueDal.getList().size();
    std::string newId = "R" + std::to_string(size + 1);
    if(size < 9) newId = "R0" + std::to_string(size + 1);
    
    // Lấy timestamp hiện tại
    std::string timestamp = getCurrentTimestamp();
    
    // Tạo và lưu bản ghi Revenue
    Revenue r(newId, timestamp, type, relatedId, amount, info);
    revenueDal.addRevenue(r);
}

void RevenueBUS::addRevenueRecord(std::string date, std::string movieId, int ticketAmount, int foodAmount) {
    // Phương thức cũ để tương thích ngược - chuyển sang format mới
    // Ghi 2 bản ghi: một cho vé, một cho đồ ăn
    if (ticketAmount > 0) {
        recordRevenue("TICKET", movieId, ticketAmount, "Legacy: " + date);
    }
    if (foodAmount > 0) {
        recordRevenue("FOOD", "N/A", foodAmount, "Legacy: " + date);
    }
}

std::vector<Revenue> RevenueBUS::getAll() {
    return revenueDal.getList();
}

std::vector<Revenue> RevenueBUS::getByDate(std::string date) {
    std::vector<Revenue> result;
    for (const auto& r : revenueDal.getList()) {
        if (r.getDateOnly() == date) {
            result.push_back(r);
        }
    }
    return result;
}