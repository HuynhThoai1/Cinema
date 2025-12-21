#include "RevenueUI.h"
#include <iomanip>

/**
 * @brief Constructor mặc định của lớp RevenueUI.
 */
RevenueUI::RevenueUI() {}

/**
 * @brief Quản lý vòng lặp menu cho phân hệ doanh thu.
 * * Cung cấp các tùy chọn để xem báo cáo tổng quát hoặc nhập dữ liệu doanh thu mới.
 * * Kết nối trực tiếp với các phương thức hiển thị và nhập liệu bên trong lớp.
 */
void RevenueUI::process() {
    int choice;
    do {
        cout << "\n--- QUAN LY DOANH THU ---\n";
        cout << "1. Xem bao cao\n2. Nhap doanh thu\n0. Quay lai\nChon: ";
        cin >> choice; cin.ignore();
        switch(choice) {
            case 1: showAllRevenue(); break;
            case 2: inputRevenue(); break;
        }
    } while(choice != 0);
}

/**
 * @brief Giao diện nhập thông tin doanh thu phim và dịch vụ.
 * * Người dùng nhập ngày, mã phim và các khoản thu.
 * * Logic tạo ID tự động sẽ được thực hiện tại tầng RevenueBUS khi gọi `addRevenueRecord`.
 */
void RevenueUI::inputRevenue() {
    string date, movie; int tick, food;
    cout << "Ngay (dd/mm/yyyy): "; getline(cin, date);
    cout << "Ma phim: "; getline(cin, movie);
    cout << "Tien ve: "; cin >> tick;
    cout << "Tien do an: "; cin >> food; cin.ignore();
    revBus.addRevenueRecord(date, movie, tick, food);
    cout << ">> Da luu!\n";
}

/**
 * @brief Hiển thị bảng thống kê doanh thu chi tiết.
 * * Sử dụng `std::setw` để căn chỉnh các cột: ID, Ngày, Mã Phim, Vé, Đồ ăn và Tổng cộng.
 * * Tổng cộng mỗi dòng được tính toán động thông qua phương thức `r.getTotalRevenue()`.
 */
void RevenueUI::showAllRevenue() {
    vector<Revenue> list = revBus.getAll();
    cout << "--------------------------------------------------------\n";
    cout << left << setw(8) << "ID" << setw(12) << "NGAY" << setw(8) << "PHIM" 
         << setw(10) << "VE" << setw(10) << "DO AN" << "TONG\n";
    for(auto& r : list) {
        cout << left << setw(8) << r.getId() << setw(12) << r.getDate() 
             << setw(8) << r.getMovieId() << setw(10) << r.getTicketRevenue() 
             << setw(10) << r.getFoodRevenue() << r.getTotalRevenue() << endl;
    }
    cout << "--------------------------------------------------------\n";
}