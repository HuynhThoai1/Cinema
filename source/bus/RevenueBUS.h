/**
 * @file RevenueBUS.h
 * @brief Lớp xử lý nghiệp vụ cho Doanh thu.
 */

#ifndef REVENUE_BUS_H
#define REVENUE_BUS_H

#include "../dal/RevenueDAL.h"
#include <vector>
#include <string>
#include <ctime>     // Để lấy thời gian thực
#include <sstream>
#include <iomanip>

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
     * @deprecated Phương thức cũ để tương thích ngược.
     */
    void addRevenueRecord(std::string date, std::string movieId, int ticketAmount, int foodAmount);

    /**
     * @brief Ghi nhận doanh thu tự động với timestamp hiện tại.
     * @param type Loại doanh thu (TICKET hoặc FOOD).
     * @param relatedId Mã liên quan (Mã phim nếu TICKET, Mã món ăn nếu FOOD).
     * @param amount Số tiền.
     * @param info Thông tin bổ sung (tùy chọn).
     */
    void recordRevenue(std::string type, std::string relatedId, int amount, std::string info = "");

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

private:
    /**
     * @brief Lấy timestamp hiện tại theo định dạng dd/mm/yyyy HH:MM:SS.
     * @return std::string Chuỗi thới gian.
     */
    std::string getCurrentTimestamp();
};

#endif