#ifndef REVENUE_H
#define REVENUE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @class Revenue
 * @brief Lớp đối tượng dữ liệu (DTO) đại diện cho một bản ghi doanh thu.
 * * Lớp này lưu trữ thông tin chi tiết về doanh thu của một bộ phim trong một ngày nhất định,
 * bao gồm tiền vé và tiền dịch vụ ăn uống.
 */
class Revenue {
private:
    /** @brief Mã định danh duy nhất của bản ghi doanh thu (ví dụ: R01, R02). */
    string id;
    
    /** @brief Ngày ghi nhận doanh thu (định dạng chuỗi, ví dụ: "2023-10-25"). */
    string date;
    
    /** @brief Mã định danh của bộ phim liên quan. */
    string movieId;
    
    /** @brief Doanh thu thu được từ việc bán vé. */
    int ticketRevenue;
    
    /** @brief Doanh thu thu được từ việc bán đồ ăn và thức uống. */
    int foodRevenue;

public:
    /**
     * @brief Khởi tạo mặc định cho đối tượng Revenue.
     */
    Revenue();

    /**
     * @brief Khởi tạo đối tượng Revenue với đầy đủ thông số.
     * @param id Mã bản ghi.
     * @param date Ngày ghi nhận.
     * @param movieId Mã phim.
     * @param tRev Doanh thu vé.
     * @param fRev Doanh thu đồ ăn.
     */
    Revenue(string id, string date, string movieId, int tRev, int fRev);

    /** @brief Lấy mã định danh bản ghi. @return string mã ID. */
    string getId() const;

    /** @brief Lấy ngày ghi nhận doanh thu. @return string ngày tháng. */
    string getDate() const;

    /** @brief Lấy mã phim của bản ghi này. @return string mã phim. */
    string getMovieId() const;

    /** @brief Lấy doanh thu từ vé. @return int số tiền vé. */
    int getTicketRevenue() const;

    /** @brief Lấy doanh thu từ đồ ăn. @return int số tiền đồ ăn. */
    int getFoodRevenue() const;

    /**
     * @brief Tính tổng doanh thu của bản ghi.
     * * Phương thức này cộng dồn doanh thu vé và doanh thu đồ ăn.
     * @return int Tổng số tiền doanh thu.
     */
    int getTotalRevenue() const;

    /**
     * @brief Hiển thị thông tin doanh thu ra màn hình console.
     * * Dữ liệu được định dạng theo dạng bảng hoặc dòng để dễ quan sát.
     */
    void display() const;
};

#endif