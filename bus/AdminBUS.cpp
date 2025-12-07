#include "AdminBUS.h"

AdminBUS::AdminBUS() {
    this->loadUsers();
}

AdminBUS::~AdminBUS() {
    for (User* user : users) {
        delete user;
    }
    users.clear();
}

void AdminBUS::loadUsers() {

    for (User* user : users) {
        delete user;
    }
    users.clear();

    // Load lại từ file
    this->users = userDal.loadUsers(DATA_FILE);
}

vector<User*> AdminBUS::getAllUsers() {
    this->loadUsers();
    return this->users;
}

bool AdminBUS::lockUser(string userId) {
    for (User* user : users) {
        if (user->getId() == userId) {
            // Không được khóa chính mình (Admin)
            if (user->getRole() == "Admin") {
                cout << "Lỗi: Không thể khóa Admin!\n";
                return false;
            }

            user->setRole("Locked"); // Đổi role thành Locked
            userDal.saveUsers(users, DATA_FILE); // Lưu ngay xuống file
            return true;
        }
    }
    return false; // Không tìm thấy ID
}

bool AdminBUS::unlockUser(string userId) {
    for (User* user : users) {
        if (user->getId() == userId) {
            if (user->getRole() == "Locked") {
                user->setRole("Customer");
                userDal.saveUsers(users, DATA_FILE);
                return true;
            }
        }
    }
    return false;
}

bool AdminBUS::removeUser(string userId) {
    for (int i = 0; i < users.size(); ++i) {
        if (users[i]->getId() == userId) {
            if (users[i]->getRole() == "Admin") {
                cout << "Lỗi: Không thể xóa Admin\n";
                return false;
            }

            delete users[i];
            users.erase(users.begin() + i);

            userDal.saveUsers(users, DATA_FILE);
            return true;
        }
    }
    return false;
}