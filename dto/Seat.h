/**
 * @file Seat.h
 * @brief Định nghĩa lớp trừu tượng (Abstract Class) cho Ghế/Hàng ghế.
 *
 * Class này đóng vai trò là lớp cha (Base Class) cho các loại ghế cụ thể
 * (như ghế thường, ghế VIP). Nó quản lý thông tin chung của một hàng ghế
 * và danh sách các vị trí đã được đặt trong hàng đó.
 * @date 2023-10-27
 */

#ifndef SEAT_H
#define SEAT_H

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

/**
 * @class Seat
 * @brief Lớp trừu tượng đại diện cho một nhóm ghế (thường là một hàng).
 *
 * Class này chứa phương thức thuần ảo calculatePrice(), bắt buộc các lớp con
 * (như NormalSeat, VIPSeat) phải tự định nghĩa lại cách tính giá.
 */
class Seat {
private:
    string _rowId;          ///< Mã hàng ghế (ví dụ: "A", "B", "C").
    string _room;           ///< Tên hoặc mã phòng chiếu chứa hàng ghế này.
    string _type;           ///< Loại ghế (VD: "NORMAL", "VIP"). Dùng để phân loại hiển thị.
    int _basePrice;         ///< Giá cơ bản của loại ghế này.
    vector<string> _seatBooked; ///< Danh sách các mã ghế (số ghế) trong hàng này đã bị đặt.

public:
    /**
     * @brief Constructor khởi tạo một hàng ghế.
     *
     * @param rowId Mã hàng (VD: "A").
     * @param room Tên phòng (VD: "Cinema 01").
     * @param type Loại ghế (VD: "VIP").
     * @param price Giá gốc của ghế.
     */
    Seat(string rowId, string room, string type, int price) {
        this->_rowId = rowId;
        this->_room = room;
        this->_type = type;
        this->_basePrice = price;
    }

    // --- Getters (Truy xuất thông tin) ---

    /**
     * @brief Lấy mã hàng ghế.
     * @return string Mã hàng (VD: "A").
     */
    string getRowId() const { return _rowId; }

    /**
     * @brief Lấy tên phòng chiếu.
     * @return string Tên phòng.
     */
    string getRoom() const { return _room; }

    /**
     * @brief Lấy loại ghế.
     * @return string Loại ghế ("NORMAL" hoặc "VIP").
     */
    string getType() const { return _type; }

    /**
     * @brief Lấy giá cơ bản.
     * @return int Giá tiền.
     */
    int getBasePrice() const { return _basePrice; }

    /**
     * @brief Lấy danh sách các ghế đã đặt trong hàng này.
     * @return vector<string> Vector chứa mã số các ghế đã đặt.
     */
    vector<string> getSeatBooked() const { return _seatBooked; }

    // --- Business Logic Methods ---

    /**
     * @brief Đánh dấu một ghế trong hàng là "Đã đặt".
     *
     * Thêm mã ghế vào danh sách _seatBooked.
     * @param seatId Mã số ghế cần đặt (VD: "1", "2").
     */
    void addBookedSeat(const string& seatId) {
        _seatBooked.push_back(seatId);
    }

    /**
     * @brief Kiểm tra xem một ghế cụ thể trong hàng có trống không.
     *
     * Duyệt qua danh sách đã đặt để kiểm tra sự tồn tại của seatId.
     *
     * @param seatId Mã số ghế cần kiểm tra (VD: "5").
     * @return true Nếu ghế chưa có ai đặt.
     * @return false Nếu ghế đã nằm trong danh sách đặt.
     */
    bool isAvailable(const string& seatId) const {
        for (const string& bookedSeat : _seatBooked) {
            if (bookedSeat == seatId) {
                return false; // Ghế đã được đặt
            }
        }
        return true; // Ghế còn trống
    }

    /**
     * @brief Tính giá vé cuối cùng (Phương thức thuần ảo).
     *
     * Đây là hàm Virtual, các lớp con (NormalSeat, VIPSeat) BẮT BUỘC phải override
     * để tính ra giá tiền cụ thể (ví dụ: ghế VIP + phụ thu, ghế đôi x2...).
     *
     * @return int Giá vé sau cùng.
     */
    virtual int calculatePrice() const = 0;
};

#endif // SEAT_H