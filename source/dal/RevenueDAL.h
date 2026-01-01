/**
 * @file RevenueDAL.h
 * @brief Lớp truy cập dữ liệu cho Doanh thu.
 */

#ifndef REVENUE_DAL_H
#define REVENUE_DAL_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../dto/Revenue.h"

/**
 * @class RevenueDAL
 * @brief Quản lý việc Đọc/Ghi dữ liệu doanh thu từ file văn bản.
 */
class RevenueDAL {
private:
    std::vector<Revenue> listRevenue; ///< Danh sách doanh thu trong RAM
    const std::string FILE_NAME = "../data/Revenue.txt"; ///< Đường dẫn file

public:
    /**
     * @brief Nạp dữ liệu doanh thu từ file text.
     */
    void loadRevenues();

    /**
     * @brief Ghi đè danh sách doanh thu hiện tại xuống file.
     */
    void saveRevenues();

    /**
     * @brief Thêm bản ghi doanh thu mới.
     * @param rev Đối tượng doanh thu cần lưu.
     */
    void addRevenue(const Revenue& rev);

    /**
     * @brief Lấy toàn bộ danh sách doanh thu.
     * @return std::vector<Revenue> Vector chứa các bản ghi.
     */
    std::vector<Revenue> getList() const;
};

#endif