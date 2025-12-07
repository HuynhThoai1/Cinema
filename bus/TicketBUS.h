/**
 * @file TicketBUS.h
 * @brief Định nghĩa lớp xử lý nghiệp vụ cho Vé (Ticket).
 *
 * Lớp này chịu trách nhiệm tạo đối tượng vé thông qua Factory và
 * yêu cầu DAL lưu trữ vé xuống file/cơ sở dữ liệu.
 * @date 2023-10-27
 */

#ifndef TICKETBUS_H
#define TICKETBUS_H

#include "../dal/TicketDAL.h"
#include "../dto/TicketFactory.h"
#include <string>

using std::string;

/**
 * @class TicketBUS
 * @brief Lớp Business Logic Layer (BUS) quản lý việc phát hành vé.
 *
 * Lớp này không thực hiện tính toán giá vé phức tạp. Nó nhận dữ liệu
 * kết quả từ UI/Controller (đã tính toán xong), đóng gói thành đối tượng Ticket
 * và lưu trữ.
 */
class TicketBUS {
private:
    TicketDAL ticketDal; ///< Đối tượng DAL để ghi dữ liệu vé xuống file.

public:
    /**
     * @brief Tạo đối tượng Vé mới và lưu vào cơ sở dữ liệu.
     *
     * Hàm này sử dụng TicketFactory để khởi tạo đối tượng vé phù hợp,
     * sau đó gọi TicketDAL để ghi thông tin vé.
     *
     * @note Dữ liệu đầu vào (như giá vé, tên phim) được coi là đã được xử lý và hợp lệ.
     * Hàm này không tính toán lại giá tiền.
     *
     * @param customerName Tên khách hàng đặt vé.
     * @param movieTitle Tên phim (dạng chuỗi hiển thị, không phải ID).
     * @param roomId Mã phòng chiếu hoặc tên phòng.
     * @param seatId Mã ghế (VD: "A1").
     * @param price Giá vé cuối cùng (dạng chuỗi để in/lưu, VD: "100000").
     * @param time Giờ chiếu (VD: "19:00").
     * @param date Ngày chiếu (VD: "27/10/2023").
     * @return true Nếu tạo và lưu vé thành công.
     * @return false Nếu có lỗi trong quá trình ghi file.
     */
    bool createAndSaveTicket(string customerName, string movieTitle, string roomId, 
                             string seatId, string price, string time, string date);
};

#endif // TICKETBUS_H