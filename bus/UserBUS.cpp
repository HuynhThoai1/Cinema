#include "UserBUS.h"
#include "../utils/Validation.h" 

UserBUS::UserBUS() : DATA_FILE("../../data/Users.txt") {
    this->currentUser = nullptr;
    this->loadData();
}

UserBUS::UserBUS(const string& filename) : DATA_FILE(filename) {
    this->currentUser = nullptr;
    this->loadData();
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
    this->users = userDal.loadUsers(this->DATA_FILE);
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
    
    if (!Validation::isValidUsername(username)) {
        // In lỗi để người dùng biết (hoặc debug)
        cout << ">> Lỗi: Username Không hợp lệ (Phải từ 5-20 ký tự, không dấu, Không khoảng trắng)!\n";
        return false; // Trả về false -> Test sẽ PASS
    }

    // 2. Kiểm tra Password hợp lệ không
    if (!Validation::isValidPassword(password)) {
        cout << ">> Lỗi: Password quá yếu (Phải từ 6 ký tự trở lên)!\n";
        return false;
    }

    // 3. Kiểm tra username đã tồn tại chưa
    for (User* user : users) {
        if (user->getUsername() == username) {
            cout << "Lỗi: Username đã tồn tại!\n";
            return false;
        }
    }
    // 4. Tự động sinh ID mới (Ví dụ: U + so_thu_tu)
    string newId = "U" +  to_string(users.size() + 1);

    // 5. Tạo user mới (Mặc định là Customer)
    User* newUser = new Customer(newId, username, password);

    // 6. Thêm vào danh sách (RAM)
    users.push_back(newUser);

    // 7. Lưu xuống file (Ổ cứng)
    userDal.addUser(newUser, DATA_FILE);

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
                userDal.saveUsers(users, DATA_FILE);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}