#include "dal/ShowtimeDAL.h"

#include <fstream>
#include <sstream>

static std::vector<std::string> split2(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

ShowtimeDAL::ShowtimeDAL(std::string filePath) : filePath(std::move(filePath)) {}

std::vector<Showtime> ShowtimeDAL::loadShowtimes() {
    std::vector<Showtime> showtimes;
    std::ifstream in(filePath);
    if (!in) return showtimes;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        // Format mặc định: id|movieId|room|startTime
        auto parts = split2(line, '|');
        if (parts.size() < 4) continue;

        showtimes.emplace_back(parts[0], parts[1], parts[2], parts[3]);
    }
    return showtimes;
}

void ShowtimeDAL::saveShowtimes(const std::vector<Showtime>& showtimes) {
    std::ofstream out(filePath, std::ios::trunc);
    for (const auto& s : showtimes) {
        out << s.getId() << '|'
            << s.getMovieId() << '|'
            << s.getRoom() << '|'
            << s.getStartTime()
            << '\n';
    }
}
