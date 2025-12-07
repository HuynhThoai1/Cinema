/**
 * @file Ticket.h
 * @brief Định nghĩa lớp Model cho Vé (Ticket).
 *
 * Lớp này đại diện cho một chiếc vé đã được bán/đặt thành công,
 * chứa đầy đủ thông tin để in ra cho khách hàng hoặc lưu vào lịch sử.
 * @date 2023-10-27
 */

#ifndef TICKET_H
#define TICKET_H

#include <string>

using std::string;

/**
 * @class Ticket
 * @brief Lớp đại diện cho đối tượng Vé xem phim.
 *
 * Chứa các thông tin chi tiết về giao dịch đặt vé như: phim, phòng, ghế, giá tiền, thời gian...
 */
class Ticket {
private:
    string _ticketID;       ///< Mã định danh duy nhất của vé (VD: TKT1234).
    string _movie;          ///< Tên phim.
    string _roomID;         ///< Mã phòng chiếu.
    string _seatID;         ///< Vị trí ghế (VD: A5).
    string _customerName;   ///< Tên khách hàng đặt vé.
    string _price;          ///< Giá vé (Lưu dạng chuỗi để giữ nguyên định dạng hiển thị).
    string _showTime;       ///< Giờ chiếu (VD: 19:30).
    string _date;           ///< Ngày chiếu (VD: 20/11/2023).

public:
    /**
     * @brief Constructor khởi tạo đầy đủ thông tin cho vé.
     *
     * @param ticketID Mã vé (thường được sinh tự động từ Factory).
     * @param movie Tên phim.
     * @param roomID Mã phòng.
     * @param seatID Mã ghế.
     * @param customerName Tên khách hàng.
     * @param price Giá vé.
     * @param showTime Giờ chiếu.
     * @param date Ngày chiếu.
     */
    Ticket(string ticketID, string movie, string roomID, string seatID,
           string customerName, string price, string showTime, string date) {
        this->_ticketID = ticketID;
        this->_movie = movie;
        this->_roomID = roomID;
        this->_seatID = seatID;
        this->_customerName = customerName;
        this->_price = price;
        this->_showTime = showTime;
        this->_date = date;
    }

    // --- Getters (Truy xuất thông tin) ---

    /**
     * @brief Lấy mã vé.
     * @return string ID vé.
     */
    string getTicketID() const { return _ticketID; }

    /**
     * @brief Lấy tên phim.
     * @return string Tên phim.
     */
    string getMovie() const { return _movie; }

    /**
     * @brief Lấy mã phòng chiếu.
     * @return string Mã phòng.
     */
    string getRoomID() const { return _roomID; }

    /**
     * @brief Lấy mã ghế.
     * @return string Mã ghế.
     */
    string getSeatID() const { return _seatID; }

    /**
     * @brief Lấy tên khách hàng.
     * @return string Tên khách hàng.
     */
    string getCustomerName() const { return _customerName; }

    /**
     * @brief Lấy giá vé.
     * @return string Giá vé.
     */
    string getPrice() const { return _price; }

    /**
     * @brief Lấy giờ chiếu.
     * @return string Giờ chiếu.
     */
    string getShowTime() const { return _showTime; }

    /**
     * @brief Lấy ngày chiếu.
     * @return string Ngày chiếu.
     */
    string getDate() const { return _date; }
};

#endif // TICKET_H