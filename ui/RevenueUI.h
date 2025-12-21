#ifndef REVENUE_UI_H
#define REVENUE_UI_H

#include "../bus/RevenueBUS.h"
#include <iostream>

/**
 * @class RevenueUI
 * @brief Lớp giao diện người dùng (Presentation Layer) cho quản lý doanh thu.
 * * Lớp này cung cấp các phương thức để người dùng tương tác với dữ liệu doanh thu,
 * bao gồm nhập dữ liệu mới và xem báo cáo. Mọi yêu cầu xử lý logic sẽ được
 * chuyển tiếp tới lớp RevenueBUS.
 */
class RevenueUI {
private:
    /** @brief Đối tượng xử lý nghiệp vụ doanh thu. */
    RevenueBUS revBus;

public:
    /**
     * @brief Khởi tạo đối tượng giao diện RevenueUI.
     */
    RevenueUI();

    /**
     * @brief Khởi động vòng lặp menu điều khiển chính của chức năng Doanh thu.
     * * Hiển thị các lựa chọn như nhập doanh thu mới, xem toàn bộ danh sách 
     * hoặc quay lại menu chính của chương trình.
     */
    void process();

    /**
     * @brief Giao diện nhận dữ liệu doanh thu từ bàn phím.
     * * Thu thập các thông tin như ngày tháng, mã phim, tiền vé và tiền đồ ăn,
     * sau đó chuyển dữ liệu cho tầng BUS để thực hiện lưu trữ.
     */
    void inputRevenue();

    /**
     * @brief Hiển thị danh sách tất cả các bản ghi doanh thu dưới dạng bảng.
     * * Truy xuất dữ liệu từ tầng nghiệp vụ và định dạng đầu ra trên Console 
     * sao cho người dùng dễ dàng theo dõi các cột thông tin.
     */
    void showAllRevenue();
};

#endif