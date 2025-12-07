/**
 * @file TicketFactory.h
 * @brief Lớp Factory để khởi tạo đối tượng Vé (Ticket).
 *
 * Áp dụng Factory Pattern: Giúp tách biệt logic khởi tạo vé (như sinh ID tự động)
 * khỏi logic nghiệp vụ chính, giúp code gọn gàng và dễ bảo trì hơn.
 * @date 2023-10-27
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
 * @brief Lớp tiện ích (Utility Class) chứa phương thức tĩnh để tạo vé.
 */
class TicketFactory {
public:
    /**
     * @brief Phương thức tĩnh (static) để tạo một đối tượng Ticket mới.
     *
     * Hàm này đóng gói quy trình tạo vé:
     * 1. Tự động sinh ID vé duy nhất.
     * 2. Gọi constructor của Ticket với đầy đủ thông tin.
     *
     * @param movie Tên phim.
     * @param roomID Mã phòng chiếu.
     * @param seatID Mã ghế (VD: "A1").
     * @param customerName Tên khách hàng.
     * @param price Giá vé (dạng chuỗi).
     * @param showTime Giờ chiếu.
     * @param date Ngày chiếu.
     *
     * @return Ticket* Con trỏ trỏ đến đối tượng Ticket vừa được tạo.
     * @warning Người gọi hàm này có trách nhiệm gọi `delete` cho con trỏ trả về để tránh Memory Leak.
     */
    static Ticket* createTicket(string movie, string roomID, string seatID,
                               string customerName, string price, 
                               string showTime, string date) {
        
        // 1. Tự động sinh ID duy nhất cho vé
        string newTicketID = generateUniqueID();

        // 2. Trả về đối tượng Ticket đã được khởi tạo đầy đủ
        return new Ticket(newTicketID, movie, roomID, seatID, customerName, price, showTime, date);
    }
    
private:
    /**
     * @brief Hàm hỗ trợ sinh ID ngẫu nhiên cho vé.
     *
     * Quy luật: "TKT" + 4 chữ số ngẫu nhiên (VD: TKT1234).
     *
     * @note Cần gọi `srand(time(0))` ở hàm `main()` một lần duy nhất để đảm bảo tính ngẫu nhiên.
     * @return string ID vé duy nhất.
     */
    static string generateUniqueID() {
        // Sinh số ngẫu nhiên từ 1000 đến 9999
        int randomNum = 1000 + (rand() % 9000); 
        return "TKT" + to_string(randomNum);
    }
};

#endif // TICKETFACTORY_H