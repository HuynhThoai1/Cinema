/**
 * @file Validation.h
 * @brief Lớp tiện ích kiểm tra tính hợp lệ của dữ liệu (Validation).
 */
#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>

using namespace std;

/**
 * @class Validation
 * @brief Cung cấp các phương thức static để validate dữ liệu nhập vào (Username, Password).
 * @details Sử dụng Regular Expression (Regex) để đảm bảo định dạng chính xác.
 */
class Validation {
public:
    /**
     * @brief Kiểm tra định dạng Username.
     * @param username Chuỗi tên đăng nhập cần kiểm tra.
     * @return true Nếu hợp lệ (5-20 ký tự, chỉ chứa chữ, số, gạch dưới).
     * @return false Nếu vi phạm định dạng.
     */
    static bool isValidUsername(const string& username);

    /**
     * @brief Kiểm tra độ mạnh của Password.
     * @param password Chuỗi mật khẩu cần kiểm tra.
     * @return true Nếu mật khẩu đủ mạnh (tối thiểu 6 ký tự).
     * @return false Nếu mật khẩu quá ngắn.
     */
    static bool isValidPassword(const string& password);
};

#endif