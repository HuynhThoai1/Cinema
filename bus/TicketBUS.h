/**
 * @file TicketBUS.h
 * @brief Định nghĩa lớp Business Logic (BUS) để quản lý vé xem phim.
 * @details File này chịu trách nhiệm xử lý logic tạo vé, lưu trữ vé thông qua DAL, 
 * và phối hợp với SeatBUS để cập nhật trạng thái ghế sau khi đặt vé thành công.
 */

#ifndef TICKETBUS_H
#define TICKETBUS_H

#include "../dal/TicketDAL.h"
#include "../dto/TicketFactory.h"
#include "../dal/DALUtils.h"
#include "SeatBUS.h"
// #include "BUSUtils.h" // Tạm ẩn để tránh lỗi nếu thiếu file này
#include <string>
#include <vector>
#include <ctime>

using std::string;
using std::vector;
using std::time_t;
/**
 * @class TicketBUS
 * @brief Lớp xử lý nghiệp vụ liên quan đến Vé (Ticket).
 * @details Lớp này sử dụng TicketFactory để khởi tạo đối tượng vé và TicketDAL để lưu trữ.
 * Ngoài ra, nó còn chứa SeatBUS để đảm bảo tính toàn vẹn dữ liệu (đặt vé thì ghế phải chuyển sang trạng thái bận).
 */
class TicketBUS {
private:
    TicketDAL ticketDal; ///< Đối tượng thao tác với dữ liệu vé (Lớp Data Access).
    SeatBUS seatBus;     ///< Đối tượng BUS ghế, dùng để cập nhật trạng thái ghế khi mua vé.

public:
    /**
     * @brief Tạo đối tượng vé mới và lưu vào cơ sở dữ liệu.
     * @details Hàm này thực hiện chuỗi hành động:
     * 1. Sử dụng TicketFactory để tạo đối tượng Ticket.
     * 2. Gọi TicketDAL để lưu vé vào file/DB.
     * 3. Gọi SeatBUS để cập nhật trạng thái ghế thành "đã đặt" (Booked).
     * * @param customerName Tên khách hàng đặt vé.
     * @param showtimeId Mã suất chiếu (để liên kết vé với suất chiếu cụ thể).
     * @param movieTitle Tên phim (lưu trữ để hiển thị nhanh).
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế (VD: "A05").
     * @param price Giá vé (dưới dạng chuỗi).
     * @param time Giờ chiếu.
     * @param date Ngày chiếu.
     * @return true Nếu tạo vé và lưu thành công.
     * @return false Nếu có lỗi (lỗi ghi file hoặc ghế đã bị người khác đặt trước đó).
     */
    string createAndSaveTicket(string customerName, string showtimeId, string movieTitle, string roomId, 
                             string seatId, string price, string time, string date);
    
    /**
     * @brief Tìm kiếm và lấy thông tin vé theo ID.
     * @param ticketId Mã định danh của vé cần tìm.
     * @return Ticket* Con trỏ đến đối tượng Ticket tìm thấy (hoặc nullptr nếu không tìm thấy).
     * @note Người gọi hàm có trách nhiệm quản lý bộ nhớ của con trỏ trả về (nếu cần).
     */
    Ticket* getTicketById(string ticketId);

    /**
     * @brief Hủy vé đã đặt.
     * @details Hàm này sẽ xóa vé khỏi dữ liệu và yêu cầu SeatBUS mở khóa (unlock) ghế tương ứng.
     * @param ticketID Mã định danh của vé cần hủy.
     * @return true Nếu hủy thành công.
     * @return false Nếu không tìm thấy vé hoặc lỗi hệ thống.
     */
    bool cancelTicket(string ticketID);
};

#endif // TICKETBUS_H