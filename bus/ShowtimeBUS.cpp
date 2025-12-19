#include "bus/ShowtimeBUS.h"

#include <algorithm>

ShowtimeBUS::ShowtimeBUS(ShowtimeDAL showtimeDal) : showtimeDal(std::move(showtimeDal)) {}

std::vector<Showtime> ShowtimeBUS::getByMovie(const std::string& movieId) {
    auto showtimes = showtimeDal.loadShowtimes();
    std::vector<Showtime> filtered;
    filtered.reserve(showtimes.size());
    for (const auto& s : showtimes) {
        if (s.getMovieId() == movieId) filtered.push_back(s);
    }
    return filtered;
}

bool ShowtimeBUS::addShowtime(const Showtime& showtime) {
    auto showtimes = showtimeDal.loadShowtimes();
    auto it = std::find_if(showtimes.begin(), showtimes.end(),
                           [&](const Showtime& s) { return s.getId() == showtime.getId(); });
    if (it != showtimes.end()) return false;

    showtimes.push_back(showtime);
    showtimeDal.saveShowtimes(showtimes);
    return true;
}

bool ShowtimeBUS::deleteShowtime(const std::string& id) {
    auto showtimes = showtimeDal.loadShowtimes();
    auto before = showtimes.size();
    showtimes.erase(std::remove_if(showtimes.begin(), showtimes.end(),
                                  [&](const Showtime& s) { return s.getId() == id; }),
                    showtimes.end());
    if (showtimes.size() == before) return false;

    showtimeDal.saveShowtimes(showtimes);
    return true;
}
