#include "UserBUS.h"

UserBUS::UserBUS() {
    this->currentUser = nullptr;
    this->loadData(); // Tự động tải dữ liệu khi khởi tạo BUS
}

UserBUS::~UserBUS() {
    for (auto user : users) {
        delete user;
    }
    users.clear();
}

void UserBUS::loadData() {
    for (User* user : users) {
        delete user;
    }
    users.clear();
    this->users = userDal.loadUsers();
}

User* UserBUS::login(string username, string password) {
    this->loadData();

    for (User* user : users) {
        // Kiểm tra username và password
        if (user->getUsername() == username && user->checkPassword(password)) {
            if (user->getRole() == "Locked") {
                cout << "Tài khoản của bạn đã bị khóa! Vui lòng liên hệ Admin\n";
                return nullptr;
            }
            this->currentUser = user;
            return user;
        }
    }
    return nullptr;
}

bool UserBUS::registerUser(string username, string password) {
    this->loadData(); 
    
    // 1. Kiểm tra username đã tồn tại chưa
    for (User* user : users) {
        if (user->getUsername() == username) {
            cout << "Lỗi: Username đã tồn tại!\n";
            return false;
        }
    }
    // 2. Tự động sinh ID mới (Ví dụ: U + so_thu_tu)
    string newId = "U" +  to_string(users.size() + 1);

    // 3. Tạo user mới (Mặc định là Customer)
    User* newUser = new Customer(newId, username, password);

    // 4. Thêm vào danh sách (RAM)
    users.push_back(newUser);

    // 5. Lưu xuống file (Ổ cứng)
    userDal.addUser(newUser);

    return true;
}

User* UserBUS::getCurrentUser() {
    return this->currentUser;
}

void UserBUS::logout() {
    this->currentUser = nullptr;
}

bool UserBUS::changePassword(string id, string oldPw, string newPw) {
    for (User* user : users) {
        if (user->getId() == id) {
            // Kiểm tra mật khẩu cũ
            if (user->checkPassword(oldPw)) {
                user->setPassword(newPw);
                userDal.saveUsers(users);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}