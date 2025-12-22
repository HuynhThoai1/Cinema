/**
 * @file RevenueBUS.h
 * @brief Lớp xử lý nghiệp vụ cho Doanh thu.
 */

#ifndef REVENUE_BUS_H
#define REVENUE_BUS_H

#include "../dal/RevenueDAL.h"
#include <vector>
#include <string>

/**
 * @class RevenueBUS
 * @brief Xử lý logic tạo mã, tính toán và lọc doanh thu.
 */
class RevenueBUS {
private:
    RevenueDAL revenueDal; ///< Đối tượng thao tác dữ liệu

public:
    /**
     * @brief Khởi tạo và nạp dữ liệu doanh thu.
     */
    RevenueBUS();

    /**
     * @brief Tạo bản ghi doanh thu mới (Tự động sinh ID).
     * @details ID sẽ được tạo tự động dạng R01, R02... dựa trên số lượng hiện có.
     * @param date Ngày tháng.
     * @param movieId Mã phim.
     * @param ticketAmount Tiền vé.
     * @param foodAmount Tiền đồ ăn.
     */
    void addRevenueRecord(std::string date, std::string movieId, int ticketAmount, int foodAmount);

    /**
     * @brief Lấy tất cả bản ghi doanh thu.
     */
    std::vector<Revenue> getAll();

    /**
     * @brief Lọc doanh thu theo ngày cụ thể.
     * @param date Chuỗi ngày cần tìm.
     * @return std::vector<Revenue> Danh sách kết quả.
     */
    std::vector<Revenue> getByDate(std::string date);
};

#endif