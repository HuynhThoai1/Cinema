#ifndef BUS_MOVIEBUS_H
#define BUS_MOVIEBUS_H

#include <string>
#include <vector>

#include "../dto/Movie.h"
#include "../dal/MovieDAL.h"
#include "../dal/ShowtimeDAL.h"

/**
 * @class MovieBUS
 * @brief Business Layer quản lý phim.
 */
class MovieBUS {
private:
    MovieDAL movieDal;
    ShowtimeDAL showtimeDal;

public:
    explicit MovieBUS(
        MovieDAL movieDal = MovieDAL(),
        ShowtimeDAL showtimeDal = ShowtimeDAL()
    );

    std::vector<Movie> getAll();

    // Edge cases:
    // - chặn id rỗng / field rỗng / duration invalid
    // - chặn trùng id
    bool addMovie(const Movie& movie);

    // Edge cases:
    // - không tồn tại -> false
    // - validate dữ liệu trước khi lưu
    bool updateMovie(const Movie& movie);

    // Edge cases:
    // - không tồn tại -> false
    // - nếu movie còn showtime -> false (không cho xóa)
    bool deleteMovie(const std::string& id);
};

#endif // BUS_MOVIEBUS_H
