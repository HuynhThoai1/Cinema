/**
 * @file NormalSeat.h
 * @brief Định nghĩa lớp Ghế Thường (NormalSeat).
 *
 * Lớp này đại diện cho các hàng ghế tiêu chuẩn trong rạp chiếu phim,
 * không có phụ phí hoặc dịch vụ đặc biệt đi kèm.
 * @date 2023-10-27
 */

#ifndef NORMAL_SEAT_H
#define NORMAL_SEAT_H

#include "Seat.h"

/**
 * @class NormalSeat
 * @brief Lớp cụ thể (Concrete Class) cho loại ghế Thường.
 *
 * Kế thừa từ lớp Seat, thiết lập loại ghế là "NORMAL" và sử dụng giá cơ bản.
 */
class NormalSeat : public Seat {
public:
    /**
     * @brief Constructor khởi tạo ghế Thường.
     *
     * @param rowId Mã hàng ghế (VD: "A", "B").
     * @param room Tên phòng chiếu.
     * @param price Giá cơ bản cho ghế thường.
     */
    NormalSeat(string rowId, string room, int price) : Seat(rowId, room, "NORMAL", price) {}

    /**
     * @brief Tính giá vé cho ghế thường.
     *
     * Ghi đè phương thức thuần ảo từ lớp cha.
     * Đối với ghế thường, giá vé chính là giá gốc đã niêm yết, không cộng thêm phụ phí.
     *
     * @return int Giá vé (bằng với BasePrice).
     */
    int calculatePrice() const override {
        return getBasePrice(); 
    }
};

#endif // NORMAL_SEAT_H