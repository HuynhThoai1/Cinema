#ifndef DAL_SHOWTIMEDAL_H
#define DAL_SHOWTIMEDAL_H

#include <string>
#include <vector>

#include "dto/Showtime.h"

/**
 * @class ShowtimeDAL
 * @brief Data Access Layer cho Showtime (đọc/ghi Showtime.txt).
 */
class ShowtimeDAL {
private:
    std::string filePath;

public:
    explicit ShowtimeDAL(std::string filePath = "Showtime.txt");

    std::vector<Showtime> loadShowtimes();
    void saveShowtimes(const std::vector<Showtime>& showtimes);
};

#endif // DAL_SHOWTIMEDAL_H
