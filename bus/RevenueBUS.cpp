#include "RevenueBUS.h"
<<<<<<< HEAD
using namespace std;
=======

>>>>>>> 0226781a988cf730ca830fe9989d4de76c815c93
/**
 * @brief Khởi tạo đối tượng RevenueBUS.
 * * Khi khởi tạo, lớp sẽ tự động gọi phương thức của RevenueDAL để nạp 
 * toàn bộ dữ liệu doanh thu từ nguồn lưu trữ vào bộ nhớ.
 */
RevenueBUS::RevenueBUS() {
    revenueDal.loadRevenues();
}

/**
 * @brief Thêm một bản ghi doanh thu mới với cơ chế tự động tạo mã ID.
 * * **Quy trình xử lý:**
 * 1. Lấy số lượng bản ghi hiện có để tính toán mã số tiếp theo.
 * 2. Định dạng ID theo mẫu: "R0x" (nếu < 10) hoặc "Rx" (nếu >= 10).
 * 3. Khởi tạo đối tượng Revenue và yêu cầu DAL lưu trữ.
 * * @param date Ngày ghi nhận doanh thu.
 * @param movieId Mã phim tương ứng.
 * @param ticketAmount Tiền bán vé.
 * @param foodAmount Tiền bán đồ ăn.
 */
void RevenueBUS::addRevenueRecord(string date, string movieId, int ticketAmount, int foodAmount) {
    // Logic tạo ID tự động đơn giản (R + size)
    int size = revenueDal.getList().size();
    string newId = "R" + to_string(size + 1);
    
    // Nếu size < 9 thì thêm số 0 cho đẹp (R01, R02...)
    if(size < 9) newId = "R0" + to_string(size + 1);

    Revenue r(newId, date, movieId, ticketAmount, foodAmount);
    revenueDal.addRevenue(r);
}

/**
 * @brief Lấy toàn bộ danh sách bản ghi doanh thu.
 * @return Vector chứa tất cả các đối tượng Revenue.
 */
vector<Revenue> RevenueBUS::getAll() {
    return revenueDal.getList();
}

/**
 * @brief Tìm kiếm và lọc danh sách doanh thu theo một ngày cụ thể.
 * @param date Chuỗi ngày cần lọc (định dạng nên khớp với dữ liệu đã lưu).
 * @return Vector chứa các bản ghi doanh thu trùng khớp với ngày truyền vào.
 */
vector<Revenue> RevenueBUS::getByDate(string date) {
    vector<Revenue> result;
    for (const auto& r : revenueDal.getList()) {
        if (r.getDate() == date) {
            result.push_back(r);
        }
    }
    return result;
}