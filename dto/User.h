/**
 * @file User.h
 * @brief Định nghĩa lớp cơ sở User đại diện cho người dùng hệ thống.
 */

#ifndef _USER_H_
#define _USER_H_
#include <string>

using std::string;

/**
 * @class User
 * @brief Lớp cha lưu trữ thông tin chung của Admin và Customer.
 */
class User {
private:
    string _id;         ///< Mã định danh người dùng (VD: U1, U2)
    string _username;   ///< Tên đăng nhập
    string _password;   ///< Mật khẩu
    string _role;       ///< Vai trò (Admin, Customer, Locked)

public:
    /**
     * @brief Constructor mặc định.
     */
    User();

    /**
     * @brief Constructor đầy đủ tham số.
     * @param id Mã định danh.
     * @param username Tên đăng nhập.
     * @param password Mật khẩu.
     * @param role Vai trò.
     */
    User(string id, string username, string password, string role);

    /**
     * @brief Destructor ảo (Virtual Destructor).
     * @note Cần thiết để đảm bảo hủy đúng đối tượng con (Admin/Customer) khi dùng đa hình.
     */
    virtual ~User();

    // --- Getters ---
    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getRole() const;

    // --- Setters ---
    void setId(string id);
    void setUsername(string username);
    void setPassword(string password);
    void setRole(string role);

    /**
     * @brief Kiểm tra mật khẩu đầu vào có khớp không.
     * @param inputPw Mật khẩu người dùng nhập vào.
     * @return true nếu khớp, false nếu sai.
     */
    bool checkPassword(string inputPw) const;
};
#endif