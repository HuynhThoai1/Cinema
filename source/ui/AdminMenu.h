/**
 * @file AdminMenu.h
 * @brief Giao diện Dashboard quản lý dành cho Admin.
 */
#ifndef _ADMIN_MENU_H_
#define _ADMIN_MENU_H_
#include <iomanip>

#include "../bus/AdminBUS.h"
#include "../bus/MovieBUS.h"
#include "../bus/ShowtimeBUS.h"
#include "../bus/RevenueBUS.h"

using std::cout, std::cin;
using std::setw, std::left, std::right;

/**
 * @class AdminMenu
 * @brief Lớp điều hướng và hiển thị các chức năng quản trị.
 * @details Kết nối với các BUS: AdminBUS (User), MovieBUS, ShowtimeBUS, RevenueBUS.
 */
class AdminMenu {
private:
    MovieBUS movieBus;       ///< Xử lý nghiệp vụ phim
    ShowtimeBUS showtimeBus; ///< Xử lý nghiệp vụ suất chiếu
    RevenueBUS revenueBus;   ///< Xử lý nghiệp vụ doanh thu
    AdminBUS adminBus;       ///< Xử lý nghiệp vụ tài khoản (Khóa/Mở/Xem)

    /**
     * @brief Menu con: Quản lý người dùng.
     * @details Hiển thị danh sách user, thực hiện khóa/mở khóa tài khoản.
     *          Được tách ra để code gọn gàng hơn.
     */
    void manageUsersMenu();
public:
    /**
     * @brief Constructor khởi tạo các đối tượng BUS cần thiết.
     */
    AdminMenu();

    /**
     * @brief Hiển thị Dashboard chính của Admin.
     * @details Chứa vòng lặp chính để điều hướng sang các menu con.
     */
    void show();
};

#endif