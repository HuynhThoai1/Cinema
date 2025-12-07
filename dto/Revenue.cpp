#include "Revenue.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 1. Constructor mặc định
Revenue::Revenue() {
    this->id = "";
    this->date = "";
    this->movieId = "";
    this->ticketRevenue = 0;
    this->foodRevenue = 0;
}

// 2. Constructor đầy đủ tham số
Revenue::Revenue(string id, string date, string movieId, int tRev, int fRev) 
    : id(id), date(date), movieId(movieId), ticketRevenue(tRev), foodRevenue(fRev) {
}

// 3. Các hàm Getter
string Revenue::getDate() const {
    return this->date;
}

string Revenue::getMovieId() const {
    return this->movieId;
}

// 4. Tính tổng doanh thu
// Logic: Tổng = Tiền vé + Tiền đồ ăn
int Revenue::getTotalRevenue() const {
    return this->ticketRevenue + this->foodRevenue;
}

// 5. Hiển thị chi tiết
void Revenue::display() const {
    // Định dạng cột: ID(10) | Date(15) | MovieID(10) | ...
    cout << left << setw(10) << id 
         << setw(15) << date 
         << setw(10) << movieId 
         << " Ticket: " << setw(10) << ticketRevenue
         << " Food: " << setw(10) << foodRevenue
         << " => Total: " << getTotalRevenue() << endl;
}