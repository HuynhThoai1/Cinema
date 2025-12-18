/**
 * @file BookingFacade.h
 * @brief Định nghĩa lớp Facade quản lý quy trình đặt vé.
 *
 * Áp dụng Design Pattern: Facade.
 * Mục đích: Cung cấp một giao diện đơn giản hóa (Simplified Interface) cho tầng UI.
 * Thay vì UI phải gọi lần lượt SeatBUS (check chỗ), MovieBUS (lấy tin), TicketBUS (lưu vé),
 * UI chỉ cần gọi một hàm duy nhất trong lớp này.
 * @date 2023-10-27
 */

#ifndef BOOKING_FACADE_H
#define BOOKING_FACADE_H

#include <string>
#include <iostream>

// Include các BUS thành phần (Subsystems)
#include "TicketBUS.h"
#include "SeatBUS.h"
#include "ShowtimeBUS.h"
#include "MovieBUS.h"

using std::string;

/**
 * @class BookingFacade
 * @brief Lớp mặt tiền (Facade) điều phối toàn bộ quy trình đặt vé.
 *
 * Lớp này chịu trách nhiệm "nhạc trưởng", điều phối sự tương tác giữa các BUS con:
 * 1. Kiểm tra ghế trống (SeatBUS).
 * 2. Lấy thông tin phim/giá vé (ShowtimeBUS, MovieBUS).
 * 3. Khóa ghế và tạo vé (SeatBUS, TicketBUS).
 */
class BookingFacade {
private:
    // --- Các hệ thống con (Subsystems) ---
    TicketBUS ticketBus;        ///< Xử lý việc tạo và lưu vé.
    SeatBUS seatBus;            ///< Xử lý trạng thái ghế (Check/Book).
    ShowtimeBUS showtimeBus;    ///< Xử lý thông tin suất chiếu (để lấy giờ, ngày, giá).
    MovieBUS movieBus;          ///< Xử lý thông tin phim (để lấy tên phim).
/**
     * @brief Hàm phụ trợ: Tính giá vé dựa trên hàng ghế.
     * Logic này được chuyển từ Class Seat cũ sang đây.
     * VD: Hàng A, B, C giá 50k. Hàng D trở đi giá 80k.
     */
    string calculatePrice(string seatId);
public:
    /**
     * @brief Constructor khởi tạo Facade.
     *
     * Khởi tạo các đối tượng BUS thành phần cần thiết.
     */
    BookingFacade();

    /**
     * @brief Xử lý trọn gói quy trình đặt vé.
     *
     * Đây là API chính mà giao diện (UI) sẽ gọi. Nó che giấu toàn bộ logic phức tạp bên dưới.
     * Quy trình thực hiện bên trong:
     * 1. Kiểm tra xem ghế (seatId) trong suất chiếu (showtimeId) có trống không?
     * 2. Nếu trống -> Lấy thông tin phim, giá tiền từ showtimeId.
     * 3. Gọi SeatBUS để đổi trạng thái ghế thành "Đã đặt".
     * 4. Gọi TicketBUS để tạo và lưu vé xuống file.
     *
     * @param userId ID hoặc tên người dùng đang đặt vé.
     * @param showtimeId Mã suất chiếu (để truy ra phim, phòng, giờ chiếu).
     * @param seatId Mã ghế người dùng chọn (VD: "A5").
     * * @return true Nếu toàn bộ quy trình thành công.
     * @return false Nếu có bất kỳ lỗi nào (ghế đã có người đặt, lỗi file...).
     */
    bool processBooking(string userId, string showtimeId, vector<string> seatList);
    bool cancelTicket(string ticketId, string& outMessage);
};

#endif // BOOKING_FACADE_H