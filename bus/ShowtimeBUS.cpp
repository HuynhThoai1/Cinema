/**
 * @file ShowtimeBUS.cpp
 * @brief Cài đặt tầng BUS cho Showtime: xử lý validate & luật nghiệp vụ.
 *
 * @details
 * Edge cases chính đã xử lý:
 * - Reject dữ liệu rỗng
 * - Validate format startTime (yyyy-mm-dd HH:MM)
 * - movieId phải tồn tại (tránh showtime "mồ côi")
 * - Reject trùng showtimeId
 * - Reject trùng lịch: cùng room + cùng startTime
 */

#include "ShowtimeBUS.h"

#include <algorithm>
#include <regex>
#include <utility>

/** @brief Kiểm tra chuỗi rỗng hoặc chỉ toàn khoảng trắng. */
static bool isBlank(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") == std::string::npos;
}

/** @brief Validate datetime dạng yyyy-mm-dd HH:MM (basic). */
static bool looksLikeDateTime(const std::string& s) {
    static const std::regex re(R"(^\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}$)");
    return std::regex_match(s, re);
}

ShowtimeBUS::ShowtimeBUS(ShowtimeDAL showtimeDal, MovieDAL movieDal)
    : showtimeDal(std::move(showtimeDal)), movieDal(std::move(movieDal)) {}

std::vector<Showtime> ShowtimeBUS::getByMovie(const std::string& movieId) {
    if (isBlank(movieId)) return {};

    auto showtimes = showtimeDal.loadShowtimes();
    std::vector<Showtime> filtered;
    filtered.reserve(showtimes.size());

    for (const auto& s : showtimes) {
        if (s.getMovieId() == movieId && !s.getId().empty()) {
            filtered.push_back(s);
        }
    }
    return filtered;
}

bool ShowtimeBUS::addShowtime(const Showtime& showtime) {
    // Validate dữ liệu cơ bản
    if (isBlank(showtime.getId()) || isBlank(showtime.getMovieId()) ||
        isBlank(showtime.getRoom()) || isBlank(showtime.getStartTime()))
        return false;

    // Validate format thời gian để tránh data rác
    if (!looksLikeDateTime(showtime.getStartTime()))
        return false;

    // Edge: movieId phải tồn tại
    {
        auto movies = movieDal.loadMovies();
        auto ok = std::any_of(movies.begin(), movies.end(),
                              [&](const Movie& m) { return m.getId() == showtime.getMovieId(); });
        if (!ok) return false;
    }

    auto showtimes = showtimeDal.loadShowtimes();

    // Edge: trùng showtimeId
    auto dupId = std::any_of(showtimes.begin(), showtimes.end(),
                             [&](const Showtime& s) { return s.getId() == showtime.getId(); });
    if (dupId) return false;

    // Edge: trùng lịch phòng + giờ (đụng lịch)
    auto clash = std::any_of(showtimes.begin(), showtimes.end(),
                             [&](const Showtime& s) {
                                 return s.getRoom() == showtime.getRoom() &&
                                        s.getStartTime() == showtime.getStartTime();
                             });
    if (clash) return false;

    showtimes.push_back(showtime);
    showtimeDal.saveShowtimes(showtimes);
    return true;
}

bool ShowtimeBUS::deleteShowtime(const std::string& id) {
    if (isBlank(id)) return false;

    auto showtimes = showtimeDal.loadShowtimes();
    auto before = showtimes.size();

    showtimes.erase(
        std::remove_if(showtimes.begin(), showtimes.end(),
                       [&](const Showtime& s) { return s.getId() == id; }),
        showtimes.end()
    );

    if (showtimes.size() == before) return false;

    showtimeDal.saveShowtimes(showtimes);
    return true;
}
