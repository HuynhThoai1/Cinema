#ifndef FOOD_UI_H
#define FOOD_UI_H

#include "../bus/FoodBUS.h" 
#include <iostream>

/**
 * @class FoodUI
 * @brief Lớp giao diện người dùng (Presentation Layer) cho quản lý thực phẩm.
 * * Lớp này chịu trách nhiệm hiển thị menu, nhận dữ liệu nhập từ bàn phím
 * và trình bày kết quả ra màn hình. Mọi yêu cầu xử lý sẽ được gửi tới tầng nghiệp vụ (FoodBUS).
 */
class FoodUI {
private:
    /** @brief Đối tượng xử lý nghiệp vụ thực phẩm để thực hiện các chức năng cốt lõi. */
    FoodBUS foodBus;

public:
    /**
     * @brief Khởi tạo đối tượng giao diện FoodUI.
     */
    FoodUI();

    /**
     * @brief Khởi động vòng lặp điều khiển chính của chức năng Food.
     * * Hiển thị menu chức năng và điều phối các lệnh thực thi dựa trên lựa chọn của người dùng.
     */
    void process();

    /**
     * @brief Hiển thị form nhập liệu để người dùng thêm món ăn mới.
     * * Thu thập ID, Tên và Giá từ Console.
     */
    void inputNewFood();

    /**
     * @brief Truy xuất và hiển thị danh sách tất cả các món ăn.
     * * Dữ liệu được định dạng dưới dạng cột để dễ quan sát.
     */
    void showAllFoods();

    /**
     * @brief Chức năng giả lập đặt hàng.
     * * Cho phép người dùng nhập nhiều mã món ăn và hiển thị tổng số tiền cần thanh toán.
     */
    void orderDemo();
};

#endif