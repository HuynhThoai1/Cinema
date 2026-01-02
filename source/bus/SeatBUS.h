/**
 * @file SeatBUS.h
 * @brief Định nghĩa lớp Business Logic (BUS) để quản lý ghế ngồi trong rạp chiếu phim.
 * @details File này chứa các cấu trúc dữ liệu và phương thức để xử lý logic nghiệp vụ
 * liên quan đến ghế, bao gồm lấy danh sách, kiểm tra trạng thái, và đặt vé.
 */

#ifndef SEAT_BUS_H
#define SEAT_BUS_H

#include "../dal/SeatDAL.h"
#include <vector>
#include <string>
#include <algorithm>
#include "../utils/FilePath.h"

using std::string;
using std::vector;

/**
 * @struct SeatDisplay
 * @brief Cấu trúc dữ liệu dùng để hiển thị thông tin ghế lên giao diện (UI).
 */
struct SeatDisplay {
    string id;      ///< Mã định danh duy nhất của ghế (VD: "A01", "B05").
    string row;     ///< Ký tự hàng của ghế (VD: "A", "B").
    int number;     ///< Số thứ tự của ghế trong hàng.
    bool isBooked;  ///< Trạng thái ghế: true nếu đã đặt/bán, false nếu còn trống.
};

/**
 * @class SeatBUS
 * @brief Lớp xử lý nghiệp vụ liên quan đến Ghế (Seat).
 * @details Lớp này đóng vai trò trung gian giữa giao diện (UI) và dữ liệu (DAL),
 * chịu trách nhiệm validate dữ liệu và thực hiện các logic đặt chỗ.
 */
class SeatBUS {
private:
    SeatDAL seatDal;                            ///< Đối tượng thao tác với dữ liệu ghế (DAL).
    const string FILE_NAME = DATA_PATH("Seats.txt"); ///< Đường dẫn đến file dữ liệu gốc của ghế.
    const vector<string> ALL_ROWS = {"A", "B", "C", "D", "E"}; ///< Danh sách các hàng ghế cố định.
    const int SEATS_PER_ROW = 10;               ///< Số lượng ghế tối đa trên mỗi hàng.

public:
    SeatBUS();
    
    /**
     * @brief Lấy danh sách toàn bộ ghế của một suất chiếu cụ thể.
     * @details Hàm này sẽ tổng hợp danh sách ghế gốc và trạng thái đặt chỗ hiện tại
     * của suất chiếu để trả về danh sách hiển thị.
     * @param showtimeId Mã suất chiếu cần lấy dữ liệu.
     * @param roomId Mã phòng chiếu (để xác định cấu trúc ghế của phòng).
     * @return vector<SeatDisplay> Danh sách các ghế kèm trạng thái (đã đặt hay chưa).
     */
    vector<SeatDisplay> getSeatsByShowtime(string showtimeId, string roomId);

    /**
     * @brief Kiểm tra xem một ghế có khả dụng (trống) hay không.
     * @param showtimeId Mã suất chiếu.
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế cần kiểm tra.
     * @return true Nếu ghế còn trống.
     * @return false Nếu ghế đã bị đặt hoặc không tồn tại.
     */
    bool checkAvailable(string showtimeId, string roomId, string seatId);

    /**
     * @brief Thực hiện đặt một ghế.
     * @details Cập nhật trạng thái ghế thành "đã đặt" trong cơ sở dữ liệu.
     * @param showtimeId Mã suất chiếu.
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế muốn đặt.
     * @return true Nếu đặt thành công.
     * @return false Nếu thất bại (ghế đã có người đặt hoặc lỗi hệ thống).
     */
    bool bookSeat(string showtimeId, string roomId, string seatId);

    /**
     * @brief Hủy đặt ghế hoặc mở khóa ghế.
     * @details Chuyển trạng thái ghế từ "đã đặt" về "trống".
     * @param showtimeId Mã suất chiếu.
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế cần mở khóa.
     * @return true Nếu mở khóa thành công.
     * @return false Nếu thất bại.
     */
    bool unlockSeat(string showtimeId, string roomId, string seatId);

    /**
     * @brief Lấy giá tiền của một ghế cụ thể.
     * @details Giá vé có thể phụ thuộc vào loại ghế (VIP/Thường) hoặc vị trí.
     * @param showtimeId Mã suất chiếu (để tính giá theo khung giờ nếu cần).
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế cần lấy giá.
     * @return long long Giá vé (đơn vị: VNĐ).
     */
    long long getSeatPrice(string showtimeId, string roomId, string seatId);

private:
    /**
     * @brief Hàm hỗ trợ tách mã ghế thành Hàng và Số.
     * @details Ví dụ: "A10" -> rowOut = "A", numOut = "10".
     * @param fullSeatId [in] Mã ghế đầy đủ.
     * @param rowOut [out] Biến tham chiếu lưu ký tự hàng.
     * @param numOut [out] Biến tham chiếu lưu số ghế.
     */
    void parseSeatId(string fullSeatId, string& rowOut, string& numOut);
};

#endif // SEAT_BUS_H