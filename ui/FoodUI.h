/**
 * @file FoodUI.h
 * @brief Giao diện Console cho chức năng quản lý Món ăn.
 */

#ifndef FOOD_UI_H
#define FOOD_UI_H

#include "../bus/FoodBUS.h" 

/**
 * @class FoodUI
 * @brief Lớp hiển thị menu và xử lý nhập liệu người dùng cho món ăn.
 */
class FoodUI {
private:
    FoodBUS foodBus; ///< Đối tượng nghiệp vụ

public:
    /**
     * @brief Constructor.
     */
    FoodUI();

    /**
     * @brief Vòng lặp chính xử lý menu Món ăn.
     */
    void process();

    /**
     * @brief Màn hình nhập thông tin món ăn mới.
     */
    void inputNewFood();

    /**
     * @brief Hiển thị bảng danh sách món ăn.
     */
    void showAllFoods();

    /**
     * @brief Chức năng demo tính tiền đơn hàng.
     */
    void orderDemo();
};

#endif