#ifndef BUS_SHOWTIMEBUS_H
#define BUS_SHOWTIMEBUS_H

#include <string>
#include <vector>

#include "../dal/ShowtimeDAL.h"

/**
 * @class ShowtimeBUS
 * @brief Business Layer quản lý suất chiếu.
 */
class ShowtimeBUS {
private:
    ShowtimeDAL showtimeDal;

public:
    explicit ShowtimeBUS(ShowtimeDAL showtimeDal = ShowtimeDAL());

    std::vector<Showtime> getByMovie(const std::string& movieId);
    bool addShowtime(const Showtime& showtime);
    bool deleteShowtime(const std::string& id);
};

#endif // BUS_SHOWTIMEBUS_H
