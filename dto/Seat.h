/**
 * @file Seat.h
 * @brief Định nghĩa lớp thực thể (DTO) lưu trữ thông tin trạng thái ghế.
 * @details Lớp này đại diện cho cấu hình của một HÀNG GHẾ trong một suất chiếu cụ thể,
 * bao gồm thông tin về giá vé của hàng đó và danh sách các ghế đã được đặt.
 */

#ifndef SEAT_H
#define SEAT_H

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

/**
 * @class Seat
 * @brief Đại diện cho trạng thái của một hàng ghế trong một suất chiếu.
 */
class Seat {
private:
    string _showtimeId;     ///< [MỚI] Mã suất chiếu (VD: "ST001"). Đây là khóa chính để phân biệt các suất.
    string _room;           ///< Mã phòng chiếu (VD: "ROOM01").
    string _rowId;          ///< Mã hàng ghế (VD: "A", "B").
    long long _price;       ///< Giá vé áp dụng cho hàng ghế này.
    vector<string> _seatBooked; ///< Danh sách các mã ghế cụ thể đã bị đặt trong hàng này (VD: {"A1", "A2"}).

public:
    /**
     * @brief Constructor mặc định.
     */
    Seat();

    /**
     * @brief Constructor đầy đủ tham số.
     * @details Khởi tạo đối tượng Seat với thông tin suất chiếu, phòng, hàng và giá.
     * @param showtimeId Mã suất chiếu (Quan trọng: Dùng để map với file Showtime).
     * @param room Mã phòng.
     * @param rowId Mã hàng.
     * @param price Giá vé (mặc định là 0 nếu không truyền).
     */
    Seat(string showtimeId, string room, string rowId, long long price = 0);

    // --- Getters ---
    
    /**
     * @brief Lấy mã suất chiếu.
     * @return string ID suất chiếu.
     */
    string getShowtimeId() const;

    /**
     * @brief Lấy mã phòng.
     * @return string ID phòng.
     */
    string getRoom() const;

    /**
     * @brief Lấy mã hàng ghế.
     * @return string Ký tự hàng (VD: "A").
     */
    string getRowId() const;

    /**
     * @brief Lấy giá vé của hàng ghế này.
     * @return long long Giá vé.
     */
    long long getPrice() const;

    /**
     * @brief Lấy danh sách các ghế đã được đặt.
     * @return vector<string> Vector chứa ID các ghế đã book (copy).
     */
    vector<string> getSeatBooked() const;

    // --- Setters ---

    /**
     * @brief Cập nhật lại toàn bộ danh sách ghế đã đặt.
     * @param bookedList Vector chứa danh sách mã ghế mới.
     */
    void setSeatBooked(const vector<string>& bookedList);
    
    /**
     * @brief Thiết lập giá vé mới cho hàng ghế.
     * @param newPrice Giá vé mới.
     */
    void setPrice(long long newPrice);

    // --- Business Logic ---

    /**
     * @brief Đánh dấu một ghế cụ thể là "đã đặt".
     * @details Thêm mã ghế vào danh sách `_seatBooked`.
     * @param seatId Mã ghế cần đặt (VD: "A5").
     */
    void addBookedSeat(const string& seatId);

    /**
     * @brief Kiểm tra xem một ghế có còn trống hay không.
     * @details Hàm sẽ tìm kiếm xem seatId có tồn tại trong danh sách `_seatBooked` không.
     * @param seatId Mã ghế cần kiểm tra.
     * @return true Nếu ghế CHƯA bị đặt (có thể mua).
     * @return false Nếu ghế ĐÃ bị đặt.
     */
    bool isAvailable(const string& seatId) const;
};

#endif // SEAT_H