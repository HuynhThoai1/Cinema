#include "Revenue.h"

/**
 * @brief Khởi tạo mặc định cho đối tượng Revenue.
 * Thiết lập các chuỗi rỗng và giá trị số bằng 0.
 */
Revenue::Revenue() {
    this->id = "";
    this->date = "";
    this->movieId = "";
    this->ticketRevenue = 0;
    this->foodRevenue = 0;
}

/**
 * @brief Khởi tạo đối tượng Revenue với đầy đủ thông số.
 * @param id Mã bản ghi doanh thu.
 * @param date Ngày ghi nhận.
 * @param movieId Mã phim.
 * @param tRev Doanh thu vé.
 * @param fRev Doanh thu đồ ăn.
 */
Revenue::Revenue(string id, string date, string movieId, int tRev, int fRev) 
    : id(id), date(date), movieId(movieId), ticketRevenue(tRev), foodRevenue(fRev) {
}

/** @brief Lấy mã định danh bản ghi. @return string mã ID. */
string Revenue::getId() const {
    return this->id;
}

/** @brief Lấy ngày ghi nhận doanh thu. @return string ngày tháng. */
string Revenue::getDate() const {
    return this->date;
}

/** @brief Lấy mã phim liên quan. @return string mã phim. */
string Revenue::getMovieId() const {
    return this->movieId;
}

/** @brief Lấy doanh thu từ bán vé. @return int số tiền vé. */
int Revenue::getTicketRevenue() const {
    return this->ticketRevenue;
}

/** @brief Lấy doanh thu từ đồ ăn/thức uống. @return int số tiền đồ ăn. */
int Revenue::getFoodRevenue() const {
    return this->foodRevenue;
}

/**
 * @brief Tính tổng doanh thu của bản ghi.
 * @return Tổng giá trị của vé và đồ ăn (ticketRevenue + foodRevenue).
 */
int Revenue::getTotalRevenue() const {
    return this->ticketRevenue + this->foodRevenue;
}

/**
 * @brief Hiển thị chi tiết bản ghi doanh thu theo định dạng hàng ngang.
 * Sử dụng setw để căn lề các cột dữ liệu thẳng hàng trên Console.
 */
void Revenue::display() const {
    cout << left << setw(10) << id 
         << setw(15) << date 
         << setw(10) << movieId 
         << " Ticket: " << setw(10) << ticketRevenue
         << " Food: " << setw(10) << foodRevenue
         << " => Total: " << getTotalRevenue() << endl;
}