/**
 * @file TicketDAL.h
 * @brief Tệp tiêu đề định nghĩa cấu trúc dữ liệu Vé và lớp xử lý file Vé.
 * @details Chứa DTO (Ticket) để lưu trữ thông tin vé và DAL (TicketDAL) để tương tác với cơ sở dữ liệu file text.
 */

#ifndef _TICKET_DAL_H_
#define _TICKET_DAL_H_

#include <string>
#include <vector>

using std::vector, std::string;

/**
 * @class Ticket
 * @brief Đối tượng chuyển giao dữ liệu (DTO) đại diện cho một vé xem phim.
 * @details Chứa đầy đủ thông tin chi tiết về một giao dịch đặt vé.
 */
class Ticket {
public:
    /** @brief Mã định danh duy nhất của vé (Ví dụ: "TK001"). */
    string _ticketID;

    /** @brief Tên phim (Ví dụ: "Avatar 2"). */
    string _movie;

    /** @brief Mã phòng chiếu (Ví dụ: "R01"). */
    string _roomID;

    /** @brief Vị trí ghế ngồi (Ví dụ: "A-5" hoặc "E-10"). */
    string _seatID;

    /** @brief Tên khách hàng đặt vé. */
    string _customerName;

    /** @brief Giá vé (Lưu dưới dạng chuỗi có định dạng, VD: "75.000"). */
    string _price;

    /** @brief Giờ chiếu (Ví dụ: "19:00"). */
    string _showTime;

    /** @brief Ngày chiếu (Ví dụ: "19/12/2025"). */
    string _date;
};

/**
 * @class TicketDAL
 * @brief Lớp Data Access Layer (DAL) chịu trách nhiệm Đọc/Ghi dữ liệu vé từ file.
 * @details Các phương thức trong lớp này đều là static để dễ dàng gọi mà không cần khởi tạo đối tượng.
 */
class TicketDAL {
public:
    /**
     * @brief Đọc danh sách tất cả các vé từ file dữ liệu.
     * * Hàm sẽ mở file, đọc từng dòng, tách dữ liệu theo định dạng chuẩn và ánh xạ vào đối tượng Ticket.
     * * @param fileName Đường dẫn đến file dữ liệu vé (thường là "Tickets.txt").
     * @return vector<Ticket> Danh sách các vé đã bán. Trả về vector rỗng nếu file lỗi hoặc chưa có dữ liệu.
     */
    static vector<Ticket> loadTickets(string fileName);

    /**
     * @brief Ghi (Thêm mới) một vé vào file dữ liệu.
     * * Quy trình thực hiện:
     * 1. Đọc danh sách vé hiện có lên bộ nhớ.
     * 2. Thêm vé mới vào danh sách.
     * 3. Ghi đè lại toàn bộ danh sách xuống file.
     * * @param fileName Đường dẫn đến file dữ liệu.
     * @param ticket Đối tượng Ticket chứa thông tin vé cần lưu.
     * @return true Nếu ghi file thành công.
     * @return false Nếu không mở được file hoặc đường dẫn sai.
     */
    static bool saveTickets(string fileName, Ticket ticket);
};

#endif