#include "MovieDAL.h"
#include <fstream>
#include <iostream>

vector<Movie> MovieDAL::loadFromFile(const string& filename) {
    vector<Movie> result;
    std::ifstream in(filename.c_str());
    if (!in.is_open()) return result;

    string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        try {
            result.push_back(Movie::deserialize(line));
        } catch (const std::exception& ex) {
            std::cerr << "[MovieDAL] Invalid line skipped: " << ex.what() << "\n";
        }
    }
    return result;
}

void MovieDAL::saveToFile(const vector<Movie>& list, const string& filename) {
    std::ofstream out(filename.c_str(), std::ios::trunc);
    if (!out.is_open()) return;

    for (size_t i = 0; i < list.size(); i++) {
        out << list[i].serialize() << "\n";
    }
}
