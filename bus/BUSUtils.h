/**
 * @file BUSUtils.h
 * @brief Tệp tiêu đề chứa các hàm tiện ích nghiệp vụ (Business Logic Utilities).
 * @details Cung cấp các công cụ xử lý logic hiển thị, đặc biệt là định dạng tiền tệ (Currency Formatting)
 * để hiển thị lên giao diện console.
 */

#ifndef _BUSUTILS_H_
#define _BUSUTILS_H_

#include <string>

/**
 * @class CurrencyFormat
 * @brief Lớp tiện ích hỗ trợ định dạng số tiền.
 * @details Chứa các phương thức tĩnh để chuyển đổi số nguyên thô sang dạng chuỗi tiền tệ dễ đọc
 * (thường dùng định dạng phân cách hàng nghìn bằng dấu chấm hoặc phẩy).
 */
class CurrencyFormat {
public:
    /**
     * @brief Định dạng một số nguyên lớn thành chuỗi tiền tệ có dấu phân cách.
     * @details Hàm sẽ chèn dấu chấm (.) sau mỗi 3 chữ số tính từ phải sang trái.
     * Ví dụ: 
     * - Input: 100000 -> Output: "100.000"
     * - Input: 10000000 -> Output: "10.000.000"
     * * @param amount Số tiền cần định dạng (kiểu long long để chứa được số tiền lớn).
     * @return std::string Chuỗi tiền tệ đã được định dạng đẹp mắt.
     */
    static std::string formatCurrency(long long amount);
};

#endif