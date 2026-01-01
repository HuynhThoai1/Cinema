#ifndef MOVIE_UI_H
#define MOVIE_UI_H

#include "../bus/MovieBUS.h"

/**
 * @file MovieUI.h
 * @brief Khai báo lớp giao diện (UI) cho module Movie.
 *
 * @details
 * - UI chỉ đảm nhiệm nhập/xuất (cin/cout) và điều hướng menu.
 * - Không xử lý logic nghiệp vụ trực tiếp; mọi thao tác đều gọi sang MovieBUS.
 */

/**
 * @class MovieUI
 * @brief Lớp giao diện console cho các chức năng Movie (xem/thêm/sửa/xóa).
 */
class MovieUI {
private:
    /** @brief Đối tượng nghiệp vụ quản lý phim. */
    MovieBUS movieBUS;


    /**
     * @brief Nhập thông tin và gọi BUS để thêm phim mới.
     */
    void addMovie();

    /**
     * @brief Nhập thông tin và gọi BUS để cập nhật phim.
     */
    void updateMovie();

    /**
     * @brief Nhập ID và gọi BUS để xóa phim.
     */
    void deleteMovie();

public:
    /**
     * @brief Hiển thị danh sách phim hiện có.
     */
    void showAll();

    /**
     * @brief Chạy menu quản lý phim.
     */
    void run();
};

#endif
