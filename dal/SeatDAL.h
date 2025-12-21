#ifndef _SEATDAL_H_
#define _SEATDAL_H_

#include <string>
#include <vector>
#include "../dto/Seat.h"

using std::vector, std::string;

/**
 * @class SeatData
 * @brief Lớp Data Access Layer (DAL) chịu trách nhiệm Đọc/Ghi dữ liệu ghế từ file.
 * @details Cung cấp các phương thức static để thao tác với file dữ liệu (thường là Seats.txt).
 */
class SeatDAL {
public:
    /**
     * @brief Đọc toàn bộ dữ liệu ghế từ file.
     * * Hàm này mở file, đọc từng dòng và phân tích cú pháp (parsing) để tạo ra danh sách các dãy ghế.
     * * @param fileName Đường dẫn đến file dữ liệu ghế (ví dụ: "Seats.txt").
     * @return vector<Seat> Danh sách các đối tượng Seat (mỗi đối tượng là một dãy ghế).
     */
    static vector<Seat> loadSeats(string fileName);

    /**
     * @brief Cập nhật và lưu trạng thái ghế xuống file.
     * * Hàm này thực hiện quy trình:
     * 1. Đọc dữ liệu cũ lên.
     * 2. Tìm dãy ghế tương ứng với `room` và `rowID`.
     * 3. Cập nhật danh sách `seatBooked` mới cho dãy đó.
     * 4. Ghi đè toàn bộ dữ liệu xuống file.
     * * @param room Mã phòng cần cập nhật (VD: "R01").
     * @param rowID Mã dãy ghế cần cập nhật (VD: "A").
     * @param seatBooked Danh sách mới các ghế đã đặt (VD: {"1", "2"}).
     * @param fileName Đường dẫn đến file dữ liệu.
     * @return true Nếu cập nhật và ghi file thành công.
     * @return false Nếu có lỗi xảy ra (không mở được file, dữ liệu sai...).
     */
    static bool saveSeats(string showtimeId, string room, string rowID, vector<string> seatBooked, string fileName);
};

#endif
