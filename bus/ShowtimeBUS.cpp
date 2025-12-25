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
    : showtimeDal(std::move(showtimeDal)), movieDal(std::move(movieDal)) {
        _showtimes = this->showtimeDal.loadShowtimes();
    }

std::vector<Showtime> ShowtimeBUS::getByMovie(const std::string& movieId) {
    if (isBlank(movieId)) return {};

    std::vector<Showtime> filtered;
    // Duyệt trên cache bộ nhớ
    for (const auto& s : _showtimes) {
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
    for (const auto& s : _showtimes) {
        if (s.getId() == showtime.getId()) return false;
    }

    // Edge: trùng phòng + thời gian (đụng lịch)
    for (const auto& s : _showtimes) {
        if (s.getRoom() == showtime.getRoom() && s.getStartTime() == showtime.getStartTime()) {
            return false; // Đụng lịch
        }
    }

    //  lưu vào danh sách tạm thời
    _showtimes.push_back(showtime);

    // Lưu xuống file
    showtimeDal.saveShowtimes(_showtimes);
    return true;
}
bool ShowtimeBUS::deleteShowtime(const std::string& id) {
    if (isBlank(id)) return false;

    size_t initialSize = _showtimes.size();
    _showtimes.erase(
        std::remove_if(_showtimes.begin(), _showtimes.end(),
                       [&](const Showtime& s) { return s.getId() == id; }),
        _showtimes.end()
    );

    // Nếu kích thước không đổi nghĩa là không tìm thấy ID để xóa
    if (_showtimes.size() == initialSize) return false;

    // Lưu xuống file
    showtimeDal.saveShowtimes(_showtimes);
    return true;
}
void ShowtimeBUS::load(const string& filename) {
    // 1. Tạo đối tượng DAL với filename
    ShowtimeDAL dal(filename); 
    
    // 2. Gọi hàm load 
    _showtimes = dal.loadShowtimes();
}

void ShowtimeBUS::save(const string& filename) const {
    // 1. Tạo đối tượng DAL với filename
    ShowtimeDAL dal(filename);
    
    // 2. Gọi hàm save (truyền danh sách _showtimes vào để lưu)
    dal.saveShowtimes(_showtimes);
}
Showtime* ShowtimeBUS::findById(const string& id) {
    for (size_t i = 0; i < _showtimes.size(); ++i) {
        if (_showtimes[i].getId() == id) {
            return &_showtimes[i];
        }
    }
    return nullptr;
}

