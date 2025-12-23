/**
 * @file MovieDAL.cpp
 * @brief Cài đặt tầng DAL cho Movie: đọc/ghi Movies từ file text.
 *
 * @details
 * - DAL chỉ phụ trách I/O (đọc/ghi file).
 * - Mọi validate nghiệp vụ nằm ở BUS.
 * - File có thể rỗng/không tồn tại: DAL phải xử lý an toàn (không crash).
 */

#include "MovieDAL.h"

#include <fstream>
#include <sstream>
#include <utility>

/** @brief Tách chuỗi theo delimiter. */
static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

/** @brief Trim khoảng trắng đầu/cuối chuỗi. */
static std::string trim(std::string s) {
    const char* ws = " \t\r\n";
    auto b = s.find_first_not_of(ws);
    auto e = s.find_last_not_of(ws);
    if (b == std::string::npos) return std::string{};
    return s.substr(b, e - b + 1);
}

/**
 * @brief Parse int strict: chuỗi phải là số hoàn chỉnh (không kèm ký tự dư).
 * @return true nếu parse thành công.
 */
static bool tryParseIntStrict(const std::string& s, int& out) {
    try {
        size_t pos = 0;
        int v = std::stoi(s, &pos);
        if (pos != s.size()) return false;
        out = v;
        return true;
    } catch (...) {
        return false;
    }
}

MovieDAL::MovieDAL(std::string filePath) : filePath(std::move(filePath)) {}

std::vector<Movie> MovieDAL::loadMovies() {
    std::vector<Movie> movies;
    std::ifstream in(filePath);
    if (!in) return movies; // file không tồn tại -> trả list rỗng

    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        auto parts = split(line, '|');
        if (parts.size() < 4) continue;

        // Trim từng field
        for (auto& p : parts) p = trim(p);

        // Hỗ trợ 2 format:
        // A) id|title|genre|duration
        // B) id|title|duration|genre|...
        const std::string id    = parts[0];
        const std::string title = parts[1];
        if (id.empty() || title.empty()) continue;

        std::string genre;
        int duration = 0;

        int tmp = 0;
        if (tryParseIntStrict(parts[2], tmp)) {
            duration = tmp;
            genre = parts[3];
        } else {
            genre = parts[2];
            if (!tryParseIntStrict(parts[3], duration)) continue;
        }

        if (genre.empty()) continue;
        if (duration <= 0 || duration > 500) continue;

        movies.emplace_back(id, title, genre, duration);
    }

    return movies;
}

void MovieDAL::saveMovies(const std::vector<Movie>& movies) {
    std::ofstream out(filePath, std::ios::trunc);

    // Lưu format chuẩn: id|title|genre|duration
    for (const auto& m : movies) {
        if (m.getId().empty()) continue; // né record rác
        out << m.getId() << '|'
            << m.getTitle() << '|'
            << m.getGenre() << '|'
            << m.getDuration()
            << '\n';
    }
}
