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
    std::string timestamp;      ///< Thời gian thực tế (dd/mm/yyyy HH:MM:SS)
    std::string revenueType;    ///< Loại doanh thu: TICKET hoặc FOOD
    std::string relatedId;      ///< Mã liên quan (Mã phim nếu TICKET, Mã món ăn nếu FOOD)
    int amount;                 ///< Số tiền doanh thu
    std::string additionalInfo; ///< Thông tin bổ sung (tùy chọn)

public:
    /**
     * @brief Constructor mặc định.
     */
    Revenue();

    /**
     * @brief Constructor đầy đủ tham số.
     * @param id Mã bản ghi.
     * @param timestamp Thời gian thực (dd/mm/yyyy HH:MM:SS).
     * @param type Loại doanh thu (TICKET/FOOD).
     * @param relatedId Mã liên quan.
     * @param amount Số tiền.
     * @param info Thông tin bổ sung (mặc định rỗng).
     */
    Revenue(std::string id, std::string timestamp, std::string type, std::string relatedId, int amount, std::string info = "");

    // --- Các phương thức Getter ---
    
    /** @brief Lấy ID bản ghi. */
    std::string getId() const;
    
    /** @brief Lấy timestamp. */
    std::string getTimestamp() const;
    
    /** @brief Lấy loại doanh thu (TICKET/FOOD). */
    std::string getRevenueType() const;
    
    /** @brief Lấy mã liên quan. */
    std::string getRelatedId() const;
    
    /** @brief Lấy số tiền doanh thu. */
    int getAmount() const;
    
    /** @brief Lấy thông tin bổ sung. */
    std::string getAdditionalInfo() const;

    /**
     * @brief Lấy ngày từ timestamp (dd/mm/yyyy).
     * @return std::string Ngày.
     */
    std::string getDateOnly() const;

    /**
     * @brief Hiển thị chi tiết bản ghi ra màn hình.
     */
    void display() const;
};

#endif