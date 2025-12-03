#include "UserDAL.h"

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// --- 1. Load Users: Đọc file và tạo object ---
vector<User*> UserDAL::loadUsers() {
    vector<User*> users;
    std::ifstream file("data/Users.txt");

    if (!file.is_open()) {
        cout << "Lỗi: Không thể mở file data/Users.txt để đọc!\n";
        return users;
    }

    string line;
    while(getline(file, line)) {
        if (line.empty()) continue;

        vector<string> data = split(line, '|'); // Ở đây ví dụ dấu ngăn cách là '|'

        // Kiểm tra dữ liệu có đủ 4 trường không (id|user|pass|role)
        if (data.size() >= 4) {
            string id = data[0];
            string username = data[1];
            string password = data[2];
            string role = data[3];

            User* user = nullptr;

            if (role == "Admin") {
                user = new Admin(id, username, password);
            } else {
                user = new Customer(id, username, password);
            }

            user->setRole(role);

            users.push_back(user);
        }
    }
    file.close();
    return users;
}

// --- 2. Save Users: ghi đè toàn bộ danh sách ---
void UserDAL::saveUsers(const vector<User*>& users) {
    std:: ofstream file("data/Users.txt", std::ios::trunc);// ios::trunc là xóa hết cũ ghi mới
    if (!file.is_open()) {
        cout << "Lỗi: Không thể mở file data/Users.txt để ghi!\n";
        return;
    }
    
    for (User* user : users) {
        file << user->getId() << "|" 
             << user->getUsername() << "|" 
             << user->getPassword() << "|" 
             << user->getRole() << "\n";
    }

    file.close();
}

// --- 3. Add User: Thêm 1 người vào cuối file ---
void UserDAL::addUser(User* user) {
    // ios::app = append (ghi nối tiếp vào cuối file)
    std::ofstream file("data/Users.txt", std::ios::app); 

    if (!file.is_open()) {
        cout << "Lỗi: Không thể mở file data/Users.txt để thêm mới!\n";
        return;
    }

    file << user->getId() << "|" 
         << user->getUsername() << "|" 
         << user->getPassword() << "|" 
         << user->getRole() << "\n";

    file.close();
}