#ifndef _SHOWTIMEBUS_H_
#define _SHOWTIMEBUS_H_

#include <vector>
#include <string>
#include "../dal/ShowtimeDAL.h"

using std::string;
using std::vector;

/**
 * @class ShowtimeBUS
 * @brief Lớp nghiệp vụ cho suất chiếu phim (Business Layer)
 *
 * Quản lý danh sách suất chiếu: load/save từ file, thêm/xóa/sửa,
 * lọc suất chiếu theo mã phim,...
 */
class ShowtimeBUS {
private:
    vector<Showtime> _showtimes;

public:
    ShowtimeBUS() = default;

    /**
     * @brief Tải danh sách suất chiếu từ file
     */
    void load(const string& filename);

    /**
     * @brief Lưu danh sách suất chiếu hiện tại xuống file
     */
    void save(const string& filename) const;

    /**
     * @brief Lấy toàn bộ danh sách suất chiếu
     */
    vector<Showtime> getAll() const;

    /**
     * @brief Thêm một suất chiếu mới
     * @return true nếu thêm thành công, false nếu trùng id
     */
    bool addShowtime(const Showtime& s);

    /**
     * @brief Xóa suất chiếu theo id
     */
    bool deleteShowtime(const string& id);

    /**
     * @brief Cập nhật suất chiếu theo id (match theo s.getId())
     */
    bool updateShowtime(const Showtime& s);

    /**
     * @brief Tìm suất chiếu theo id
     * @return con trỏ tới Showtime trong vector, hoặc nullptr nếu không thấy
     *
     * Lưu ý: con trỏ chỉ dùng tạm thời, không lưu giữ lâu dài.
     */
    Showtime* findById(const string& id);

    /**
     * @brief Lấy danh sách suất chiếu theo mã phim
     */
    vector<Showtime> getByMovieId(const string& movieId) const;
};

#endif
