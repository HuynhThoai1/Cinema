#include "dal/MovieDAL.h"

#include <fstream>
#include <sstream>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

MovieDAL::MovieDAL(std::string filePath) : filePath(std::move(filePath)) {}

std::vector<Movie> MovieDAL::loadMovies() {
    std::vector<Movie> movies;
    std::ifstream in(filePath);
    if (!in) return movies;

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        // Format mặc định: id|title|genre|duration
        auto parts = split(line, '|');
        if (parts.size() < 4) continue;

        int duration = 0;
        try { duration = std::stoi(parts[3]); } catch (...) { duration = 0; }

        movies.emplace_back(parts[0], parts[1], parts[2], duration);
    }
    return movies;
}

void MovieDAL::saveMovies(const std::vector<Movie>& movies) {
    std::ofstream out(filePath, std::ios::trunc);
    for (const auto& m : movies) {
        out << m.getId() << '|'
            << m.getTitle() << '|'
            << m.getGenre() << '|'
            << m.getDuration()
            << '\n';
    }
}
