/**
 * @file MovieBUS.cpp
 * @brief Cài đặt tầng BUS cho Movie: xử lý validate & luật nghiệp vụ.
 *
 * @details
 * Edge cases chính đã xử lý:
 * - Reject dữ liệu rỗng / duration không hợp lệ
 * - Reject trùng ID khi thêm
 * - Update phải tồn tại
 * - Delete: chặn xóa Movie nếu còn Showtime tham chiếu (đảm bảo toàn vẹn dữ liệu)
 */

#include "MovieBUS.h"
#include <algorithm>
#include <utility>

/** @brief Kiểm tra chuỗi rỗng hoặc chỉ toàn khoảng trắng. */
static bool isBlank(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") == std::string::npos;
}

MovieBUS::MovieBUS(MovieDAL movieDal, ShowtimeDAL showtimeDal)
    : movieDal(std::move(movieDal)), showtimeDal(std::move(showtimeDal)) {
        _movies = this->movieDal.loadMovies();
    }

std::vector<Movie> MovieBUS::getAll() {
    auto movies = _movies;

    // Edge: loại bỏ record rác (id rỗng)
    movies.erase(
        std::remove_if(movies.begin(), movies.end(),
                       [](const Movie& m) { return m.getId().empty(); }),
        movies.end()
    );
    return movies;
}

bool MovieBUS::addMovie(const Movie& movie) {
    if (isBlank(movie.getId()) || isBlank(movie.getTitle()) || isBlank(movie.getGenre())) return false;
    if (movie.getDuration() <= 0 || movie.getDuration() > 500) return false;

    for (const auto& m : _movies) {
        if (m.getId() == movie.getId()) return false;
    }

    _movies.push_back(movie);
    movieDal.saveMovies(_movies);
    return true;
}

bool MovieBUS::updateMovie(const Movie& movie) {
    if (isBlank(movie.getId()) || isBlank(movie.getTitle()) || isBlank(movie.getGenre())) return false;
    if (movie.getDuration() <= 0 || movie.getDuration() > 500) return false;

    bool found = false;
    for (auto& m : _movies) {
        if (m.getId() == movie.getId()) {
            m = movie; 
            found = true;
            break;
        }
    }

    if (!found) return false;

    movieDal.saveMovies(_movies);
    return true;
}

bool MovieBUS::deleteMovie(const std::string& id) {
    if (isBlank(id)) return false;

    auto showtimes = showtimeDal.loadShowtimes();
    auto hasShowtime = std::any_of(showtimes.begin(), showtimes.end(),
                                   [&](const Showtime& s) { return s.getMovieId() == id; });
    if (hasShowtime) return false;

    size_t initialSize = _movies.size();

    _movies.erase(
        std::remove_if(_movies.begin(), _movies.end(),
                       [&](const Movie& m) { return m.getId() == id; }),
        _movies.end()
    );

    if (_movies.size() == initialSize) return false;

    movieDal.saveMovies(_movies);
    return true;
}
void MovieBUS::load(const string& filename) {
    // 1. Tạo đối tượng DAL tạm thời với filename mới
    MovieDAL tempDal(filename);
    
    // 2. Gọi hàm load từ đối tượng tạm này
    _movies = tempDal.loadMovies();
}

void MovieBUS::save(const string& filename) const {
    // 1. Tạo đối tượng DAL tạm thời với filename mới
    MovieDAL tempDal(filename);
    
    // 2. Gọi hàm save từ đối tượng tạm này
    tempDal.saveMovies(_movies);
}

optional<Movie> MovieBUS::findById(const string& id){
    for (const auto& m : _movies)
        if (m.getId() == id) return m;
    return std::nullopt;
}


vector<Movie> MovieBUS::findByTitle(const string& namePart) const {
    vector<Movie> result;
    for (size_t i = 0; i < _movies.size(); i++) {
        if (_movies[i].getTitle().find(namePart) != string::npos) {
            result.push_back(_movies[i]);
        }
    }
    return result;
}
