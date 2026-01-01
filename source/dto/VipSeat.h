/**
 * @file VipSeat.h
 * @brief Định nghĩa lớp Ghế VIP (VipSeat).
 *
 * Lớp này kế thừa từ lớp trừu tượng Seat, đại diện cho các hàng ghế VIP
 * với mức giá hoặc cách tính tiền đặc biệt.
 * @date 2023-10-27
 */

#ifndef VIP_SEAT_H
#define VIP_SEAT_H

#include "Seat.h"

/**
 * @class VipSeat
 * @brief Lớp cụ thể (Concrete Class) cho loại ghế VIP.
 *
 * Thiết lập loại ghế mặc định là "VIP" và triển khai logic tính giá riêng.
 */
class VipSeat : public Seat {
public:
    /**
     * @brief Constructor khởi tạo ghế VIP.
     *
     * Gọi constructor của lớp cha (Seat) với tham số type được cố định là "VIP".
     *
     * @param rowId Mã hàng ghế (VD: "H", "K").
     * @param room Tên phòng chiếu.
     * @param price Giá cơ bản cho ghế VIP.
     */
    VipSeat(string rowId, string room, int price) : Seat(rowId, room, "VIP", price) {}

    /**
     * @brief Tính giá vé cuối cùng cho ghế VIP.
     *
     * Ghi đè (Override) phương thức thuần ảo từ lớp cha.
     * Hiện tại trả về giá cơ bản, nhưng có thể mở rộng để cộng thêm phụ phí dịch vụ
     * hoặc nhân hệ số giá tại đây.
     *
     * @return int Giá vé của ghế VIP.
     */
    int calculatePrice() const override {
        // Có thể mở rộng logic: return getBasePrice() + 15000; (Phụ thu)
        return getBasePrice();
    }
};

#endif // VIP_SEAT_H