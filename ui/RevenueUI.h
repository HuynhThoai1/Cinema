/**
 * @file RevenueUI.h
 * @brief Giao diện Console cho chức năng quản lý Doanh thu.
 */

#ifndef REVENUE_UI_H
#define REVENUE_UI_H

#include "../bus/RevenueBUS.h"

/**
 * @class RevenueUI
 * @brief Lớp hiển thị menu và báo cáo doanh thu.
 */
class RevenueUI {
private:
    RevenueBUS revBus; ///< Đối tượng nghiệp vụ

public:
    /**
     * @brief Constructor.
     */
    RevenueUI();

    /**
     * @brief Vòng lặp chính xử lý menu Doanh thu.
     */
    void process();

    /**
     * @brief Màn hình nhập liệu doanh thu hằng ngày.
     */
    void inputRevenue();

    /**
     * @brief Hiển thị bảng báo cáo doanh thu tổng hợp.
     */
    void showAllRevenue();
};

#endif