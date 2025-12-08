#ifndef _TICKET_DAL_H_
#define _TICKET_DAL_H_

#include <string>
#include <vector>
#include "../dto/Ticket.h"

using std::vector, std::string;

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