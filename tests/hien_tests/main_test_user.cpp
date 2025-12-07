#include <iostream>
#include <vector>
#include <string>

// LƯU Ý: Sửa đường dẫn include tùy thuộc vào cấu trúc thư mục thật của bạn
// Nếu file này nằm ngang hàng với folder bus, dal, dto thì để như sau:
#include "../../bus/UserBUS.h"
#include "../../bus/AdminBUS.h"
#include "../../dto/User.h"

using namespace std;

int main() {
    UserBUS userBus;
    AdminBUS adminBus;

    cout << "========================================" << endl;
    cout << "      TEST MODULE TAI KHOAN (FULL)      " << endl;
    cout << "========================================" << endl;

    // --- BƯỚC 1: ĐĂNG KÝ USER MỚI ---
    string testUser = "nguoi_A";
    string testPass = "123456";
    
    cout << "\n[1] TEST DANG KY: " << testUser << endl;
    if (userBus.registerUser(testUser, testPass)) {
        cout << "-> Dang ky THANH CONG!" << endl;
    } else {
        cout << "-> User co the da ton tai (Bo qua buoc dang ky)." << endl;
    }

    // --- BƯỚC 2: TÌM ID CỦA USER VỪA TẠO ---
    // (Cần ID để Admin khóa, ta phải tìm trong danh sách)
    string targetID = "";
    vector<User*> listUsers = adminBus.getAllUsers();
    
    cout << "\n[2] DANH SACH USER HIEN CO:" << endl;
    for (User* u : listUsers) {
        cout << " - ID: " << u->getId() 
             << " | User: " << u->getUsername() 
             << " | Role: " << u->getRole() << endl;
             
        if (u->getUsername() == testUser) {
            targetID = u->getId();
        }
    }

    if (targetID == "") {
        cout << "Loi: Khong tim thay user " << testUser << " de test!" << endl;
        return 1;
    }

    // --- BƯỚC 3: ĐĂNG NHẬP THỬ (LÚC CHƯA BỊ KHÓA) ---
    cout << "\n[3] TEST LOGIN LAN 1 (Chua bi khoa): ";
    if (userBus.login(testUser, testPass) != nullptr) {
        cout << "-> Dang nhap THANH CONG (Dung)." << endl;
    } else {
        cout << "-> Dang nhap THAT BAI (Sai)." << endl;
    }
    userBus.logout(); // Đăng xuất ngay

    // --- BƯỚC 4: ADMIN KHÓA TÀI KHOẢN ---
    cout << "\n[4] ADMIN KHOA TAI KHOAN: " << targetID << endl;
    if (adminBus.lockUser(targetID)) {
        cout << "-> Khoa THANH CONG!" << endl;
    } else {
        cout << "-> Khoa THAT BAI!" << endl;
    }

    // --- BƯỚC 5: ĐĂNG NHẬP THỬ (KHI ĐÃ BỊ KHÓA) ---
    cout << "\n[5] TEST LOGIN LAN 2 (Da bi khoa): ";
    // Mong đợi kết quả là nullptr (thất bại)
    if (userBus.login(testUser, testPass) == nullptr) {
        cout << "-> He thong chan dang nhap (Dung logic)." << endl;
    } else {
        cout << "-> Van dang nhap duoc (SAI LOGIC)!" << endl;
    }

    // --- BƯỚC 6: ADMIN MỞ KHÓA ---
    cout << "\n[6] ADMIN MO KHOA TAI KHOAN: " << targetID << endl;
    if (adminBus.unlockUser(targetID)) {
        cout << "-> Mo khoa THANH CONG!" << endl;
    }

    // --- BƯỚC 7: ĐĂNG NHẬP LẠI ---
    cout << "\n[7] TEST LOGIN LAN 3 (Sau khi mo khoa): ";
    if (userBus.login(testUser, testPass) != nullptr) {
        cout << "-> Dang nhap THANH CONG (Dung)." << endl;
    } else {
        cout << "-> Dang nhap THAT BAI (Sai)." << endl;
    }

    cout << "\n========================================" << endl;
    cout << "           KET THUC TEST                " << endl;
    cout << "========================================" << endl;

    return 0;
}