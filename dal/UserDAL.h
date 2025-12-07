/**
 * @file UserDAL.h
 * @brief Tầng truy cập dữ liệu (Data Access Layer) cho User.
 * @details Chịu trách nhiệm đọc và ghi file data/Users.txt.
 */

#ifndef _USER_DAL_H
#define _USER_DAL_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../dto/User.h"
#include "../dto/Admin.h"
#include "../dto/Customer.h"

using std::vector, std::string;
using std::istringstream;
using std::cout, std::ofstream, std::ifstream;

class UserDAL {
public:
    /**
     * @brief Đọc danh sách người dùng từ file text.
     * @return vector<User*> Danh sách chứa con trỏ đến các đối tượng User (Admin/Customer).
     * @param filename Đường dẫn tới file dữ liệu (VD: "data/Users.txt")
     */
    vector<User*> loadUsers(const string& filename);

    /**
     * @brief Ghi đè toàn bộ danh sách người dùng vào file.
     * @param users Danh sách user cần lưu.
     * @warning Hành động này sẽ xóa nội dung cũ của file và ghi mới (Truncate).
     * @param filename Đường dẫn file.
     */
    void saveUsers(const vector<User*>& users, const string& filename);

    /**
     * @brief Thêm một người dùng mới vào cuối file (Append).
     * @param user Con trỏ đến người dùng cần thêm.
     * @param filename Đường dẫn file.
     */
    void addUser(User* user, const string& filename);
};
#endif