#ifndef REVENUE_BUS_H
#define REVENUE_BUS_H

#include "../dal/RevenueDAL.h"
#include <vector>
#include <string>

/**
 * @class RevenueBUS
 * @brief Lớp xử lý nghiệp vụ cho quản lý doanh thu.
 * * Lớp này chịu trách nhiệm điều phối các hoạt động liên quan đến doanh thu 
 * như tự động tạo mã bản ghi, lọc dữ liệu theo thời gian và kết nối với 
 * tầng truy cập dữ liệu (RevenueDAL).
 */
class RevenueBUS {
private:
    /** @brief Đối tượng tương tác trực tiếp với cơ sở dữ liệu hoặc file doanh thu. */
    RevenueDAL revenueDal;

public:
    /**
     * @brief Khởi tạo đối tượng xử lý nghiệp vụ doanh thu.
     * * Thực hiện việc nạp dữ liệu từ nguồn vào bộ nhớ tạm thông qua RevenueDAL.
     */
    RevenueBUS();

    /**
     * @brief Thêm một bản ghi doanh thu mới vào hệ thống.
     * * Phương thức này bao gồm logic nghiệp vụ để tự động cấp phát mã ID 
     * theo định dạng quy chuẩn (ví dụ: R01, R02...) trước khi lưu.
     * * @param date Ngày phát sinh doanh thu (định dạng chuỗi).
     * @param movieId Mã phim tương ứng với doanh thu.
     * @param ticketAmount Số tiền thu được từ bán vé.
     * @param foodAmount Số tiền thu được từ bán đồ ăn/thức uống.
     */
    void addRevenueRecord(string date, string movieId, int ticketAmount, int foodAmount);

    /**
     * @brief Lấy toàn bộ danh sách lịch sử doanh thu.
     * @return vector<Revenue> Danh sách các đối tượng Revenue đã được lưu trữ.
     */
    vector<Revenue> getAll();

    /**
     * @brief Tìm kiếm các bản ghi doanh thu theo một ngày cụ thể.
     * @param date Chuỗi ngày cần tìm kiếm.
     * @return vector<Revenue> Danh sách các bản ghi trùng khớp với ngày được cung cấp.
     */
    vector<Revenue> getByDate(string date);
};

#endif