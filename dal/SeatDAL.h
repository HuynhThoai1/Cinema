
/**
 * @file SeatDAL.h
 * @brief Tệp tiêu đề định nghĩa cấu trúc dữ liệu Ghế và lớp xử lý file Ghế.
 * @details Chứa DTO (Seat) và DAL (SeatData) để quản lý trạng thái đặt chỗ trong rạp chiếu phim.
 */

#ifndef _SEATDAL_H_
#define _SEATDAL_H_

#include <string>
#include <vector>

using std::vector, std::string;

/**
 * @class Seat
 * @brief Đối tượng chuyển giao dữ liệu (DTO) đại diện cho một DÃY GHẾ trong phòng chiếu.
 * @details Mặc dù tên là Seat, nhưng cấu trúc này lưu trữ trạng thái của cả một hàng ghế (Row),
 * bao gồm danh sách các số ghế đã được đặt trong hàng đó.
 */
class Seat {
public:
    /** * @brief Mã phòng chiếu (Ví dụ: "R01", "R02"). 
     */
    string _roomID;    

    /** * @brief Mã dãy ghế / Hàng ghế (Ví dụ: "A", "B", "C"). 
     */
    string _rowID;

    /** * @brief Danh sách các số ghế đã được đặt trong dãy này.
     * @note Ví dụ: {"1", "3", "5"} nghĩa là ghế số 1, 3, 5 trong dãy đã có người ngồi.
     */
    vector<string> _seatBooked;
};

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
    static vector<Seat> loadSeats(const string& fileName);

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
    static bool saveSeats(const string& room, const string& rowID, const vector<string>& seatBooked, const string& fileName);
};

#endif
