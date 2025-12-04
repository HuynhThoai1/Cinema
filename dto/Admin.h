/**
 * @file Admin.h
 * @brief Định nghĩa lớp Admin (Quản trị viên).
 */

#ifndef _ADMIN_H_
#define _ADMIN_H_
#include "User.h"
#include <iostream>

using std::cout;

/**
 * @class Admin
 * @brief Lớp đại diện cho quản trị viên, kế thừa từ User.
 */
class Admin: public User {
public:
    /**
     * @brief Constructor mặc định (Role mặc định là "Admin").
     */
    Admin();

    /**
     * @brief Constructor có tham số.
     * @param id Mã định danh.
     * @param username Tên đăng nhập.
     * @param password Mật khẩu.
     */
    Admin(string id, string username, string password);
    
    ~Admin();

    /** @brief Chức năng quản lý phim (Thêm/Sửa/Xóa). */
    void manageMovies();

    /** @brief Chức năng quản lý suất chiếu. */
    void manageShowtimes();

    /** @brief Chức năng xem báo cáo doanh thu. */
    void viewRevenue();
};

#endif