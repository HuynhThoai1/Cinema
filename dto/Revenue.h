<<<<<<< HEAD
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
=======
#include "Revenue.h"

/**
 * @brief Constructor mặc định.
 * Khởi tạo các giá trị chuỗi rỗng và các giá trị số bằng 0.
 */
Revenue::Revenue() {
    this->id = "";
    this->date = "";
    this->movieId = "";
    this->ticketRevenue = 0;
    this->foodRevenue = 0;
}

/**
 * @brief Constructor tham số.
 * Gán các giá trị cụ thể cho từng thuộc tính của bản ghi doanh thu.
 */
Revenue::Revenue(string id, string date, string movieId, int tRev, int fRev) {
    this->id = id;
    this->date = date;
    this->movieId = movieId;
    this->ticketRevenue = tRev;
    this->foodRevenue = fRev;
}

// --- Các phương thức Getter ---

string Revenue::getId() const { return id; }
string Revenue::getDate() const { return date; }
string Revenue::getMovieId() const { return movieId; }
int Revenue::getTicketRevenue() const { return ticketRevenue; }
int Revenue::getFoodRevenue() const { return foodRevenue; }

/**
 * @brief Tính toán tổng doanh thu.
 * @return Giá trị bằng tổng của doanh thu vé và doanh thu thực phẩm.
 */
int Revenue::getTotalRevenue() const {
    return ticketRevenue + foodRevenue;
}

/**
 * @brief Hiển thị thông tin doanh thu.
 * Sử dụng thư viện iomanip để định dạng bảng dữ liệu đẹp mắt trên Console.
 */
void Revenue::display() const {
    cout << left << setw(10) << id 
         << setw(15) << date 
         << setw(15) << movieId 
         << setw(15) << ticketRevenue 
         << setw(15) << foodRevenue 
         << setw(15) << getTotalRevenue() << endl;
}
>>>>>>> 0226781a988cf730ca830fe9989d4de76c815c93
