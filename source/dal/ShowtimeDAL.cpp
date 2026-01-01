/**
 * @file ShowtimeDAL.cpp
 * @brief Cài đặt tầng DAL cho Showtime: đọc/ghi Showtimes từ file text.
 *
 * @details
 * - DAL chỉ phụ trách I/O (đọc/ghi file).
 * - Dòng lỗi format sẽ bị bỏ qua để tránh crash.
 * - Hỗ trợ đoán format trường startTime/room để tránh đảo cột.
 */

#include "ShowtimeDAL.h"

#include <fstream>
#include <sstream>
#include <regex>
#include <utility>

/** @brief Tách chuỗi theo delimiter. */
static std::vector<std::string> split2(const std::string& s, char delim) {
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
 * @brief Kiểm tra chuỗi có giống định dạng datetime "yyyy-mm-dd HH:MM" hay không.
 */
static bool looksLikeDateTime(const std::string& s) {
    static const std::regex re(R"(^\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}$)");
    return std::regex_match(s, re);
}

ShowtimeDAL::ShowtimeDAL(std::string filePath) : filePath(std::move(filePath)) {}

std::vector<Showtime> ShowtimeDAL::loadShowtimes() {
    std::vector<Showtime> showtimes;
    std::ifstream in(filePath);
    if (!in) return showtimes;

    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        auto parts = split2(line, '|');
        if (parts.size() < 4) continue;
        for (auto& p : parts) p = trim(p);

        const std::string id      = parts[0];
        const std::string movieId = parts[1];
        if (id.empty() || movieId.empty()) continue;

        std::string room;
        std::string startTime;

        // Hỗ trợ 2 format:
        // A) id|movieId|room|startTime
        // B) id|movieId|startTime|room
        if (looksLikeDateTime(parts[2])) {
            startTime = parts[2];
            room = parts[3];
        } else if (looksLikeDateTime(parts[3])) {
            room = parts[2];
            startTime = parts[3];
        } else {
            // Không đoán được -> bỏ để tránh record rác
            continue;
        }

        if (room.empty() || startTime.empty()) continue;

        // DTO Showtime ctor trong code bạn: (id, movieId, room, startTime)
        showtimes.emplace_back(id, movieId, room, startTime);
    }

    return showtimes;
}

void ShowtimeDAL::saveShowtimes(const std::vector<Showtime>& showtimes) {
    std::ofstream out(filePath, std::ios::trunc);

    // Lưu theo format phổ biến: id|movieId|startTime|room
    for (const auto& s : showtimes) {
        if (s.getId().empty()) continue;
        out << s.getId() << '|'
            << s.getMovieId() << '|'
            << s.getStartTime() << '|'
            << s.getRoom()
            << '\n';
    }
}
