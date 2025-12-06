#include "Admin.h"

// --- 1. Constructor ---
Admin::Admin(): User() {
    this->setRole("Admin");
}

Admin::Admin(string id, string username, string password)
    : User(id, username, password, "Admin") {}

// --- 2. Destructor ---
Admin::~Admin() {
    // Do nothing
}

// ---3. Method ---
void Admin::manageMovies() {
    cout << "[Admin] đang quản lý phim (Thêm/Xóa/Sửa)...\n";
    // Sau này sẽ kết nối với MovieBUS
}

void Admin::manageShowtimes() {
    cout << "[Admin] đang quản lý xuất chiếu...\n";
    // Sau này sẽ kết nối với ShowtimeBUS
}

void Admin::viewRevenue() {
    cout << "[Admin] đang xem báo cáo danh thu...\n";
    // Sau này sẽ kết nối với RevenueBUS
}