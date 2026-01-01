#ifndef BUS_SHOWTIMEBUS_H
#define BUS_SHOWTIMEBUS_H

#include <string>
#include <vector>
using std::string;
using std::vector;
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
    vector<Showtime> _showtimes;
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
        /**
     * @brief Tải danh sách suất chiếu từ file
     */
    void load(const string& filename);

    /**
     * @brief Lưu danh sách suất chiếu hiện tại xuống file
     */
    void save(const string& filename) const;
        /**
     * @brief Tìm suất chiếu theo id
     * @return con trỏ tới Showtime trong vector, hoặc nullptr nếu không thấy
     *
     * Lưu ý: con trỏ chỉ dùng tạm thời, không lưu giữ lâu dài.
     */
    Showtime* findById(const string& id);



};

#endif // BUS_SHOWTIMEBUS_H
