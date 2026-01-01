/**
 * @file FoodUI.h
 * @brief Giao diện Console cho chức năng quản lý Món ăn.
 */

#ifndef FOOD_UI_H
#define FOOD_UI_H

#include "../bus/FoodBUS.h"
#include "../bus/RevenueBUS.h"  // [MỚI] Để ghi nhận doanh thu tự động 

/**
 * @class FoodUI
 * @brief Lớp hiển thị menu và xử lý nhập liệu người dùng cho món ăn.
 */
class FoodUI {
private:
    FoodBUS foodBus;       ///< Đối tượng nghiệp vụ
    RevenueBUS revenueBus; ///< [MỚI] Để ghi nhận doanh thu

public:
    /**
     * @brief Constructor.
     */
    FoodUI();

    /**
     * @brief Menu quản lý món ăn cho Admin.
     */
    void adminMenu();

    /**
     * @brief Menu mua thức ăn cho Customer.
     */
    void customerMenu();

    /**
     * @brief Màn hình nhập thông tin món ăn mới.
     */
    void inputNewFood();

    /**
     * @brief Cập nhật thông tin món ăn.
     */
    void updateFood();

    /**
     * @brief Xóa món ăn.
     */
    void deleteFood();

    /**
     * @brief Hiển thị bảng danh sách món ăn.
     */
    void showAllFoods();

    /**
     * @brief Chức năng mua thức ăn cho khách hàng.
     */
    void purchaseFood();
};

#endif