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