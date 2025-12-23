#ifndef SHOWTIME_UI_H
#define SHOWTIME_UI_H

#include "../bus/ShowtimeBUS.h"

/**
 * @file ShowtimeUI.h
 * @brief Khai báo lớp giao diện (UI) cho module Showtime.
 *
 * @details
 * - UI chỉ đảm nhiệm nhập/xuất và điều hướng menu.
 * - Validate nghiệp vụ (movieId tồn tại, trùng lịch phòng+giờ, format datetime...)
 *   nằm trong ShowtimeBUS.
 */

/**
 * @class ShowtimeUI
 * @brief Lớp giao diện console cho các chức năng Showtime (xem/thêm/xóa).
 */
class ShowtimeUI {
private:
    /**
     * @brief Đối tượng nghiệp vụ quản lý suất chiếu.
     * @note Ở dự án của bạn đang khởi tạo DAL trực tiếp với "data/Showtime.txt".
     */
    ShowtimeBUS showtimeBUS{ShowtimeDAL("data/Showtime.txt")};

    /** @brief Hiển thị suất chiếu theo movieId. */
    void showByMovie();

    /** @brief Nhập thông tin và gọi BUS để thêm suất chiếu. */
    void addShowtime();

    /** @brief Nhập id và gọi BUS để xóa suất chiếu. */
    void deleteShowtime();

public:
    /** @brief Chạy menu quản lý suất chiếu. */
    void run();
};

#endif
