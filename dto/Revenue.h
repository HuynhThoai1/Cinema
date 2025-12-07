/**
 * @file Revenue.h
 * @brief Khai báo lớp Revenue (DTO) đại diện cho thông tin doanh thu.
 * @details File này định nghĩa cấu trúc dữ liệu doanh thu bao gồm tiền vé và tiền đồ ăn
 * theo từng suất chiếu hoặc ngày (tùy nghiệp vụ), cùng các phương thức tính toán tổng.
 */

#ifndef REVENUE_H
#define REVENUE_H

#include <string>
#include <iostream>
#include <iomanip>

using std::string;

/**
 * @class Revenue
 * @brief Lớp đại diện cho một bản ghi doanh thu.
 * * Lớp này lưu trữ thông tin về doanh thu bán vé và bán đồ ăn
 * gắn liền với một bộ phim và ngày cụ thể.
 */
class Revenue {
private:
    /** @brief Mã định danh của bản ghi doanh thu. */
    string id;

    /** @brief Ngày ghi nhận doanh thu (định dạng chuỗi, ví dụ: DD/MM/YYYY). */
    string date;

    /** @brief Mã của bộ phim liên quan đến doanh thu này. */
    string movieId;

    /** @brief Doanh thu từ bán vé (đơn vị tiền tệ). */
    int ticketRevenue;

    /** @brief Doanh thu từ bán đồ ăn/nước uống (đơn vị tiền tệ). */
    int foodRevenue;

public:
    /**
     * @brief Constructor mặc định.
     * * Khởi tạo đối tượng Revenue với các giá trị rỗng hoặc bằng 0.
     */
    Revenue();

    /**
     * @brief Constructor đầy đủ tham số.
     * * @param id Mã bản ghi.
     * @param date Ngày tháng.
     * @param movieId Mã bộ phim.
     * @param tRev Doanh thu vé (Ticket Revenue).
     * @param fRev Doanh thu đồ ăn (Food Revenue).
     */
    Revenue(string id, string date, string movieId, int tRev, int fRev);

    /**
     * @brief Lấy ngày ghi nhận doanh thu.
     * * @return string Chuỗi ngày tháng.
     */
    string getDate() const;

    /**
     * @brief Lấy mã bộ phim.
     * * @return string ID của phim.
     */
    string getMovieId() const;

    /**
     * @brief Tính tổng doanh thu.
     * * Hàm này cộng doanh thu vé và doanh thu đồ ăn để trả về tổng số tiền thu được.
     * * @return int Tổng doanh thu (ticketRevenue + foodRevenue).
     */
    int getTotalRevenue() const;

    /**
     * @brief Hiển thị chi tiết doanh thu.
     * * In ra màn hình các thông tin: Ngày, Phim, Tiền vé, Tiền đồ ăn và Tổng cộng
     * theo định dạng bảng (sử dụng setw).
     */
    void display() const;
};

#endif