/**
 * @file CustomerMenu.h
 * @brief Giao diện chức năng dành cho Khách hàng.
 */
#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include <iostream>
#include "../dto/User.h"
#include "../bus/MovieBUS.h"
#include "MovieUI.h"
// #include "../bus/BookingFacade.h"

/**
 * @class CustomerMenu
 * @brief Lớp hiển thị menu cho khách hàng (Xem phim, đặt vé).
 */
class CustomerMenu {
private:
    //BookingFacade bookingFacade;  ///< Facade pattern xử lý đặt vé phức tạp
    MovieBUS movieBus;              ///< Lấy danh sách phim hiển thị
    User* currentUser;               ///< Người dùng hiện tại (Khách hàng)
public:
    CustomerMenu();

    /**
     * @brief Hiển thị menu chính của Khách hàng.
     * @details Bao gồm các chức năng: Xem danh sách phim, Đặt vé, Xem lịch sử.
     */
    void show();
    void setCurrentUser(User* user);
};

#endif