/**
 * @file Revenue.h
 * @brief Định nghĩa lớp đối tượng Doanh thu (Data Transfer Object).
 */

#ifndef REVENUE_H
#define REVENUE_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * @class Revenue
 * @brief Lớp lưu trữ thông tin về một bản ghi doanh thu.
 * @details Bao gồm doanh thu từ vé và đồ ăn của một bộ phim trong một ngày cụ thể.
 */
class Revenue {
private:
    std::string id;             ///< Mã bản ghi doanh thu (Ví dụ: R01)
    std::string date;           ///< Ngày ghi nhận (dd/mm/yyyy)
    std::string movieId;        ///< Mã bộ phim
    int ticketRevenue;          ///< Doanh thu từ bán vé
    int foodRevenue;            ///< Doanh thu từ bán đồ ăn

public:
    /**
     * @brief Constructor mặc định.
     */
    Revenue();

    /**
     * @brief Constructor đầy đủ tham số.
     * @param id Mã bản ghi.
     * @param date Ngày tháng.
     * @param movieId Mã phim.
     * @param tRev Tiền vé.
     * @param fRev Tiền đồ ăn.
     */
    Revenue(std::string id, std::string date, std::string movieId, int tRev, int fRev);

    // --- Các phương thức Getter ---
    
    /** @brief Lấy ID bản ghi. */
    std::string getId() const;
    
    /** @brief Lấy ngày ghi nhận. */
    std::string getDate() const;
    
    /** @brief Lấy mã phim. */
    std::string getMovieId() const;
    
    /** @brief Lấy doanh thu vé. */
    int getTicketRevenue() const;
    
    /** @brief Lấy doanh thu đồ ăn. */
    int getFoodRevenue() const;

    /**
     * @brief Tính tổng doanh thu.
     * @return int Tổng của tiền vé và tiền đồ ăn.
     */
    int getTotalRevenue() const;

    /**
     * @brief Hiển thị chi tiết bản ghi ra màn hình.
     */
    void display() const;
};

#endif