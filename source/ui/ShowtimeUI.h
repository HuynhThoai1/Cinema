#ifndef SHOWTIME_UI_H
#define SHOWTIME_UI_H

#include "../bus/ShowtimeBUS.h"
#include "../dal/ShowtimeDAL.h"
#include "../dal/MovieDAL.h"

/**
 * @file ShowtimeUI.h
 * @brief UI console cho module Showtime, tách hành vi Admin và Customer.
 *
 * @details
 * - Customer: chỉ xem lịch chiếu (hiển thị tất cả suất chiếu).
 * - Admin: xem lịch chiếu + thêm/xóa suất chiếu + (tuỳ chọn) tìm theo MovieID.
 * - Mọi validate nghiệp vụ nằm trong ShowtimeBUS (movieId tồn tại, trùng lịch phòng+giờ, format datetime...).
 */

class ShowtimeUI {
private:
    /** @brief BUS xử lý nghiệp vụ suất chiếu. */
    ShowtimeBUS showtimeBUS;

    /** @brief Hiển thị toàn bộ suất chiếu (không tìm kiếm). */
    void showAllShowtimes();

    /** @brief (Tuỳ chọn) Tìm suất chiếu theo MovieID, tách riêng để rõ ràng tính năng. */
    void searchShowtimesByMovieId();

    /** @brief Admin thêm suất chiếu. */
    void addShowtime();

    /** @brief Admin xóa suất chiếu. */
    void deleteShowtime();

public:
    /**
     * @brief Khởi tạo ShowtimeUI với đường dẫn dữ liệu.
     * @param showtimesPath File showtimes (vd: data/Showtime.txt)
     * @param moviesPath File movies (vd: data/Movies.txt) để BUS validate movieId tồn tại
     */
    explicit ShowtimeUI(
        const std::string& showtimesPath = "../data/Showtime.txt",
        const std::string& moviesPath = "../data/Movies.txt"
    );

    /**
     * @brief Menu của Admin (xem tất cả, tìm theo movieId, thêm, xóa).
     */
    void runAdmin();

    /**
     * @brief Menu của Customer (xem tất cả lịch chiếu).
     */
    void runCustomer();

    /**
     * @brief Giữ tương thích: run() = Admin (theo yêu cầu bạn).
     */
    void run();
};

#endif
