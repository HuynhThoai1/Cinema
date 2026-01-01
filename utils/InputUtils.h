/**
 * @file InputUtils.h
 * @brief Tiện ích xử lý nhập liệu an toàn.
 */
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class InputUtils {
public:
    /**
     * @brief Nhập một số nguyên từ bàn phím.
     * @details Hàm này sẽ lặp lại mãi cho đến khi người dùng nhập đúng số.
     *          Nó tự động xử lý việc xóa bộ nhớ đệm và thông báo lỗi.
     * @param message Dòng thông báo nhắc người dùng (VD: "Moi chon: ").
     * @return int Số nguyên hợp lệ người dùng vừa nhập.
     */
    static int readInt(const string& message);

    /**
     * @brief Hỏi người dùng Yes/No.
     * @details Chỉ chấp nhận 'y' hoặc 'n' (không phân biệt hoa thường).
     * @param message Thông báo (VD: "Ban co chac? (y/n): ").
     * @return char 'y' hoặc 'n'.
     */
    static char readYesNo(const string& message);
};

#endif