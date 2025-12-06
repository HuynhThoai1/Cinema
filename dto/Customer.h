/**
 * @file Customer.h
 * @brief Định nghĩa lớp Customer (Khách hàng).
 */

#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_
#include "User.h"
#include <iostream>

using std::cout;

/**
 * @class Customer
 * @brief Lớp đại diện cho khách hàng mua vé, kế thừa từ User.
 */
class Customer: public User {
public:
    /**
     * @brief Constructor mặc định (Role mặc định là "Customer").
     */
    Customer();

    /**
     * @brief Constructor có tham số.
     * @param id Mã định danh.
     * @param username Tên đăng nhập.
     * @param password Mật khẩu.
     */
    Customer(string id, string username, string password);
    
    ~Customer();

    /** @brief Xem danh sách phim đang chiếu. */
    void viewMovies();

    /** @brief Xem lịch chiếu phim. */
    void viewShowtimes();

    /** @brief Thực hiện đặt vé. */
    void bookTicket();
};

#endif