/**
 * @file Revenue_BUS.h
 * @brief Khai báo lớp RevenueBUS xử lý nghiệp vụ liên quan đến doanh thu.
 * @details File này cung cấp các phương thức để ghi nhận doanh thu mới (vé, đồ ăn) 
 * và trích xuất báo cáo doanh thu theo tiêu chí (ngày, phim).
 */

#ifndef REVENUE_BUS_H
#define REVENUE_BUS_H

#include "../dal/RevenueDAL.h"
#include <vector>
#include <string>

// Sử dụng using riêng lẻ để tránh ô nhiễm namespace
using std::vector;
using std::string;

/**
 * @class RevenueBUS
 * @brief Lớp Business Logic Layer (BUS) quản lý luồng tiền tệ.
 * * Lớp này xử lý logic cộng dồn doanh thu và lọc dữ liệu báo cáo
 * trước khi trả về cho giao diện người dùng.
 */
class RevenueBUS {
private:
    /**
     * @brief Đối tượng RevenueDAL để tương tác với cơ sở dữ liệu/file.
     */
    RevenueDAL revenueDal;

public:
    /**
     * @brief Ghi nhận doanh thu từ bán vé.
     * * Hàm này nhận thông tin ngày và số tiền, sau đó gọi DAL để cập nhật
     * hoặc tạo mới bản ghi doanh thu cho ngày đó.
     * * @param date Ngày phát sinh doanh thu (định dạng chuỗi).
     * @param amount Số tiền bán vé cần cộng thêm vào.
     */
    void addTicketRevenue(string date, int amount);

    /**
     * @brief Ghi nhận doanh thu từ bán đồ ăn/nước uống.
     * * Tương tự như bán vé, hàm này cộng dồn doanh thu thực phẩm vào bản ghi của ngày tương ứng.
     * * @param date Ngày phát sinh doanh thu.
     * @param amount Số tiền bán đồ ăn cần cộng thêm.
     */
    void addFoodRevenue(string date, int amount);

    /**
     * @brief Lấy báo cáo doanh thu của một ngày cụ thể.
     * * Tìm kiếm trong danh sách doanh thu để trả về đối tượng Revenue trùng khớp với ngày yêu cầu.
     * * @param date Ngày cần xem báo cáo.
     * @return Revenue Đối tượng chứa thông tin doanh thu của ngày đó.
     */
    Revenue getRevenueByDate(string date);

    /**
     * @brief Lấy danh sách doanh thu liên quan đến một bộ phim.
     * * Hàm này lọc danh sách tổng để tìm ra các bản ghi doanh thu
     * mà bộ phim này có được chiếu.
     * * @param movieId Mã định danh của bộ phim.
     * @return vector<Revenue> Danh sách các bản ghi doanh thu liên quan đến phim này.
     */
    vector<Revenue> getRevenueByMovie(string movieId);
};

#endif