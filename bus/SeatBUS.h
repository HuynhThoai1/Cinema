/**
 * @file SeatBUS.h
 * @brief Định nghĩa lớp xử lý nghiệp vụ cho Ghế (Seat).
 *
 * File này chứa các định nghĩa để quản lý trạng thái ghế, đặt ghế,
 * và chuyển đổi dữ liệu thô từ DAL sang dạng cấu trúc phẳng để UI dễ hiển thị.
 * @date 2023-10-27
 */

#ifndef SEAT_BUS_H
#define SEAT_BUS_H

#include "../dal/SeatDAL.h"
#include <vector>
#include <string>
#include <algorithm> // Để dùng std::find, std::remove

using namespace std;

/**
 * @struct SeatDisplay
 * @brief Cấu trúc dữ liệu đại diện cho một ghế đơn lẻ (DTO - Data Transfer Object).
 *
 * Cấu trúc này được dùng để tách dữ liệu từ DAL (lưu theo dòng) thành từng ghế riêng biệt,
 * giúp giao diện (UI) dễ dàng vẽ sơ đồ phòng chiếu.
 */
struct SeatDisplay {
    string id;      ///< Mã ghế đầy đủ (VD: "A1").
    string row;     ///< Hàng ghế (VD: "A").
    int number;     ///< Số thứ tự ghế trong hàng (VD: 1).
    bool isBooked;  ///< Trạng thái ghế: true = đã đặt, false = còn trống.
};

/**
 * @class SeatBUS
 * @brief Lớp Business Logic Layer (BUS) quản lý nghiệp vụ về ghế.
 *
 * Chịu trách nhiệm tương tác với SeatDAL, kiểm tra tính hợp lệ của việc đặt ghế,
 * và cung cấp danh sách ghế đã được định dạng cho tầng Presentation (UI).
 */
class SeatBUS {
private:
    SeatDAL seatDal; ///< Đối tượng truy cập dữ liệu ghế.
    const string FILE_NAME = "../data/Seats.txt"; ///< Đường dẫn file dữ liệu (Cấu hình cứng).

public:
    /**
     * @brief Lấy danh sách toàn bộ ghế của một phòng chiếu cụ thể.
     *
     * Hàm này thực hiện việc "làm phẳng" (flatten) dữ liệu:
     * Đọc các dòng ghế từ DAL, sau đó tách từng dòng thành các ghế đơn lẻ (SeatDisplay).
     *
     * @param roomId Mã phòng chiếu (VD: "R01").
     * @return vector<SeatDisplay> Danh sách các ghế để vẽ lên màn hình.
     */
    vector<SeatDisplay> getSeatsByRoom(string roomId);

    /**
     * @brief Kiểm tra xem một ghế cụ thể có trống hay không.
     *
     * @param roomId Mã phòng chiếu chứa ghế.
     * @param seatId Mã ghế cần kiểm tra (VD: "A1").
     * @return true Nếu ghế còn trống.
     * @return false Nếu ghế đã được đặt hoặc không tồn tại.
     */
    bool checkAvailable(string roomId, string seatId);

    /**
     * @brief Thực hiện đặt một ghế.
     *
     * Cập nhật trạng thái của ghế thành "đã đặt" trong cơ sở dữ liệu/file.
     *
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế muốn đặt.
     * @return true Nếu đặt thành công.
     * @return false Nếu thất bại (ghế đã có người đặt hoặc lỗi ghi file).
     */
    bool bookSeat(string roomId, string seatId);

    /**
     * @brief Hủy đặt ghế (Mở khóa ghế).
     *
     * Chuyển trạng thái ghế từ "đã đặt" sang "trống". Dùng cho trường hợp hủy vé
     * hoặc rollback giao dịch.
     *
     * @param roomId Mã phòng chiếu.
     * @param seatId Mã ghế cần mở khóa.
     * @return true Nếu mở khóa thành công.
     * @return false Nếu thất bại.
     */
    bool unlockSeat(string roomId, string seatId);

private:
    /**
     * @brief Hàm tiện ích: Phân tích mã ghế đầy đủ thành Hàng và Số.
     *
     * Ví dụ: Input "A12" -> Row "A", Number "12".
     *
     * @param[in] fullSeatId Mã ghế đầu vào.
     * @param[out] rowOut Biến tham chiếu lưu kết quả Hàng.
     * @param[out] numOut Biến tham chiếu lưu kết quả Số (dạng chuỗi).
     */
    void parseSeatId(string fullSeatId, string& rowOut, string& numOut);
};

#endif // SEAT_BUS_H