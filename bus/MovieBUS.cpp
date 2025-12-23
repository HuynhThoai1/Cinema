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
    : movieDal(std::move(movieDal)), showtimeDal(std::move(showtimeDal)) {}

std::vector<Movie> MovieBUS::getAll() {
    auto movies = movieDal.loadMovies();

    // Edge: loại bỏ record rác (id rỗng)
    movies.erase(
        std::remove_if(movies.begin(), movies.end(),
                       [](const Movie& m) { return m.getId().empty(); }),
        movies.end()
    );
    return movies;
}

bool MovieBUS::addMovie(const Movie& movie) {
    // Validate dữ liệu cơ bản
    if (isBlank(movie.getId()) || isBlank(movie.getTitle()) || isBlank(movie.getGenre())) return false;
    if (movie.getDuration() <= 0 || movie.getDuration() > 500) return false;

    auto movies = movieDal.loadMovies();

    // Edge: trùng ID
    auto it = std::find_if(movies.begin(), movies.end(),
                           [&](const Movie& m) { return m.getId() == movie.getId(); });
    if (it != movies.end()) return false;

    movies.push_back(movie);
    movieDal.saveMovies(movies);
    return true;
}

bool MovieBUS::updateMovie(const Movie& movie) {
    // Validate dữ liệu cơ bản
    if (isBlank(movie.getId()) || isBlank(movie.getTitle()) || isBlank(movie.getGenre())) return false;
    if (movie.getDuration() <= 0 || movie.getDuration() > 500) return false;

    auto movies = movieDal.loadMovies();

    // Edge: phải tồn tại mới update được
    auto it = std::find_if(movies.begin(), movies.end(),
                           [&](const Movie& m) { return m.getId() == movie.getId(); });
    if (it == movies.end()) return false;

    *it = movie;
    movieDal.saveMovies(movies);
    return true;
}

bool MovieBUS::deleteMovie(const std::string& id) {
    if (isBlank(id)) return false;

    // Edge: Không cho xóa Movie nếu còn Showtime thuộc Movie đó
    auto showtimes = showtimeDal.loadShowtimes();
    auto hasShowtime = std::any_of(showtimes.begin(), showtimes.end(),
                                   [&](const Showtime& s) { return s.getMovieId() == id; });
    if (hasShowtime) return false;

    auto movies = movieDal.loadMovies();
    auto before = movies.size();

    movies.erase(
        std::remove_if(movies.begin(), movies.end(),
                       [&](const Movie& m) { return m.getId() == id; }),
        movies.end()
    );

    // Edge: không tìm thấy ID
    if (movies.size() == before) return false;

    movieDal.saveMovies(movies);
    return true;
}
