#ifndef BUS_SHOWTIMEBUS_H
#define BUS_SHOWTIMEBUS_H

#include <string>
#include <vector>

#include "../dal/ShowtimeDAL.h"
#include "../dal/MovieDAL.h"

/**
 * @class ShowtimeBUS
 * @brief Business Layer quản lý suất chiếu.
 */
class ShowtimeBUS {
private:
    ShowtimeDAL showtimeDal;
    MovieDAL movieDal;

public:
    explicit ShowtimeBUS(
        ShowtimeDAL showtimeDal = ShowtimeDAL(),
        MovieDAL movieDal = MovieDAL()
    );

    std::vector<Showtime> getByMovie(const std::string& movieId);

    // Edge cases:
    // - id/movieId/room/startTime rỗng -> false
    // - movieId không tồn tại -> false
    // - trùng showtimeId -> false
    // - trùng phòng + thời gian (đụng lịch) -> false
    bool addShowtime(const Showtime& showtime);

    bool deleteShowtime(const std::string& id);
};

#endif // BUS_SHOWTIMEBUS_H
