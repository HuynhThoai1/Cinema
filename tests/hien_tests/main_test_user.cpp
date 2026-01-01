// #include "ui/Menu.h"

// int main() {
//     // Khởi chạy ứng dụng từ Menu chính
//     Menu appMenu;
//     appMenu.showMainMenu();
//     return 0;
// }

#include <iostream>
#include <fstream>
#include "../../bus/UserBUS.h"
#include "../../bus/AdminBUS.h"

using namespace std;

// --- CẤU HÌNH ---
const string TEST_FILE = "../../Users.txt";

// --- HÀM HỖ TRỢ ---
void printPass(string msg) {
    cout << "\033[1;32m[PASS] " << msg << "\033[0m\n";
}
void printFail(string msg) {
    cout << "\033[1;31m[FAIL] " << msg << "\033[0m\n";
}

// Hàm reset dữ liệu test về trạng thái ban đầu
void resetTestData() {
    ofstream file(TEST_FILE);
    // Dữ liệu mẫu chuẩn: ID | User | Pass | Role
    file << "U1|admin_root|123456|Admin\n";
    file << "U2|khach_a|123456|Customer\n";
    file << "U3|khach_bi_khoa|123456|Locked\n";
    file << "U4|khach_doi_pass|123456|Customer\n";
    file.close();
    cout << ">> Da reset du lieu test tai: " << TEST_FILE << "\n\n";
}

int main() {
    // 1. Chuẩn bị dữ liệu sạch
    resetTestData();
    
    // 2. Khởi tạo BUS với file test
    UserBUS userBus(TEST_FILE);
    AdminBUS adminBus(TEST_FILE); // Yêu cầu AdminBUS cũng phải hỗ trợ constructor filename

    cout << "==============================================\n";
    cout << "                 (FULL TEST)                  \n";
    cout << "==============================================\n";

    // ==========================================
    // PHẦN 1: KIỂM TRA ĐĂNG NHẬP (LOGIN)
    // ==========================================
    cout << "\n--- [1] TEST LOGIN ---\n";
    
    // 1.1 Login đúng
    if (userBus.login("admin_root", "123456") != nullptr) printPass("Admin login: OK");
    else printFail("Admin login: Thất bại");

    if (userBus.login("khach_a", "123456") != nullptr) printPass("Customer login: OK");
    else printFail("Customer login: Thất bại");

    // 1.2 Login sai pass
    if (userBus.login("khach_a", "sai_pass") == nullptr) printPass("Chặn sai pass: OK");
    else printFail("Lỗi: Sai pass vẫn vào được");

    // 1.3 Login user không tồn tại
    if (userBus.login("ma_ma_tong_quan", "123") == nullptr) printPass("Chặn user ao: OK");
    else printFail("Lỗi: User ảo vẫn vào được");

    // 1.4 Login tài khoản bị khóa (Locked)
    if (userBus.login("khach_bi_khoa", "123456") == nullptr) printPass("Chặn tài khoản Locked: OK");
    else printFail("Lỗi: Tài khoản Locked vẫn đăng nhập được!");

    // ==========================================
    // PHẦN 2: KIỂM TRA ĐĂNG KÝ (VALIDATION)
    // ==========================================
    cout << "\n--- [2] TEST REGISTER & VALIDATION ---\n";

    // 2.1 Username ngắn (< 5 ký tự)
    if (!userBus.registerUser("abc", "123456")) printPass("Chặn username ngắn: OK");
    else printFail("Lỗi: Username ngắn (<5) vẫn cho đăng ký");

    // 2.2 Username quá dài (> 20 ký tự)
    if (!userBus.registerUser("day_la_mot_cai_ten_rat_rat_la_dai", "123456")) printPass("Chặn username dài: OK");
    else printFail("Lỗi: Username dài (>20) vẫn cho đăng ký");

    // 2.3 Username chứa ký tự đặc biệt
    if (!userBus.registerUser("user@name", "123456")) printPass("Chặn ký tự đặc biệt (@): OK");
    else printFail("Lỗi: Username chứa ký tự đặc biệt vẫn cho đăng ký");

    // 2.4 Password yếu (< 6 ký tự)
    if (!userBus.registerUser("user_moi", "123")) printPass("Chặn password yếu: OK");
    else printFail("Lỗi: Password yếu (<6) vẫn cho đăng ký");

    // 2.5 Trùng Username
    if (!userBus.registerUser("khach_a", "123456")) printPass("Chặn trùng username: OK");
    else printFail("Lỗi: Username đã tồn tại vẫn cho đăng ký");

    // 2.6 Đăng ký hợp lệ
    if (userBus.registerUser("user_hop_le", "pass_xin_xo")) {
        printPass("Đăng ký hợp lệ: OK");
        // Kiểm tra lại bằng cách login luôn
        if (userBus.login("user_hop_le", "pass_xin_xo") != nullptr) printPass("-> Login được bằng tài khoản mới: OK");
        else printFail("-> Login tài khoản mới thất bại");
    } else printFail("Lỗi: Đăng ký hợp lệ bi chặn");

    // ==========================================
    // PHẦN 3: KIỂM TRA ĐỔI MẬT KHẨU
    // ==========================================
    cout << "\n--- [3] TEST ĐỔI MẬT KHẨU ---\n";
    // User U4: khach_doi_pass | 123456
    
    // 3.1 Đổi sai mật khẩu cũ
    if (!userBus.changePassword("U4", "pass_sai", "new_pass")) printPass("Chặn đổi pass (sai pass cũ): OK");
    else printFail("Lỗi: Sai pass cũ vẫn cho đổi");

    // 3.2 Đổi thành công
    if (userBus.changePassword("U4", "123456", "new_pass_123")) {
        printPass("đổi pass thành công: OK");
        // Login lại bằng pass mới
        if (userBus.login("khach_doi_pass", "new_pass_123") != nullptr) printPass("-> Login pass mới: OK");
        else printFail("-> Login pass mới thất bại");
    } else printFail("Lỗi: Đổi pass bị thất bại");

    // ==========================================
    // PHẦN 4: KIỂM TRA ADMIN (LOCK/UNLOCK)
    // ==========================================
    cout << "\n--- [4] TEST ADMIN ACTIONS ---\n";
    
    // 4.1 Khóa Admin (Không được phép)
    if (!adminBus.lockUser("U1")) printPass("Chặn khóa Admin: OK"); // U1 là Admin
    else printFail("Lỗi: Cho phép khóa Admin!");

    // 4.2 Khóa Customer (U2: khach_a)
    if (adminBus.lockUser("U2")) {
        printPass("Khóa Customer (U2): OK");
        // Kiểm tra xem U2 có login được không
        if (userBus.login("khach_a", "123456") == nullptr) printPass("-> U2 đã bị chặn đăng nhập: OK");
        else printFail("-> U2 bị khóa vẫn đăng nhập được!");
    } else printFail("Lỗi: Khóa Customer thất bại");

    // 4.3 Mở khóa Customer (U2)
    if (adminBus.unlockUser("U2")) {
        printPass("Mở khóa Customer (U2): OK");
        // Kiểm tra login lại
        if (userBus.login("khach_a", "123456") != nullptr) printPass("-> U2 đã đăng nhập lại được: OK");
        else printFail("-> U2 đã mở khóa vẫn không vào được!");
    } else printFail("Lỗi: Mở khóa thất bại");

    cout << "\n==============================================\n";
    cout << "           HOÀN TẤT KIỂM TRA                   \n";
    cout << "==============================================\n";

    return 0;
}