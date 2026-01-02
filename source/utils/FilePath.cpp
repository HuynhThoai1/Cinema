#include "FilePath.h" 

std::string DATA_PATH(const std::string& file) {
    // Ưu tiên chạy từ source/
    if (std::filesystem::exists("data/" + file)) {
        return "data/" + file;
    }
    // Trường hợp chạy từ release/
    if (std::filesystem::exists("../data/" + file)) {
        return "../data/" + file;
    }
    // Fallback
    return file;
}