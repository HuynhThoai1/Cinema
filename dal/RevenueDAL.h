/**
 * @file Revenue_DAL.h
 * @brief Khai báo lớp RevenueDAL dùng để quản lý truy cập dữ liệu doanh thu.
 * @details File này cung cấp các phương thức để thao tác với danh sách doanh thu như đọc, ghi và lấy dữ liệu.
 */

#ifndef REVENUE_DAL_H
#define REVENUE_DAL_H

#include <vector>
#include "../dto/Revenue.h"

// Sử dụng using std::vector thay vì using namespace std để tránh xung đột tên trong header
using std::vector; 

/**
 * @class RevenueDAL
 * @brief Lớp Data Access Layer (DAL) quản lý các thao tác dữ liệu cho đối tượng Revenue.
 * * Lớp này chịu trách nhiệm tương tác với nguồn dữ liệu (file/database) 
 * để thực hiện các nghiệp vụ liên quan đến doanh thu.
 */
class RevenueDAL {
private:
    /**
     * @brief Vector lưu trữ danh sách các đối tượng Revenue trong bộ nhớ.
     */
    vector<Revenue> listRevenue;

public:
    /**
     * @brief Tải dữ liệu doanh thu từ nguồn lưu trữ.
     * * Hàm này đọc dữ liệu (thường là từ file text hoặc binary), 
     * parse dữ liệu và lưu vào biến thành viên listRevenue.
     */
    void loadRevenues();

    /**
     * @brief Thêm một bản ghi doanh thu mới.
     * * Hàm này sẽ thêm một đối tượng Revenue vào danh sách listRevenue
     * và thường sẽ thực hiện ghi cập nhật xuống file lưu trữ.
     * * @param rev Đối tượng Revenue cần thêm (truyền tham chiếu hằng `const &` để tránh copy dữ liệu, giúp tối ưu hiệu năng).
     */
    void addRevenue(const Revenue& rev);

    /**
     * @brief Lấy danh sách toàn bộ doanh thu.
     * * @return vector<Revenue> Bản sao danh sách các đối tượng Revenue hiện có.
     */
    vector<Revenue> getList() const;
};

#endif