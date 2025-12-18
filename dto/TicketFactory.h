/**
 * @file TicketFactory.h
 * @brief Áp dụng Factory Pattern để khởi tạo đối tượng Vé (Ticket).
 * @details Lớp này đóng gói logic tạo vé và tự động sinh mã định danh duy nhất (ID) cho mỗi vé,
 * giúp tách biệt việc khởi tạo đối tượng khỏi các lớp xử lý nghiệp vụ chính.
 */

#ifndef TICKETFACTORY_H
#define TICKETFACTORY_H

#include "Ticket.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using std::string;
using std::to_string;

/**
 * @class TicketFactory
 * @brief Lớp nhà máy (Factory) chuyên trách việc tạo ra các instance của Ticket.
 */
class TicketFactory {
public:
    /**
     * @brief Tạo một đối tượng Ticket mới với ID được sinh tự động.
     * @details Phương thức tĩnh này sẽ gọi hàm sinh ID ngẫu nhiên, sau đó khởi tạo
     * đối tượng Ticket với đầy đủ thông tin được cung cấp.
     * * @param showtimeId Mã suất chiếu (liên kết vé với suất chiếu cụ thể).
     * @param movie Tên phim.
     * @param roomID Mã phòng chiếu.
     * @param seatID Mã ghế (VD: "A5").
     * @param customerName Tên khách hàng.
     * @param price Giá vé (dưới dạng chuỗi).
     * @param showTime Giờ chiếu.
     * @param date Ngày chiếu.
     * @return Ticket* Con trỏ đến đối tượng Ticket mới được tạo.
     */
    static Ticket* createTicket(string showtimeId, string movie, string roomID, string seatID,
                               string customerName, string price, 
                               string showTime, string date);
    
private:
    /**
     * @brief Sinh mã vé ngẫu nhiên (Helper function).
     * @details Tạo mã theo định dạng "TKT" + 4 chữ số ngẫu nhiên (VD: "TKT1234").
     * * @note Cần gọi hàm `srand(time(0))` một lần duy nhất trong hàm `main()` 
     * để đảm bảo số sinh ra là ngẫu nhiên thực sự mỗi khi chạy chương trình.
     * * @return string Mã vé duy nhất.
     */
    static string generateUniqueID() {
        // [QUAN TRỌNG] Biến static sẽ giữ giá trị của nó qua các lần gọi hàm
        static int counter = 0; 
        
        // Lấy thời gian hiện tại (tính bằng giây tính từ năm 1970)
        time_t now = time(nullptr);
        
        // Tăng biến đếm
        counter++; 
        
        // Reset counter nếu quá lớn (tùy chọn, để số ngắn gọn)
        if (counter > 999) counter = 0;

        // Cấu trúc ID: TKT_[Giây]_[Số thứ tự]
        // VD: TKT1702912345001, TKT1702912345002
        string id = "TKT" + to_string(now) + to_string(counter);
        
        return id;
    }
};

#endif // TICKETFACTORY_H